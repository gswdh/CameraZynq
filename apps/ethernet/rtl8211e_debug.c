#include "rtl8211e_debug.h"

#include "xil_printf.h"

void printBMCR(uint16_t reg)
{
    xil_printf("BMCR - Basic Mode Control Register (0x00)\r\n");
    xil_printf("Reset: %s\r\n", (reg & (1 << 15)) ? "PHY Reset" : "Normal operation");
    xil_printf("Loopback: %s\r\n", (reg & (1 << 14)) ? "Enabled" : "Disabled");
    xil_printf("Speed Selection: ");
    if ((reg & (1 << 13)) && !(reg & (1 << 6)))
    {
        xil_printf("100Mbps\r\n");
    }
    else if (!(reg & (1 << 13)) && !(reg & (1 << 6)))
    {
        xil_printf("10Mbps\r\n");
    }
    else
    {
        xil_printf("Reserved\r\n");
    }
    xil_printf("Auto-Negotiation: %s\r\n", (reg & (1 << 12)) ? "Enabled" : "Disabled");
    xil_printf("Power Down: %s\r\n", (reg & (1 << 11)) ? "Enabled" : "Disabled");
    xil_printf("Isolate: %s\r\n", (reg & (1 << 10)) ? "Enabled" : "Disabled");
    xil_printf("Restart Auto-Negotiation: %s\r\n", (reg & (1 << 9)) ? "Restarted" : "Normal");
    xil_printf("Duplex Mode: %s\r\n", (reg & (1 << 8)) ? "Full" : "Half");
    xil_printf("Collision Test: %s\r\n", (reg & (1 << 7)) ? "Enabled" : "Disabled");
    xil_printf("\r\n");
}

void printBMSR(uint16_t reg)
{
    xil_printf("BMSR - Basic Mode Status Register (0x01)\r\n");
    xil_printf("100Base-TX Full Duplex: %s\r\n", (reg & (1 << 14)) ? "Capable" : "Not Capable");
    xil_printf("100Base-TX Half Duplex: %s\r\n", (reg & (1 << 13)) ? "Capable" : "Not Capable");
    xil_printf("10Base-T Full Duplex: %s\r\n", (reg & (1 << 12)) ? "Capable" : "Not Capable");
    xil_printf("10Base-T Half Duplex: %s\r\n", (reg & (1 << 11)) ? "Capable" : "Not Capable");
    xil_printf("Link Status: %s\r\n", (reg & (1 << 2)) ? "Up" : "Down");
    xil_printf("Auto-Negotiation Complete: %s\r\n", (reg & (1 << 5)) ? "Yes" : "No");
    xil_printf("Remote Fault: %s\r\n", (reg & (1 << 4)) ? "Detected" : "Not Detected");
    xil_printf("1000Base-T Extended Status: %s\r\n", (reg & (1 << 8)) ? "Supported" : "Not Supported");
    xil_printf("\r\n");
}

void printPHYID1(uint16_t reg)
{
    xil_printf("PHYID1 - PHY Identifier Register 1 (0x02)\r\n");
    xil_printf("OUI MSB: 0x%04X\r\n", reg);
    xil_printf("\r\n");
}

void printPHYID2(uint16_t reg)
{
    xil_printf("PHYID2 - PHY Identifier Register 2 (0x03)\r\n");
    xil_printf("OUI LSB: 0x%X\r\n", (reg >> 10) & 0x3F);
    xil_printf("Model Number: 0x%X\r\n", (reg >> 4) & 0x3F);
    xil_printf("Revision Number: 0x%X\r\n", reg & 0xF);
    xil_printf("\r\n");
}

