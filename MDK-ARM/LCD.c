#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_spi.h"
#include "LCD.h"
#include "SPI.h"




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
		
	//writecmd(0x36);  //Memory access control
	//write8(0x00);
	
	
	//Sleep mode off
	writecmd(HX8357D_CMD_SLPOUT);
	HAL_Delay(150);
	
	//Display ON
	writecmd(HX8357D_CMD_DISPON);
	HAL_Delay(50);
	
	//Change display orientation
	writecmd(0x36);
	write8(MADCTL_MV);
	
}




