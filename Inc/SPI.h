#ifndef _SPI_H
#define _SPI_H
#include "stm32l4xx_hal.h"


//SPI INSTANCE
#define HSPI_INSTANCE							&hspi1

//PGA commands
#define PGA_WRITE 0x2A
#define GAIN1 0x02
#define GAIN2 0x12
#define GAIN5 0x22
#define GAIN10 0x32
#define GAIN20 0x42
#define GAIN50 0x52
#define GAIN100 0x62
#define GAIN200 0x72

//TFT pin/port defines
#define LCD_CS_PORT								GPIOE
#define LCD_CS_PIN								GPIO_PIN_11
#define LCD_DC_PORT								GPIOE
#define LCD_DC_PIN								GPIO_PIN_10
#define	LCD_RST_PORT							GPIOE
#define	LCD_RST_PIN								GPIO_PIN_12

//PGA pin/port defines
#define PGA_CS_PORT								GPIOC
#define PGA_CS_PIN								GPIO_PIN_15

void write8(uint8_t value);
void setGain(uint8_t gain);
void writecmd(uint8_t cmd);
void SPI_Send(unsigned char SPI_Data);
void SPI_Init(void);

#endif

