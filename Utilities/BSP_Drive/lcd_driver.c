/*!
    \file  lcd_driver.c
    \brief lcd driver functions

    \version 2025-02-19, V1.4.0, demo for GD32W51x_F5HC
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32w51x_f5hc.h"       /* 改为 GD32W51x_F5HC 主头文件 */
#include "lcd_driver.h"

#include "systick.h"

#define H_VIEW

#ifdef H_VIEW
#define X_MAX_PIXEL         (uint16_t)320
#define Y_MAX_PIXEL         (uint16_t)240
#else
#define X_MAX_PIXEL         (uint16_t)240
#define Y_MAX_PIXEL         (uint16_t)320
#endif



static uint8_t spi_write_byte(uint32_t spi_periph, uint8_t byte);
static void spi1_init(void);
static void lcd_write_index(uint8_t index);
static void lcd_write_data(uint8_t data);
static void lcd_write_data_16bit(uint8_t datah, uint8_t datal);
static void lcd_reset(void);

/*!
    \brief      send a byte through the SPI interface and return a byte received from the SPI bus
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  byte: data to be send
    \param[out] none
    \retval     the value of the received byte
*/
static uint8_t spi_write_byte(uint32_t spi_periph, uint8_t byte)
{
    __IO uint8_t data;
    while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_TBE));
    spi_i2s_data_transmit(spi_periph, (uint16_t)byte);
    while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE));
    data = (uint8_t)spi_i2s_data_receive(spi_periph);
    return(data);
}
/*!
    \brief      send a halfword through the SPI interface and return a halfwold received from the SPI bus
    \param[in]  spi_periph: SPIx(x=0,1)
    \param[in]  halfword: data to be send
    \param[out] none
    \retval     the value of the received halfword
*/
uint16_t spi_write_halfword(uint32_t spi_periph, uint16_t halfword)
{
    __IO uint16_t data;
    while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_TBE));
    spi_i2s_data_transmit(spi_periph, halfword);
    while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE));
    data = spi_i2s_data_receive(spi_periph);
    return(data);
}

#if (USE_DMA_LCD==1)
uint16_t rx_array[1];
/*!
    \brief      configure LCD DMA
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void lcd_dma_config(void)
{
    dma_multi_data_parameter_struct dma_init_parameter;

    /* peripheral clock enable */
    rcu_periph_clock_enable(RCU_DMA0);

    /* DMA peripheral configure */
    dma_deinit(DMA0, DMA_CH4);
    dma_multi_data_para_struct_init(&dma_init_parameter);
    dma_init_parameter.memory0_addr         = 0U;
    dma_init_parameter.memory_width         = DMA_MEMORY_WIDTH_16BIT;
    dma_init_parameter.memory_inc           = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_parameter.memory_burst_width   = DMA_MEMORY_BURST_4_BEAT;
    dma_init_parameter.periph_addr          = (uint32_t)&SPI_DATA(SPI1);
    dma_init_parameter.periph_width         = DMA_PERIPH_WIDTH_16BIT;
    dma_init_parameter.periph_inc           = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_parameter.periph_burst_width   = DMA_PERIPH_BURST_SINGLE;
    dma_init_parameter.direction            = DMA_MEMORY_TO_PERIPH;
    dma_init_parameter.critical_value       = DMA_FIFO_2_WORD;
    dma_init_parameter.circular_mode        = DMA_CIRCULAR_MODE_DISABLE;
    dma_init_parameter.number               = 0;
    dma_init_parameter.priority             = DMA_PRIORITY_ULTRA_HIGH;
    dma_multi_data_mode_init(DMA0, DMA_CH4, &dma_init_parameter);
    /* connect DMA0_CH4 to SPI1 TX */
    dma_channel_subperipheral_select(DMA0, DMA_CH4, DMA_SUBPERI0);
    /* interrupt configure */
    dma_interrupt_enable(DMA0, DMA_CH4, DMA_INT_FTF);
    nvic_irq_enable(DMA0_Channel4_IRQn, 0, 0);

    /* DMA peripheral configure */
    dma_deinit(DMA0, DMA_CH3);
    dma_multi_data_para_struct_init(&dma_init_parameter);
    dma_init_parameter.memory0_addr         = (uint32_t)rx_array;
    dma_init_parameter.memory_width         = DMA_MEMORY_WIDTH_16BIT;
    dma_init_parameter.memory_inc           = DMA_MEMORY_INCREASE_DISABLE;
    dma_init_parameter.memory_burst_width   = DMA_MEMORY_BURST_SINGLE;
    dma_init_parameter.periph_addr          = (uint32_t)&SPI_DATA(SPI1);
    dma_init_parameter.periph_width         = DMA_PERIPH_WIDTH_16BIT;
    dma_init_parameter.periph_inc           = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_parameter.periph_burst_width   = DMA_PERIPH_BURST_SINGLE;
    dma_init_parameter.direction            = DMA_PERIPH_TO_MEMORY;
    dma_init_parameter.critical_value       = DMA_FIFO_1_WORD;
    dma_init_parameter.circular_mode        = DMA_CIRCULAR_MODE_DISABLE;
    dma_init_parameter.number               = 0U;
    dma_init_parameter.priority             = DMA_PRIORITY_ULTRA_HIGH;
    dma_multi_data_mode_init(DMA0, DMA_CH3, &dma_init_parameter);
    /* connect DMA0_CH3 to SPI1 RX */
    dma_channel_subperipheral_select(DMA0, DMA_CH3, DMA_SUBPERI0);
    /* interrupt configure */
    dma_interrupt_enable(DMA0, DMA_CH3, DMA_INT_FTF);
    nvic_irq_enable(DMA0_Channel3_IRQn, 0, 0);
}
#endif

