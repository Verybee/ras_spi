#include <stdio.h>
#include <unistd.h>
#include "spiu.h"

int main(){
	unsigned char rx_data[8]={1,2,3,4,5,6,7,8};
	unsigned char tx_data[8];
	spi_init(0);
	while(1){
		spi_data_rw(0, tx_data, rx_data, 8);
		sleep(1);
	}
	return 0;
}
