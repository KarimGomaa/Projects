vlib work 
vlog RAM.v SPI.v tb_SPI.v  
vsim -voptargs=+acc work.tb_SPI
add wave -position insertpoint  \
sim:/tb_SPI/MOSI \
sim:/tb_SPI/SS_N \
sim:/tb_SPI/clk \
sim:/tb_SPI/rst_n
add wave -position insertpoint  \
sim:/tb_SPI/dut1/cs \
sim:/tb_SPI/dut1/ns
add wave -position insertpoint  \
sim:/tb_SPI/dut1/rx_data_saver
add wave -position insertpoint  \
sim:/tb_SPI/dut1/count
add wave -position insertpoint  \
sim:/tb_SPI/dut1/write_disable