`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

    

module Phase_Creater(
    CLK_H,
    phase,
    tdata,
    Flag,
    Reset
    
);
    input Reset;
    input [31:0]tdata;
    input CLK_H;
    output wire signed [15:0]phase;
    output wire [1:0]Flag;
    
    
    wire m_flag_bri;
    
    //assign Flag[3]=m_flag_bri;
    
    reg s_tdata_flag;
    //reg m_tdata_flag;
    
    
    dds_compiler_0 dds1(
        .aclk(CLK_H),
        .m_axis_data_tdata(phase),
        .m_axis_data_tvalid(m_flag_bri),
        .s_axis_phase_tdata(tdata),
        .s_axis_phase_tvalid(s_tdata_flag),
        .event_pinc_invalid(Flag[0]),
        .event_poff_invalid(Flag[1])
    );
    
    always @(posedge CLK_H or negedge Reset)begin
        if (!Reset)begin
            s_tdata_flag<=1'b0;
        end
        
        else begin
            s_tdata_flag<=1'b1;
            
        end
    end    
endmodule