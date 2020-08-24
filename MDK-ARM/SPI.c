#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_spi.h"
#include "SPI.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//CS pin -> PE11
//DC pin -> PE10

extern SPI_HandleTypeDef hspi1;
static uint16_t LCD_HEIGHT = 320;
static uint16_t LCD_WIDTH	 = 480;



void SPI_Send(unsigned char SPI_Data)
{
	HAL_SPI_Transmit(HSPI_INSTANCE, &SPI_Data, 1, 1);
}	


void write8(uint8_t value){
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);	
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	SPI_Send(value);	
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void setGain(uint8_t gain){
	HAL_GPIO_WritePin(PGA_CS_PORT, PGA_CS_PIN, GPIO_PIN_RESET);
	SPI_Send(PGA_WRITE);
	SPI_Send(gain);
	HAL_GPIO_WritePin(PGA_CS_PORT, PGA_CS_PIN, GPIO_PIN_SET);
}



void writecmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);	
	SPI_Send(cmd);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void SPI_Init(void)
{
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
}
/*
void LCD_Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);	
}

void LCD_Enable(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}


void LCD_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	writecmd(0x2A); //Column address set
	write8(X1>>8);
	write8(X1);
	write8(X2>>8);
	write8(X2);

	writecmd(0x2B); //Row address set
	write8(Y1>>8);
	write8(Y1);
	write8(Y2>>8);
	write8(Y2);

	writecmd(0x2C);  //Write to Ram
}

void LCD_Draw_Color(uint16_t Color)
{
	//SENDS COLOR
	unsigned char TempBuffer[2] = {Color>>8, Color};	
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);	
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit(HSPI_INSTANCE, TempBuffer, 2, 1);	
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}



void LCD_Draw_Color_Burst(uint16_t Color, uint32_t Size)
{
	
	uint32_t Buffer_Size = 0;
	if((Size*2) < BURST_MAX_SIZE)
	{
		Buffer_Size = Size;
	}
	else
	{
		Buffer_Size = BURST_MAX_SIZE;
	}
		
	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);	
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

	unsigned char chifted = 	Color>>8;;
	unsigned char burst_buffer[Buffer_Size];
	for(uint32_t j = 0; j < Buffer_Size; j+=2)
		{
			burst_buffer[j] = 	chifted;
			burst_buffer[j+1] = Color;
		}

	uint32_t Sending_Size = Size*2;
	uint32_t Sending_in_Block = Sending_Size/Buffer_Size;
	uint32_t Remainder_from_block = Sending_Size%Buffer_Size;

	if(Sending_in_Block != 0)
	{
		for(uint32_t j = 0; j < (Sending_in_Block); j++)
			{
			HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Buffer_Size, 10);	
			}
	}

	//REMAINDER!
	HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Remainder_from_block, 10);	
		
	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void LCD_Fill_Screen(uint16_t Color)
{
	LCD_Set_Address(0,0,LCD_WIDTH,LCD_HEIGHT);	
	LCD_Draw_Color_Burst(Color, LCD_WIDTH*LCD_HEIGHT);	
}

void LCD_Vertical_Line(uint16_t x, uint16_t y, uint16_t height, uint16_t color)
{
	//Error check x or y out of bounds
	if((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
	if((y+height-1) >= LCD_HEIGHT) height = LCD_HEIGHT-y;
	LCD_Set_Address(x,y,x,y+height-1);
	LCD_Draw_Color_Burst(color,height);
}

void LCD_Horizontal_Line(uint16_t x, uint16_t y, uint16_t width, uint16_t color)
{
	//Error check x or y out of bounds
	if((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
	if((x+width-1) >= LCD_WIDTH) width = LCD_WIDTH-x;
	LCD_Set_Address(x,y,x+width-1,y);
	LCD_Draw_Color_Burst(color,width);
}

void LCD_Draw_Rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
	//Error check x or y out of bounds
	if((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) return;
	if((y+height-1) >= LCD_HEIGHT) height = LCD_HEIGHT-y;
	if((x+width-1) >= LCD_WIDTH) width = LCD_WIDTH-x;
	LCD_Set_Address(x,y,x+width-1,y+height-1);
	LCD_Draw_Color_Burst(color,width*height);
}

void LCD_Draw_Grid(void)
{
	//LCD_Fill_Screen(BLACK);
	for(int i=16;i<=480;i += 32)
	{
		LCD_Vertical_Line(i,0,480,LIGHTGREY);
	}
	for(int i=0;i<=320;i += 32)
	{
		LCD_Horizontal_Line(0,i,480,LIGHTGREY);
	}
	
	LCD_Vertical_Line(240,0,320,GREEN);
	LCD_Horizontal_Line(0,0,480,GREEN);
	
}

//Draws char. x/y -> position, size must be 1(small) or 2(large).  color = text color, backColor = background color
void LCD_Draw_Char(uint16_t x, uint16_t y, uint16_t color, uint16_t backColor, uint16_t character, uint8_t size)
{
	if(size>2) return;
	if(size==1)
	{
		LCD_Set_Address(x,y,x+5,y+8);
		writecmd(0x2C);
		for(int i=0;i<8;i++)
		{
			for(int j=2;j<8;j++)
			{
					//fills in pixels corresponding to color bitmap in char8
					if((chars8[character-0x20][6-i]>>(7-j))&0x01)
					{
						write8(color>>8);
						write8(color);
					}
					else
					{
						write8(backColor>>8);
						write8(backColor);
					}
				}
			}
		}
	else
	{
		LCD_Set_Address(x,y,x+7,y+16);
		writecmd(0x2C);
		for(int i=0;i<16;i++)
		{
			for(int j=0;j<8;j++)
			{
					if((chars16[character-0x20][16-i]>>(7-j))&0x01)
					{
						write8(color>>8);
						write8(color);
					}
					
					else
					{
						write8(backColor>>8);
						write8(backColor);
					}
				}
			}
		}		
}

void LCD_Set_Rotation(uint8_t rotation){
	writecmd(0x36);
	switch(rotation){
		case 0:
						write8(0x48);
						LCD_WIDTH = 320;
						LCD_HEIGHT = 480;
						break;
		case 1: 
						write8(0x28);
						LCD_WIDTH = 480;
						LCD_HEIGHT = 320;
						break;
		case 2:
						write8(0x88);
						LCD_WIDTH = 320;
						LCD_HEIGHT = 480;
						break;
		case 3:
						write8(0xE8);
						LCD_WIDTH = 480;
						LCD_HEIGHT = 320;
						break;
	}
}


void LCD_Draw_String(uint16_t x, uint16_t y, uint16_t color, uint16_t backColor, unsigned char *str, uint8_t size)
{
	
	uint8_t k = 1;
	switch (size)
	{
	case 1:
		while (*str)
		{
			if ((x+(size*8))>LCD_WIDTH)
			{
				x = 1;
				y = y + (size*8);
			}
			LCD_Draw_Char(x, y, color, backColor, *str, size);
			x += size*8-2;
			*str++;
		}
	break;
	case 2:
		while (*str)
		{
			if ((x+(size*8))>LCD_WIDTH)
			{
				x = 1;
				y = y + (size*8);
			}
			LCD_Draw_Char(x,y,color,backColor,*str,size);
			x += k*8;
			*str++;
		}
	break;
	}
}

void swapInt(int16_t *x, int16_t *y)
{
	int16_t temp = *x;
	*x = *y;
	*y = temp;
}

void LCD_Point(uint16_t x, uint16_t y, uint16_t color)
{
	//error checking to make sure x and y are in bounds
	if((x>=LCD_WIDTH)||(y>=LCD_HEIGHT)) return;
	LCD_Set_Address(x,y,LCD_WIDTH-1,LCD_HEIGHT-1);
	writecmd(0x2C);
	write8(color>>8);
	write8(color);
}


//uses Bresenham's algorithm
void LCD_Line(uint16_t color, int16_t x1, int16_t x2, int16_t y1, int16_t y2)
{
		//s=1 if rise>run, otherwise 0
		int s = abs(y2-y1)>abs(x2-x1);
	
		//Set up points so dx(change in x) always positive, will draw on TFT left to right
		if(s)
		{
			swapInt(&x1,&y1);
			swapInt(&x2,&y2);
		}
		if(x1>x2)
		{
			swapInt(&x1,&x2);
			swapInt(&y1,&y2);
		}
		//Variables for change in x,y, and yStep will be used to hold positive or negative slope
		int16_t dx,dy;
		int16_t yStep;
		dx = (x2-x1);
		int16_t e = dx/2;
		dy = abs(y2-y1);
		
		if(y1<y2) yStep = 1;
		else yStep = -1;
		
		for(;x1<=x2;x1++)
		{
			if(s) LCD_Point(y1,x1,color);
			else LCD_Point(x1,y1,color);
			e -=dy;
			if(e<0)
			{
				y1 += yStep;
				e = dx;
			}
		}
}
*/


