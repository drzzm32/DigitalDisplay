module PWMCtrller(
	clk, rst,
	inpos, inneg, out
);
	// 50MHz@10kHz,50%
	parameter CNT = 32'd5000;
	parameter CNTPOS = 32'd2500;
	
	input clk, rst;
	input[7:0] inpos, inneg;
	output reg[7:0] out;
	reg[31:0] cnt;
	
	initial begin
		cnt <= 32'b0;
		out <= 8'b0;
	end
	
	always @(posedge clk or negedge rst) begin
		if (!rst) begin
			cnt <= 32'b0;
			out <= 8'b0;
		end else begin
		
			if (cnt < CNT) cnt <= cnt + 32'b1;
			else cnt <= 32'b0;
			
			if (cnt < CNTPOS) out <= inpos;
			else out <= inneg;
			
		end
	end

endmodule
