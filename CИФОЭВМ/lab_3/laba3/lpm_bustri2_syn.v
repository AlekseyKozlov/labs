// Copyright (C) 1991-2009 Altera Corporation
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, Altera MegaCore Function License 
// Agreement, or other applicable license agreement, including, 
// without limitation, that your use is for the sole purpose of 
// programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the 
// applicable agreement for further details.

// VENDOR "Altera"
// PROGRAM "Quartus II"
// VERSION "Version 9.1 Build 222 10/21/2009 SJ Web Edition"

// DATE "10/11/2016 20:55:10"

// 
// Device: Altera EP2S15F484C3 Package FBGA484
// 

// 
// This greybox netlist file is for third party Synthesis Tools
// for timing and resource estimation only.
// 


module lpm_bustri2 (
	data,
	enabledt,
	enabletr,
	result,
	tridata)/* synthesis synthesis_greybox=0 */;
input 	[3:0] data;
input 	enabledt;
input 	enabletr;
output 	[3:0] result;
inout 	[3:0] tridata;

wire gnd;
wire vcc;
wire unknown;

assign gnd = 1'b0;
assign vcc = 1'b1;
// unknown value (1'bx) is not needed for this tool. Default to 1'b0
assign unknown = 1'b0;

wire \tridata[0]~0 ;
wire \tridata[1]~1 ;
wire \tridata[2]~2 ;
wire \tridata[3]~3 ;


