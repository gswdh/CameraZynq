#include "gmax0505.h"

#include "xparameters.h"
#include "xgpio.h"

#include "gpio.h"
#include "log.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"

#define LOG_TAG "GMAX"

#define GMAX_12BITS

/* The Instance of the GPIO Driver */
static XGpio gmax_gpio = {0};

/* GMAX sensor configurations */
#if defined(GMAX_12BITS)
const uint8_t gmax_config[256] = {0x22, 0x05, 0x00, 0xF4, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x14, 0x01, 0x00, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x14, 0x00, 0x00, 0x06, 0x02, 0x02, 0x04, 0x04, 0x00, 0x20, 0x23, 0x01, 0xc4, 0x35, 0xcb, 0x3b, 0x35, 0xfc, 0xff, 0xff, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x34, 0xD8, 0x10, 0x4F, 0x3D, 0x00, 0x08, 0x90, 0xC0, 0x1D, 0x09, 0xC4, 0x32, 0x4B, 0x5B, 0x05, 0xD0, 0xA0, 0xC3, 0x44, 0x02, 0x10, 0x70, 0x43, 0x0E, 0x30, 0xD0, 0xF0, 0xD0, 0x44, 0x07, 0xD0, 0xC0, 0xC3, 0x44, 0x34, 0xF0, 0x80, 0xC3, 0xFF, 0x4B, 0xA4, 0xA1, 0x40, 0x0E, 0x41, 0xFC, 0x1F, 0x81, 0x0C, 0x7C, 0x00, 0x18, 0x1B, 0x01, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x07, 0xD0, 0xC0, 0xC3, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x1B, 0x21, 0x80, 0xF3, 0x83, 0x84, 0x9D, 0xCC, 0x77, 0xF3, 0xDD, 0x0D, 0xD3, 0x00, 0x00, 0x1C, 0xB0, 0x0D, 0xFE, 0x62, 0xC1, 0x1F, 0x8A, 0xCA, 0xE7, 0xA8, 0x3C, 0xCA, 0xFE, 0x82, 0x34, 0x7F, 0xC1, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#elif defined(GMAX_10BITS)
const uint8_t gmax_config[256] = {0x26, 0x04, 0x00, 0x14, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x14, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x14, 0x00, 0x00, 0x07, 0x0A, 0x02, 0x04, 0x04, 0x00, 0x20, 0x23, 0x01, 0xE4, 0x01, 0xC4, 0x13, 0x15, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x08, 0x90, 0xC0, 0x09, 0x09, 0xFC, 0x00, 0x44, 0x1D, 0x0D, 0x9C, 0x10, 0x43, 0x1E, 0x06, 0x30, 0x90, 0x02, 0x0C, 0x27, 0xAC, 0x30, 0xC7, 0x1D, 0x0F, 0x9C, 0x30, 0xC3, 0x1D, 0x2B, 0xCC, 0xF0, 0xC2, 0xFF, 0x4B, 0xA4, 0xA1, 0x40, 0x0E, 0x41, 0xFC, 0x1F, 0x81, 0x0C, 0x7C, 0x00, 0x0C, 0x1C, 0x01, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x0F, 0x9C, 0x30, 0x43, 0x1E, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x1B, 0x21, 0x80, 0xF3, 0x83, 0x80, 0x9D, 0x18, 0x7C, 0x06, 0xDF, 0x0D, 0xF3, 0x00, 0x00, 0x1C, 0xB0, 0x0D, 0x9E, 0x6A, 0xB9, 0x1F, 0x8A, 0xFE, 0xE7, 0xFF, 0x3F, 0x80, 0xFE, 0x7E, 0x44, 0x7F, 0xAD, 0x56, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#else
#error "Need to specify GMAX0505 bit depth."
#endif

static void write_data_bit(bool value)
{
    gpio_write(SEN_SPI_MOSI, value);
    gpio_reset(SEN_SPI_CLK);
    gpio_set(SEN_SPI_CLK);
}

static void write_data_byte(uint8_t value)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        write_data_bit(value & (1 << (7 - i)));
    }
}

static bool read_data_bit()
{
    gpio_reset(SEN_SPI_CLK);
    gpio_set(SEN_SPI_CLK);
    return gpio_read(SEN_SPI_MISO);
}

static uint8_t read_data_byte()
{
    uint8_t value = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        value |= read_data_bit() << (7 - i);
    }

    return value;
}

static void gmax_gpio_init()
{
    /*
     * Initialize the GPIO driver so that it's ready to use,§
     * specify the device ID that is generated in xparameters.h
     */
    XGpio_Config *cfg_ptr = XGpio_LookupConfig(XPAR_SENSOR_BD_0_AXI_GPIO_0_BASEADDR);
    if (XGpio_Initialize(&gmax_gpio, XPAR_SENSOR_BD_0_AXI_GPIO_0_BASEADDR) != XST_SUCCESS)
    {
        log_info(LOG_TAG, "Init fail.\n");
        return;
    }

    /* Set channel one to all outputs, set them to 0*/
    XGpio_SetDataDirection(&gmax_gpio, 1, 0x0);
    XGpio_DiscreteWrite(&gmax_gpio, 1, 0x0);
}

