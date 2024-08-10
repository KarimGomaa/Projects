/*
* Register to be Instantiate in the Main Module
*
* Designed By : Karim Gomaa
*/

module register(in,clk,CEREG,rst,register_data);
parameter INPUTBITS=1;
parameter RSTTYPE_register= "SYNC" ;
parameter MUX_SEL= 1; // Can Be 1: REG or 0 : COMB
input [INPUTBITS-1:0] in;
input clk,CEREG,rst;
output reg [INPUTBITS-1:0] register_data; 

generate
	if(RSTTYPE_register == "SYNC" && MUX_SEL == 1 ) begin
		always @(posedge clk) begin
			if(rst)
				register_data <= 0;
			else if(CEREG)
				register_data <= in;
		end
	end
	else if (RSTTYPE_register == "ASYNC" && MUX_SEL== 1 ) begin
		always @(posedge clk or posedge rst) begin	
			if(rst)
				register_data <= 0;
			else if(CEREG)
				register_data <= in;
		end
	end
	else begin
		always @(*)begin
			register_data <= in;
		end
	end
endgenerate

endmodule