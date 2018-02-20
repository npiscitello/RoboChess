
module DE0_Basic_Computer (
	// Inputs
	CLOCK_50,
	KEY,
	SW,

	//  Communication
	UART_RXD,
	
/*****************************************************************************/
	// Bidirectionals
	GPIO_0,
	GPIO_1,

	//  Memory (SDRAM)
	DRAM_DQ,


/*****************************************************************************/
	// Outputs
	// 	Simple
	LEDG,

	HEX0,
	HEX1,
	HEX2,
	HEX3,
	
	//  Communication
	UART_TXD,
	
	//  Memory (SDRAM)
	DRAM_ADDR,
	
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_RAS_N,
	DRAM_CLK,
	DRAM_CKE,
	DRAM_CS_N,
	DRAM_WE_N,
	DRAM_UDQM,
	DRAM_LDQM
);

/*****************************************************************************
 *                           Parameter Declarations                          *
 *****************************************************************************/


/*****************************************************************************
 *                             Port Declarations                             *
 *****************************************************************************/
// Inputs
input				CLOCK_50;
input		[2:0]	KEY;
input		[9:0]	SW;


//  Communication
input				UART_RXD;

// Bidirectionals
inout		[31:0]	GPIO_0;
inout		[31:0]	GPIO_1;

//  Memory (SDRAM)
inout		[15:0]	DRAM_DQ;

// Outputs
// 	Simple
output		[9:0]	LEDG;

output		[7:0]	HEX0;
output		[7:0]	HEX1;
output		[7:0]	HEX2;
output		[7:0]	HEX3;

//  Communication
output				UART_TXD;

//  Memory (SDRAM)
output		[11:0]	DRAM_ADDR;

output		[ 1: 0]	DRAM_BA;
output				DRAM_CAS_N;
output				DRAM_RAS_N;
output				DRAM_CLK;
output				DRAM_CKE;
output				DRAM_CS_N;
output				DRAM_WE_N;
output				DRAM_UDQM;
output				DRAM_LDQM;

/*****************************************************************************
 *                 Internal Wires and Registers Declarations                 *
 *****************************************************************************/
// Internal Wires
// Used to connect the Nios 2 system clock to the non-shifted output of the PLL
wire				system_clock;

// Internal Registers

// State Machine Registers

/*****************************************************************************
 *                         Finite State Machine(s)                           *
 *****************************************************************************/


/*****************************************************************************
 *                             Sequential Logic                              *
 *****************************************************************************/


/*****************************************************************************
 *                            Combinational Logic                            *
 *****************************************************************************/

// Output Assignments

/*****************************************************************************
 *                              Internal Modules                             *
 *****************************************************************************/
nios_system NiosII (
	// 1) global signals:
	.clk									(system_clock),
	.reset_n								(KEY[0]),

	// the_Slider_switches
	.SW_to_the_Slider_switches				(SW),

	// the_Pushbuttons
	.KEY_to_the_Pushbuttons					({KEY[2:1], 1'b1}),

	// the_Expansion_JP1
	.GPIO_0_to_and_from_the_Expansion_JP1	(GPIO_0),

	// the_Expansion_JP2
	.GPIO_1_to_and_from_the_Expansion_JP2	(GPIO_1),

	// the_Green_LEDs
	.LEDG_from_the_Green_LEDs				(LEDG),

	// the_HEX3_HEX0
	.HEX0_from_the_HEX3_HEX0				(HEX0),
	.HEX1_from_the_HEX3_HEX0				(HEX1),
	.HEX2_from_the_HEX3_HEX0				(HEX2),
	.HEX3_from_the_HEX3_HEX0				(HEX3),
	
	// the_Serial_port
	.UART_RXD_to_the_Serial_port			(UART_RXD),
	.UART_TXD_from_the_Serial_port			(UART_TXD),
	
	// the sdram
	.zs_addr_from_the_sdram					(DRAM_ADDR),
	.zs_ba_from_the_sdram					(DRAM_BA),
	.zs_cas_n_from_the_sdram				(DRAM_CAS_N),
	.zs_cke_from_the_sdram					(DRAM_CKE),
	.zs_cs_n_from_the_sdram					(DRAM_CS_N),
	.zs_dq_to_and_from_the_sdram			(DRAM_DQ),
	.zs_dqm_from_the_sdram					({DRAM_UDQM, DRAM_LDQM}),
	.zs_ras_n_from_the_sdram				(DRAM_RAS_N),
	.zs_we_n_from_the_sdram					(DRAM_WE_N)
);

sdram_pll neg_3ns (CLOCK_50, DRAM_CLK, system_clock);

endmodule
