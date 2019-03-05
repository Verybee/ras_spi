#################################################
## This Fire Build by Ray Wang 
## 2019.03.05 Version 0.1
#################################################

#include "wiringPi.h"
#include "stdio.h"
#include "stdlib.h"
#include "wiringPISPI.h"

int initSPI()
{
	int spiFD;
	spiFD = wiringPiSPISetup(0,2000000);
	if(spiFD == -1){
		printf("Init spi Failed!\n");
	}
	return spiFD;
}

int main()
{
	char DATA[1] = 1;
	initSPI();
	while(1)
	{
		wiringPiSPIDataRW(0,Data,1);
	}
	return 0;
}
