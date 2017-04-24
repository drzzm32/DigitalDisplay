module Decoder(
	in, out
);

	input[4:0] in;
	output reg[7:0] out;
	
	always begin
		case (in[3:0])
			4'h0: out = 8'hFA;
			4'h1: out = 8'h22;
			4'h2: out = 8'hB9;
			4'h3: out = 8'hAB;
			4'h4: out = 8'h63;
			4'h5: out = 8'hCB;
			4'h6: out = 8'hDB;
			4'h7: out = 8'hA2;
			4'h8: out = 8'hFB;
			4'h9: out = 8'hEB;
			4'hA: out = 8'hF3;
			4'hB: out = 8'h5B;
			4'hC: out = 8'hD8;
			4'hD: out = 8'h3B;
			4'hE: out = 8'hD9;
			4'hF: out = 8'hD1;
		endcase
		out[2] = in[4];
	end
	
endmodule
