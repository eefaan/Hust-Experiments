// (c) Copyright 1995-2017 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.

// IP VLNV: imgtec.org:user:MIPS_MicroAptiv_UP:1.3.1
// IP Revision: 4

// The following must be inserted into your Verilog file for this
// core to be instantiated. Change the instance name and port connections
// (in parentheses) to your own signal names.

//----------- Begin Cut here for INSTANTIATION Template ---// INST_TAG
MIPSfpga_system_MIPS_MicroAptiv_UP_0_0 your_instance_name (
  .SI_ClkIn(SI_ClkIn),          // input wire SI_ClkIn
  .SI_Reset(SI_Reset),          // input wire SI_Reset
  .SI_ColdReset(SI_ColdReset),  // input wire SI_ColdReset
  .SI_Int(SI_Int),              // input wire [7 : 0] SI_Int
  .HCLK(HCLK),                  // output wire HCLK
  .HRESETn(HRESETn),            // output wire HRESETn
  .HRDATA(HRDATA),              // input wire [31 : 0] HRDATA
  .HREADY(HREADY),              // input wire HREADY
  .HRESP(HRESP),                // input wire HRESP
  .HADDR(HADDR),                // output wire [31 : 0] HADDR
  .HBURST(HBURST),              // output wire [2 : 0] HBURST
  .HPROT(HPROT),                // output wire [3 : 0] HPROT
  .HMASTLOCK(HMASTLOCK),        // output wire HMASTLOCK
  .HSIZE(HSIZE),                // output wire [2 : 0] HSIZE
  .HTRANS(HTRANS),              // output wire [1 : 0] HTRANS
  .HWRITE(HWRITE),              // output wire HWRITE
  .HWDATA(HWDATA),              // output wire [31 : 0] HWDATA
  .EJ_TCK(EJ_TCK),              // input wire EJ_TCK
  .EJ_TDO(EJ_TDO),              // output wire EJ_TDO
  .EJ_TDI(EJ_TDI),              // input wire EJ_TDI
  .EJ_TMS(EJ_TMS),              // input wire EJ_TMS
  .EJ_TRST_N(EJ_TRST_N),        // input wire EJ_TRST_N
  .EJ_DINT(EJ_DINT)            // input wire EJ_DINT
);
// INST_TAG_END ------ End INSTANTIATION Template ---------

