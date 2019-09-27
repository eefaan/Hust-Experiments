module IF_ID(
    input rst,
    input en,
    input clk,
    input [31:0]IR_if,
    input [31:0]PC_if,

    output reg[31:0]IR_id,
    output reg[31:0]PC_id
    );

    always @(posedge clk)begin
        if(rst) begin
            IR_id = 32'b0;
            PC_id = 32'b0;
        end
        else if(en) begin
            IR_id = IR_if;
            PC_id = PC_if;
        end
    end

endmodule
