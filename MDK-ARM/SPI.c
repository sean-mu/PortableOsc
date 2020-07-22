#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_spi.h"
#include "SPI.h"

//CS pin -> PE11
//DC pin -> PE10

extern SPI_HandleTypeDef hspi1;
volatile uint16_t LCD_HEIGHT = 480;
volatile uint16_t LCD_WIDTH	 = 320;



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
