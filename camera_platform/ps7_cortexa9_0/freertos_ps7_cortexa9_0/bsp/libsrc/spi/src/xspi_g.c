#include "xspi.h"

XSpi_Config XSpi_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,axi-quad-spi-3.2", /* compatible */
		0x41e00000, /* reg */
		0x0, /* xlnx,hasfifos */
		0x0, /* xlnx,slaveonly */
		0x1, /* xlnx,num-ss-bits */
		0x8, /* bits-per-word */
		0x0, /* xlnx,spi-mode */
		0x0, /* xlnx,axi-interface */
		0x0, /* xlnx,Axi4-address */
		0x0, /* xlnx,xip-mode */
		0x0, /* xlnx,startup-block */
		0x0, /* fifo-size */
		0x101f, /* interrupts */
		0xf8f01000 /* interrupt-parent */
	},
	{
		"xlnx,axi-quad-spi-3.2", /* compatible */
		0x41e10000, /* reg */
		0x0, /* xlnx,hasfifos */
		0x0, /* xlnx,slaveonly */
		0x1, /* xlnx,num-ss-bits */
		0x8, /* bits-per-word */
		0x0, /* xlnx,spi-mode */
		0x0, /* xlnx,axi-interface */
		0x0, /* xlnx,Axi4-address */
		0x0, /* xlnx,xip-mode */
		0x0, /* xlnx,startup-block */
		0x0, /* fifo-size */
		0x1020, /* interrupts */
		0xf8f01000 /* interrupt-parent */
	},
	 {
		 NULL
	}
};