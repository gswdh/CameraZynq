
`timescale 1 ns / 1 ps

	module spi_dma_v1_0 #
	(
		// Users to add parameters here

		// User parameters ends
		// Do not modify the parameters beyond this line


		// Parameters of Axi Slave Bus Interface CONTROL
		parameter integer C_CONTROL_DATA_WIDTH	= 32,
		parameter integer C_CONTROL_ADDR_WIDTH	= 6,

		// Parameters of Axi Slave Bus Interface DATA
		parameter integer C_DATA_TDATA_WIDTH	= 32
	)
	(
		// Users to add ports here

		// User ports ends
		// Do not modify the ports beyond this line


		// Ports of Axi Slave Bus Interface CONTROL
		input wire  control_aclk,
		input wire  control_aresetn,
		input wire [C_CONTROL_ADDR_WIDTH-1 : 0] control_awaddr,
		input wire [2 : 0] control_awprot,
		input wire  control_awvalid,
		output wire  control_awready,
		input wire [C_CONTROL_DATA_WIDTH-1 : 0] control_wdata,
		input wire [(C_CONTROL_DATA_WIDTH/8)-1 : 0] control_wstrb,
		input wire  control_wvalid,
		output wire  control_wready,
		output wire [1 : 0] control_bresp,
		output wire  control_bvalid,
		input wire  control_bready,
		input wire [C_CONTROL_ADDR_WIDTH-1 : 0] control_araddr,
		input wire [2 : 0] control_arprot,
		input wire  control_arvalid,
		output wire  control_arready,
		output wire [C_CONTROL_DATA_WIDTH-1 : 0] control_rdata,
		output wire [1 : 0] control_rresp,
		output wire  control_rvalid,
		input wire  control_rready,

		// Ports of Axi Slave Bus Interface DATA
		input wire  data_aclk,
		input wire  data_aresetn,
		output wire  data_tready,
		input wire [C_DATA_TDATA_WIDTH-1 : 0] data_tdata,
		input wire [(C_DATA_TDATA_WIDTH/8)-1 : 0] data_tstrb,
		input wire  data_tlast,
		input wire  data_tvalid

		// SPI IO
		output wire spi_clk, spi_ncs, spi_mosi,
		input wire spi_miso
	);
// Instantiation of Axi Bus Interface CONTROL
	spi_dma_v1_0_CONTROL # ( 
		.C_S_AXI_DATA_WIDTH(C_CONTROL_DATA_WIDTH),
		.C_S_AXI_ADDR_WIDTH(C_CONTROL_ADDR_WIDTH)
	) spi_dma_v1_0_CONTROL_inst (
		.S_AXI_ACLK(control_aclk),
		.S_AXI_ARESETN(control_aresetn),
		.S_AXI_AWADDR(control_awaddr),
		.S_AXI_AWPROT(control_awprot),
		.S_AXI_AWVALID(control_awvalid),
		.S_AXI_AWREADY(control_awready),
		.S_AXI_WDATA(control_wdata),
		.S_AXI_WSTRB(control_wstrb),
		.S_AXI_WVALID(control_wvalid),
		.S_AXI_WREADY(control_wready),
		.S_AXI_BRESP(control_bresp),
		.S_AXI_BVALID(control_bvalid),
		.S_AXI_BREADY(control_bready),
		.S_AXI_ARADDR(control_araddr),
		.S_AXI_ARPROT(control_arprot),
		.S_AXI_ARVALID(control_arvalid),
		.S_AXI_ARREADY(control_arready),
		.S_AXI_RDATA(control_rdata),
		.S_AXI_RRESP(control_rresp),
		.S_AXI_RVALID(control_rvalid),
		.S_AXI_RREADY(control_rready)
	);

// Instantiation of Axi Bus Interface DATA
	spi_dma_v1_0_DATA # ( 
		.C_S_AXIS_TDATA_WIDTH(C_DATA_TDATA_WIDTH)
	) spi_dma_v1_0_DATA_inst (
		.S_AXIS_ACLK(data_aclk),
		.S_AXIS_ARESETN(data_aresetn),
		.S_AXIS_TREADY(data_tready),
		.S_AXIS_TDATA(data_tdata),
		.S_AXIS_TSTRB(data_tstrb),
		.S_AXIS_TLAST(data_tlast),
		.S_AXIS_TVALID(data_tvalid)
	);

	// Add user logic here

	// User logic ends

	endmodule