/*!
    \brief      initialize SPI1
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void spi1_init(void)
{
    spi_parameter_struct spi_init_struct;
    /* enable the GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    /* enable the SPI1 clock */
    rcu_periph_clock_enable(RCU_SPI1);

    /* SPI1 GPIO configuration: SCK/PC11, MISO/PC13, MOSI/PD0 */
    gpio_af_set(GPIOC, GPIO_AF_9, GPIO_PIN_13 | GPIO_PIN_11);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13 | GPIO_PIN_11);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_166MHZ, GPIO_PIN_13 | GPIO_PIN_11);

    /* MOSI/PD0 */
    gpio_af_set(GPIOD, GPIO_AF_9, GPIO_PIN_0);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_166MHZ, GPIO_PIN_0);

    /* GPIOB configuration (LCD_RST/PB1, LCD_DC/PB2) */
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1 | GPIO_PIN_2);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_166MHZ, GPIO_PIN_1 | GPIO_PIN_2);

    /* GPIOC configuration (LCD_RST/PC3) */
    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_166MHZ, GPIO_PIN_3);

    /* SPI1 parameter configuration */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_2;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(SPI1, &spi_init_struct);

#if (USE_DMA_LCD==1)
    lcd_dma_config();
    spi_dma_enable(SPI1, SPI_DMA_TRANSMIT);
    spi_dma_enable(SPI1, SPI_DMA_RECEIVE);
#endif
    spi_enable(SPI1);
}

/*!
    \brief      write the register address
    \param[in]  index: the value of register address to be written
    \param[out] none
    \retval     none
*/
static void lcd_write_index(uint8_t index)
{
    LCD_RS_CLR;
    spi_write_byte(SPI1, index);
}

/*!
    \brief      write the register data
    \param[in]  data: the value of register data to be written
    \param[out] none
    \retval     none
*/
static void lcd_write_data(uint8_t data)
{
    LCD_RS_SET;
    spi_write_byte(SPI1, data);
}

/*!
    \brief      write the register data(an unsigned 16-bit data)
    \param[in]  datah: the high 8bit of register data to be written
    \param[in]  datal: the low 8bit of register data to be written
    \param[out] none
    \retval     none
*/
static void lcd_write_data_16bit(uint8_t datah, uint8_t datal)
{
    lcd_write_data(datah);
    lcd_write_data(datal);
}


