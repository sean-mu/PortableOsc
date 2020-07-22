#ifndef _SPI_H
#define _SPI_H
#include "stm32l4xx_hal.h"


//SPI INSTANCE
#define HSPI_INSTANCE							&hspi1




//CHIP SELECT PIN AND PORT, STANDARD GPIO
#define LCD_CS_PORT								GPIOE
#define LCD_CS_PIN								GPIO_PIN_11

//DATA COMMAND PIN AND PORT, STANDARD GPIO
#define LCD_DC_PORT								GPIOE
#define LCD_DC_PIN								GPIO_PIN_10

//RESET PIN AND PORT, STANDARD GPIO
#define	LCD_RST_PORT							GPIOE
#define	LCD_RST_PIN								GPIO_PIN_12

#define BURST_MAX_SIZE 	500

#define BLACK       0x0000      
#define NAVY        0x000F      
#define DARKGREEN   0x03E0      
#define DARKCYAN    0x03EF      
#define MAROON      0x7800      
#define PURPLE      0x780F      
#define OLIVE       0x7BE0      
#define LIGHTGREY   0xC618      
#define DARKGREY    0x7BEF      
#define BLUE        0x001F      
#define GREEN       0x07E0      
#define CYAN        0x07FF      
#define RED         0xF800     
#define MAGENTA     0xF81F      
#define YELLOW      0xFFE0      
#define WHITE       0xFFFF      
#define ORANGE      0xFD20      
#define GREENYELLOW 0xAFE5     
#define PINK        0xF81F



void write8(uint8_t value);
void writecmd(uint8_t cmd);
void SPI_Send(unsigned char SPI_Data);
void SPI_Init(void);
void LCD_Reset(void);
void LCD_Enable(void);
void LCD_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
void LCD_Draw_Color(uint16_t Color);
void LCD_Draw_Color_Burst(uint16_t Color, uint32_t Size);
void LCD_Fill_Screen(uint16_t Color);



#endif

