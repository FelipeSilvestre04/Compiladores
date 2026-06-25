module rom
#(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=8)
(
	input [(ADDR_WIDTH-1):0] addr,
	input clk, 
	output reg [(DATA_WIDTH-1):0] q
);

	reg [DATA_WIDTH-1:0] rom[2**ADDR_WIDTH-1:0];


	initial
	begin
		$readmemb("programa.txt", rom);
	end

	always @ (*)
	begin
		q = rom[addr];
	end

endmodule
