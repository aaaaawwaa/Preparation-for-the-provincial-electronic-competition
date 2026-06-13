// ============================================================
// 方案2: STM32+FPGA 2ASK/AM 接收机 — FPGA顶层模块
// 功能:
//   1. 从外部ADC采集包络检波后的信号
//   2. 双路FIR数字滤波:
//      - LPF: 截止11.5kHz, 恢复模拟信号 → DAC输出
//      - NBPF: 中心11.5kHz, 带宽80Hz, 提取2ASK信号 → 整形输出
//   3. STM32接口: 并行总线(地址+数据), 用于读取滤波结果和状态
// ============================================================

module top (
    input  wire        clk_50m,          // 50MHz 主时钟
    input  wire        rst_n,            // 复位,低有效

    // ADC接口 (假设外部12-bit ADC, 如ADS7866)
    input  wire [11:0] adc_data,         // ADC采样数据
    output wire        adc_clk,          // ADC采样时钟 (46kHz)

    // DAC接口 (双路, 如TLV5618)
    output wire [11:0] dac_lpf_data,     // LPF输出 → 模拟信号
    output wire [11:0] dac_bpf_data,     // BPF输出 → 2ASK(调试用)

    // STM32并行接口
    input  wire        stm_cs_n,         // 片选
    input  wire        stm_rd_n,         // 读使能
    input  wire        stm_wr_n,         // 写使能
    input  wire [2:0]  stm_addr,         // 寄存器地址
    inout  wire [7:0]  stm_data,         // 数据总线(双向)

    // 2ASK解码输出 (经整形后送STM32)
    output wire        ask_data_out,     // 2ASK解码数据
    output wire        ask_clk_out       // 2ASK同步时钟
);

// ============================================================
// 内部信号
// ============================================================
wire        sample_clk;                  // ADC采样时钟(内部)
reg  [11:0] sample_data;                 // 采样数据寄存
wire [15:0] lpf_out;                     // LPF输出 (Q15格式)
wire [15:0] bpf_out;                     // BPF输出 (Q15格式)
reg  [15:0] lpf_out_reg;
reg  [15:0] bpf_out_reg;
reg  [11:0] dac_lpf_data_reg;
reg  [11:0] dac_bpf_data_reg;

