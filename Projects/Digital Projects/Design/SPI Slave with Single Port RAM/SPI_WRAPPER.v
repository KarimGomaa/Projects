module SPI_WRAPPER(MOSI,MISO,SS_N,clk,rst_n);

input MOSI,SS_N,clk,rst_n;
output MISO;

wire rx_data,rx_valid,tx_data,tx_valid;

SPI dut1(MOSI,MISO,SS_n,clk,rst_n,rx_data,rx_valid,tx_data,tx_valid);

endmodule