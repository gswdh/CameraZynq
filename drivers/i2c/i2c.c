#include "i2c.h"

#include "log.h"

#include "xparameters.h"
#include "xiicps.h"

#include <stdlib.h>

#define LOG_TAG "I2C"

static XIicPs i2c = {0};

static void i2c_scan_bus(void)
{
    for (uint16_t i = 0; i < 256; i++)
    {
        uint8_t data[1] = {0};
        if (i2c_write(i, data, 1) == true)
        {
            log_info(LOG_TAG, "Device at address 0x%02X\n", i);
        }
    }
}

void i2c_init(const uint32_t clk_rate_hz)
{
    int status = 0;

    XIicPs_Config *config = XIicPs_LookupConfig(XPAR_PS7_I2C_0_DEVICE_ID);
    status = XIicPs_CfgInitialize(&i2c, config, config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XIicPs_CfgInitialize error with code %d\n", status);
        return;
    }

    status = XIicPs_SelfTest(&i2c);
    if (status != XST_SUCCESS)
    {
        log_error(LOG_TAG, "XIicPs_SelfTest error with code %d\n", status);
        return;
    }

    XIicPs_SetSClk(&i2c, clk_rate_hz);

    log_info(LOG_TAG, "init done\n");
}

bool i2c_write(const uint16_t slave_addr, const uint8_t *const data, const uint32_t len)
{
    int status = XIicPs_MasterSendPolled(&i2c, (uint8_t *)data, len, slave_addr);
    if (status != XST_SUCCESS)
    {
        return false;
    }

    return true;
}

bool i2c_read(const uint16_t slave_addr, uint8_t *const data, const uint32_t len)
{
    int status = XIicPs_MasterRecvPolled(&i2c, data, len, slave_addr);
    if (status != XST_SUCCESS)
    {
        return false;
    }

    return true;
}

void i2c_write_reg(const uint16_t slave_addr, const uint8_t reg_addr, const uint8_t *const data, const uint32_t len)
{
    uint8_t *payload = (uint8_t *)malloc(len + sizeof(reg_addr));
    if (payload == NULL)
    {
        log_error(LOG_TAG, "payload is NULL\n");
        return;
    }

    // Set the first byte as the register address
    payload[0] = reg_addr;

    // The rest is the data
    if (data != NULL)
    {
        memcpy(payload + sizeof(reg_addr), data, len);
    }

    // Write it out
    i2c_write(slave_addr, payload, len + sizeof(reg_addr));

    // Get out memory back
    free(payload);
}

void i2c_read_reg(const uint16_t slave_addr, const uint8_t reg_addr, uint8_t *const data, const uint32_t len)
{
    // Set the pointer first
    i2c_write(slave_addr, &reg_addr, sizeof(reg_addr));

    // Get some data
    i2c_read(slave_addr, data, len);
}