void printANAR(uint16_t reg)
{
    xil_printf("ANAR - Auto-Negotiation Advertisement Register (0x04)\r\n");
    xil_printf("Next Page: %s\r\n", (reg & (1 << 15)) ? "Yes" : "No");
    xil_printf("Remote Fault: %s\r\n", (reg & (1 << 13)) ? "Yes" : "No");
    xil_printf("Asymmetric Pause: %s\r\n", (reg & (1 << 11)) ? "Supported" : "Not Supported");
    xil_printf("Pause: %s\r\n", (reg & (1 << 10)) ? "Supported" : "Not Supported");
    xil_printf("100Base-TX Full Duplex: %s\r\n", (reg & (1 << 8)) ? "Advertised" : "Not Advertised");
    xil_printf("100Base-TX Half Duplex: %s\r\n", (reg & (1 << 7)) ? "Advertised" : "Not Advertised");
    xil_printf("10Base-T Full Duplex: %s\r\n", (reg & (1 << 6)) ? "Advertised" : "Not Advertised");
    xil_printf("10Base-T Half Duplex: %s\r\n", (reg & (1 << 5)) ? "Advertised" : "Not Advertised");
    xil_printf("\r\n");
}
void printANLPAR(uint16_t reg)
{
    xil_printf("ANLPAR - Auto-Negotiation Link Partner Ability Register (0x05)\r\n");
    xil_printf("Next Page: %s\r\n", (reg & (1 << 15)) ? "Able" : "Not Able");
    xil_printf("Acknowledged: %s\r\n", (reg & (1 << 14)) ? "Yes" : "No");
    xil_printf("Remote Fault: %s\r\n", (reg & (1 << 13)) ? "Detected" : "Not Detected");
    xil_printf("Asymmetric Pause: %s\r\n", (reg & (1 << 11)) ? "Supported" : "Not Supported");
    xil_printf("Pause: %s\r\n", (reg & (1 << 10)) ? "Supported" : "Not Supported");
    xil_printf("100Base-T4: %s\r\n", (reg & (1 << 9)) ? "Supported" : "Not Supported");
    xil_printf("100Base-TX Full Duplex: %s\r\n", (reg & (1 << 8)) ? "Supported" : "Not Supported");
    xil_printf("100Base-TX: %s\r\n", (reg & (1 << 7)) ? "Supported" : "Not Supported");
    xil_printf("10Base-T Full Duplex: %s\r\n", (reg & (1 << 6)) ? "Supported" : "Not Supported");
    xil_printf("10Base-T: %s\r\n", (reg & (1 << 5)) ? "Supported" : "Not Supported");
    xil_printf("\r\n");
}
void printANER(uint16_t reg)
{
    xil_printf("ANER - Auto-Negotiation Expansion Register (0x06)\r\n");
    xil_printf("Local Device Next Page Able: %s\r\n", (reg & (1 << 2)) ? "Yes" : "No");
    xil_printf("Link Partner Next Page Able: %s\r\n", (reg & (1 << 3)) ? "Yes" : "No");
    xil_printf("Parallel Detection Fault: %s\r\n", (reg & (1 << 4)) ? "Detected" : "Not Detected");
    xil_printf("\r\n");
}

void printANNPTR(uint16_t reg)
{
    xil_printf("ANNPTR - Auto-Negotiation Next Page Transmit Register (0x07)\r\n");
    xil_printf("Next Page: %s\r\n", (reg & (1 << 15)) ? "Yes" : "No");
    xil_printf("Message Page: %s\r\n", (reg & (1 << 13)) ? "Yes" : "No");
    xil_printf("Acknowledge2: %s\r\n", (reg & (1 << 12)) ? "Yes" : "No");
    // The Message/Unformatted field is too specific and might be used for various purposes,
    // printing it as is.
    xil_printf("Message/Unformatted Field: 0x%03X\r\n", reg & 0x07FF);
    xil_printf("\r\n");
}

void printANNPRR(uint16_t reg)
{
    xil_printf("ANNPRR - Auto-Negotiation Next Page Receive Register (0x08)\r\n");
    xil_printf("Next Page Able: %s\r\n", (reg & (1 << 15)) ? "Yes" : "No");
    xil_printf("Message Page: %s\r\n", (reg & (1 << 13)) ? "Yes" : "No");
    xil_printf("Acknowledge2: %s\r\n", (reg & (1 << 12)) ? "Yes" : "No");
    // Similar to ANNPTR, the Message/Unformatted field varies by use case.
    xil_printf("Message/Unformatted Field: 0x%03X\r\n", reg & 0x07FF);
    xil_printf("\r\n");
}

void printINSR(uint16_t reg)
{
    xil_printf("INSR - Interrupt Status Register (0x13)\r\n");
    xil_printf("Auto-Negotiation Error: %s\r\n", (reg & (1 << 15)) ? "Occurred" : "No Error");
    xil_printf("Page Received: %s\r\n", (reg & (1 << 12)) ? "Yes" : "No");
    xil_printf("Auto-Negotiation Completed: %s\r\n", (reg & (1 << 11)) ? "Yes" : "No");
    xil_printf("Link Status Change: %s\r\n", (reg & (1 << 10)) ? "Changed" : "No Change");
    xil_printf("Symbol Error: %s\r\n", (reg & (1 << 9)) ? "Detected" : "No Error");
    xil_printf("False Carrier: %s\r\n", (reg & (1 << 8)) ? "Detected" : "No Error");
    xil_printf("Jabber Detected: %s\r\n", (reg & 1) ? "Yes" : "No");
    xil_printf("\r\n");
}