#include <stdio.h>
#include <unistd.h>
#include "spi_user.h"

int main(){
	int i;
	unsigned char tx_data1[8]={1,2,3,4,5,6,7,8};
	unsigned char tx_data2[8]={8,7,6,5,4,3,2,1};
	unsigned char rx_data[8];
	spi_init(0);
	spi_init(1);
	
	while(1){
		spi_data_rw(0, tx_data1, rx_data, 8);
		spi_data_rw(1, tx_data2, rx_data, 8);
		sleep(1);
	}
	return 0;
}
