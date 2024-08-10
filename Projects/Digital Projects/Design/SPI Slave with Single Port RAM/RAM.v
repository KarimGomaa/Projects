module RAM(din,rx_valid,clk,rst_n,dout,tx_valid,check_condition);

parameter MEM_SIZE=8;
parameter MEM_DEPTH=256;
parameter ADDR_SIZE=8;
parameter IAM_IN_WRITE=0;
parameter IAM_IN_READ_ADDRESS=1;
parameter IAM_IN_READ_DATA=2;


input [MEM_SIZE+1:0] din;
input rx_valid,clk,rst_n;
input [1:0] check_condition;
output reg [MEM_SIZE-1:0] dout;
output reg tx_valid;

reg [MEM_SIZE-1:0] mem [MEM_DEPTH-1:0];
reg [ADDR_SIZE-1:0] holded_read_address;
reg [ADDR_SIZE-1:0] holded_write_address;

always @(posedge clk or negedge rst_n) begin
	if(~rst_n) begin
	dout <=0;
	tx_valid <=0;
	end
	else if (rx_valid) begin
			if(din[9:8] == 2'b00 && check_condition == IAM_IN_WRITE ) begin
				holded_write_address<=din[7:0];
				tx_valid<=0;
			end
			else if (din[9:8] == 2'b01 && check_condition == IAM_IN_WRITE ) begin
				mem[holded_write_address]<=din[7:0];
				tx_valid<=0;
			end
			else if (din[9:8] == 2'b10 && check_condition == IAM_IN_READ_ADDRESS ) begin
				holded_read_address<=din[7:0];
				tx_valid<=0;
			end
			else if (din[9:8] == 2'b11 && check_condition == IAM_IN_READ_DATA) begin
				dout<=mem[holded_read_address];
				tx_valid<=1;
			end
	end
end
endmodule