static uint16_t gmax_training_word()
{
    /* Should return 0x086E for default config */
    return ((gmax_config[216] & 0x01) << 11) + (gmax_config[215] << 3) + ((gmax_config[214] & 0xE0) >> 5);
}

static void gmax_set_training_word(uint16_t word)
{
    uint32_t reg = XGpio_DiscreteRead(&gmax_gpio, 1) & 0xFFFFF000;
    reg |= word & 0x0FFF;
    XGpio_DiscreteWrite(&gmax_gpio, 1, reg);
}

static bool gmax_sync_complete()
{
    return (bool)(XGpio_DiscreteRead(&gmax_gpio, 2) & 0x1);
}

static bool gmax_sync(bool en)
{
    if (en)
    {
        XGpio_DiscreteSet(&gmax_gpio, 1, 0x00001000);
    }
    else
    {
        XGpio_DiscreteClear(&gmax_gpio, 1, 0x00001000);
    }
}

static void gmax_delay_ms(uint32_t time_ms)
{
    vTaskDelay(pdMS_TO_TICKS(time_ms));
}

void gmax_power_on()
{
    gpio_reset(SEN_SYS_NRESET);
    gmax_delay_ms(10);
    gpio_set(PWR_SEN_1V3_EN);
    gmax_delay_ms(10);
    gpio_set(PWR_SEN_3V3A_EN);
    gmax_delay_ms(10);
    gpio_set(PWR_SEN_3V6_EN);
    gpio_set(PWR_SEN_4V1_EN);
    gmax_delay_ms(10);
    gpio_set(PWR_SEN_0V7_EN);
    gmax_delay_ms(10);
    gpio_set(PWR_SEN_N1V3A_EN);
    gmax_delay_ms(10);
    gpio_set(SEN_SYS_NRESET);
}

void gmax_power_off()
{
    gpio_reset(SEN_SYS_NRESET);
    gmax_delay_ms(10);
    gpio_reset(PWR_SEN_N1V3A_EN);
    gmax_delay_ms(10);
    gpio_reset(PWR_SEN_0V7_EN);
    gmax_delay_ms(10);
    gpio_reset(PWR_SEN_3V6_EN);
    gpio_reset(PWR_SEN_4V1_EN);
    gmax_delay_ms(10);
    gpio_reset(PWR_SEN_3V3A_EN);
    gmax_delay_ms(10);
    gpio_reset(PWR_SEN_1V3_EN);
}

void gmax_spi_write(uint8_t reg, uint8_t *data, uint32_t len)
{
    // Select is active high
    gpio_set(SEN_SPI_NCS);

    // Do the RW bit (1 for write)
    write_data_bit(true);

    // Output the register address
    write_data_byte(reg);

    // Clock the data out
    for (uint32_t i = 0; i < len; i++)
    {
        write_data_byte(data[i]);
    }

    // Finish with reseting the select line
    gpio_reset(SEN_SPI_NCS);
}

void gmax_spi_read(uint8_t reg, uint8_t *data, uint32_t len)
{
    // Select is active high
    gpio_set(SEN_SPI_NCS);

    // Do the RW bit (0 for read)
    write_data_bit(false);

    // Output the register address
    write_data_byte(reg);

    // Need a dummy bit
    write_data_bit(false);

    // Clock the data out
    for (uint32_t i = 0; i < len; i++)
    {
        data[i] = read_data_byte();
    }

    // Finish with reseting the select line
    gpio_reset(SEN_SPI_NCS);
}

void gmax_init()
{
    /* Setup the FPGA HW */
    gmax_gpio_init();
    gmax_set_training_word(0x0761);

    /* That */
    gmax_power_on();

    /* Write config with streaming off and reg 209[3:0] = 0100 */
    gmax_spi_write(0x00, (uint8_t *)gmax_config, 256);

    /* Datasheet defined 1ms */
    gmax_delay_ms(1);

    /* Now set reg 209[3:0] to 0000 (datasheet magic) */
    uint8_t value = gmax_config[209] & 0xF0;
    gmax_spi_write(209, &value, 1);

    /* Datasheet defined 5ms */
    gmax_delay_ms(5);

    /* Now enable streaming */
    value = gmax_config[0] | 0x01;
    gmax_spi_write(0x00, &value, 1);

    /* Enable the FPGA syncing */
    gmax_sync(true);

    /* Wait for the syncing to be done */
    while (!gmax_sync_complete())
    {
        gmax_delay_ms(10);
    }

    /* Disable the FPGA syncing otherwise image data will trigger the sync module */
    gmax_sync(false);

    /* Let's turn an LED on in celebration */
    gpio_set(FPGA_LED_1);
}