stratixii_io \tridata[0]~I (
	.datain(data[0]),
	.ddiodatain(gnd),
	.oe(enabledt),
	.outclk(gnd),
	.outclkena(vcc),
	.inclk(gnd),
	.inclkena(vcc),
	.areset(gnd),
	.sreset(gnd),
	.ddioinclk(gnd),
	.dqsupdateen(vcc),
	.linkin(gnd),
	.delayctrlin(6'b000000),
	.offsetctrlin(6'b000000),
	.terminationcontrol(14'b00000000000000),
	.combout(\tridata[0]~0 ),
	.regout(),
	.ddioregout(),
	.dqsbusout(),
	.linkout(),
	.padio(tridata[0]));
defparam \tridata[0]~I .ddio_mode = "none";
defparam \tridata[0]~I .ddioinclk_input = "negated_inclk";
defparam \tridata[0]~I .dqs_delay_buffer_mode = "none";
defparam \tridata[0]~I .dqs_out_mode = "none";
defparam \tridata[0]~I .inclk_input = "normal";
defparam \tridata[0]~I .input_async_reset = "none";
defparam \tridata[0]~I .input_power_up = "low";
defparam \tridata[0]~I .input_register_mode = "none";
defparam \tridata[0]~I .input_sync_reset = "none";
defparam \tridata[0]~I .oe_async_reset = "none";
defparam \tridata[0]~I .oe_power_up = "low";
defparam \tridata[0]~I .oe_register_mode = "none";
defparam \tridata[0]~I .oe_sync_reset = "none";
defparam \tridata[0]~I .operation_mode = "bidir";
defparam \tridata[0]~I .output_async_reset = "none";
defparam \tridata[0]~I .output_power_up = "low";
defparam \tridata[0]~I .output_register_mode = "none";
defparam \tridata[0]~I .output_sync_reset = "none";
defparam \tridata[0]~I .sim_dqs_delay_increment = 0;
defparam \tridata[0]~I .sim_dqs_intrinsic_delay = 0;
defparam \tridata[0]~I .sim_dqs_offset_increment = 0;

stratixii_io \tridata[1]~I (
	.datain(data[1]),
	.ddiodatain(gnd),
	.oe(enabledt),
	.outclk(gnd),
	.outclkena(vcc),
	.inclk(gnd),
	.inclkena(vcc),
	.areset(gnd),
	.sreset(gnd),
	.ddioinclk(gnd),
	.dqsupdateen(vcc),
	.linkin(gnd),
	.delayctrlin(6'b000000),
	.offsetctrlin(6'b000000),
	.terminationcontrol(14'b00000000000000),
	.combout(\tridata[1]~1 ),
	.regout(),
	.ddioregout(),
	.dqsbusout(),
	.linkout(),
	.padio(tridata[1]));
defparam \tridata[1]~I .ddio_mode = "none";
defparam \tridata[1]~I .ddioinclk_input = "negated_inclk";
defparam \tridata[1]~I .dqs_delay_buffer_mode = "none";
defparam \tridata[1]~I .dqs_out_mode = "none";
defparam \tridata[1]~I .inclk_input = "normal";
defparam \tridata[1]~I .input_async_reset = "none";
defparam \tridata[1]~I .input_power_up = "low";
defparam \tridata[1]~I .input_register_mode = "none";
defparam \tridata[1]~I .input_sync_reset = "none";
defparam \tridata[1]~I .oe_async_reset = "none";
defparam \tridata[1]~I .oe_power_up = "low";
defparam \tridata[1]~I .oe_register_mode = "none";
defparam \tridata[1]~I .oe_sync_reset = "none";
defparam \tridata[1]~I .operation_mode = "bidir";
defparam \tridata[1]~I .output_async_reset = "none";
defparam \tridata[1]~I .output_power_up = "low";
defparam \tridata[1]~I .output_register_mode = "none";
defparam \tridata[1]~I .output_sync_reset = "none";
defparam \tridata[1]~I .sim_dqs_delay_increment = 0;
defparam \tridata[1]~I .sim_dqs_intrinsic_delay = 0;
defparam \tridata[1]~I .sim_dqs_offset_increment = 0;

stratixii_io \tridata[2]~I (
	.datain(data[2]),
	.ddiodatain(gnd),
	.oe(enabledt),
	.outclk(gnd),
	.outclkena(vcc),
	.inclk(gnd),
	.inclkena(vcc),
	.areset(gnd),
	.sreset(gnd),
	.ddioinclk(gnd),
	.dqsupdateen(vcc),
	.linkin(gnd),
	.delayctrlin(6'b000000),
	.offsetctrlin(6'b000000),
	.terminationcontrol(14'b00000000000000),
	.combout(\tridata[2]~2 ),
	.regout(),
	.ddioregout(),
	.dqsbusout(),
	.linkout(),
	.padio(tridata[2]));
defparam \tridata[2]~I .ddio_mode = "none";
defparam \tridata[2]~I .ddioinclk_input = "negated_inclk";
defparam \tridata[2]~I .dqs_delay_buffer_mode = "none";
defparam \tridata[2]~I .dqs_out_mode = "none";
defparam \tridata[2]~I .inclk_input = "normal";
defparam \tridata[2]~I .input_async_reset = "none";
defparam \tridata[2]~I .input_power_up = "low";
defparam \tridata[2]~I .input_register_mode = "none";
defparam \tridata[2]~I .input_sync_reset = "none";
defparam \tridata[2]~I .oe_async_reset = "none";
defparam \tridata[2]~I .oe_power_up = "low";
defparam \tridata[2]~I .oe_register_mode = "none";
defparam \tridata[2]~I .oe_sync_reset = "none";
defparam \tridata[2]~I .operation_mode = "bidir";
defparam \tridata[2]~I .output_async_reset = "none";
defparam \tridata[2]~I .output_power_up = "low";
defparam \tridata[2]~I .output_register_mode = "none";
defparam \tridata[2]~I .output_sync_reset = "none";
defparam \tridata[2]~I .sim_dqs_delay_increment = 0;
defparam \tridata[2]~I .sim_dqs_intrinsic_delay = 0;
defparam \tridata[2]~I .sim_dqs_offset_increment = 0;

stratixii_io \tridata[3]~I (
	.datain(data[3]),
	.ddiodatain(gnd),
	.oe(enabledt),
	.outclk(gnd),
	.outclkena(vcc),
	.inclk(gnd),
	.inclkena(vcc),
	.areset(gnd),
	.sreset(gnd),
	.ddioinclk(gnd),
	.dqsupdateen(vcc),
	.linkin(gnd),
	.delayctrlin(6'b000000),
	.offsetctrlin(6'b000000),
	.terminationcontrol(14'b00000000000000),
	.combout(\tridata[3]~3 ),
	.regout(),
	.ddioregout(),
	.dqsbusout(),
	.linkout(),
	.padio(tridata[3]));
defparam \tridata[3]~I .ddio_mode = "none";
defparam \tridata[3]~I .ddioinclk_input = "negated_inclk";
defparam \tridata[3]~I .dqs_delay_buffer_mode = "none";
defparam \tridata[3]~I .dqs_out_mode = "none";
defparam \tridata[3]~I .inclk_input = "normal";
defparam \tridata[3]~I .input_async_reset = "none";
defparam \tridata[3]~I .input_power_up = "low";
defparam \tridata[3]~I .input_register_mode = "none";
defparam \tridata[3]~I .input_sync_reset = "none";
defparam \tridata[3]~I .oe_async_reset = "none";
defparam \tridata[3]~I .oe_power_up = "low";
defparam \tridata[3]~I .oe_register_mode = "none";
defparam \tridata[3]~I .oe_sync_reset = "none";
defparam \tridata[3]~I .operation_mode = "bidir";
defparam \tridata[3]~I .output_async_reset = "none";
defparam \tridata[3]~I .output_power_up = "low";
defparam \tridata[3]~I .output_register_mode = "none";
defparam \tridata[3]~I .output_sync_reset = "none";
defparam \tridata[3]~I .sim_dqs_delay_increment = 0;
defparam \tridata[3]~I .sim_dqs_intrinsic_delay = 0;
defparam \tridata[3]~I .sim_dqs_offset_increment = 0;

stratixii_io \result[0]~I (
	.datain(\tridata[0]~0 ),
	.ddiodatain(gnd),
	.oe(enabletr),
	.outclk(gnd),
	.outclkena(vcc),
	.inclk(gnd),
	.inclkena(vcc),
	.areset(gnd),
	.sreset(gnd),
	.ddioinclk(gnd),
	.dqsupdateen(vcc),
	.linkin(gnd),
	.delayctrlin(6'b000000),
	.offsetctrlin(6'b000000),
	.terminationcontrol(14'b00000000000000),
	.combout(),
	.regout(),
	.ddioregout(),
	.dqsbusout(),
	.linkout(),
	.padio(result[0]));
defparam \result[0]~I .ddio_mode = "none";
defparam \result[0]~I .ddioinclk_input = "negated_inclk";
defparam \result[0]~I .dqs_delay_buffer_mode = "none";
defparam \result[0]~I .dqs_out_mode = "none";
defparam \result[0]~I .inclk_input = "normal";
defparam \result[0]~I .input_async_reset = "none";
defparam \result[0]~I .input_power_up = "low";
defparam \result[0]~I .input_register_mode = "none";
defparam \result[0]~I .input_sync_reset = "none";
defparam \result[0]~I .oe_async_reset = "none";
defparam \result[0]~I .oe_power_up = "low";
defparam \result[0]~I .oe_register_mode = "none";
defparam \result[0]~I .oe_sync_reset = "none";
defparam \result[0]~I .operation_mode = "output";
defparam \result[0]~I .output_async_reset = "none";
defparam \result[0]~I .output_power_up = "low";
defparam \result[0]~I .output_register_mode = "none";
defparam \result[0]~I .output_sync_reset = "none";
defparam \result[0]~I .sim_dqs_delay_increment = 0;
defparam \result[0]~I .sim_dqs_intrinsic_delay = 0;
defparam \result[0]~I .sim_dqs_offset_increment = 0;

stratixii_io \result[1]~I (
	.datain(\tridata[1]~1 ),
	.ddiodatain(gnd),
	.oe(enabletr),
	.outclk(gnd),
	.outclkena(vcc),
	.inclk(gnd),
	.inclkena(vcc),
	.areset(gnd),
	.sreset(gnd),
	.ddioinclk(gnd),
	.dqsupdateen(vcc),
	.linkin(gnd),
	.delayctrlin(6'b000000),
	.offsetctrlin(6'b000000),
	.terminationcontrol(14'b00000000000000),
	.combout(),
	.regout(),
	.ddioregout(),
	.dqsbusout(),
	.linkout(),
	.padio(result[1]));
defparam \result[1]~I .ddio_mode = "none";
defparam \result[1]~I .ddioinclk_input = "negated_inclk";
defparam \result[1]~I .dqs_delay_buffer_mode = "none";
defparam \result[1]~I .dqs_out_mode = "none";
defparam \result[1]~I .inclk_input = "normal";
defparam \result[1]~I .input_async_reset = "none";
defparam \result[1]~I .input_power_up = "low";
defparam \result[1]~I .input_register_mode = "none";
defparam \result[1]~I .input_sync_reset = "none";
defparam \result[1]~I .oe_async_reset = "none";
defparam \result[1]~I .oe_power_up = "low";
defparam \result[1]~I .oe_register_mode = "none";
defparam \result[1]~I .oe_sync_reset = "none";
defparam \result[1]~I .operation_mode = "output";
defparam \result[1]~I .output_async_reset = "none";
defparam \result[1]~I .output_power_up = "low";
defparam \result[1]~I .output_register_mode = "none";
defparam \result[1]~I .output_sync_reset = "none";
defparam \result[1]~I .sim_dqs_delay_increment = 0;
defparam \result[1]~I .sim_dqs_intrinsic_delay = 0;
defparam \result[1]~I .sim_dqs_offset_increment = 0;

stratixii_io \result[2]~I (
	.datain(\tridata[2]~2 ),
	.ddiodatain(gnd),
	.oe(enabletr),
	.outclk(gnd),
	.outclkena(vcc),
	.inclk(gnd),
	.inclkena(vcc),
	.areset(gnd),
	.sreset(gnd),
	.ddioinclk(gnd),
	.dqsupdateen(vcc),
	.linkin(gnd),
	.delayctrlin(6'b000000),
	.offsetctrlin(6'b000000),
	.terminationcontrol(14'b00000000000000),
	.combout(),
	.regout(),
	.ddioregout(),
	.dqsbusout(),
	.linkout(),
	.padio(result[2]));
defparam \result[2]~I .ddio_mode = "none";
defparam \result[2]~I .ddioinclk_input = "negated_inclk";
defparam \result[2]~I .dqs_delay_buffer_mode = "none";
defparam \result[2]~I .dqs_out_mode = "none";
defparam \result[2]~I .inclk_input = "normal";
defparam \result[2]~I .input_async_reset = "none";
defparam \result[2]~I .input_power_up = "low";
defparam \result[2]~I .input_register_mode = "none";
defparam \result[2]~I .input_sync_reset = "none";
defparam \result[2]~I .oe_async_reset = "none";
defparam \result[2]~I .oe_power_up = "low";
defparam \result[2]~I .oe_register_mode = "none";
defparam \result[2]~I .oe_sync_reset = "none";
defparam \result[2]~I .operation_mode = "output";
defparam \result[2]~I .output_async_reset = "none";
defparam \result[2]~I .output_power_up = "low";
defparam \result[2]~I .output_register_mode = "none";
defparam \result[2]~I .output_sync_reset = "none";
defparam \result[2]~I .sim_dqs_delay_increment = 0;
defparam \result[2]~I .sim_dqs_intrinsic_delay = 0;
defparam \result[2]~I .sim_dqs_offset_increment = 0;

stratixii_io \result[3]~I (
	.datain(\tridata[3]~3 ),
	.ddiodatain(gnd),
	.oe(enabletr),
	.outclk(gnd),
	.outclkena(vcc),
	.inclk(gnd),
	.inclkena(vcc),
	.areset(gnd),
	.sreset(gnd),
	.ddioinclk(gnd),
	.dqsupdateen(vcc),
	.linkin(gnd),
	.delayctrlin(6'b000000),
	.offsetctrlin(6'b000000),
	.terminationcontrol(14'b00000000000000),
	.combout(),
	.regout(),
	.ddioregout(),
	.dqsbusout(),
	.linkout(),
	.padio(result[3]));
defparam \result[3]~I .ddio_mode = "none";
defparam \result[3]~I .ddioinclk_input = "negated_inclk";
defparam \result[3]~I .dqs_delay_buffer_mode = "none";
defparam \result[3]~I .dqs_out_mode = "none";
defparam \result[3]~I .inclk_input = "normal";
defparam \result[3]~I .input_async_reset = "none";
defparam \result[3]~I .input_power_up = "low";
defparam \result[3]~I .input_register_mode = "none";
defparam \result[3]~I .input_sync_reset = "none";
defparam \result[3]~I .oe_async_reset = "none";
defparam \result[3]~I .oe_power_up = "low";
defparam \result[3]~I .oe_register_mode = "none";
defparam \result[3]~I .oe_sync_reset = "none";
defparam \result[3]~I .operation_mode = "output";
defparam \result[3]~I .output_async_reset = "none";
defparam \result[3]~I .output_power_up = "low";
defparam \result[3]~I .output_register_mode = "none";
defparam \result[3]~I .output_sync_reset = "none";
defparam \result[3]~I .sim_dqs_delay_increment = 0;
defparam \result[3]~I .sim_dqs_intrinsic_delay = 0;
defparam \result[3]~I .sim_dqs_offset_increment = 0;

endmodule
