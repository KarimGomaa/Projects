vlib work 
vlog spartan.v register.v tb_spartan.v  
vsim -voptargs=+acc work.tb_spartan
add wave *
run -all