/////////////////////////////////////////////////
// This File Built by Rey Wang 
// 2019.03.05 Version 0.1
/////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "spi_user.h"

static const char	*spiDev0 = SPI_DEVICE0;
static const char	*spiDev1 = SPI_DEVICE1;

static int		spifds[2];
/*******************************************************************
 *spi_data_rw
 *	read and write data from user,only for 8bits.
 *	This is a full-duplex operation
 *******************************************************************/
int spi_data_rw(uint8_t channel, uint8_t *tx_data, uint8_t *rx_data, uint16_t len){
	struct spi_ioc_transfer spi_tr ;
	memset(&spi_tr, 0, sizeof(spi_tr));

	spi_tr.tx_buf		= (unsigned long)tx_data;
	spi_tr.rx_buf		= (unsigned long)rx_data;
	spi_tr.len		= len;
	spi_tr.delay_usecs	= 0;
	spi_tr.speed_hz		= SPI_SPEED_DEFINE;
	spi_tr.bits_per_word	= SPI_BPW_DEFINE;

	return ioctl(spifds[channel], SPI_IOC_MESSAGE(1), &spi_tr) ;
}

/********************************************************************
 *spi_init 
 *	open spi device and setup it with the parameter from spi.h
 ********************************************************************/
int spi_init(uint8_t channel){
	int fd;
	int MODE = SPI_MODE_DEFINE;
	int BPW = SPI_BPW_DEFINE;
	int SPEED = SPI_SPEED_DEFINE;

	fd = open((channel == 0 ? spiDev0 : spiDev1), O_RDWR);
	if(fd < 0){
		printf("Unable to open SPI device: %s\n",strerror(errno));
		return -1;
	}
	printf("SPI Channel %d open @ %d\n",channel,fd);
	spifds[channel] = fd;

/////////////////////////////
//Set SPI Mode
/////////////////////////////
	if( ioctl(fd, SPI_IOC_WR_MODE, &MODE) < 0 ){
		printf("Can't set spi write mode:%s\n",strerror(errno));
		return -1;
	}
	if( ioctl(fd, SPI_IOC_RD_MODE, &MODE) < 0 ){
		printf("Can't set spi read mode:%s\n",strerror(errno));
		return -1;
	}

/////////////////////////////
//Set SPI Bits per word
/////////////////////////////
	if( ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &BPW) < 0 ){
		printf("Can't set spi write bit per word:%s\n",strerror(errno));
		return -1;
	}
	if( ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &BPW) < 0 ){
		printf("Can't set spi read bit per word:%s\n",strerror(errno));
		return -1;
	}

/////////////////////////////
//Set SPI Speed
/////////////////////////////
	if( ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPEED) < 0 ){
		printf("Can't set spi write speed:%s\n",strerror(errno));
		return -1;
	}
	if( ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &SPEED) < 0 ){
		printf("Can't set spi read speed:%s\n",strerror(errno));
		return -1;
	}

	return 0;
}

