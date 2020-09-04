#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_spi.h"
#include "LCD.h"
#include "SPI.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


extern SPI_HandleTypeDef hspi1;
static uint16_t LCD_HEIGHT = 320;
static uint16_t LCD_WIDTH	 = 480;

void LCD_Display_Measurements(uint16_t sample[],int atten)
{
	LCD_Fill_Screen(BLACK);
	float max=0;
	float min=320;
	float volt=0.0;
	
	if(atten==1)
	{
		for(int x=0;x<478;x++)
		{
			sample[x]=sample[x]/5;
		}
	}
	
	//calc max/min sample values
	for(int x=0;x<478;x++)
	{
		if(sample[x] > max)
		{
			max = sample[x];
		}
		if(sample[x] < min)
		{
			min = sample[x];
		}
	}
	
	//calc average
	float avg = 0;
	for(int x=0;x<478;x++)
	{
		avg+=sample[x];
	}
	avg = avg/478.0f;
	
	//Convert max min and avg into voltage values
	max = max*(25.0f/320.0f);
	min = min*(25.0f/320.0f);
	avg = avg*(25.0f/320.0f);
	
	//Display Vmax
	LCD_Draw_String(0,300,GREEN,BLACK,"Vmax",2);
	char buf[5];
	snprintf(buf,5,"%f",max);
	LCD_Draw_String(50,300,GREEN,BLACK,buf,2);
	
	//Display Vmin
	LCD_Draw_String(0,280,GREEN,BLACK,"Vmin",2);
	snprintf(buf,5,"%f",min);
	LCD_Draw_String(50,280,GREEN,BLACK,buf,2);
	
	//calc and display peak to peak voltage
	volt = max-min;
	LCD_Draw_String(0,260,GREEN,BLACK,"Vpp",2);
	snprintf(buf,5,"%f",volt);
	LCD_Draw_String(50,260,GREEN,BLACK,buf,2);
	
	//Display average voltage
	LCD_Draw_String(0,240,GREEN,BLACK,"Avg",2);
	snprintf(buf,5,"%f",avg);
	LCD_Draw_String(50,240,GREEN,BLACK,buf,2);
	
	

	
}

void LCD_Init(void){
	
	LCD_Enable();
	SPI_Init();
	LCD_Reset();
	
	//Software reset
	writecmd(HX8357D_CMD_SWRESET);
	HAL_Delay(1000);
	
	//Enable extended commands
	writecmd(HX8357D_CMD_SETEXC);
	write8(0xFF);
	write8(0x83);
	write8(0x57);
	write8(0xFF);
	HAL_Delay(300);
	
	//Set oscillator  Normal mode 70Hz, Idle mode 55 Hz
	writecmd(HX8357D_CMD_SETOSC);
	write8(0x68);
	
	//Set Panel BGR
	writecmd(HX8357D_CMD_SETPANEL);
	write8(0x05);
	
	//16 bit color mode
	writecmd(HX8357D_CMD_COLMOD);
	write8(0x55);
		
	writecmd(0x36);  //Memory access control
	write8(0x00);
  writecmd(0x35);
	write8(0x00);
	
	writecmd(0x44);
	write8(0x00);
	write8(0x02);
	
	//Sleep mode off
	writecmd(HX8357D_CMD_SLPOUT);
	HAL_Delay(150);
	
	//Display ON
	writecmd(HX8357D_CMD_DISPON);
	HAL_Delay(50);
	

	
	//Change display orientation
	//writecmd(0x36);
	//write8(MADCTL_MV);
	
}

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
		LCD_Vertical_Line(i,0,288,LIGHTGREY);
	}
	for(int i=0;i<=320;i += 32)
	{
		LCD_Horizontal_Line(0,i,480,LIGHTGREY);
	}
	
	LCD_Vertical_Line(240,0,288,GREEN);
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




