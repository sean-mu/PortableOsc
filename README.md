Project: Portable Oscilloscope

Description:  This project utlizes an STM32l476-Discovery Board's ADC to display an input test signal in graphical format
			  on a 3.5" TFT Display using the HX8357-D driver board.  


Pinmap:  Pinout used can be viewed by opening the included pinmap.png file.

Notes and thanks:  Most of the graphical code is ported from the Adafruit arduino HX8357-D and graphics libraries.

Use:  The device displays a single array of ADC data at a time.  This is triggered anytime a button attached to PB2 is pressed.  Measurements currently including minimum
	  maximum, and peak to peak voltages can be displayed by pushing a button attached to PB3.  The current ADC value is also printed to show the 12-bit ADC was used.  
	  Voltage ranges of 0-25, or 0-5V are available, and this is switched via button input to PB6.
	  Time scale can be changed from 64 microseconds per division to 10.67 microseconds per division via button input to PB7.