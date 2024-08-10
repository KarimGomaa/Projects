module SPI(MOSI,MISO,SS_n,clk,rst_n,rx_data,rx_valid,tx_data,tx_valid);

parameter IDLE=3'b000;
parameter CHK_CMD=3'b001;
parameter WRITE=3'b010;
parameter READ_DATA=3'b011;
parameter READ_ADDRESS=3'b100;


input MOSI,SS_n,clk,rst_n,tx_valid;
input [7:0] tx_data;
output reg MISO,rx_valid;
output reg [9:0] rx_data;

reg [2:0] cs,ns;
reg [9:0] rx_data_saver;
reg [7:0] tx_data_saver;
reg [3:0] count;
reg write_disable,read_disable,read_address_finish;
reg [2:0] check_condition_checker;

RAM dut(rx_data,rx_valid,clk,rst_n,tx_data,tx_valid,check_condition_checker);

//State Memory
always @(posedge clk or negedge rst_n) begin
	if(~rst_n) begin
		cs <= IDLE;
	end
	else
		cs <= ns;
end

//Output Logic 
always @(cs or posedge clk) begin
	case(cs)
		IDLE: begin 
		count<=9;
		write_disable<=0;
		check_condition_checker<=3;
		end
		CHK_CMD: begin
			
		end
		WRITE: begin
				rx_data_saver[count]=MOSI;
				if (count == 0) begin
				check_condition_checker<=0;
				rx_data=rx_data_saver;
				rx_valid<=1;
				write_disable<=1;
				end
				count=count-1;
		end
		READ_DATA: begin
			
		end
		READ_ADDRESS: begin
			
		end
		default: begin
			
					end
	endcase
end

//Next State
always @(cs,SS_n,MOSI) begin
	case(cs)
		IDLE: begin 
			if(SS_n == 0)
				ns<=CHK_CMD;
			else
				ns<=IDLE;	
		end
		CHK_CMD: begin
			if(SS_n == 0 && MOSI == 1 && read_address_finish==0 && read_disable ==0)
				ns<=READ_ADDRESS;
			else if(SS_n == 0 && MOSI == 1 && read_address_finish==1 && read_disable ==0)
				ns<=READ_DATA;
			else if(SS_n == 0 && MOSI == 0)
				ns<=WRITE;
			else 	
				ns<=IDLE;	
		end
		WRITE: begin
			if(SS_n == 0 && write_disable == 0)
				ns<=WRITE;
			else
				ns<=IDLE;
		end
		READ_DATA: begin
			if(SS_n == 0 && read_disable == 0)
				ns<=READ_DATA;
			else
				ns<=IDLE;
		end
		READ_ADDRESS: begin
			if(SS_n == 0 && read_disable==0)
				ns<=READ_ADDRESS;
			else
				ns<=IDLE;
		end
		default: begin
				ns<=IDLE;
		end
	endcase
end

integer j;
always @(*) begin
	if(tx_valid)
		for(j=9;j>=0;j=j-1)
		MISO=tx_data_saver[j];
end

endmodule