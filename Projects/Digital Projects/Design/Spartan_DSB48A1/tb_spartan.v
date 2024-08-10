module tb_spartan();

reg [17:0] A,B,D;
reg [47:0] C;
reg	 	CLK,CARRYIN,RSTA,RSTB,RSTM,RSTP,RSTC,RSTD,RSTCARRYIN,
		RSTOPMODE,CEA,CEB,CEM,CEP,CEC,CED,CECARRYIN,CEOPMODE;
reg [7:0]	opmode;
reg [17:0]	BCIN;
reg [47:0]	PCIN;

wire [17:0] BCOUT;
wire [47:0] PCOUT,P;
wire [35:0] M;
wire CARRYOUT,CARRYOUTF;


SPARTAN_DSB48A1 dut(A,B,D,C,CLK,CARRYIN,opmode,BCIN,RSTA,RSTB,RSTM,RSTP,RSTC,RSTD,RSTCARRYIN,
		RSTOPMODE,CEA,CEB,CEM,CEP,CEC,CED,CECARRYIN,CEOPMODE,PCIN,BCOUT,PCOUT,P,M,CARRYOUT,CARRYOUTF);


initial begin
	CLK=0;
	forever
	#2 CLK = ~CLK;
end

initial begin
D <= $urandom_range(1,10000);
B <= $urandom_range(1,10000);
A <= $urandom_range(1,10000);
C <= $urandom_range(1,10000);
RSTA<= 1;
RSTB<= 1;
RSTM<= 1;
RSTP<= 1;
RSTC<= 1;
RSTD<= 1;
RSTCARRYIN<= 1;
RSTOPMODE<= 1;
CARRYIN<= 0;
CEA<= 0;
CEB<= 0;
CEM<= 0;
CEP<= 0;
CEC<= 0;
CED<= 0;
CECARRYIN<= 1;
CEOPMODE<= 1;
opmode <= 7'b0000_0101;
BCIN <= 33;
PCIN<= 0;
#50

	if(BCOUT!=0 && PCOUT!=0 && P!=0 && M!=0 && CARRYOUT!=0 && CARRYOUTF!=0) begin
	$display("Error -_- !!!!");
	$stop;
	end

D <= $urandom_range(1,10000);
B <= $urandom_range(1,10000);
A <= $urandom_range(1,10000);
C <= $urandom_range(1,10000);
RSTA<= 1;
RSTB<= 1;
RSTM<= 1;
RSTP<= 1;
RSTC<= 1;
RSTD<= 1;
RSTCARRYIN<= 1;
RSTOPMODE<= 1;
CARRYIN<= 1;
CEA<= 1;
CEB<= 1;
CEM<= 1;
CEP<= 1;
CEC<= 1;
CED<= 1;
CECARRYIN<= 1;
CEOPMODE<= 1;
opmode <= 7'b0000_0101;
BCIN <= 33;
PCIN<= 0;
#50

	if(BCOUT!=0 && PCOUT!=0 && P!=0 && M!=0 && CARRYOUT!=0 && CARRYOUTF!=0) begin
	$display("Error -_- !!!!");
	$stop;
	end

RSTA<= 1;
RSTB<= 0;
RSTM<= 1;
RSTP<= 1;
RSTC<= 1;
RSTD<= 1;
RSTCARRYIN<= 1;
RSTOPMODE<= 1;
CARRYIN<= 1;
CEA<= 1;
CEB<= 1;
CEM<= 1;
CEP<= 1;
CEC<= 1;
CED<= 1;
CECARRYIN<= 1;
CEOPMODE<= 1;
opmode <= 7'b0000_0101;
D <= $urandom_range(1,10000);
B <= $urandom_range(1,10000);
A <= $urandom_range(1,10000);
C <= $urandom_range(1,10000);
BCIN <= 33;
PCIN<= 0;
#50

	if(BCOUT!=B && PCOUT!=0 && P!=0 && M!=0 && CARRYOUT!=0 && CARRYOUTF!=0) begin
	$display("Error -_- !!!!");
	$stop;
	end	

RSTA<= 0;
RSTB<= 0;
RSTM<= 0;
RSTP<= 1;
RSTC<= 1;
RSTD<= 1;
RSTCARRYIN<= 1;
RSTOPMODE<= 1;
CARRYIN<= 1;
CEA<= 1;
CEB<= 1;
CEM<= 1;
CEP<= 1;
CEC<= 1;
CED<= 1;
CECARRYIN<= 1;
CEOPMODE<= 1;
opmode <= 7'b0000_0101;
D <= $urandom_range(1,10000);
B <= 10;
A <= 10;
C <= $urandom_range(1,10000);
BCIN <= 33;
PCIN<= 0;
#50

	if(BCOUT!=B && PCOUT!=0 && P!=0 && M!=100 && CARRYOUT!=0 && CARRYOUTF!=0) begin
	$display("Error -_- !!!!");
	$stop;
	end		

RSTA<= 0;
RSTB<= 0;
RSTM<= 0;
RSTP<= 0;
RSTC<= 0;
RSTD<= 0;
RSTCARRYIN<= 0;
RSTOPMODE<= 0;
CARRYIN<= 1;
CEA<= 1;
CEB<= 1;
CEM<= 1;
CEP<= 1;
CEC<= 1;
CED<= 1;
CECARRYIN<= 1;
CEOPMODE<= 1;
opmode <= 7'b0000_1101;
D <= $urandom_range(1,10000);
B <= 10;
A <= 10;
C <= 1;
BCIN <= 33;
PCIN<= 0;
#50

	if(BCOUT!=B && PCOUT!=101 && P!=101 && M!=100 && CARRYOUT!=0 && CARRYOUTF!=0) begin
	$display("Error -_- !!!!");
	$stop;
	end	

RSTA<= 0;
RSTB<= 0;
RSTM<= 0;
RSTP<= 0;
RSTC<= 0;
RSTD<= 0;
RSTCARRYIN<= 0;
RSTOPMODE<= 0;
CARRYIN<= 1;
CEA<= 1;
CEB<= 1;
CEM<= 1;
CEP<= 1;
CEC<= 1;
CED<= 1;
CECARRYIN<= 1;
CEOPMODE<= 1;
opmode <= 7'b0101_1001;
D <= 15;
B <= 10;
A <= 10;
C <= 1;
BCIN <= 33;
PCIN<= 0;
#50

	if(BCOUT!=5 && M!=50 && CARRYOUT!=0 && CARRYOUTF!=0) begin
	$display("Error -_- !!!!");
	$stop;
	end		

$stop;
end

initial begin
$monitor("D=%d , B=%d , A=%d , C=%d, BCOUT=%d , PCOUT=%d , P=%d , M=%d, CARRYOUT=%d, CARRYOUTF=%d",D,B,A,C,BCOUT,PCOUT,P,M,CARRYOUT,CARRYOUTF);
end 

endmodule