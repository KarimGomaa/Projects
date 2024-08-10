/*
* SPARTAN_DSB48A1 Module design Main Module
*
* Designed By : Karim Gomaa
*/

module SPARTAN_DSB48A1(A,B,D,C,CLK,CARRYIN,opmode,BCIN,
			RSTA,RSTB,RSTM,RSTP,RSTC,RSTD,RSTCARRYIN,RSTOPMODE,
			CEA,CEB,CEM,CEP,CEC,CED,CECARRYIN,CEOPMODE,
			PCIN,BCOUT,PCOUT,P,M,CARRYOUT,CARRYOUTF);

///////////////////////////////////////////// Initialization /////////////////////////////////////////////

input [17:0] A,B,D;
input [47:0] C;
input	CLK,CARRYIN,RSTA,RSTB,RSTM,RSTP,RSTC,RSTD,RSTCARRYIN,
		RSTOPMODE,CEA,CEB,CEM,CEP,CEC,CED,CECARRYIN,CEOPMODE;
input [7:0]	opmode;
input [17:0]	BCIN;
input [47:0]	PCIN;

output reg [17:0] BCOUT;
output reg [47:0] PCOUT,P;
output reg [35:0] M;
output reg CARRYOUT,CARRYOUTF;

parameter A0REG=0;						// Can Be 1: REG or 0 : COMB
parameter A1REG=1;						// Can Be 1: REG or 0 : COMB
parameter B0REG=0;						// Can Be 1: REG or 0 : COMB
parameter B1REG=1;						// Can Be 1: REG or 0 : COMB
parameter CREG=1;						// Can Be 1: REG or 0 : COMB
parameter DREG=1;						// Can Be 1: REG or 0 : COMB
parameter MREG=1;						// Can Be 1: REG or 0 : COMB
parameter PREG=1;						// Can Be 1: REG or 0 : COMB
parameter CARRYINREG=1;					// Can Be 1: REG or 0 : COMB
parameter CARRYOUTREG=1;				// Can Be 1: REG or 0 : COMB
parameter OPMODEREG=1;					// Can Be 1: REG or 0 : COMB
parameter CARRYINSEL= "OPMODE5"; 		// Can be OPMODE5 or CARRYIN 
parameter B_INPUT= "DIRECT";	 		// Can be DIRECT or CASCADE 
parameter RSTTYPE= "SYNC"; 				// Can be SYNC or ASYNC

wire [17:0] B_wire,D_REG_wire,B0_REG_wire,A0_REG_wire;
wire [17:0] PreADDSUB_wire,MUX1_wire,B1_REG_wire,A1_REG_wire;
wire [35:0] MULT_wire,M_REG_wire;
wire [47:0] C_REG_wire,D_A_B_wire,XMUX_wire,ZMUX_wire,PostADDSUB_wire,P_REG_wire;
wire CYI_wire,CYI_REG_wire,CYO_wire,CYO_REG_wire;
wire [7:0] OPMODE;


///////////////////////////////////////////// First Stage /////////////////////////////////////////////
register #(.INPUTBITS(18),.RSTTYPE_register(RSTTYPE),.MUX_SEL(DREG)) D_Reg(.in(D),.clk(CLK),.CEREG(CED),.rst(RSTD),.register_data(D_REG_wire));
assign B_wire = (B_INPUT == "DIRECT")? B : (B_INPUT == "CASCADE")? BCIN :0;
register #(.INPUTBITS(18),.RSTTYPE_register(RSTTYPE),.MUX_SEL(B0REG)) B0_Reg(.in(B_wire),.clk(CLK),.CEREG(CEB),.rst(RSTB),.register_data(B0_REG_wire));
register #(.INPUTBITS(18),.RSTTYPE_register(RSTTYPE),.MUX_SEL(A0REG)) A0_Reg(.in(A),.clk(CLK),.CEREG(CEA),.rst(RSTA),.register_data(A0_REG_wire));
register #(.INPUTBITS(48),.RSTTYPE_register(RSTTYPE),.MUX_SEL(CREG)) C_Reg(.in(C),.clk(CLK),.CEREG(CEC),.rst(RSTC),.register_data(C_REG_wire));
register #(.INPUTBITS(8),.RSTTYPE_register(RSTTYPE),.MUX_SEL(OPMODEREG)) OPMODE_Reg(.in(opmode),.clk(CLK),.CEREG(CEOPMODE),.rst(RSTOPMODE),.register_data(OPMODE));
///////////////////////////////////////// End Of First Stage //////////////////////////////////////////

