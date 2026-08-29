module rom
#(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=8)
(
	input [(ADDR_WIDTH-1):0] addr,
	input clk, 
	output reg [(DATA_WIDTH-1):0] q
);

	(* ram_init_file = "programa.mif" *)
	reg [DATA_WIDTH-1:0] rom[2**ADDR_WIDTH-1:0];


	initial
	begin
		q = {DATA_WIDTH{1'b0}};
		$readmemb("programa.txt", rom);
	end

	always @ (posedge clk)
	begin
		q <= rom[addr];
	end

endmodule
