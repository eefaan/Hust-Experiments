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

(* X_CORE_INFO = "m14k_top_wrap,Vivado 2015.2" *)
(* CHECK_LICENSE_TYPE = "MIPSfpga_system_MIPS_MicroAptiv_UP_0_0,m14k_top_wrap,{}" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module MIPSfpga_system_MIPS_MicroAptiv_UP_0_0 (
  SI_ClkIn,
  SI_Reset,
  SI_ColdReset,
  SI_Int,
  HCLK,
  HRESETn,
  HRDATA,
  HREADY,
  HRESP,
  HADDR,
  HBURST,
  HPROT,
  HMASTLOCK,
  HSIZE,
  HTRANS,
  HWRITE,
  HWDATA,
  EJ_TCK,
  EJ_TDO,
  EJ_TDI,
  EJ_TMS,
  EJ_TRST_N,
  EJ_DINT
);

input wire SI_ClkIn;
input wire SI_Reset;
input wire SI_ColdReset;
input wire [7 : 0] SI_Int;
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 HCLK CLK" *)
output wire HCLK;
output wire HRESETn;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HRDATA" *)
input wire [31 : 0] HRDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HREADY" *)
input wire HREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HRESP" *)
input wire HRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HADDR" *)
output wire [31 : 0] HADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HBURST" *)
output wire [2 : 0] HBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HPROT" *)
output wire [3 : 0] HPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HMASTLOCK" *)
output wire HMASTLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HSIZE" *)
output wire [2 : 0] HSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HTRANS" *)
output wire [1 : 0] HTRANS;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HWRITE" *)
output wire HWRITE;
(* X_INTERFACE_INFO = "xilinx.com:interface:ahblite:2.0 ahblite HWDATA" *)
output wire [31 : 0] HWDATA;
input wire EJ_TCK;
output wire EJ_TDO;
input wire EJ_TDI;
input wire EJ_TMS;
input wire EJ_TRST_N;
input wire EJ_DINT;

  m14k_top_wrap inst (
    .SI_ClkIn(SI_ClkIn),
    .SI_Reset(SI_Reset),
    .SI_ColdReset(SI_ColdReset),
    .SI_Int(SI_Int),
    .HCLK(HCLK),
    .HRESETn(HRESETn),
    .HRDATA(HRDATA),
    .HREADY(HREADY),
    .HRESP(HRESP),
    .HADDR(HADDR),
    .HBURST(HBURST),
    .HPROT(HPROT),
    .HMASTLOCK(HMASTLOCK),
    .HSIZE(HSIZE),
    .HTRANS(HTRANS),
    .HWRITE(HWRITE),
    .HWDATA(HWDATA),
    .EJ_TCK(EJ_TCK),
    .EJ_TDO(EJ_TDO),
    .EJ_TDI(EJ_TDI),
    .EJ_TMS(EJ_TMS),
    .EJ_TRST_N(EJ_TRST_N),
    .EJ_DINT(EJ_DINT)
  );
endmodule
