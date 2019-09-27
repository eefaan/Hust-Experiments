`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/19 08:26:31
// Design Name: 
// Module Name: Display
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


module reveal(halt,clk,num,an,seg);
input halt;   //暂停信号
input clk;
input  [31:0]num;
output [7:0] seg; //7段数码管驱动
output [7:0] an;  //7段数码管片选信号

wire clk_N;
wire [2:0]out;
wire [3:0]seginput;

wire [31:0]num;


  

//divider #(10000)div(clk,0,clk_N);//8.该行代码为上开发板的代码
 assign clk_N = clk;//8.该行代码为仿真程序的代码
 
counter cou(clk_N,out);
_7Seg_Driver_Choice cho(out,an);
evalu eva(out,num,seginput);
_7Seg_Driver_Decode dec (seginput,seg);


endmodule

module _7Seg_Driver_Decode(sw, seg);//7段显示译码器
   input [3:0] sw;      //拨动16位开关
   output reg [7:0] seg; //7位数码管驱动

   
   always @(sw) begin
      case(sw[3:0])
      
      4'b0000: seg  = 8'b00000011;
      4'b0001: seg  = 8'b10011111;
      4'b0010: seg  = 8'b00100101;
      4'b0011: seg  = 8'b00001101;
      4'b0100: seg  = 8'b10011001;
      4'b0101: seg  = 8'b01001001;
      4'b0110: seg  = 8'b01000001;
      4'b0111: seg  = 8'b00011111;
      4'b1000: seg  = 8'b00000001;
      4'b1001: seg  = 8'b00011001;
      4'b1010: seg  = 8'b11111111;
      4'b1011: seg  = 8'b11111111;
      4'b1100: seg  = 8'b11111111;
      4'b1101: seg  = 8'b11111111;
      4'b1110: seg  = 8'b11111111;
      4'b1111: seg  = 8'b11111111;
      default : seg = 8'b11111111;
       
      endcase
    end 
  endmodule
  
 module counter(clk, out);
  input clk;                    // 计数时钟
  output reg[2:0] out;             // 计数值
  initial begin
  out = 0;
  end
  
  always @(posedge clk)  begin  // 在时钟上升沿计数器加1
      out = out + 1;            // 功能实现
      if(out>= 8) begin     
          out = 0;
      end                        
  end                           
  endmodule
  
 module _7Seg_Driver_Choice(sw, an); 
    input [2:0] sw;      
    output reg [7:0]an;  //7位数码管片选择信号
    always @(sw) begin
    case(sw[2:0])
    3'b000:an = 8'b11111110;
    3'b001:an = 8'b11111101;
    3'b010:an = 8'b11111011;
    3'b011:an = 8'b11110111;
    3'b100:an = 8'b11101111;
    3'b101:an = 8'b11011111;
    3'b110:an = 8'b10111111;
    3'b111:an = 8'b01111111;
    default:an = 8'b11111110;
      endcase
    end 
endmodule


module evalu(out,num,seginput);
   input [2:0]out;
   input [31:0]num;
   output reg [3:0]seginput;
   
   always @* begin 
   case(out)
   3'b000:seginput = num[3:0];
   3'b001:seginput = num[7:4];
   3'b010:seginput = num[11:8];
   3'b011:seginput = num[15:12];   
   3'b100:seginput = num[19:16];
   3'b101:seginput = num[23:20];
   3'b110:seginput = num[27:24];
   3'b111:seginput = num[31:28];
   default: seginput = 4'h0;
      endcase
   end

endmodule
