#include "usb.h"

#include "xparameters.h" /* XPAR parameters */
#include "xusbps.h"      /* USB controller driver */
#include "xil_printf.h"  /* USB controller driver */
#include "xscugic.h"
#include "xinterrupt_wrap.h"
#include "xil_cache.h"

static XScuGic IntcInstance; /* The instance of the IRQ Controller */
static XUsbPs usb_instance;  /* The instance of the USB Controller */
static XUsbPs_DeviceConfig dev_config;

#define MEMORY_SIZE (64 * 1024)

u8 buffer[MEMORY_SIZE] = {0};

static volatile int NumIrqs = 0;

static void UsbIntrHandler(void *CallBackRef, u32 Mask)
{
    NumIrqs++;
}

static void XUsbPs_Ep0EventHandler(void *CallBackRef, u8 EpNum,
                                   u8 EventType, void *Data)
{
    XUsbPs *InstancePtr;
    int Status;
    XUsbPs_SetupData SetupData;
    u8 *BufferPtr;
    u32 BufferLen;
    u32 Handle;

    Xil_AssertVoid(NULL != CallBackRef);

    InstancePtr = (XUsbPs *)CallBackRef;

    switch (EventType)
    {

    /* Handle the Setup Packets received on Endpoint 0. */
    case XUSBPS_EP_EVENT_SETUP_DATA_RECEIVED:
        Status = XUsbPs_EpGetSetupData(InstancePtr, EpNum, &SetupData);
        if (XST_SUCCESS == Status)
        {
            // /* Handle the setup packet. */
            // (int)XUsbPs_Ch9HandleSetupPacket(InstancePtr,
            //                                  &SetupData);
        }
        break;

    /* We get data RX events for 0 length packets on endpoint 0. We receive
     * and immediately release them again here, but there's no action to be
     * taken.
     */
    case XUSBPS_EP_EVENT_DATA_RX:
        /* Get the data buffer. */
        Status = XUsbPs_EpBufferReceive(InstancePtr, EpNum,
                                        &BufferPtr, &BufferLen, &Handle);
        if (XST_SUCCESS == Status)
        {
            /* Return the buffer. */
            XUsbPs_EpBufferRelease(Handle);
        }
        break;

    default:
        /* Unhandled event. Ignore. */
        break;
    }
}

static void XUsbPs_Ep1EventHandler(void *CallBackRef, u8 EpNum,
                                   u8 EventType, void *Data)
{
    XUsbPs *InstancePtr;
    int Status;
    u8 *BufferPtr;
    u32 BufferLen;
    u32 InavalidateLen;
    u32 Handle;

    Xil_AssertVoid(NULL != CallBackRef);

    InstancePtr = (XUsbPs *)CallBackRef;

    switch (EventType)
    {
    case XUSBPS_EP_EVENT_DATA_RX:
        /* Get the data buffer.*/
        Status = XUsbPs_EpBufferReceive(InstancePtr, EpNum,
                                        &BufferPtr, &BufferLen, &Handle);
        /* Invalidate the Buffer Pointer */
        InavalidateLen = BufferLen;
        if (BufferLen % 32)
        {
            InavalidateLen = (BufferLen / 32) * 32 + 32;
        }

        Xil_DCacheInvalidateRange((unsigned int)BufferPtr,
                                  InavalidateLen);
        if (XST_SUCCESS == Status)
        {
            // /* Handle the storage class request. */
            // XUsbPs_HandleStorageReq(InstancePtr, EpNum,
            //                         BufferPtr, BufferLen);
            /* Release the buffer. */
            XUsbPs_EpBufferRelease(Handle);
        }
        break;

    default:
        /* Unhandled event. Ignore. */
        break;
    }
}

void usb_init()
{
    XUsbPs_Config *usb_config = XUsbPs_LookupConfig(XPAR_XUSBPS_0_BASEADDR);

    // Init the USB peripheral
    int status = XUsbPs_CfgInitialize(&usb_instance,
                                      usb_config,
                                      usb_config->BaseAddress);

    // Start the interrupts
    status = XSetupInterruptSystem(&usb_instance, &XUsbPs_IntrHandler,
                                   usb_config->IntrId,
                                   usb_config->IntrParent,
                                   XINTERRUPT_DEFAULT_PRIORITY);

    /*
     * For this example we only configure Endpoint 0 and Endpoint 1.
     *
     * Bufsize = 0 indicates that there is no buffer allocated for OUT
     * (receive) endpoint 0. Endpoint 0 is a control endpoint and we only
     * receive control packets on that endpoint. Control packets are 8
     * bytes in size and are received into the Queue Head's Setup Buffer.
     * Therefore, no additional buffer space is needed.
     */
    dev_config.EpCfg[0].Out.Type = XUSBPS_EP_TYPE_CONTROL;
    dev_config.EpCfg[0].Out.NumBufs = 2;
    dev_config.EpCfg[0].Out.BufSize = 64;
    dev_config.EpCfg[0].Out.MaxPacketSize = 64;
    dev_config.EpCfg[0].In.Type = XUSBPS_EP_TYPE_CONTROL;
    dev_config.EpCfg[0].In.NumBufs = 2;
    dev_config.EpCfg[0].In.MaxPacketSize = 64;

    dev_config.EpCfg[1].Out.Type = XUSBPS_EP_TYPE_BULK;
    dev_config.EpCfg[1].Out.NumBufs = 16;
    dev_config.EpCfg[1].Out.BufSize = 512;
    dev_config.EpCfg[1].Out.MaxPacketSize = 512;
    dev_config.EpCfg[1].In.Type = XUSBPS_EP_TYPE_BULK;
    dev_config.EpCfg[1].In.NumBufs = 16;
    dev_config.EpCfg[1].In.MaxPacketSize = 512;

    dev_config.NumEndpoints = 2;

    Xil_DCacheFlushRange((unsigned int)buffer, MEMORY_SIZE);

    /* Finish the configuration of the dev_config structure and configure
     * the DEVICE side of the controller.
     */
    dev_config.DMAMemPhys = (u32)buffer;

    status = XUsbPs_ConfigureDevice(&usb_instance, &dev_config);

    status = XUsbPs_IntrSetHandler(&usb_instance, UsbIntrHandler, NULL,
                                   XUSBPS_IXR_UE_MASK);

    status = XUsbPs_EpSetHandler(&usb_instance, 0,
                                 XUSBPS_EP_DIRECTION_OUT,
                                 XUsbPs_Ep0EventHandler, &usb_instance);

    status = XUsbPs_EpSetHandler(&usb_instance, 1,
                                 XUSBPS_EP_DIRECTION_OUT,
                                 XUsbPs_Ep1EventHandler, &usb_instance);

    XUsbPs_IntrEnable(&usb_instance, XUSBPS_IXR_UR_MASK |
                                         XUSBPS_IXR_UI_MASK);

    XUsbPs_Start(&usb_instance);
}