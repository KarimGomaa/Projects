module tb_SPI();

reg MOSI,SS_N,clk,rst_n;
wire MISO;
wire rxdata,rx_valid,tx_data,tx_valid;

SPI dut1(MOSI,MISO,SS_N,clk,rst_n,rx_data,rx_valid,tx_data,tx_valid);

initial begin
	clk=0;
	forever
	#2 clk = ~clk;
end

initial begin
SS_N<=1;
rst_n<=0;
#4
rst_n<=1;
SS_N<=0;
MOSI<=0;  //write
#4
MOSI<=0;  // address
@(negedge clk);
//send 10 bits example but must contain 10'b00_1101_1101
MOSI<=0; 
@(negedge clk);
MOSI<=0;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=0;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=0;
@(negedge clk);
MOSI<=1;
@(negedge clk);
// now we have write in hold_write_address =1101_1101
// we will write in the memory 1010_1010
// so we need to send 0 to write and then he will be waiting for the 10 bit 
// we will send 01_1010_1010
MOSI<=0; //write
@(negedge clk);
MOSI<=0;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=0;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=0;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=0;
@(negedge clk);
MOSI<=1;
@(negedge clk);
MOSI<=0;
@(negedge clk);
// we wrote now in address 1101_1101 this number 1010_1010 

$stop;

end

endmodule