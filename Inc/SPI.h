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
void LCD_Vertical_Line(uint16_t x, uint16_t y, uint16_t height, uint16_t color);
void LCD_Horizontal_Line(uint16_t x, uint16_t y, uint16_t width, uint16_t color);
void LCD_Draw_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void LCD_Draw_Grid(void);
void LCD_Draw_Char(uint16_t x, uint16_t y, uint16_t color, uint16_t number, uint16_t character, uint8_t size);
void LCD_Set_Rotation(uint8_t rotation);

static unsigned char const chars8[][8] = {
	//SPACE
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	// !
	{0x04,0x04,0x04,0x04,0x00,0x04,0x00,0x00},
	// "
	{0x0A,0x0A,0x0A,0x00,0x00,0x00,0x00,0x00},
	// #
	{0x0A,0x0A,0x1F,0x0A,0x1F,0x0A,0x0A,0x00},
	// $
	{0x04,0x0F,0x14,0x0E,0x05,0x1E,0x04,0x00},
	// %
	{0x18,0x19,0x02,0x04,0x08,0x13,0x03,0x00},
	// &
	{0x0C,0x12,0x14,0x08,0x14,0x12,0x0D,0x00},
	// '
	{0x0C,0x04,0x08,0x00,0x00,0x00,0x00,0x00},
	// (
	{0x02,0x04,0x08,0x08,0x08,0x04,0x02,0x00},
	// )
	{0x08,0x04,0x02,0x02,0x02,0x04,0x08,0x00},
	// *
	{0x00,0x04,0x15,0x0E,0x15,0x04,0x00,0x00},
	// +
	{0x00,0x04,0x04,0x1F,0x04,0x04,0x00,0x00},
	// ,
	{0x00,0x00,0x00,0x00,0x0C,0x04,0x08,0x00},
	// -
	{0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00},
	// .
	{0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00},
	// /
	{0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00},
	// 0
	{0x0E,0x11,0x13,0x15,0x19,0x11,0x0E,0x00},
	// 1
	{0x04,0x0C,0x04,0x04,0x04,0x04,0x0E,0x00},
	// 2
	{0x0E,0x11,0x01,0x02,0x04,0x08,0x1F,0x00},
	// 3
	{0x1F,0x02,0x04,0x02,0x01,0x11,0x0E,0x00},
	// 4
	{0x02,0x06,0x0A,0x12,0x1F,0x02,0x02,0x00},
	// 5
	{0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E,0x00},
	// 6
	{0x06,0x08,0x10,0x1E,0x11,0x11,0x0E,0x00},
	// 7
	{0x1F,0x01,0x02,0x04,0x08,0x08,0x08,0x00},
	// 8
	{0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E,0x00},
	// 9
	{0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C,0x00},
	// :
	{0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00},
	// ;
	{0x00,0x0C,0x0C,0x00,0x0C,0x04,0x08,0x00},
	// <
	{0x02,0x04,0x08,0x10,0x08,0x04,0x02,0x00},
	// =
	{0x00,0x00,0x1F,0x00,0x1F,0x00,0x00,0x00},
	// >
	{0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00},
	// ?
	{0x0E,0x11,0x01,0x02,0x04,0x00,0x04,0x00},
	// @
	{0x0E,0x11,0x01,0x0D,0x15,0x15,0x0E,0x00},
	// A
	{0x0E,0x11,0x11,0x11,0x1F,0x11,0x11,0x00},
	// B
	{0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E,0x00},
	// C
	{0x0E,0x11,0x10,0x10,0x10,0x11,0x0E,0x00},
	// D
	{0x1C,0x12,0x11,0x11,0x11,0x12,0x1C,0x00},
	// E
	{0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F,0x00},
	// F
	{0x1F,0x10,0x10,0x1E,0x10,0x10,0x10,0x00},
	//{0x00,0x10,0x10,0x10,0x1E,0x10,0x10,0x1F},
	// G
	{0x0E,0x11,0x10,0x17,0x11,0x11,0x0E,0x00},
	// H
	{0x11,0x11,0x11,0x1F,0x11,0x11,0x11,0x00},
	// I
	{0x0E,0x04,0x04,0x04,0x04,0x04,0x0E,0x00},
	// J
	{0x07,0x02,0x02,0x02,0x02,0x12,0x0C,0x00},
	// K
	{0x11,0x12,0x14,0x18,0x14,0x12,0x11,0x00},
	// L
	{0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0x00},
	// M
	{0x11,0x1B,0x15,0x15,0x11,0x11,0x11,0x00},
	// N
	{0x11,0x11,0x19,0x15,0x13,0x11,0x11,0x00},
	// O
	{0x0E,0x11,0x11,0x11,0x11,0x11,0x0E,0x00},
	// P
	{0x1E,0x11,0x11,0x1E,0x10,0x10,0x10,0x00},
	// Q
	{0x0E,0x11,0x11,0x11,0x15,0x12,0x0D,0x00},
	// R
	{0x1E,0x11,0x11,0x1E,0x14,0x12,0x11,0x00},
	// S
	{0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E,0x00},
	// T
	{0x1F,0x04,0x04,0x04,0x04,0x04,0x04,0x00},
	// U
	{0x11,0x11,0x11,0x11,0x11,0x11,0x0E,0x00},
	// V
	{0x11,0x11,0x11,0x11,0x11,0x0A,0x04,0x00},
	// W
	{0x11,0x11,0x11,0x11,0x15,0x15,0x0E,0x00},
	// X
	{0x11,0x11,0x0A,0x04,0x0A,0x11,0x11,0x00},
	// Y
	{0x11,0x11,0x11,0x0A,0x04,0x04,0x04,0x00},
	// Z
	{0x1F,0x01,0x02,0x04,0x08,0x10,0x1F,0x00},
	// [
	{0x0E,0x08,0x08,0x08,0x08,0x08,0x0E,0x00},
	//
	{0x11,0x0A,0x1F,0x04,0x1F,0x04,0x04,0x00},
	// ]
	{0x0E,0x02,0x02,0x02,0x02,0x02,0x0E,0x00},
	// ^
	{0x04,0x0A,0x11,0x00,0x00,0x00,0x00,0x00},
	// _
	{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00},
	// '
	{0x08,0x04,0x00,0x00,0x00,0x00,0x00,0x00},
	// a
	{0x00,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x00},
	// b
	{0x10,0x10,0x1E,0x11,0x11,0x11,0x1E,0x00},
	// c
	{0x00,0x00,0x0E,0x10,0x10,0x11,0x0E,0x00},
	// d
	{0x01,0x01,0x0D,0x13,0x11,0x11,0x0F,0x00},
	// e
	{0x00,0x00,0x0E,0x11,0x1F,0x10,0x0E,0x00},
	// f
	{0x06,0x09,0x08,0x1C,0x08,0x08,0x08,0x00},
	// g
	{0x00,0x0F,0x11,0x11,0x0F,0x01,0x0E,0x00},
	// h
	{0x10,0x10,0x16,0x19,0x11,0x11,0x11,0x00},
	// i
	{0x04,0x00,0x0C,0x04,0x04,0x04,0x0E,0x00},
	// j
	{0x02,0x00,0x06,0x02,0x02,0x12,0x0C,0x00},
	// k
	{0x10,0x10,0x12,0x14,0x18,0x14,0x12,0x00},
	// l
	{0x18,0x08,0x08,0x08,0x08,0x08,0x1C,0x00},
	// m
	{0x00,0x00,0x1A,0x15,0x15,0x11,0x11,0x00},
	// n
	{0x00,0x00,0x16,0x19,0x11,0x11,0x11,0x00},
	// o
	{0x00,0x00,0x0E,0x11,0x11,0x11,0x0E,0x00},
	// p
	{0x00,0x00,0x1E,0x11,0x1E,0x10,0x10,0x00},
	// q
	{0x00,0x00,0x0F,0x11,0x0F,0x01,0x01,0x00},
	// r
	{0x00,0x00,0x16,0x19,0x10,0x10,0x10,0x00},
	// s
	{0x00,0x00,0x0E,0x10,0x0E,0x01,0x1E,0x00},
	// t
	{0x08,0x08,0x1C,0x08,0x08,0x09,0x06,0x00},
	// u
	{0x00,0x00,0x11,0x11,0x11,0x13,0x0D,0x00},
	// v
	{0x00,0x00,0x11,0x11,0x11,0x0A,0x04,0x00},
	// w
	{0x00,0x00,0x11,0x11,0x11,0x15,0x0A,0x00},
	// x
	{0x00,0x00,0x11,0x0A,0x04,0x0A,0x11,0x00},
	// y
	{0x00,0x00,0x11,0x11,0x0F,0x01,0x0E,0x00},
	// z
	{0x00,0x00,0x1F,0x02,0x04,0x08,0x1F,0x00}
};


