#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "spi_user.h"
#include "gpio_user.h"
#include "gt30l32.h"
#include "ssd1325.h"

int error_flag;

int main(){
	int i;
	uint8_t tx_data1[8]={1,2,3,4,5,6,7,8};
	uint8_t tx_data2[8]={8,7,6,5,4,3,2,1};
	uint8_t rx_data[36];
	uint8_t addr[]={0x1D,0xD9,0x90};
	int data_bits=16;
	error_flag = 0;
	spi_init(OLED);
	spi_init(ZK);
	gpio_init();
	while(1){
		//transform_word('A',rx_data);
		//transform_GB("王",rx_data);
		//for(i=0;i<data_bits;i++)printf("%X ",*(rx_data+i)); //For Debug
		//printf("\n");//For Debug
		error_flag = gpio_rw(DC, 1);
		if(error_flag < 0)break;
		sleep(1);
	}
	printf("Run ERROR(%d), Now EXIT!\n",error_flag);
	return error_flag;
}
