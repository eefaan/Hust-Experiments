`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/01 21:26:39
// Design Name: 
// Module Name: memory_circuit
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module memory_circuit
#(parameter DATA_WIDTH=8,parameter ADDR_WIDTH=4)(
    input clk,
    input we, 
    inout [(DATA_WIDTH-1):0] data,
    input [(ADDR_WIDTH-1):0] addr
);    
    
    // Declare the RAM variable
    reg [DATA_WIDTH-1:0] ram[2**ADDR_WIDTH-1:0];
    
    initial begin
       $readmemh("C:/rom_init.txt", ram);
    end

    always @ (posedge clk) begin
        if (we)
            ram[addr] <= data;
        end
    
    assign data = we? 32'bz : ram[addr];
endmodule
