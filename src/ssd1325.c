/////////////////////////////////////////////////
// This File Built by Rayden.Wang
// 2019.03.13 Version 0.1
//
/////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "ssd1325.h"
#include "spi_user.h"
#include "gpio_user.h"

static uint8_t NULL_BUF[4096];

int ssd1325_send_command(uint8_t ADDR, uint8_t len, uint8_t *command){
	uint8_t buf[16];
	if(len > 16){
		printf("SSD1325 command length ERROR:(%d)\n",len);
		return -1;
	}
	gpio_rw(DC, 0);
	memset(buf, 0, sizeof(uint8_t)*16);
	buf[0] = ADDR;
	if(len > 1)memmove(buf+1, command, len-1);
	spi_data_rw(OLED, buf, NULL_BUF, len);
	return 0;
}

int ssd1325_flash(uint8_t *buf){
	static uint32_t GRAY_MASK = GRAY << 28;
	uint32_t RAM_MASK;
	uint16_t cont;
	uint8_t cont_bits;
	uint8_t RAM_DISPLAY[4096];
	for(cont=0;cont<1024;cont++){
		RAM_MASK = 0;
		for(cont_bits=0;cont_bits<8;cont_bits++){
			RAM_MASK >>= 4;
			if(1 == ((*(buf+cont) >> cont_bits) & 0x01))RAM_MASK |= GRAY_MASK;
		}
		RAM_DISPLAY[cont*4]     = (RAM_MASK >> 24) & 0xFF;
		RAM_DISPLAY[cont*4 + 1] = (RAM_MASK >> 16) & 0xFF;
		RAM_DISPLAY[cont*4 + 2] = (RAM_MASK >> 8)  & 0xFF;
		RAM_DISPLAY[cont*4 + 3] = (RAM_MASK)       & 0xFF;
		//printf("[%d] BUF:0x%X --> RAM_MASK:0x%X\n",cont,*(buf+cont),RAM_MASK);
	}
	gpio_rw(DC, 1);
	spi_data_rw(OLED, RAM_DISPLAY, NULL_BUF, 4096);
	gpio_rw(DC, 0);
	return 0;
}

int ssd1325_init(){
	uint8_t comdata[5];
	int error_flag;
	memset(NULL_BUF, 0, sizeof(uint8_t)*1024);
	gpio_rw(DC, 0);
	gpio_rw(RES, 0);
	usleep(100);
	gpio_rw(RES, 1);
	
	error_flag = 0;
	// Set clock
	error_flag += ssd1325_send_command(SET_DP_OFF,NULL_BUF); // Display OFF
	comdata[0] = 0x01; // Divide of Oscillator
	comdata[1] = 0x90; // Frequency of Oscillator
	error_flag += ssd1325_send_command(SET_FREQ,comdata); // Set display clock divide ratio and oscillator frequency
	comdata[0] = 0x27; // 39 DCLKs for per period
	error_flag += ssd1325_send_command(SET_RP,comdata); // Set row period
	comdata[0] = 0x05;
	comdata[1] = 0x50;
	error_flag += ssd1325_send_command(SET_PL,comdata); // Set phase length

	// Set Interface of OLED
	comdata[0] = 0x50;
	error_flag += ssd1325_send_command(SET_MR,comdata); // Set multiplex ratio
	comdata[0] = 0x00;
	comdata[1] = 0x3F;
	error_flag += ssd1325_send_command(SET_CA,comdata); // Set Start/End column address
	comdata[0] = 0x04;
	comdata[1] = 0x43;
	error_flag += ssd1325_send_command(SET_RA,comdata); // Set Start/End Row address
	comdata[0] = 0x00;
	error_flag += ssd1325_send_command(SET_DO,comdata); // Set display offset
	comdata[0] = 0x00;
	error_flag += ssd1325_send_command(SET_DSL,comdata); // Set display start line
	comdata[0] = 0x52;
	error_flag += ssd1325_send_command(SET_RE,comdata); // Set Re-Map

	// Other configure
	comdata[0] = 0x02;
	error_flag += ssd1325_send_command(SET_MC,comdata); // Set master configuration
	error_flag += ssd1325_send_command(SET_CR_FULL,NULL_BUF); // Set current range
	comdata[0] = 0x4F;
	error_flag += ssd1325_send_command(SET_CC,comdata); // Set contrast control
	comdata[0] = 0x10;
	error_flag += ssd1325_send_command(SET_PV,comdata); // Set pre-charge voltage
	comdata[0] = 0x02;
	error_flag += ssd1325_send_command(SET_PCCL,comdata); // Set pre-charge compensation level
	comdata[0] = 0x28;
	error_flag += ssd1325_send_command(SET_PCCE,comdata); // Set pre_charge compensation enable
	comdata[0] = 0x1C;
	error_flag += ssd1325_send_command(SET_VV,comdata); // Set VCOMH voltage
	comdata[0] = 0x0D;
	error_flag += ssd1325_send_command(SET_VSL,comdata); // Set segment low voltage
	error_flag += ssd1325_send_command(SET_DM_NORMAL,NULL_BUF); // Set display mode normal

	// Clean BUF
	comdata[0] = 0x00; // 
	comdata[1] = 0x00;
	comdata[2] = 0x3F;
	comdata[3] = 0x3F;
	comdata[4] = 0x00;
	error_flag += ssd1325_send_command(GAC_DR,comdata); // Draw a rectangle (Clean BUFFER)
	error_flag += ssd1325_send_command(SET_DP_ON,NULL_BUF); // Display on
	if(error_flag < 0){
		printf("Initial ERROR(%d)\n",error_flag);
		return -1;
	}
	return 0;
}

int ssd1325_test(){
	ssd1325_send_command(SET_DM_ED_ON,NULL_BUF);
	ssd1325_send_command(SET_DP_ON,NULL_BUF);
	sleep(1);
	ssd1325_send_command(SET_DP_OFF,NULL_BUF);
}

