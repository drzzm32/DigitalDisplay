module Counter(
	clk, rst, out
);
	// 50MHz@250us
	parameter CNT = 32'd12500;
	
	input clk, rst;
	output out;
	reg[31:0] cnt;
	
	initial begin
		cnt <= 32'b0;
	end
	
	always @(posedge clk or negedge rst) begin
		if (!rst) begin
			cnt <= 32'b0;
		end else begin
		
			if (cnt < CNT) cnt <= cnt + 32'b1;
			else cnt <= 32'b0;
			
		end
	end
	
	assign out = (cnt == CNT);

endmodule
