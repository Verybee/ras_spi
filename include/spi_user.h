#ifndef __SPIU_H
#define __SPIU_H
/////////////////////////////////////////////////
// This File Built by Ray Wang 
// 2019.03.05 Version 0.1
/////////////////////////////////////////////////
#include <stdint.h>

#define SPI_DEVICE0		"/dev/spidev0.0"
#define SPI_DEVICE1		"/dev/spidev0.1"
#define SPI_MODE_DEFINE		SPI_MODE_3
#define SPI_BPW_DEFINE		8
#define SPI_SPEED_DEFINE	2000000
#define ZK			1
#define OLED			0

/*********************************************************
 * spi_init(u8 channel)
 *********************************************************/
int spi_init(uint8_t);

/***************************************************************
 * spi_data_rw(u8 channel, u8 *tx_buf, u8 *rx_buf, u16 len)
 ***************************************************************/
int spi_data_rw(uint8_t, uint8_t *, uint8_t *, uint16_t);

#endif
