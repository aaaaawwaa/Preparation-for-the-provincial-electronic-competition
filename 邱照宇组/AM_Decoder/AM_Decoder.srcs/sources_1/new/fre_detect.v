`timescale 1ns / 1ps

//fft模块，wave是输入信号，range是频率能量信号，sample是频率下标，与频率映射是（采样率*sample/8192）采样率由一个s_cnt的那个分频变量决定
//采样率具体看fft_handle模块
module fre_detect(
    wave,
    CLK_H,
    Reset,
    range,
    sample

);
    
    parameter width=16-1;
    
    input [11:0]wave;
    input CLK_H;
    input Reset;
    
    output reg [16:0]range;
    output reg [12:0]sample;
        
    wire fft_out_valid;
    wire [12:0]Sample_CNT;
    wire [31:0]fre_med;
   
    fft_handle fft_task(
        .CLK_H(CLK_H),
        .Reset(Reset),
        .wave_in(wave),
        .fft_out(fre_med),
        .sample_cnt(Sample_CNT)
    );

    wire [31:0]med_I;
    wire [31:0]med_Q;
    
    mult_gen_1 mod_I(
        .CLK(CLK_H),
        .A(fre_med[15:0]),
        .B(fre_med[15:0]),
        .P(med_I)
    );
    
     mult_gen_1 mod_Q(
        .CLK(CLK_H),
        .A(fre_med[31:16]),
        .B(fre_med[31:16]),
        .P(med_Q)
    );
    
    reg sqrt_in_valid;
    
    wire [10:0]fifo_count;
    
    wire full_flag;
    wire empty_flag;
    
    reg wr_en;
    
    wire [15:0]fre_cnt_med;
    wire fre_cnt_valid;
    
    wire [16:0]modulus;
    wire sqrt_out_valid;
    reg [12:0]sample_in;
    wire [12:0]sample_out;
    
    cordic_0 cordic_sqrt_0(
        .aclk(CLK_H),
        
        .s_axis_cartesian_tdata({2'b0,med_I+med_Q}),
        .s_axis_cartesian_tvalid(sqrt_in_valid),
        .s_axis_cartesian_tuser(Sample_CNT),
        
        .m_axis_dout_tdata(modulus),
        .m_axis_dout_tvalid(sqrt_out_valid),
        .m_axis_dout_tuser(sample_out)
    );
    

    
  
    
    reg [12:0]cnt;
    reg [12:0]sample_delay_1;
    reg [12:0]sample_delay_2;
    reg [12:0]sample_delay_3;
    reg [12:0]sample_delay_4;
    reg [12:0]sample_delay_5;
    
    reg [16:0]Max_range;
    reg [12:0]Max_sample;
    
    always@(posedge CLK_H or negedge Reset)begin
        if(!Reset)begin
            range<=0;
            wr_en<=0;
            sqrt_in_valid<=0;
            cnt<=0;
            sample_in<=0;
            sample_delay_1<=0;
            sample<=0;
        end
        
        else begin
        
            sqrt_in_valid<=1;
            
            if(sqrt_out_valid)begin
                sample_delay_1<=sample_out;
                sample_delay_2<=sample_delay_1;
                sample_delay_3<=sample_delay_2;
                sample_delay_4<=sample_delay_3;
                sample_delay_5<=sample_delay_4;
                sample<=sample_delay_5;
                range<=modulus;
            end
            
            if(sample<=12'd4095)begin
                if(sample==12'd0)begin 
                    Max_range<=17'd0;
                    Max_sample<=13'd0;
                end
                else begin
                    if(range>=Max_range)begin
                        Max_range<=range;
                        Max_sample<=sample;
                    end
                end
            end
        end
    end
    
endmodule
