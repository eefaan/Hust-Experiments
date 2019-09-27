module sum_rom(addr, sum_out, data);
    input [2:0] addr;           // 地址
    input [31:0] sum_out;
    output reg [3:0] data;          // 地址addr处存储的数据 
    
always @(addr)  begin    //根据addr地址值 用初始化的存储器mem为data赋值
        case(addr)
            3'b000: data = sum_out[3:0];
            3'b001: data = sum_out[7:4];
            3'b010: data = sum_out[11:8];
            3'b011: data = sum_out[15:12];
            3'b100: data = sum_out[19:16];
            3'b101: data = sum_out[23:20];
            3'b110: data = sum_out[27:24];
            3'b111: data = sum_out[31:28];
            default: data = 0;
        endcase
    end                   
endmodule
