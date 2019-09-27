module ROM#(
	parameter Nmem = 512,// Number of memory entries,
	parameter ROM_DATA = "ROM_DATA.txt"// file to read data from
	)(
	input wire 	[31:0] 	addr,
	output wire [31:0] 	data
	);

	reg [31:0] memory [0:Nmem-1];  // 32-bit memory with Nmem entries

	initial begin
		$readmemh(ROM_DATA, memory, 0, Nmem-1);
	end

	// assign data = memory[addr[11:2]][31:0];
	assign data = memory[addr[11:2]][31:0];
endmodule
