/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>

#include "lcd_driver.h"

#define MY_DISP_HOR_RES    XSIZE_PHYS
#define MY_DISP_VER_RES    YSIZE_PHYS

#define LV_BUF_TYPE 2

#if(LV_BUF_TYPE==1)
    __attribute__((aligned(8))) static lv_color_t buf_2[320 * 120];
#elif(LV_BUF_TYPE==2)
    __attribute__((aligned(8))) static lv_color_t buf_2[320 * 120];
    __attribute__((aligned(8))) static lv_color_t buf_3[320 * 120];
#endif

static volatile lv_disp_drv_t * g_disp_drv = NULL;

/*********************
 *      DEFINES
 *********************/
#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    static lv_disp_draw_buf_t draw_buf;
    static lv_disp_drv_t disp_drv;

    disp_init();

#if(LV_BUF_TYPE==1)
    lv_disp_draw_buf_init(&draw_buf, buf_2, NULL, 320 * 120);
#elif(LV_BUF_TYPE==2)
    lv_disp_draw_buf_init(&draw_buf, buf_2, buf_3, 320 * 120);
#endif

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
    /* initialize LCD */
    lcd_init();
//    lcd_clear(BLACK);
//    lcd_clear(RED);
//    lcd_fill(0, 0, 320, 120, GREEN);
//    lcd_fill(0, 120, 320, 120, GREEN);
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

uint16_t *data;

/*!
    \brief      copy image data to LCD
    \param[in]  x: the x position of the start point
    \param[in]  y: the y position of the start point
    \param[in]  w: width of the image 
    \param[in]  h: height of the image
    \param[in]  src_data: pointer to the source image data
    \param[out] none
    \retval     none
*/
void lcd_copy(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *src_data)
{
    uint16_t *data;
    data = src_data;
#if (USE_DMA_LCD==1)
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
    /* Send refresh data */
    LCD_RS_SET;
    LCD_CS_CLR;
    dma_flag_clear(DMA0, DMA_CH3, DMA_INT_FLAG_FTF);
    dma_flag_clear(DMA0, DMA_CH4, DMA_INT_FLAG_FTF);
    dma_memory_address_generation_config(DMA0, DMA_CH4, DMA_MEMORY_INCREASE_ENABLE);
    dma_memory_address_config(DMA0, DMA_CH4, DMA_MEMORY_0, (uint32_t)src_data);
    dma_transfer_number_config(DMA0, DMA_CH4, w * h);
    dma_transfer_number_config(DMA0, DMA_CH3, w * h);
    dma_channel_enable(DMA0, DMA_CH3);
    dma_channel_enable(DMA0, DMA_CH4);
#else
    uint16_t i, m;
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
    /* Send refresh data */
    LCD_RS_SET;
    LCD_CS_CLR;
    for(i = 0; i < h; i ++) {
        for(m = 0; m < w; m ++) {
            spi_write_halfword(SPI1, *data);
            data++;
        }
    }
    LCD_CS_SET;
#endif
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    if(!disp_flush_enabled) {
        lv_disp_flush_ready(disp_drv);
        return;
    }
#if (USE_DMA_LCD==1)
    while(g_disp_drv != NULL);
    g_disp_drv = disp_drv;
    lcd_copy(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (uint16_t *)color_p);
#else
    lcd_copy(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (uint16_t *)color_p);
    lv_disp_flush_ready(disp_drv);
#endif
}

#if (USE_DMA_LCD==1)
void DMA0_Channel3_IRQHandler(void)
{
    if(SET == dma_interrupt_flag_get(DMA0, DMA_CH3, DMA_INT_FLAG_FTF)) {
        dma_interrupt_flag_clear(DMA0, DMA_CH3, DMA_INT_FLAG_FTF);
    }
}
void DMA0_Channel4_IRQHandler(void)
{
    if(SET == dma_interrupt_flag_get(DMA0, DMA_CH4, DMA_INT_FLAG_FTF)) {
        dma_interrupt_flag_clear(DMA0, DMA_CH4, DMA_INT_FLAG_FTF);
        /* inform lvgl */
        if(g_disp_drv != NULL) {
            LCD_CS_SET;
            lv_disp_flush_ready((lv_disp_drv_t *)g_disp_drv);
            g_disp_drv = NULL;
        }
    }
}
#endif
#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
