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




