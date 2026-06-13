`timescale 1ns / 1ps

module FIR_130m_5m(

     CLK_H,
     phase_input,
     phase_output,
     Reset
     
);

    input signed [27:0]phase_input;
    input CLK_H;
    input Reset;
    
    output wire signed [15:0]phase_output;
    
    wire handle_flag;

    reg signed [15:0]phase_output_saver;
    
    wire signed [15:0]phase_output_med;
    
    reg fir_valid;
    wire out_valid;
    
    assign phase_output=phase_output_saver;
    
    fir_compiler_0 fir_0(
       .aclk(CLK_H),
   
       .s_axis_data_tdata(phase_input), 
       .s_axis_data_tready(handle_flag),
       .s_axis_data_tvalid(fir_valid),
       .m_axis_data_tvalid(out_valid),
       .m_axis_data_tdata(phase_output_med)
   );
   
   always@(posedge CLK_H or negedge Reset)begin
       if(!Reset)begin
           fir_valid<=1'b0;
       end
       
       else begin
           if(handle_flag==1)begin
               fir_valid<=1'b1;
           end
           
           if(out_valid==1) phase_output_saver<=phase_output_med;
           
       end
   end
    
endmodule
