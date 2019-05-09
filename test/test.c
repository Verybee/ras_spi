#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include "spi_user.h"
#include "gpio_user.h"
#include "gt30l32.h"
#include "ssd1325.h"
#include "graph.h"

int error_flag;

void *oled_flash(){
	while(1){
		error_flag += ssd1325_flash(display_buffer);
		usleep(5000);
	}
}

int main(){
	uint8_t x,y;
	uint8_t flag=1;
	pthread_t OLED_T;
	error_flag = 0;
	error_flag += spi_init(OLED);
	//error_flag += spi_init(ZK);
	error_flag += gpio_init();
	error_flag += ssd1325_init();
	//A new pthread
	error_flag += pthread_create(&OLED_T,NULL,oled_flash,NULL);
	while(1)
	{
		if(error_flag < 0)break;

		for(y=0;y<16;y++){
			for(x=0;x<128;x++){
				pix_set(display_buffer,x,y*4+0,flag);
				pix_set(display_buffer,x,y*4+1,flag);
				pix_set(display_buffer,x,y*4+2,flag);
				pix_set(display_buffer,x,y*4+3,flag);
				usleep(20000);
			}
		}
		if(0 == flag)flag = 1;
		else flag = 0;
		//sleep(1);
	}
	printf("Run ERROR(%d), Now EXIT!\n",error_flag);
	return error_flag;
}
