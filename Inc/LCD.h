#ifndef _LCD_H
#define _LCD_H

// HX8357-D Commands
#define HX8357D_CMD_SWRESET     0x01
#define HX8357D_CMD_SLPOUT      0x11
#define HX8357D_CMD_DISPON      0x29
#define HX8357D_CMD_COLMOD      0x3A
#define HX8357D_CMD_SETOSC      0xB0
#define HX8357D_CMD_SETEXC      0xB9
#define HX8357D_CMD_SETPANEL    0xCC
#define HX8357D_MADCTL  				0x36

#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left

void LCD_Init(void);
void LCD_Init2(void);


#endif
