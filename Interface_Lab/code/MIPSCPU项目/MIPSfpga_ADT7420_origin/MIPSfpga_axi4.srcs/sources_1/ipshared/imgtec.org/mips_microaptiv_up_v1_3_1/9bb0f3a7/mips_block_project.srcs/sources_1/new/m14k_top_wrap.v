// m14k_top_wrap.v

// This module is wrapper around m14k_top rtl. It instantiates m14k_top. Initilizes the static signals.
// Only clock-reset, EJTAG and AHB-Lite interfaces are brought out.

`include "m14k_const.vh"

module m14k_top_wrap (

  // Clocks and resets
  input           SI_ClkIn,	      // clock input
  input           SI_Reset,       // greset (Active high)
  input           SI_ColdReset,   // Cold greset (Active high)
  input  [7:0]    SI_Int,         // Ext. Interrupt pin

  // AHB lite interface
  output          HCLK,
  output          HRESETn,

  input  [31:0]   HRDATA,
  input           HREADY,
  input           HRESP,
  output [31:0]   HADDR,
  output [2:0]    HBURST,

  output [3:0]    HPROT,
  output          HMASTLOCK,
  output [2:0]    HSIZE,
  output [1:0]    HTRANS,

  output          HWRITE,
  output [31:0]   HWDATA,

  // EJTAG external interface
  input           EJ_TCK,
  output          EJ_TDO,
  input           EJ_TDI,
  input           EJ_TMS,
  input           EJ_TRST_N,
  input           EJ_DINT
);

 wire                                   SI_Endian;
 wire                                   SI_NMI;
 wire [1:0]                             SI_MergeMode;       // SI_MergeMode[0] not used in this design
 wire [9:0]	                            SI_CPUNum;          // EBase CPU number
 wire [2:0]	                            SI_IPTI;            // TimerInt connection
 wire   	                            SI_EICPresent;      // External Interrupt cpntroller present
 wire [5:0]	                            SI_EICVector;       // Vector number for EIC interrupt
 wire [17:1]	                        SI_Offset;
 wire [3:0]	                            SI_EISS;            // Shadow set, comes with the requested interrupt
 wire                                   SI_BootExcISAMode;
 wire [3:0]                             SI_SRSDisable;      // Disable banks of shadow sets
 wire                                   SI_TraceDisable;    // Disables trace hardware
 wire                                   SI_ClkOut;          // External bus reference clock
 wire                                   SI_ERL;             // Error level pin
 wire                                   SI_EXL;             // Exception level pin
 wire                                   SI_NMITaken;        // NMI pinned out
 wire                                   SI_NESTERL;         // nested error level pinned out
 wire                                   SI_NESTEXL;         // nested exception level pinned out
 wire                                   SI_RP;              // Reduce power pin
 wire                                   SI_Sleep;           // Processor is in sleep mode
 wire                                   SI_TimerInt;        // count==compare interrupt
 wire [1:0]	                            SI_SWInt;           // Software interrupt requests to external interrupt controller
 wire                                   SI_IAck;            // Interrupt Acknowledge
 wire [7:0]                             SI_IPL;             // Current IPL, contains information of which int SI_IACK ack.
 wire [5:0] 	                        SI_IVN;             // Cuurent IVN, contains information of which int SI_IAck ack.
 wire [17:1] 	                        SI_ION;             // Cuurent ION, contains information of which int SI_IAck ack.
 wire [7:0]                             SI_Ibs;             // Instruction break status
 wire [3:0]                             SI_Dbs;             // Data break status

 wire                                   PM_InstnComplete;

 wire        	                        gscanmode;
 wire        	                        gscanenable;
 wire [`M14K_NUM_SCAN_CHAIN-1:0]        gscanin;
 wire [`M14K_NUM_SCAN_CHAIN-1:0]        gscanout;
 wire                                   gscanramwr;

 wire                                   gmbinvoke;
 wire                                   gmbdone;           // Asserted to indicate that all mem-BIST test is done
 wire                                   gmbddfail;  	   // Asserted to indicate that D$ date test failed
 wire                                   gmbtdfail;  	   // Asserted to indicate that D$ tag test failed
 wire                                   gmbwdfail;  	   // Asserted to indicate that D$ WS test failed
 wire                                   gmbspfail;  	   // Asserted to indicate that D$ date test failed
 wire                                   gmbdifail;  	   // Asserted to indicate that I$ date test failed
 wire                                   gmbtifail;  	   // Asserted to indicate that I$tag test failed
 wire                                   gmbwifail;  	   // Asserted to indicate that I$WS test failed
 wire                                   gmbispfail;  	   // Asserted to indicate that D$ date test failed

 wire [7:0]	                            gmb_ic_algorithm;  // Alogrithm selection for I$ BIST controller.
 wire [7:0]	                            gmb_dc_algorithm;  // Alogrithm selection for D$ BIST controller.
 wire [7:0]	                            gmb_isp_algorithm; // Alogrithm selection for ISPRAM BIST controller.
 wire [7:0]	                            gmb_sp_algorithm;  // Alogrithm selection for DSPRAM BIST controller.

 wire [`M14K_TOP_BIST_IN-1:0]	        BistIn;
 wire [`M14K_TOP_BIST_OUT-1:0]          BistOut;

 wire                                   EJ_TDOzstate;
 wire                                   EJ_ECREjtagBrk;
 wire [10:0] 	                        EJ_ManufID;
 wire [15:0] 	                        EJ_PartNumber;
 wire [3:0] 	                        EJ_Version;
 wire   	                            EJ_DINTsup;
 wire   	                            EJ_DisableProbeDebug;
 wire                                   EJ_PerRst;
 wire                                   EJ_PrRst;
 wire                                   EJ_SRstE;
 wire                                   EJ_DebugM;     // Indication that we are in debug mode

 wire [2:0]	                            TC_ClockRatio; // User's clock ratio selection.
 wire                                   TC_Valid;      // Data valid indicator.  Not used in this design.
 wire [63:0]	                        TC_Data;       // Data from TCB.
 wire                                   TC_Stall;      // Stall request.  Not used in this design.
 wire                                   TC_PibPresent; // PIB is present

 wire [`M14K_UDI_EXT_TOUDI_WIDTH-1:0]   UDI_toudi;     // External input to UDI module
 wire [`M14K_UDI_EXT_FROMUDI_WIDTH-1:0] UDI_fromudi;   // Output from UDI module to external system
 wire [`M14K_CP2_EXT_TOCP2_WIDTH-1:0]   CP2_tocp2;     // External input to COP2
 wire [`M14K_CP2_EXT_FROMCP2_WIDTH-1:0] CP2_fromcp2;   // External output from COP2
 wire [`M14K_ISP_EXT_TOISP_WIDTH-1:0]   ISP_toisp;     // External input ISPRAM
 wire [`M14K_ISP_EXT_FROMISP_WIDTH-1:0] ISP_fromisp;   // External output from ISPRAM
 wire [`M14K_DSP_EXT_TODSP_WIDTH-1:0]   DSP_todsp;     // External input DSPRAM
 wire [`M14K_DSP_EXT_FROMDSP_WIDTH-1:0] DSP_fromdsp;   // External output from DSPRAM
 wire [2:0]                             SI_IPFDCI;     // FDC connection
 wire                                   SI_FDCInt;     // FDC receive FIFO full interrupt
 wire [2:0]                             SI_IPPCI;      // PCI connection
 wire                                   SI_PCInt;      // PCI receive full interrupt

 reg                                    ej_trst_n_int;
 reg  [3:0]                             ej_rst_cnt;

// Tie off the m14k_top top other signals
 assign SI_NMI = 0;
 assign SI_EICPresent = 0;
 assign SI_EICVector = 0;
 assign SI_EISS = 0;
 assign SI_Offset = 0;
 assign SI_IPTI = 3'h7;	          // TimerInt connection
 assign SI_CPUNum = 0;	          // EBase CPU number
 assign SI_Endian = 0;	          // Base endianess: 1=big
 assign SI_MergeMode = 0;
 assign SI_SRSDisable = 4'b1111;  // Disable banks of shadow sets
 assign SI_TraceDisable = 1;      // Disables trace hardware
 assign SI_IPFDCI = 0;            // FDC connection
 assign SI_IPPCI = 0;             // PCI connection
 assign SI_AHBStb = 1;            //AHB: Signal indicating phase and frequency relationship between clk and hclk.
 assign SI_BootExcISAMode = 0;

 assign EJ_ManufID = 0;
 assign EJ_PartNumber = 0;
 assign EJ_Version = 0;
 assign EJ_DINTsup = 0;
 assign EJ_DisableProbeDebug = 0; // Must be 0 to enable EJTAG debug

 assign TC_Stall = 0;             // Stall request. Not used in this design.
 assign TC_PibPresent = 0;        // PIB is present

 assign gscanmode = 0;
 assign gscanenable = 0;
 assign gmbinvoke = 0;
 assign gscanramwr = 0;

 assign gmb_ic_algorithm = 0;
 assign gmb_dc_algorithm = 0;
 assign gmb_isp_algorithm = 0;
 assign gmb_sp_algorithm = 0;

 assign UDI_toudi = 0; // External input to UDI module
 assign CP2_tocp2 = 0; // External input to COP2
 assign ISP_toisp = 0; // External input ISPRAM
 assign DSP_todsp = 0; // External input DSPRAM

 // Hold the EJTAG in reset for 16 clock cycles
 always @(posedge SI_ClkIn, negedge EJ_TRST_N) 
 begin
   if(EJ_TRST_N == 1'b0)
       begin
         ej_trst_n_int <= 1'b0;
         ej_rst_cnt    <= 4'h0;
	   end
   else
       begin
         if(ej_rst_cnt == 4'hf)
             ej_trst_n_int <= 1'b1;

         if(ej_rst_cnt != 4'hf)
             ej_rst_cnt    <= ej_rst_cnt + 4'b1;
    end
 end // always@

 // Instantiate the MIPS m14k_top UP IP

 m14k_top m14k_top_i (
   .HRDATA               (HRDATA),
   .HREADY               (HREADY),
   .HRESP                (HRESP),
   .SI_AHBStb            (SI_AHBStb),
   .HCLK                 (HCLK),
   .HRESETn              (HRESETn),
   .HADDR                (HADDR),
   .HBURST               (HBURST),
   .HPROT                (HPROT),
   .HMASTLOCK            (HMASTLOCK),
   .HSIZE                (HSIZE),
   .HTRANS               (HTRANS),
   .HWRITE               (HWRITE),
   .HWDATA               (HWDATA),
   .SI_ClkIn             (SI_ClkIn),
   .SI_ColdReset         (SI_ColdReset),
   .SI_Endian            (SI_Endian),
   .SI_Int               (SI_Int),
   .SI_NMI               (SI_NMI),
   .SI_Reset             (SI_Reset),
   .SI_MergeMode         (SI_MergeMode),
   .SI_CPUNum            (SI_CPUNum),
   .SI_IPTI              (SI_IPTI),
   .SI_EICPresent        (SI_EICPresent),
   .SI_EICVector         (SI_EICVector),
   .SI_Offset            (SI_Offset),
   .SI_EISS              (SI_EISS),
   .SI_BootExcISAMode    (SI_BootExcISAMode),
   .SI_SRSDisable        (SI_SRSDisable),
   .SI_TraceDisable      (SI_TraceDisable),
   .SI_ClkOut            (SI_ClkOut),
   .SI_ERL               (SI_ERL),
   .SI_EXL               (SI_EXL),
   .SI_NMITaken          (SI_NMITaken),
   .SI_NESTERL           (SI_NESTERL),
   .SI_NESTEXL           (SI_NESTEXL),
   .SI_RP                (SI_RP),
   .SI_Sleep             (SI_Sleep),
   .SI_TimerInt          (SI_TimerInt),
   .SI_SWInt             (SI_SWInt),
   .SI_IAck              (SI_IAck),
   .SI_IPL               (SI_IPL),
   .SI_IVN               (SI_IVN),
   .SI_ION               (SI_ION),
   .SI_Ibs               (SI_Ibs),
   .SI_Dbs               (SI_Dbs),
   .PM_InstnComplete     (PM_InstnComplete),
   .gscanmode            (gscanmode),
   .gscanenable          (gscanenable),
   .gscanin              (gscanin),
   .gscanout             (gscanout),
   .gscanramwr           (gscanramwr),
   .gmbinvoke            (gmbinvoke),
   .gmbdone              (gmbdone),
   .gmbddfail            (gmbddfail),
   .gmbtdfail            (gmbtdfail),
   .gmbwdfail            (gmbwdfail),
   .gmbspfail            (gmbspfail),
   .gmbdifail            (gmbdifail),
   .gmbtifail            (gmbtifail),
   .gmbwifail            (gmbwifail),
   .gmbispfail           (gmbispfail),
   .gmb_ic_algorithm     (gmb_ic_algorithm),
   .gmb_dc_algorithm     (gmb_dc_algorithm),
   .gmb_isp_algorithm    (gmb_isp_algorithm),
   .gmb_sp_algorithm     (gmb_sp_algorithm),
   .BistIn               (BistIn),
   .BistOut              (BistOut),
   .EJ_TCK               (EJ_TCK),
   .EJ_TDO               (EJ_TDO),
   .EJ_TDI               (EJ_TDI),
   .EJ_TMS               (EJ_TMS),
   .EJ_TRST_N            (~SI_Reset), //ej_trst_n_int),
   .EJ_TDOzstate         (EJ_TDOzstate),
   .EJ_ECREjtagBrk       (EJ_ECREjtagBrk),
   .EJ_ManufID           (EJ_ManufID),
   .EJ_PartNumber        (EJ_PartNumber),
   .EJ_Version           (EJ_Version),
   .EJ_DINTsup           (EJ_DINTsup),
   .EJ_DINT              (EJ_DINT),
   .EJ_DisableProbeDebug (EJ_DisableProbeDebug),
   .EJ_PerRst            (EJ_PerRst),
   .EJ_PrRst             (EJ_PrRst),
   .EJ_SRstE             (EJ_SRstE),
   .EJ_DebugM            (EJ_DebugM),
   .TC_ClockRatio        (TC_ClockRatio),
   .TC_Valid             (TC_Valid),
   .TC_Data              (TC_Data),
   .TC_Stall             (TC_Stall),
   .TC_PibPresent        (TC_PibPresent),
   .UDI_toudi            (UDI_toudi),
   .UDI_fromudi          (UDI_fromudi),
   .CP2_tocp2            (CP2_tocp2),
   .CP2_fromcp2          (CP2_fromcp2),
   .ISP_toisp            (ISP_toisp),
   .ISP_fromisp          (ISP_fromisp),
   .DSP_todsp            (DSP_todsp),
   .DSP_fromdsp          (DSP_fromdsp),
   .SI_IPFDCI            (SI_IPFDCI),
   .SI_FDCInt            (SI_FDCInt),
   .SI_IPPCI             (SI_IPPCI),
   .SI_PCInt             (SI_PCInt)
 );

endmodule
