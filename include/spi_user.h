#ifndef __SPIU_H
#define __SPIU_H
/////////////////////////////////////////////////
// This Fire Build by Ray Wang 
// 2019.03.05 Version 0.1
/////////////////////////////////////////////////

#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define SPI_DEVICE0		"/dev/spidev0.0"
#define SPI_DEVICE1		"/dev/spidev0.1"
#define SPI_MODE_DEFINE		SPI_MODE_3
#define SPI_BPW_DEFINE		8
#define SPI_SPEED_DEFINE	2000000

int spi_init(int channel);
int spi_data_rw(int channel, unsigned char *tx_data, unsigned char *rx_data, int len);

#endif