///////////////////////////////////////////// Second Stage /////////////////////////////////////////////
assign PreADDSUB_wire = ( OPMODE[6] == 1 )? D_REG_wire-B0_REG_wire : D_REG_wire+B0_REG_wire; 
assign MUX1_wire = ( OPMODE[4] == 1 )? PreADDSUB_wire:B0_REG_wire;
register #(.INPUTBITS(18),.RSTTYPE_register(RSTTYPE),.MUX_SEL(B1REG)) B1_Reg(.in(MUX1_wire),.clk(CLK),.CEREG(CEB),.rst(RSTB),.register_data(B1_REG_wire));
register #(.INPUTBITS(18),.RSTTYPE_register(RSTTYPE),.MUX_SEL(A1REG)) A1_Reg(.in(A0_REG_wire),.clk(CLK),.CEREG(CEA),.rst(RSTA),.register_data(A1_REG_wire));
///////////////////////////////////////// End Of Seocnd Stage //////////////////////////////////////////

///////////////////////////////////////////// Third Stage /////////////////////////////////////////////
assign MULT_wire = B1_REG_wire * A1_REG_wire;
register #(.INPUTBITS(36),.RSTTYPE_register(RSTTYPE),.MUX_SEL(MREG)) M_Reg(.in(MULT_wire),.clk(CLK),.CEREG(CEM),.rst(RSTM),.register_data(M_REG_wire));

assign XMUX_wire = (OPMODE[1:0] == 0'b00)? 0 : 
					(OPMODE[1:0] == 0'b01)? M_REG_wire :
					(OPMODE[1:0] == 0'b10)? P_REG_wire : {D_REG_wire[11:0],A1_REG_wire[17:0],B1_REG_wire[17:0]};

assign ZMUX_wire = (OPMODE[3:2] == 0'b00)? 0 : 
					(OPMODE[3:2] == 0'b01)? PCIN :
					(OPMODE[3:2] == 0'b10)? P_REG_wire : C_REG_wire ;

assign CYI_wire = (CARRYINSEL == "OPMODE5")? OPMODE[5] :
					(CARRYINSEL == "CARRYIN")? CARRYIN : 0;

register #(.INPUTBITS(1),.RSTTYPE_register(RSTTYPE),.MUX_SEL(CARRYINREG)) CYI_Reg(.in(CYI_wire),.clk(CLK),.CEREG(CECARRYIN),.rst(RSTCARRYIN),.register_data(CYI_REG_wire));
///////////////////////////////////////// End Of Third Stage //////////////////////////////////////////

///////////////////////////////////////////// Fourth Stage /////////////////////////////////////////////
assign {CYO_wire,PostADDSUB_wire} = (OPMODE[7]==1)? ZMUX_wire-(XMUX_wire+CYI_REG_wire) : ZMUX_wire+XMUX_wire+CYI_REG_wire ;

register #(.INPUTBITS(1),.RSTTYPE_register(RSTTYPE),.MUX_SEL(CARRYOUTREG)) CYO_Reg(.in(CYO_wire),.clk(CLK),.CEREG(CECARRYIN),.rst(RSTCARRYIN),.register_data(CYO_REG_wire));

register #(.INPUTBITS(48),.RSTTYPE_register(RSTTYPE),.MUX_SEL(PREG)) P_Reg(.in(PostADDSUB_wire),.clk(CLK),.CEREG(CEP),.rst(RSTP),.register_data(P_REG_wire));
///////////////////////////////////////// End Of Fourth Stage //////////////////////////////////////////


always @(*) begin
	BCOUT <=B1_REG_wire;
	PCOUT <=P_REG_wire;
	P <=P_REG_wire;
	M <=M_REG_wire;
	CARRYOUT <=CYO_REG_wire;
	CARRYOUTF <=CYO_REG_wire;
	end

endmodule