// ============================================================
// 采样时钟分频: 50MHz → 46kHz (1086分频)
// ============================================================
reg [10:0] clk_div;
always @(posedge clk_50m or negedge rst_n) begin
    if (!rst_n)
        clk_div <= 11'd0;
    else if (clk_div >= 11'd1085)
        clk_div <= 11'd0;
    else
        clk_div <= clk_div + 1'd1;
end
assign sample_clk = (clk_div == 11'd0);
assign adc_clk    = sample_clk;

// ============================================================
// 采样数据锁存
// ============================================================
always @(posedge clk_50m or negedge rst_n) begin
    if (!rst_n)
        sample_data <= 12'd0;
    else if (sample_clk)
        sample_data <= adc_data;
end

// ============================================================
// 双路FIR滤波器实例化
// ============================================================

// LPF: 32阶, 截止11.5kHz @ 46kHz采样率, 汉明窗
fir_filter #(
    .TAP_NUM(32),
    .COEF_FILE("lpf_coef.mif")
) u_lpf (
    .clk       (clk_50m),
    .rst_n     (rst_n),
    .sample_clk(sample_clk),
    .data_in   ({sample_data, 4'b0}),  // 12-bit → Q15
    .data_out  (lpf_out)
);

// NBPF: 64阶, 中心11.5kHz, BW=80Hz @ 46kHz采样率
fir_filter #(
    .TAP_NUM(64),
    .COEF_FILE("bpf_coef.mif")
) u_bpf (
    .clk       (clk_50m),
    .rst_n     (rst_n),
    .sample_clk(sample_clk),
    .data_in   ({sample_data, 4'b0}),
    .data_out  (bpf_out)
);

// ============================================================
// DAC输出映射 (Q15 → 12-bit)
// ============================================================
always @(posedge clk_50m or negedge rst_n) begin
    if (!rst_n) begin
        lpf_out_reg    <= 16'd0;
        bpf_out_reg    <= 16'd0;
        dac_lpf_data_reg <= 12'd0;
        dac_bpf_data_reg <= 12'd0;
    end
    else if (sample_clk) begin
        lpf_out_reg    <= lpf_out;
        bpf_out_reg    <= bpf_out;
        dac_lpf_data_reg <= lpf_out[15:4];   // Q15截取高12位
        dac_bpf_data_reg <= bpf_out[15:4];
    end
end

assign dac_lpf_data = dac_lpf_data_reg;
assign dac_bpf_data = dac_bpf_data_reg;

// ============================================================
// 2ASK解码: 过零检测 + 整形
// ============================================================
reg [15:0] bpf_abs;
reg [15:0] threshold;
reg        bpf_slice;
reg        ask_data_reg;
reg        ask_clk_reg;

// 自适应阈值 (取BPF输出峰值的一半)
always @(posedge clk_50m or negedge rst_n) begin
    if (!rst_n) begin
        threshold <= 16'd100;
    end
    else if (sample_clk) begin
        bpf_abs <= (bpf_out[15]) ? (~bpf_out + 1'b1) : bpf_out;
        if (bpf_abs > threshold)
            threshold <= (threshold + bpf_abs) >> 1;  // 慢速跟踪峰值
        else
            threshold <= threshold - (threshold >> 10); // 缓慢衰减
    end
end

// 过零比较输出
always @(posedge clk_50m or negedge rst_n) begin
    if (!rst_n) begin
        bpf_slice    <= 1'b0;
        ask_data_reg <= 1'b0;
        ask_clk_reg  <= 1'b0;
    end
    else if (sample_clk) begin
        bpf_slice    <= (bpf_abs > threshold) ? 1'b1 : 1'b0;
        ask_data_reg <= bpf_slice;
        ask_clk_reg  <= sample_clk;
    end
end

assign ask_data_out = ask_data_reg;
assign ask_clk_out  = ask_clk_reg;

// ============================================================
// STM32并行接口寄存器
// ============================================================
// 寄存器映射:
// addr 0: 状态寄存器  [0]=BPF_lock, [1]=data_valid
// addr 1: LPF输出高8位
// addr 2: LPF输出低8位
// addr 3: BPF输出高8位
// addr 4: BPF输出低8位
// addr 5: 2ASK解码数据FIFO (读1字节)
// addr 6: 阈值/控制

reg  [4:0]  sample_count;
wire        data_valid;
reg  [7:0]  status_reg;
reg  [7:0]  stm_data_out;
wire [7:0]  stm_data_in;
reg         stm_data_oe;

assign data_valid = (sample_count >= 5'd20) ? 1'b1 : 1'b0;

always @(posedge clk_50m or negedge rst_n) begin
    if (!rst_n)
        sample_count <= 5'd0;
    else if (sample_clk) begin
        if (sample_count < 5'd31)
            sample_count <= sample_count + 1'd1;
    end
end

// 状态寄存器
always @(posedge clk_50m or negedge rst_n) begin
    if (!rst_n)
        status_reg <= 8'd0;
    else if (sample_clk) begin
        status_reg[0] <= data_valid;
        status_reg[1] <= (bpf_abs > threshold) ? 1'b1 : 1'b0;
        status_reg[7:2] <= 6'd0;
    end
end

// 读数据
always @(*) begin
    stm_data_out = 8'd0;
    case (stm_addr)
        3'd0:   stm_data_out = status_reg;
        3'd1:   stm_data_out = lpf_out_reg[15:8];
        3'd2:   stm_data_out = lpf_out_reg[7:0];
        3'd3:   stm_data_out = bpf_out_reg[15:8];
        3'd4:   stm_data_out = bpf_out_reg[7:0];
        3'd5:   stm_data_out = {ask_data_reg, ask_clk_reg, 6'd0};
        default: stm_data_out = 8'd0;
    endcase
end

// 双向数据总线控制
assign stm_data = (!stm_cs_n && !stm_rd_n) ? stm_data_out : 8'hzz;

endmodule