/*!
    \brief      reset the lcd
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void lcd_reset(void)
{
    LCD_RST_CLR;
    delay_1ms(100);
    LCD_RST_SET;
    delay_1ms(50);
}

/*!
    \brief      initialize the lcd
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_init(void)
{
    spi1_init();

    /* DEBUG: toggle LED1 (PB6) to confirm lcd_init is reached */
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, GPIO_PIN_6);
    GPIO_BOP(GPIOB) = GPIO_PIN_6;  /* LED1 ON */

    LCD_CS_CLR;
    lcd_reset();

    /* write the register address 0xCB*/
    lcd_write_index(0xCB);
    lcd_write_data(0x39);
    lcd_write_data(0x2C);
    lcd_write_data(0x00);
    lcd_write_data(0x34);
    lcd_write_data(0x02);

    /* write the register address 0xCF*/
    lcd_write_index(0xCF);
    lcd_write_data(0x00);
    lcd_write_data(0XC1);
    lcd_write_data(0X30);

    /* write the register address 0xE8*/
    lcd_write_index(0xE8);
    lcd_write_data(0x85);
    lcd_write_data(0x00);
    lcd_write_data(0x78);

    /* write the register address 0xEA*/
    lcd_write_index(0xEA);
    lcd_write_data(0x00);
    lcd_write_data(0x00);

    /* write the register address 0xED*/
    lcd_write_index(0xED);
    lcd_write_data(0x64);
    lcd_write_data(0x03);
    lcd_write_data(0X12);
    lcd_write_data(0X81);

    /* write the register address 0xF7*/
    lcd_write_index(0xF7);
    lcd_write_data(0x20);

    /* power control VRH[5:0] */
    lcd_write_index(0xC0);
    lcd_write_data(0x23);

    /* power control SAP[2:0];BT[3:0] */
    lcd_write_index(0xC1);
    lcd_write_data(0x10);

    /* vcm control */
    lcd_write_index(0xC5);
    lcd_write_data(0x3e);
    lcd_write_data(0x28);

    /* vcm control2 */
    lcd_write_index(0xC7);
    lcd_write_data(0x86);

    lcd_write_index(0x36);
#ifdef H_VIEW
    lcd_write_data(0xE8);
#else
    lcd_write_data(0x48);
#endif

    /* write the register address 0x3A*/
    lcd_write_index(0x3A);
    lcd_write_data(0x55);

    /* write the register address 0xB1*/
    lcd_write_index(0xB1);
    lcd_write_data(0x00);
    lcd_write_data(0x10);

    /* display function control */
    lcd_write_index(0xB6);
    lcd_write_data(0x08);
    lcd_write_data(0x82);
    lcd_write_data(0x27);

    /* 3gamma function disable */
    lcd_write_index(0xF2);
    lcd_write_data(0x00);

    /* gamma curve selected  */
    lcd_write_index(0x26);
    lcd_write_data(0x01);

    /* set gamma  */
    lcd_write_index(0xE0);
    lcd_write_data(0x0F);
    lcd_write_data(0x31);
    lcd_write_data(0x2B);
    lcd_write_data(0x0C);
    lcd_write_data(0x0E);
    lcd_write_data(0x08);
    lcd_write_data(0x4E);
    lcd_write_data(0xF1);
    lcd_write_data(0x37);
    lcd_write_data(0x07);
    lcd_write_data(0x10);
    lcd_write_data(0x03);
    lcd_write_data(0x0E);
    lcd_write_data(0x09);
    lcd_write_data(0x00);

    /* set gamma  */
    lcd_write_index(0XE1);
    lcd_write_data(0x00);
    lcd_write_data(0x0E);
    lcd_write_data(0x14);
    lcd_write_data(0x03);
    lcd_write_data(0x11);
    lcd_write_data(0x07);
    lcd_write_data(0x31);
    lcd_write_data(0xC1);
    lcd_write_data(0x48);
    lcd_write_data(0x08);
    lcd_write_data(0x0F);
    lcd_write_data(0x0C);
    lcd_write_data(0x31);
    lcd_write_data(0x36);
    lcd_write_data(0x0F);

    /* exit sleep */
    lcd_write_index(0x11);
    delay_1ms(120);

    /* display on */
    lcd_write_index(0x29);
    lcd_write_index(0x2c);

    LCD_CS_SET;
}

