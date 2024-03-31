
#include <stdio.h>
#include "xparameters.h"
#include "xil_printf.h"

#include "xuartps.h"
#include "uartps_header.h"

#include "xdmaps.h"
#include "dmaps_header.h"

#include "xscuwdt.h"
#include "scuwdt_header.h"

#include "xqspips.h"
#include "qspips_header.h"

#include "xuartlite.h"
#include "uartlite_header.h"

#include "xgpio.h"
#include "gpio_header.h"

#include "xscutimer.h"
#include "scutimer_header.h"
int main ()
{

    static XUartPs uart0;
    static XDmaPs dmac_s;
    static XScuWdt scuwdt;
    static XQspiPs qspi;
    static XUartLite axi_uartlite_0;
    static XGpio axi_gpio_0;
    static XScuTimer scutimer;

    print("---Entering main---\n\r");

    {
        int status;
        print("\r\nRunning UartPsPolledExample for uart0 ... \r\n");
        status = UartPsPolledExample(&uart0, XPAR_UART0_BASEADDR);
        if (status == 0) {
            print("UartPsPolledExample PASSED \r\n");
        } else {
            print("UartPsPolledExample FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning UartPsIntrExample for uart0 ... \r\n");
        status = UartPsIntrExample(&uart0, XPAR_UART0_BASEADDR);
        if (status == 0) {
            print("UartPsIntrExample PASSED \r\n");
        } else {
            print("UartPsIntrExample FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning XDmaPs_Example_W_Intr for dmac_s ... \r\n");
        status = XDmaPs_Example_W_Intr(&dmac_s, XPAR_DMAC_S_BASEADDR);
        if (status == 0) {
            print("XDmaPs_Example_W_Intr PASSED \r\n");
        } else {
            print("XDmaPs_Example_W_Intr FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning ScuWdtIntrExample for scuwdt ... \r\n");
        status = ScuWdtIntrExample(&scuwdt, XPAR_SCUWDT_BASEADDR);
        if (status == 0) {
            print("ScuWdtIntrExample PASSED \r\n");
        } else {
            print("ScuWdtIntrExample FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning ScuWdtPolledExample for scuwdt ... \r\n");
        status = ScuWdtPolledExample(&scuwdt, XPAR_SCUWDT_BASEADDR);
        if (status == 0) {
            print("ScuWdtPolledExample PASSED \r\n");
        } else {
            print("ScuWdtPolledExample FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning QspiPsSelfTestExample for qspi ... \r\n");
        status = QspiPsSelfTestExample(XPAR_QSPI_BASEADDR);
        if (status == 0) {
            print("QspiPsSelfTestExample PASSED \r\n");
        } else {
            print("QspiPsSelfTestExample FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning UartLiteSelfTestExample for axi_uartlite_0 ... \r\n");
        status = UartLiteSelfTestExample(XPAR_AXI_UARTLITE_0_BASEADDR);
        if (status == 0) {
            print("UartLiteSelfTestExample PASSED \r\n");
        } else {
            print("UartLiteSelfTestExample FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning GpioOutputExample for axi_gpio_0 ... \r\n");
        status = GpioOutputExample(&axi_gpio_0, XPAR_AXI_GPIO_0_BASEADDR);
        if (status == 0) {
            print("GpioOutputExample PASSED \r\n");
        } else {
            print("GpioOutputExample FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning ScuTimerPolledExample for scutimer ... \r\n");
        status = ScuTimerPolledExample(&scutimer, XPAR_SCUTIMER_BASEADDR);
        if (status == 0) {
            print("ScuTimerPolledExample PASSED \r\n");
        } else {
            print("ScuTimerPolledExample FAILED \r\n");
        }
    }

    {
        int status;
        print("\r\nRunning ScuTimerIntrExample for scutimer ... \r\n");
        status = ScuTimerIntrExample(&scutimer, XPAR_SCUTIMER_BASEADDR);
        if (status == 0) {
            print("ScuTimerIntrExample PASSED \r\n");
        } else {
            print("ScuTimerIntrExample FAILED \r\n");
        }
    }

    print("---Exiting main---");
    return 0;
}
