`timescale 1ns / 1ps

//采样率请看第124行

module fft_handle(
    wave_in,
    CLK_H,
    Reset,
    fft_out,
    sample_cnt,
    fft_out_valid

    );
    
    input [11:0]wave_in;
    input CLK_H;
    input Reset;

    
    output reg [31:0]fft_out;
    output [12:0]sample_cnt;
    output fft_out_valid;
    
    reg Sample_finish;
    reg Sample_start;
    
    
    wire [12:0]bram_addr;
    wire [11:0]bram_out;
    
    reg bram_ena;
    reg bram_wea;
    
    
    
    blk_mem_gen_0 sample(
    
        .addra({1'b0,bram_addr}),
        .clka(CLK_H),
        
        .dina(wave_in),
        .douta(bram_out),
        
        .ena(bram_ena),
        .wea(bram_wea)
    );

    
wire              fft_s_config_tready;

wire signed [31:0] fft_s_data_tdata;
reg               fft_s_data_tvalid;
wire              fft_s_data_tready;
reg               fft_s_data_tlast;

wire signed [31:0] fft_m_data_tdata;

wire               fft_m_data_tvalid;
reg                fft_m_data_tready;
wire               fft_m_data_tlast;

wire          fft_event_frame_started;
wire          fft_event_tlast_unexpected;
wire          fft_event_tlast_missing;
wire          fft_event_status_channel_halt;
wire          fft_event_data_in_channel_halt;
wire          fft_event_data_out_channel_halt;

reg config_valid;
wire [23:0]  fft_m_data_tuser;

reg data_finish_flag;
    
reg fft_start_flag;

assign fft_s_data_tdata={12'b0,bram_out};

xfft_0 fft(
    .aclk(CLK_H),                                                // 时钟信号（input）
    //.aresetn(Reset),                                           // 复位信号，低有效（input）
    .s_axis_config_tdata(8'd1),                                // ip核设置参数内容，为1时做FFT运算，为0时做IFFT运算（input）
    .s_axis_config_tvalid(config_valid),                               // ip核配置输入有效，可直接设置为1（input）
    .s_axis_config_tready(fft_s_config_tready),                // output wire s_axis_config_tready
    //作为接收时域数据时是从设备
    .s_axis_data_tdata(fft_s_data_tdata),                      // 把时域信号往FFT IP核传输的数据通道,[31:16]为虚部，[15:0]为实部（input，主->从）
    .s_axis_data_tvalid(fft_s_data_tvalid),                    // 表示主设备正在驱动一个有效的传输（input，主->从）
    .s_axis_data_tready(fft_s_data_tready),                    // 表示从设备已经准备好接收一次数据传输（output，从->主），当tvalid和tready同时为高时，启动数据传输
    .s_axis_data_tlast(fft_s_data_tlast),                      // 主设备向从设备发送传输结束信号（input，主->从，拉高为结束）
    //作为发送频谱数据时是主设备
    .m_axis_data_tdata(fft_m_data_tdata),                      // FFT输出的频谱数据，[47:24]对应的是虚部数据，[23:0]对应的是实部数据(output，主->从)。
    .m_axis_data_tuser(fft_m_data_tuser),                      // 输出频谱的索引(output，主->从)，该值*fs/N即为对应频点；
    .m_axis_data_tvalid(fft_m_data_tvalid),                    // 表示主设备正在驱动一个有效的传输（output，主->从）
    //.m_axis_data_tready(fft_m_data_tready),                    // 表示从设备已经准备好接收一次数据传输（input，从->主），当tvalid和tready同时为高时，启动数据传输
    .m_axis_data_tlast(fft_m_data_tlast)                     // 主设备向从设备发送传输结束信号（output，主->从，拉高为结束）
    //其他输出数据
//    .event_frame_started(fft_event_frame_started),                  // output wire event_frame_started
//    .event_tlast_unexpected(fft_event_tlast_unexpected),            // output wire event_tlast_unexpected
//    .event_tlast_missing(fft_event_tlast_missing),                  // output wire event_tlast_missing
//    .event_status_channel_halt(fft_event_status_channel_halt),      // output wire event_status_channel_halt
//    .event_data_in_channel_halt(fft_event_data_in_channel_halt),    // output wire event_data_in_channel_halt
//    .event_data_out_channel_halt(fft_event_data_out_channel_halt)   // output wire event_data_out_channel_halt
  );

    
    
    
    
    reg [9:0]s_cnt;
    reg [12:0]addr;
    reg fifo_rs;
    
    reg [12:0]Reset_cnt;
    
    always@(posedge CLK_H or negedge Reset)begin
        if(!Reset)begin
            addr<=13'd0;
            Sample_finish<=1'd0;
            Sample_start<=1'd1;
            bram_ena<=1'b1;
            bram_wea<=1'b0;
            s_cnt<=10'b0;
            fft_start_flag<=1'b0;
        end
        else if(s_cnt>10'd999)begin//采样率=65M/这个比较的数+1
            s_cnt<=10'd0;
            if(Sample_start&&!Sample_finish) begin   
                if(addr>=13'd8191) begin
                    if(addr==13'd8191) begin
                        bram_wea<=1'b0;
                    
                        fft_start_flag<=1'd1;
                        Sample_finish<=1'd1;
                        Sample_start<=1'd0;
                    end

                end
            
                else if(!Sample_finish)begin
                    bram_wea<=1'b1;

                    addr<=addr+13'd1;

                end
            
            end
        
            else begin

                if(Reset_cnt==13'd3000) begin
                    Sample_start<=10'd1;
                    Reset_cnt<=11'd0;
                    fft_start_flag<=1'b0;
                    Sample_finish<=1'b0;
                    bram_wea<=1'b1;
                    addr<=13'd0;
                end
            
                
                if(data_finish_flag) begin
                    Reset_cnt<=Reset_cnt+1'd1;
                end
            end
        end
        else s_cnt<=s_cnt+13'd1;
    end
    
    reg [12:0]count;
    
always @ (posedge CLK_H or negedge Reset) begin
    if(!Reset) begin
        fft_s_data_tvalid <= 1'b0;
//        fft_s_data_tdata  <= 32'd0;
        fft_s_data_tlast  <= 1'b0;
        data_finish_flag  <= 1'b0;
        
        count <= 13'd0;        

    end
    else if ( fft_start_flag&&!data_finish_flag)begin
        if (fft_s_data_tready) begin 
            if(count>=13'd8191) begin
                fft_s_data_tvalid <= 1'b1;
                fft_s_data_tlast<=1'b1;
                data_finish_flag <= 1'b1;
            end
            else begin
                fft_s_data_tvalid <= 1'b1;
                count <= count + 1'b1;
            end
            
        end
        else begin
            fft_s_data_tvalid <= 1'b0;
            
        end
    end
    
    else begin
        fft_s_data_tlast<=1'b0;
        fft_s_data_tvalid <= 1'b0;
        
        if(Sample_start) begin
                fft_s_data_tvalid <= 1'b0;
                data_finish_flag<=1'b0;
                count<=13'd0;
        end
        
    end
end

    reg [12:0]sample_wire;
    reg sent_flag;
    assign sample_cnt=sample_wire;

    assign bram_addr=bram_wea ? addr : count;


    
always@(posedge CLK_H or negedge Reset) begin
        if(!Reset)begin
            config_valid<=0;
            fft_out<=0;
        end
        else begin
   
            if(sent_flag==1'b0) config_valid<=1;
            
            if((fft_s_config_tready==1'b1)&&(config_valid==1))begin
                 config_valid<=0;
                 sent_flag<=1'b1;
            end
        
            if(fft_m_data_tvalid==1'b1)begin
                fft_out<=fft_m_data_tdata;
                sample_wire<=fft_m_data_tuser[12:0];
            end
            
        end
    end    
endmodule
