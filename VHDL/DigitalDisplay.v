module DigitalDisplay(
	clk, rst,
	ctrl,
	data, pos
);

	input clk, rst;
	input[7:0] ctrl;
	output[7:0] data;
	output reg[3:0] pos;
	
	wire signal;
	wire[7:0] bus;
	reg[4:0] buffer[4:0];
	reg[2:0] index;

	Counter cnt(clk, rst, signal);
	Decoder dec(buffer[0], bus);
	PWMCtrller pwm(clk, rst, bus, 8'b0, data);
	
	initial begin
		pos <= 4'b1111;
		index <= 3'd1;
		buffer[1] <= 5'd8 | 5'b10000;
		buffer[2] <= 5'd8 | 5'b10000;
		buffer[3] <= 5'd8 | 5'b10000;
		buffer[4] <= 5'd8 | 5'b10000;
	end
	
	always @(posedge signal or negedge rst or negedge ctrl[7]) begin
		if (!rst) begin
			pos <= 4'b1111;
			index <= 3'd1;
			buffer[1] <= 5'd8 | 5'b10000;
			buffer[2] <= 5'd8 | 5'b10000;
			buffer[3] <= 5'd8 | 5'b10000;
			buffer[4] <= 5'd8 | 5'b10000;
		end else if (!ctrl[7]) begin
			buffer[ctrl[6:5] + 3'd1] <= ctrl[4:0];
		end else begin
			pos <= ~(4'b1000 >> (index - 3'd1));
			buffer[0] <= buffer[index];
			index <= (index < 3'd4) ? index + 3'd1 : 3'd1;
		end
	end
	
endmodule
