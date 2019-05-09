#ifndef __SSD1325_H
#define __SSD1325_H
///////////////////////////////////////////
// This File Built by Rey Wang
// 2019.03.12 Version 0.1
///////////////////////////////////////////
#include <stdint.h>

// Fundamental Command Table
#define SET_CA		0x15,3  //Set Column Address
#define SET_RA		0x75,3  //Set Row Address
#define SET_CC		0x81,2  //Set Contrast Current

#define SET_CR_RESET	0x84,1  //Set Current Range --> RESET
#define SET_CR_HALF	0x85,1  //Set Current Range --> HALF
#define SET_CR_FULL	0x86,1  //Set Current Range --> FULL

#define SET_RE		0xA0,2  //Set Re-map
#define SET_DSL		0xA1,2  //Set Display Start Line
#define SET_DO		0xA2,2  //Set Display Offset

#define SET_DM_NORMAL	0xA4,1  //Set Display Mode --> Normal
#define SET_DM_ED_ON	0xA5,1  //Set Display Mode --> Entire Display On
#define SET_DM_ED_OFF	0xA6,1  //Set Display Mode --> Entire Display Off
#define SET_DM_ID	0xA7,1  //Set Display Mode --> Inverse Display

#define SET_MR		0xA8,2  //Set Multiplex Ratio
#define SET_MC		0xAD,2  //Set Master Configuration
#define SET_DP_OFF	0xAE,1  //Set Display OFF
#define SET_DP_ON	0xAF,1  //Set Display ON

#define SET_PCCE	0xB0,2  //Set Pre-charge Compensation Enable
#define SET_PCCL	0xB4,2  //Set Pre-Charge Compensation Level
#define SET_PV		0xBC,2  //Set Pre-Charge Voltage
#define SET_PL		0xB1,3  //Set Phase Length
#define SET_RP		0xB2,2  //Set Row Period(frame frequency)
#define SET_FREQ	0xB3,3  //Set Display Clock Divide Ratio
#define SET_GRAY	0xB8,16 //Set Gray Scale Table
#define SET_VV		0xBE,2  //Set Vcomh Voltage
#define SET_VSL		0xBF,2  //Set Segment Low Voltage
#define OLED_NOP	0xE3,1  //NOP

//Graphic acceleration command
#define GAC_GACO	0x23,2  //Graphic Acceleration Command Options
#define GAC_DR		0x24,6  //Draw Rectangle
#define GAC_COPY	0x25,7  //Copy
#define GAC_HS		0x26,4  //Horizontal Scroll
#define GAC_STOP	0x2E,1  //Stop Moving
#define GAC_START	0x2F,1  //Start Moving

#define GRAY		0x0F

/***************************************************************
 * Mapping between display_buffer and OLED display
 *
 *   +---+----------------------------------------+
 *   |   |                 COLUME                 |
 *   +---+----------------------------------------+
 *   |   |   D0  |   D1  | ...... |  D14  |  D15  |
 *   |   +-------+-------+--------+-------+-------+
 *   | R |  D16  |  D17  | ...... |  D30  |  D31  |
 *   |   +-------+-------+--------+-------+-------+
 *   | O |    ......       ......      ......     |
 *   |   +-------+-------+--------+-------+-------+
 *   | W |  D992 |  D993 | ...... | D1016 | D1017 |
 *   |   +-------+-------+--------+-------+-------+
 *   |   | D1008 | D1009 | ...... | D1022 | D1023 |
 *   +---+-------+-------+--------+-------+-------+
 ***************************************************************/
static uint8_t display_buffer[1024];
 
/**********************************************************************
 * ssd1325_send_command(u8 addr, u8 len, u8 *data)
 * 	@Addr & len: Them are defined by Fundamental Command Table 
 * 	             and Graphic acceleration command Table
 **********************************************************************/
int ssd1325_send_command(uint8_t, uint8_t, uint8_t *);

/**********************************************************************
 * ssd1325_flash(uint8_t *buf);
 * 	Send display_buffer to OLED
 **********************************************************************/
int ssd1325_flash(uint8_t *);

int ssd1325_init();

int ssd1325_test();

#endif
