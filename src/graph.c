/////////////////////////////////////////////////
// This File Built by Rey Wang
// 2019.03.22 Version 0.1
//
/////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <string.h>

void pix_set(uint8_t *buf, uint8_t x, uint8_t y, uint8_t status){
	uint8_t pix_byte;
	uint8_t pix_x,pix_y;
	uint16_t num;
	if((x < 128) && (y < 64)){
		pix_byte = 0x01 << 7 - x%8;
		num = x/8 + y*16;
		if(0 == status) *(buf + num) &= ~pix_byte;
		else *(buf + num) |= pix_byte;
	}
	//printf("Pixel (%d,%d) changed to %d\t(num=%d,data=0x%X)\n",x,y,status,num,*(buf + num));
}

void pix_inv(){

}