/*!
    \brief      set lcd display region
    \param[in]  x_start: the x position of the start point
    \param[in]  y_start: the y position of the start point
    \param[in]  x_end: the x position of the end point
    \param[in]  y_end: the y position of the end point
    \param[out] none
    \retval     none
*/
void lcd_set_region(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
{
    LCD_CS_CLR;

    /* write the register address 0x2A*/
    lcd_write_index(0x2A);
    lcd_write_data_16bit(x_start >> 8, x_start);
    lcd_write_data_16bit(x_end >> 8, x_end);

    /* write the register address 0x2B*/
    lcd_write_index(0x2B);
    lcd_write_data_16bit(y_start >> 8, y_start);
    lcd_write_data_16bit(y_end >> 8, y_end);

    /* write the register address 0x2C*/
    lcd_write_index(0x2C);
    LCD_CS_SET;
}

/*!
    \brief      set the start display point of lcd
    \param[in]  x: the x position of the start point
    \param[in]  y: the y position of the start point
    \param[out] none
    \retval     none
*/
void lcd_set_xy(uint16_t x, uint16_t y)
{
    /* write the register address 0x2A*/
    lcd_write_index(0x2A);
    lcd_write_data_16bit(x >> 8, x);

    /* write the register address 0x2B*/
    lcd_write_index(0x2B);
    lcd_write_data_16bit(y >> 8, y);

    /* write the register address 0x2C*/
    lcd_write_index(0x2C);
}

/*!
    \brief      draw a point on the lcd
    \param[in]  x: the x position of the point
    \param[in]  y: the y position of the point
    \param[in]  data: the register data to be written
    \param[out] none
    \retval     none
*/
void gui_draw_point(uint16_t x, uint16_t y, uint16_t data)
{
    lcd_set_xy(x, y);
    lcd_write_data(data >> 8);
    lcd_write_data(data);
}

/*!
    \brief      clear the lcd
    \param[in]  color: lcd display color
    \param[out] none
    \retval     none
*/
void lcd_clear(uint16_t color)
{
    unsigned int i, m;
    /* set lcd display region */
    lcd_set_region(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
    LCD_RS_SET;

    LCD_CS_CLR;
    for(i = 0; i < Y_MAX_PIXEL; i ++) {
        for(m = 0; m < X_MAX_PIXEL; m ++) {
            spi_write_byte(SPI1, color >> 8);
            spi_write_byte(SPI1, color);
        }
    }
    LCD_CS_SET;
}


uint16_t fill_color;
/*!
    \brief      fill LCD region with specific color
    \param[in]  x: the x position of the start point
    \param[in]  y: the y position of the start point
    \param[in]  w: width of the region
    \param[in]  h: height of the region
    \param[in]  color: fill color
    \param[out] none
    \retval     none
*/
void lcd_fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    fill_color = color;
    /* SPI_FRAMESIZE_8BIT */
    spi_disable(SPI1);
    SPI_CTL0(SPI1) &= ~SPI_CTL0_FF16;
    spi_enable(SPI1);
    /* Set the refresh area */
    lcd_set_region(x, y, x + w - 1, y + h - 1);
    /* SPI_FRAMESIZE_16BIT */
    spi_disable(SPI1);
    SPI_CTL0(SPI1) |= SPI_CTL0_FF16;
    spi_enable(SPI1);
#if (USE_DMA_LCD==1)
    /* Send refresh data */
    LCD_RS_SET;
    LCD_CS_CLR;
    dma_interrupt_disable(DMA0, DMA_CH3, DMA_INT_FTF);
    dma_interrupt_disable(DMA0, DMA_CH4, DMA_INT_FTF);

    dma_flag_clear(DMA0, DMA_CH3, DMA_FLAG_FTF);
    dma_flag_clear(DMA0, DMA_CH4, DMA_FLAG_FTF);
    dma_memory_address_generation_config(DMA0, DMA_CH4, DMA_MEMORY_INCREASE_DISABLE);
    dma_memory_address_config(DMA0, DMA_CH4, DMA_MEMORY_0, (uint32_t)&fill_color);
    dma_transfer_number_config(DMA0, DMA_CH4, w * h);
    dma_transfer_number_config(DMA0, DMA_CH3, w * h);
    dma_channel_enable(DMA0, DMA_CH3);
    dma_channel_enable(DMA0, DMA_CH4);
    while(dma_flag_get(DMA0, DMA_CH3, DMA_FLAG_FTF) == RESET);
    dma_flag_clear(DMA0, DMA_CH3, DMA_FLAG_FTF);
    while(dma_flag_get(DMA0, DMA_CH4, DMA_FLAG_FTF) == RESET);
    dma_flag_clear(DMA0, DMA_CH4, DMA_FLAG_FTF);

    dma_interrupt_enable(DMA0, DMA_CH3, DMA_INT_FTF);
    dma_interrupt_enable(DMA0, DMA_CH4, DMA_INT_FTF);
    LCD_CS_SET;

#else
    /* Send refresh data */
    LCD_RS_SET;
    LCD_CS_CLR;
    for(int i = 0; i < h; i ++) {
        for(int m = 0; m < w; m ++) {
            spi_write_halfword(SPI1, fill_color);
        }
    }
    LCD_CS_SET;
#endif
}
