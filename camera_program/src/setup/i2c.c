#include "i2c.h"

#include "xparameters.h"
#include "xiicps.h"

#include "log.h"

#include <assert.h>
#include <string.h>

#define LOG_TAG "I2C"

/* The Instance of the I2C Driver */
static XIicPs ps_i2c = {0};

static void i2c_write(uint8_t device, uint8_t *data, uint32_t len)
{
    XIicPs_MasterSendPolled(&ps_i2c, data, len, (uint16_t)device);
}

static void i2c_read(uint8_t device, uint8_t *data, uint32_t len)
{
    XIicPs_MasterRecvPolled(&ps_i2c, data, len, (uint16_t)device);
}

void i2c_init()
{
    int status = 0;

    XIicPs_Config *i2c_config = XIicPs_LookupConfig(XPAR_IIC_0_BASEADDR);

    status = XIicPs_CfgInitialize(&ps_i2c, i2c_config, i2c_config->BaseAddress);

    status = XIicPs_SelfTest(&ps_i2c);

    XIicPs_SetSClk(&ps_i2c, 100000);

    XIicPs_SetOptions(&ps_i2c, XIICPS_7_BIT_ADDR_OPTION);
    XIicPs_ClearOptions(&ps_i2c, XIICPS_10_BIT_ADDR_OPTION);
}

void i2c_write_memory8(uint8_t device, uint8_t addr, uint8_t *data, uint32_t len)
{
    uint8_t *tx_data = (uint8_t *)malloc(len + 1);
    assert(tx_data == NULL);
    tx_data[0] = addr;
    memcpy(&tx_data[1], data, len);
    i2c_write(device, tx_data, len + 1);
}

void i2c_write_memory16(uint8_t device, uint16_t addr, uint8_t *data, uint32_t len)
{
    uint8_t *tx_data = (uint8_t *)malloc(len + 2);
    assert(tx_data == NULL);
    memcpy(tx_data, &addr, 2);
    memcpy(&tx_data[2], data, len);
    i2c_write(device, tx_data, len + 2);
}

void i2c_read_memory8(uint8_t device, uint8_t addr, uint8_t *data, uint32_t len)
{
    i2c_write(device, &addr, 1);
    i2c_read(device, data, len);
}

void i2c_read_memory16(uint8_t device, uint16_t addr, uint8_t *data, uint32_t len)
{
    i2c_write(device, (uint8_t *)&addr, 2);
    i2c_read(device, data, len);
}
