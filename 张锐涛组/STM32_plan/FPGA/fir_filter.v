// ============================================================
// FIR滤波器通用模块 (串行MAC实现, 资源优化)
// ============================================================

module fir_filter #(
    parameter TAP_NUM  = 32,                // 滤波器阶数
    parameter COEF_FILE = "coef.mif"        // 系数文件
)(
    input  wire        clk,
    input  wire        rst_n,
    input  wire        sample_clk,           // 采样时钟
    input  wire [15:0] data_in,              // 输入数据 (Q15)
    output reg  [15:0] data_out              // 输出数据 (Q15)
);

reg  [15:0] shift_reg [0:TAP_NUM-1];         // 延迟线
reg  [15:0] coef_rom  [0:TAP_NUM-1];         // 系数ROM
reg  [15:0] coef;                             // 当前系数
reg  [15:0] dly_data;                         // 当前延迟数据
reg  [31:0] mac_acc;                          // MAC累加器
reg  [31:0] mac_temp;
reg  [7:0]  tap_idx;                          // 抽头索引
reg         mac_busy;
reg         calc_done;
integer     i;

// 初始化系数ROM (实际使用时由工具加载)
initial begin
    // 默认32阶LPF系数 (11.5kHz @ 46kHz, 汉明窗)
    // 归一化Q15格式
    if (TAP_NUM == 32) begin
        coef_rom[0]  = 16'h0000; coef_rom[1]  = 16'h0002;
        coef_rom[2]  = 16'h0009; coef_rom[3]  = 16'h0018;
        coef_rom[4]  = 16'h0032; coef_rom[5]  = 16'h005A;
        coef_rom[6]  = 16'h0090; coef_rom[7]  = 16'h00D2;
        coef_rom[8]  = 16'h011A; coef_rom[9]  = 16'h0163;
        coef_rom[10] = 16'h01A5; coef_rom[11] = 16'h01DA;
        coef_rom[12] = 16'h01FB; coef_rom[13] = 16'h0204;
        coef_rom[14] = 16'h01F2; coef_rom[15] = 16'h01C9;
        coef_rom[16] = 16'h018D; coef_rom[17] = 16'h0146;
        coef_rom[18] = 16'h00FE; coef_rom[19] = 16'h00C2;
        coef_rom[20] = 16'h0098; coef_rom[21] = 16'h0083;
        coef_rom[22] = 16'h0082; coef_rom[23] = 16'h0092;
        coef_rom[24] = 16'h00AE; coef_rom[25] = 16'h00CF;
        coef_rom[26] = 16'h00ED; coef_rom[27] = 16'h0102;
        coef_rom[28] = 16'h0109; coef_rom[29] = 16'h0101;
        coef_rom[30] = 16'h00EF; coef_rom[31] = 16'h00DC;
    end
    // 64阶NBPF系数 (中心11.5kHz, BW=80Hz @ 46kHz)
    else if (TAP_NUM == 64) begin
        coef_rom[0]  = 16'h0000; coef_rom[1]  = 16'hFFFC;
        coef_rom[2]  = 16'h0004; coef_rom[3]  = 16'h0002;
        coef_rom[4]  = 16'hFFF9; coef_rom[5]  = 16'h000A;
        coef_rom[6]  = 16'h0000; coef_rom[7]  = 16'hFFFC;
        coef_rom[8]  = 16'h0010; coef_rom[9]  = 16'hFFFC;
        coef_rom[10] = 16'hFFFB; coef_rom[11] = 16'h0018;
        coef_rom[12] = 16'hFFF8; coef_rom[13]  = 16'hFFFD;
        coef_rom[14] = 16'h0023; coef_rom[15]  = 16'hFFF8;
        coef_rom[16] = 16'h0006; coef_rom[17] = 16'h0030;
        coef_rom[18] = 16'h0000; coef_rom[19]  = 16'h0015;
        coef_rom[20] = 16'h0040; coef_rom[21] = 16'h0010;
        coef_rom[22] = 16'h002C; coef_rom[23] = 16'h0051;
        coef_rom[24] = 16'h002D; coef_rom[25] = 16'h004B;
        coef_rom[26] = 16'h0062; coef_rom[27] = 16'h0056;
        coef_rom[28] = 16'h0070; coef_rom[29] = 16'h0070;
        coef_rom[30] = 16'h0086; coef_rom[31] = 16'h007C;
        coef_rom[32] = 16'h0095; coef_rom[33] = 16'h007C;
        coef_rom[34] = 16'h0086; coef_rom[35] = 16'h0070;
        coef_rom[36] = 16'h0070; coef_rom[37] = 16'h0056;
        coef_rom[38] = 16'h0062; coef_rom[39] = 16'h004B;
        coef_rom[40] = 16'h002D; coef_rom[41] = 16'h0051;
        coef_rom[42] = 16'h002C; coef_rom[43] = 16'h0010;
        coef_rom[44] = 16'h0040; coef_rom[45] = 16'h0015;
        coef_rom[46] = 16'h0000; coef_rom[47] = 16'h0030;
        coef_rom[48] = 16'h0006; coef_rom[49] = 16'hFFF8;
        coef_rom[50] = 16'h0023; coef_rom[51] = 16'hFFFD;
        coef_rom[52] = 16'hFFF8; coef_rom[53] = 16'h0018;
        coef_rom[54] = 16'hFFFB; coef_rom[55] = 16'hFFFC;
        coef_rom[56] = 16'h0010; coef_rom[57] = 16'hFFFC;
        coef_rom[58] = 16'h0000; coef_rom[59] = 16'h000A;
        coef_rom[60] = 16'hFFF9; coef_rom[61] = 16'h0002;
        coef_rom[62] = 16'h0004; coef_rom[63] = 16'hFFFC;
    end
end

// 延迟线更新
always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        for (i = 0; i < TAP_NUM; i = i + 1)
            shift_reg[i] <= 16'd0;
    end
    else if (sample_clk) begin
        shift_reg[0] <= data_in;
        for (i = 1; i < TAP_NUM; i = i + 1)
            shift_reg[i] <= shift_reg[i-1];
    end
end

// MAC控制
always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        tap_idx    <= 8'd0;
        mac_acc    <= 32'd0;
        mac_busy   <= 1'b0;
        calc_done  <= 1'b0;
        data_out   <= 16'd0;
    end
    else if (sample_clk) begin
        tap_idx   <= 8'd1;
        mac_acc   <= $signed(shift_reg[0]) * $signed(coef_rom[0]);
        mac_busy  <= 1'b1;
        calc_done <= 1'b0;
    end
    else if (mac_busy && tap_idx < TAP_NUM) begin
        mac_acc  <= mac_acc + $signed(shift_reg[tap_idx]) * $signed(coef_rom[tap_idx]);
        tap_idx  <= tap_idx + 1'd1;
    end
    else if (mac_busy) begin
        mac_busy  <= 1'b0;
        calc_done <= 1'b1;
        // 截取高16位作为Q15输出
        data_out  <= mac_acc[30:15];
    end
end

endmodule
