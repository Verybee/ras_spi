/////////////////////////////////////////////////
// This File Built by Rayden.Wang
// 2019.03.13 Version 0.1
//
//  +-----Interface with M270_ZK OLED-----+
//  |  NAME  |  BCM  |  PHY  |  FUNCTION  |
//  +--------+-------+-------+------------+
//  |  MOSI  |  ---  |   19  |      SDA   |
//  |  MISO  |  ---  |   21  |      FS0   |
//  |  SCLK  |  ---  |   23  |      SCL   |
//  |   CE0  |  ---  |   24  |      CS1   |
//  |   CE1  |  ---  |   26  |      CS2   |
//  | GPIO.0 |   17  |   11  |       DC   |
//  | GPIO.1 |   18  |   12  |      RES   |
//  +--------+-------+-------+------------+
//
/////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "gpio_user.h"

static const char	*gpioDev = GPIO_DEVICE;
static int		gpiofd;
static uint8_t		IO_status[2];

int gpio_rw(uint8_t number, uint8_t status){
	struct gpiohandle_data gpio_data_tr;
	memset(&gpio_data_tr, 0, sizeof(gpio_data_tr));
	IO_status[number-17] = status;
	memmove(gpio_data_tr.values, IO_status, 2);
	if( ioctl(gpiofd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &gpio_data_tr) < 0){
		printf("SET LINE %d VALUE (%d) ERROR: %s\n",number ,gpio_data_tr.values[number-17], strerror(errno));
		return -1;
	}
	return 0;
}

int gpio_init(){
	int fd;
	struct gpiohandle_request gpio_tr ;
	memset(&gpio_tr, 0, sizeof(gpio_tr));
	fd = open(gpioDev, O_RDWR);
	if( fd < 0){
		printf("Unable to open GPIO: %s\n",strerror(errno));
		return -1;
	}

	gpio_tr.lineoffsets[0] = DC;
	gpio_tr.lineoffsets[1] = RES;
	gpio_tr.flags = GPIOHANDLE_REQUEST_OUTPUT;
	gpio_tr.default_values[0] = 0;
	gpio_tr.default_values[1] = 0;
	gpio_tr.lines = 2;

	if( ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &gpio_tr) < 0 ){
		printf("GET GPIO HANDLE ERROR: %s\n",strerror(errno));
		return -1;
	}
	gpiofd = gpio_tr.fd;
	printf("GPIO handle open @ %d\n",gpiofd);
	return 0;
}
