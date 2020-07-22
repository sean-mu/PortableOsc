#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_spi.h"
#include "LCD.h"
#include "SPI.h"

#define CS_LOW (HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET)) //pull CS low
#define CS_HIGH (HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET)) //pull CS high


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
	
	//Sleep mode off
	writecmd(HX8357D_CMD_SLPOUT);
	HAL_Delay(150);
	
	//Display ON
	writecmd(HX8357D_CMD_DISPON);
	HAL_Delay(50);
	
}