static unsigned char const chars16[][16] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/

	{0x00,0x00,0x00,0x18,0x3C,0x3C,0x3C,0x18,0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x00},/*"!",1*/

	{0x00,0x00,0x00,0x66,0x66,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/

	{0x00,0x00,0x00,0x36,0x36,0x7F,0x36,0x36,0x36,0x7F,0x36,0x36,0x00,0x00,0x00,0x00},/*"#",3*/

	{0x00,0x18,0x18,0x3C,0x66,0x60,0x30,0x18,0x0C,0x06,0x66,0x3C,0x18,0x18,0x00,0x00},/*"$",4*/

	{0x00,0x00,0x70,0xD8,0xDA,0x76,0x0C,0x18,0x30,0x6E,0x5B,0x1B,0x0E,0x00,0x00,0x00},/*"%",5*/

	{0x00,0x00,0x00,0x38,0x6C,0x6C,0x38,0x60,0x6F,0x66,0x66,0x3B,0x00,0x00,0x00,0x00},/*"&",6*/

	{0x00,0x00,0x00,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/

	{0x00,0x00,0x00,0x0C,0x18,0x18,0x30,0x30,0x30,0x30,0x30,0x18,0x18,0x0C,0x00,0x00},/*"(",8*/

	{0x00,0x00,0x00,0x30,0x18,0x18,0x0C,0x0C,0x0C,0x0C,0x0C,0x18,0x18,0x30,0x00,0x00},/*")",9*/

	{0x00,0x00,0x00,0x00,0x00,0x36,0x1C,0x7F,0x1C,0x36,0x00,0x00,0x00,0x00,0x00,0x00},/*"*",10*/

	{0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00},/*"+",11*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x0C,0x18,0x00,0x00},/*",",12*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"-",13*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x00},/*".",14*/

	{0x00,0x00,0x00,0x06,0x06,0x0C,0x0C,0x18,0x18,0x30,0x30,0x60,0x60,0x00,0x00,0x00},/*"/",15*/

	{0x00,0x00,0x00,0x1E,0x33,0x37,0x37,0x33,0x3B,0x3B,0x33,0x1E,0x00,0x00,0x00,0x00},/*"0",16*/

	{0x00,0x00,0x00,0x0C,0x1C,0x7C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x00,0x00,0x00,0x00},/*"1",17*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x06,0x0C,0x18,0x30,0x60,0x7E,0x00,0x00,0x00,0x00},/*"2",18*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x06,0x1C,0x06,0x66,0x66,0x3C,0x00,0x00,0x00,0x00},/*"3",19*/

	{0x00,0x00,0x00,0x30,0x30,0x36,0x36,0x36,0x66,0x7F,0x06,0x06,0x00,0x00,0x00,0x00},/*"4",20*/

	{0x00,0x00,0x00,0x7E,0x60,0x60,0x60,0x7C,0x06,0x06,0x0C,0x78,0x00,0x00,0x00,0x00},/*"5",21*/

	{0x00,0x00,0x00,0x1C,0x18,0x30,0x7C,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00,0x00},/*"6",22*/

	{0x00,0x00,0x00,0x7E,0x06,0x0C,0x0C,0x18,0x18,0x30,0x30,0x30,0x00,0x00,0x00,0x00},/*"7",23*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x76,0x3C,0x6E,0x66,0x66,0x3C,0x00,0x00,0x00,0x00},/*"8",24*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x3E,0x0C,0x18,0x38,0x00,0x00,0x00,0x00},/*"9",25*/

	{0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x00},/*":",26*/

	{0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x1C,0x1C,0x0C,0x18,0x00,0x00},/*";",27*/

	{0x00,0x00,0x00,0x06,0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x06,0x00,0x00,0x00,0x00},/*"<",28*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"=",29*/

	{0x00,0x00,0x00,0x60,0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x60,0x00,0x00,0x00,0x00},/*">",30*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x0C,0x18,0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x00},/*"?",31*/

	{0x00,0x00,0x00,0x7E,0xC3,0xC3,0xCF,0xDB,0xDB,0xCF,0xC0,0x7F,0x00,0x00,0x00,0x00},/*"@",32*/

	{0x00,0x00,0x00,0x18,0x3C,0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00,0x00,0x00,0x00},/*"A",33*/

	{0x00,0x00,0x00,0x7C,0x66,0x66,0x66,0x7C,0x66,0x66,0x66,0x7C,0x00,0x00,0x00,0x00},/*"B",34*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x60,0x60,0x60,0x66,0x66,0x3C,0x00,0x00,0x00,0x00},/*"C",35*/

	{0x00,0x00,0x00,0x78,0x6C,0x66,0x66,0x66,0x66,0x66,0x6C,0x78,0x00,0x00,0x00,0x00},/*"D",36*/

	{0x00,0x00,0x00,0x7E,0x60,0x60,0x60,0x7C,0x60,0x60,0x60,0x7E,0x00,0x00,0x00,0x00},/*"E",37*/

	{0x00,0x00,0x00,0x7E,0x60,0x60,0x60,0x7C,0x60,0x60,0x60,0x60,0x00,0x00,0x00,0x00},/*"F",38*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x60,0x60,0x6E,0x66,0x66,0x3E,0x00,0x00,0x00,0x00},/*"G",39*/

	{0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00},/*"H",40*/

	{0x00,0x00,0x00,0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x3C,0x00,0x00,0x00,0x00},/*"I",41*/

	{0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x66,0x66,0x3C,0x00,0x00,0x00,0x00},/*"J",42*/

	{0x00,0x00,0x00,0x66,0x66,0x6C,0x6C,0x78,0x6C,0x6C,0x66,0x66,0x00,0x00,0x00,0x00},/*"K",43*/

	{0x00,0x00,0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7E,0x00,0x00,0x00,0x00},/*"L",44*/

	{0x00,0x00,0x00,0x63,0x63,0x77,0x6B,0x6B,0x6B,0x63,0x63,0x63,0x00,0x00,0x00,0x00},/*"M",45*/

	{0x00,0x00,0x00,0x63,0x63,0x73,0x7B,0x6F,0x67,0x63,0x63,0x63,0x00,0x00,0x00,0x00},/*"N",46*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00,0x00},/*"O",47*/

	{0x00,0x00,0x00,0x7C,0x66,0x66,0x66,0x7C,0x60,0x60,0x60,0x60,0x00,0x00,0x00,0x00},/*"P",48*/

	{0x00,0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x0C,0x06,0x00,0x00},/*"Q",49*/

	{0x00,0x00,0x00,0x7C,0x66,0x66,0x66,0x7C,0x6C,0x66,0x66,0x66,0x00,0x00,0x00,0x00},/*"R",50*/

	{0x00,0x00,0x00,0x3C,0x66,0x60,0x30,0x18,0x0C,0x06,0x66,0x3C,0x00,0x00,0x00,0x00},/*"S",51*/

	{0x00,0x00,0x00,0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00},/*"T",52*/

	{0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00,0x00},/*"U",53*/

	{0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00,0x00,0x00,0x00},/*"V",54*/

	{0x00,0x00,0x00,0x63,0x63,0x63,0x6B,0x6B,0x6B,0x36,0x36,0x36,0x00,0x00,0x00,0x00},/*"W",55*/

	{0x00,0x00,0x00,0x66,0x66,0x34,0x18,0x18,0x2C,0x66,0x66,0x66,0x00,0x00,0x00,0x00},/*"X",56*/

	{0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00},/*"Y",57*/

	{0x00,0x00,0x00,0x7E,0x06,0x06,0x0C,0x18,0x30,0x60,0x60,0x7E,0x00,0x00,0x00,0x00},/*"Z",58*/

	{0x00,0x00,0x00,0x3C,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3C,0x00},/*"[",59*/

	{0x00,0x00,0x00,0x60,0x60,0x30,0x30,0x18,0x18,0x0C,0x0C,0x06,0x06,0x00,0x00,0x00},/*"\",60*/

	{0x00,0x00,0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00},/*"]",61*/

	{0x00,0x18,0x3C,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",62*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00},/*"_",63*/

	{0x00,0x00,0x00,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",64*/

	{0x00,0x00,0x00,0x00,0x00,0x3C,0x06,0x06,0x3E,0x66,0x66,0x3E,0x00,0x00,0x00,0x00},/*"a",65*/

	{0x00,0x00,0x00,0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0x66,0x7C,0x00,0x00,0x00,0x00},/*"b",66*/

	{0x00,0x00,0x00,0x00,0x00,0x3C,0x66,0x60,0x60,0x60,0x66,0x3C,0x00,0x00,0x00,0x00},/*"c",67*/

	{0x00,0x00,0x00,0x06,0x06,0x3E,0x66,0x66,0x66,0x66,0x66,0x3E,0x00,0x00,0x00,0x00},/*"d",68*/

	{0x00,0x00,0x00,0x00,0x00,0x3C,0x66,0x66,0x7E,0x60,0x60,0x3C,0x00,0x00,0x00,0x00},/*"e",69*/

	{0x00,0x00,0x00,0x1E,0x30,0x30,0x30,0x7E,0x30,0x30,0x30,0x30,0x00,0x00,0x00,0x00},/*"f",70*/

	{0x00,0x00,0x00,0x00,0x00,0x3E,0x66,0x66,0x66,0x66,0x66,0x3E,0x06,0x06,0x7C,0x00},/*"g",71*/

	{0x00,0x00,0x00,0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00},/*"h",72*/

	{0x00,0x00,0x18,0x18,0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,0x00,0x00},/*"i",73*/

	{0x00,0x00,0x0C,0x0C,0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x78,0x00},/*"j",74*/

	{0x00,0x00,0x00,0x60,0x60,0x66,0x66,0x6C,0x78,0x6C,0x66,0x66,0x00,0x00,0x00,0x00},/*"k",75*/

	{0x00,0x00,0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,0x00,0x00},/*"l",76*/

	{0x00,0x00,0x00,0x00,0x00,0x7E,0x6B,0x6B,0x6B,0x6B,0x6B,0x63,0x00,0x00,0x00,0x00},/*"m",77*/

	{0x00,0x00,0x00,0x00,0x00,0x7C,0x66,0x66,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00},/*"n",78*/

	{0x00,0x00,0x00,0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00,0x00},/*"o",79*/

	{0x00,0x00,0x00,0x00,0x00,0x7C,0x66,0x66,0x66,0x66,0x66,0x7C,0x60,0x60,0x60,0x00},/*"p",80*/

	{0x00,0x00,0x00,0x00,0x00,0x3E,0x66,0x66,0x66,0x66,0x66,0x3E,0x06,0x06,0x06,0x00},/*"q",81*/

	{0x00,0x00,0x00,0x00,0x00,0x66,0x6E,0x70,0x60,0x60,0x60,0x60,0x00,0x00,0x00,0x00},/*"r",82*/

	{0x00,0x00,0x00,0x00,0x00,0x3E,0x60,0x60,0x3C,0x06,0x06,0x7C,0x00,0x00,0x00,0x00},/*"s",83*/

	{0x00,0x00,0x00,0x30,0x30,0x7E,0x30,0x30,0x30,0x30,0x30,0x1E,0x00,0x00,0x00,0x00},/*"t",84*/

	{0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x3E,0x00,0x00,0x00,0x00},/*"u",85*/

	{0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00,0x00,0x00,0x00},/*"v",86*/

	{0x00,0x00,0x00,0x00,0x00,0x63,0x6B,0x6B,0x6B,0x6B,0x36,0x36,0x00,0x00,0x00,0x00},/*"w",87*/

	{0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x3C,0x18,0x3C,0x66,0x66,0x00,0x00,0x00,0x00},/*"x",88*/

	{0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x0C,0x18,0xF0,0x00},/*"y",89*/

	{0x00,0x00,0x00,0x00,0x00,0x7E,0x06,0x0C,0x18,0x30,0x60,0x7E,0x00,0x00,0x00,0x00},/*"z",90*/

	{0x00,0x00,0x00,0x0C,0x18,0x18,0x18,0x30,0x60,0x30,0x18,0x18,0x18,0x0C,0x00,0x00},/*"{",91*/

	{0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00},/*"|",92*/

	{0x00,0x00,0x00,0x30,0x18,0x18,0x18,0x0C,0x06,0x0C,0x18,0x18,0x18,0x30,0x00,0x00},/*"}",93*/

	{0x00,0x00,0x00,0x71,0xDB,0x8E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",94*/
};
#endif

