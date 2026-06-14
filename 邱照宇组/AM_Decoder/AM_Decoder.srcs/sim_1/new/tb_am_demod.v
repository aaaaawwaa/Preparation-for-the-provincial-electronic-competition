`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// 公司:
// 工程师:
//
// 创建日期: 2026/06/12
// 设计名称: AM解调器测试平台
// 模块名称: tb_am_demod
// 项目名称: AM_Decoder
// 目标器件: XC7Z020CLG484-2 (Zynq-7020)
// 工具版本: Vivado 2018.3
// 描述:
//   测试am_demod模块的AM包络检波解调功能。
//   产生一个AM调制测试信号:
//     - 载波: ~1MHz 正弦波 (100MHz时钟下, 100个采样点/周期)
//     - 调制信号: ~10kHz 正弦波 (10000个采样点/周期)
//     - 调制指数: 0.8 (80% 调制度)
//   然后送入am_demod模块, 观察解调输出波形。
//
// 依赖: am_demod.v
//
// 版本:
// 版本 0.01 - 文件创建
// 附加说明:
//
//////////////////////////////////////////////////////////////////////////////////

module tb_am_demod();

    ////////////////////////////////////////////////////////////////////////////////
    // 参数定义
    ////////////////////////////////////////////////////////////////////////////////
    localparam INPUT_WIDTH  = 12;
    localparam AVG_SHIFT    = 8;
    localparam OUTPUT_WIDTH = 16;
    localparam DC_REMOVAL   = 1'b1;
    localparam DC_SHIFT     = 16;

    // AM信号生成参数
    // 载波: 100MHz / 100 = 1MHz
    localparam integer CARRIER_DIV = 100;
    // 调制: 100MHz / 10000 = 10kHz
    localparam integer MOD_DIV     = 10000;

    ////////////////////////////////////////////////////////////////////////////////
    // 信号声明
    ////////////////////////////////////////////////////////////////////////////////
    reg                     clk;
    reg                     rst_n;
    reg [INPUT_WIDTH-1:0]   am_in;
    wire [OUTPUT_WIDTH-1:0] demod_out;
    wire                    demod_valid;

    // AM信号生成变量
    real carrier_phase;     // 载波相位 (弧度)
    real mod_phase;         // 调制信号相位 (弧度)
    real carrier_val;       // 载波瞬时值
    real mod_val;           // 调制信号瞬时值 (0.1 ~ 0.9)
    real am_val;            // AM调制信号瞬时值
    integer am_int;         // AM信号整数值

    ////////////////////////////////////////////////////////////////////////////////
    // 待测模块实例化
    ////////////////////////////////////////////////////////////////////////////////
    am_demod #(
        .INPUT_WIDTH  (INPUT_WIDTH),
        .AVG_SHIFT    (AVG_SHIFT),
        .OUTPUT_WIDTH (OUTPUT_WIDTH),
        .DC_REMOVAL   (DC_REMOVAL),
        .DC_SHIFT     (DC_SHIFT)
    ) u_am_demod (
        .clk         (clk),
        .rst_n       (rst_n),
        .am_in       (am_in),
        .demod_out   (demod_out),
        .demod_valid (demod_valid)
    );

    ////////////////////////////////////////////////////////////////////////////////
    // 时钟生成 - 100MHz (周期 10ns)
    ////////////////////////////////////////////////////////////////////////////////
    initial clk = 0;
    always #5 clk = ~clk;

    ////////////////////////////////////////////////////////////////////////////////
    // 复位与AM测试信号生成
    ////////////////////////////////////////////////////////////////////////////////
    initial begin
        // 初始化
        rst_n         = 0;
        am_in         = 0;
        carrier_phase = 0.0;
        mod_phase     = 0.0;

        // 保持复位 1us
        #1000;
        rst_n = 1;
        #100;
    end

    // 每个时钟周期产生一个AM调制采样点
    always @(posedge clk) begin
        if (!rst_n) begin
            carrier_phase <= 0.0;
            mod_phase     <= 0.0;
            am_in         <= '0;
        end else begin
            // 更新载波相位 (1MHz)
            carrier_phase = carrier_phase + 2.0 * 3.14159265358979 / CARRIER_DIV;
            if (carrier_phase >= 2.0 * 3.14159265358979)
                carrier_phase = carrier_phase - 2.0 * 3.14159265358979;

            // 更新调制信号相位 (10kHz)
            mod_phase = mod_phase + 2.0 * 3.14159265358979 / MOD_DIV;
            if (mod_phase >= 2.0 * 3.14159265358979)
                mod_phase = mod_phase - 2.0 * 3.14159265358979;

            // 载波: 单位幅度正弦波
            carrier_val = $sin(carrier_phase);

            // 调制信号: 直流偏置 0.5 + 0.4*sin (调制指数 0.8)
            // 范围: 0.1 ~ 0.9 (避免过调制)
            mod_val = 0.5 + 0.4 * $sin(mod_phase);

            // AM调制: 载波 * 调制信号
            am_val = carrier_val * mod_val;

            // 转换为12位有符号整数 (-2048 ~ +2047)
            // 幅度缩放: 最大幅度为 0.9, 映射到 2047*0.9 ≈ 1842
            am_int = $rtoi(am_val * 2047.0);

            // 限幅到12位有符号范围
            if (am_int > 2047)  am_int = 2047;
            if (am_int < -2048) am_int = -2048;

            am_in <= am_int[INPUT_WIDTH-1:0];
        end
    end

    ////////////////////////////////////////////////////////////////////////////////
    // 仿真运行控制
    ////////////////////////////////////////////////////////////////////////////////
    initial begin
        // 等待足够的建立时间:
        //   滑动平均填充: 256 个周期 = 2.56us
        //   直流阻断建立: ~65536 个周期 ≈ 655us
        // 总共运行约 1000us (1ms) 即 100000 个时钟周期
        #1000000;  // 1ms

        $display("仿真完成: 运行了 1ms (100000 个时钟周期)");
        $display("  滑动平均窗口: %0d 个采样点", 1 << AVG_SHIFT);
        $display("  -3dB截止频率: ~%0d kHz", 443000 / (1 << AVG_SHIFT));
        $display("  直流阻断截止频率: ~%0d Hz", 100000000 / (2 * 355 * (1 << DC_SHIFT)));
        $finish;
    end

    ////////////////////////////////////////////////////////////////////////////////
    // 波形输出 (Vivado仿真器波形窗口查看)
    ////////////////////////////////////////////////////////////////////////////////
    initial begin
        $dumpfile("tb_am_demod.vcd");
        $dumpvars(0, tb_am_demod);
    end

endmodule
