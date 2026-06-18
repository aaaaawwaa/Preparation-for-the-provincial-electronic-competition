`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////



module MovingAvg_Subtractor #(
    parameter WINDOW_POW  = 8,          // 
    parameter DATA_WIDTH  = 13          // 
)(
    input            [DATA_WIDTH-1:0] In,       // 
    input                          valid,    // 
    input                          CLK_H,    // 
    input                          Reset,    // 
    output reg          [DATA_WIDTH-1:0] Out,  // 
    output reg                     valid_out // 
);

    localparam WINDOW_SIZE = 1 << WINDOW_POW;           // 
    localparam SUM_WIDTH   = DATA_WIDTH + WINDOW_POW;   // 


    reg signed [DATA_WIDTH-1:0] delay_line [0:WINDOW_SIZE-1];

    reg [WINDOW_POW-1:0]        wr_ptr;         // å¾
    reg [WINDOW_POW-1:0]        sample_cnt;     // ?
    reg signed [SUM_WIDTH-1:0]  running_sum;    // 


    wire signed [DATA_WIDTH-1:0] oldest_sample;
    assign oldest_sample = (sample_cnt >= WINDOW_SIZE) ? delay_line[wr_ptr]
                                                       : {DATA_WIDTH{1'b0}};


    wire signed [SUM_WIDTH-1:0] sum_new;
    assign sum_new = running_sum + In - oldest_sample;

    wire signed [DATA_WIDTH-1:0] moving_avg;
    assign moving_avg = sum_new >>> WINDOW_POW;

    always@(posedge CLK_H or negedge Reset) begin
        if(!Reset) begin
            Out         <= {DATA_WIDTH{1'b0}};
            valid_out   <= 1'b0;
            running_sum <= {SUM_WIDTH{1'b0}};
            wr_ptr      <= 0;
            sample_cnt  <= 0;
        end
        else if(valid) begin
            delay_line[wr_ptr] <= In;
            wr_ptr <= wr_ptr + 1'b1;

            if(sample_cnt < WINDOW_SIZE)
                sample_cnt <= sample_cnt + 1'b1;

            running_sum <= sum_new;

            Out <= moving_avg;

            valid_out <= (sample_cnt >= WINDOW_SIZE - 1);
        end
        else begin
            valid_out <= 1'b0;
        end
    end

endmodule
