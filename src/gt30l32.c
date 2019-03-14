///////////////////////////////////////////
// This File Built by Ray Wang
// 2019.03.12 Version 0.1
///////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "spi_user.h"
#include "gt30l32.h"

/**********************************************
 * read_gt30l32
 * 	interface between user and gt30l32
 *
 * 	tx_data --> 3 bytes address
 * 	rx_data --> data from gt30l32
 **********************************************/
int read_gt30l32(uint8_t *tx_data, uint8_t *rx_data, uint8_t data_bits){
	uint8_t addr[36];
	uint8_t data[36];
	uint8_t len;
	uint8_t cont;
	if(data_bits > 32){
		printf("Too long data: %d.\n",data_bits);
		return -1;
	}
// Read Function
	memset(addr,0xff,sizeof(uint8_t)*36);
	sprintf(addr, "%c", READ_COM);
	memmove(addr+1,tx_data,3);
	len = data_bits + 4;
	spi_data_rw(ZK, addr, data, len);

// Write Function
	memmove(rx_data, data+4, data_bits);
	return 0;
}

/*************************************************
 * transform_word
 * 	transform a word to OLED data
 *
 * 	word --> an ASCII word
 * 	buf  --> a buffer of OLED datas
 *************************************************/
uint32_t transform_word(unsigned char word, uint8_t *buf){
	uint8_t addr[3];
	uint32_t tmp_addr=0;
	if(word < 0x20 || word > 0x7E){
		printf("ASCII word range ERROR!(%d)\n",word);
		return -1;
	}
	tmp_addr = (uint32_t) ((word - 0x20) << 4) + BASE_ADDR_AS;
	addr[0] = (tmp_addr & 0x00FF0000) >> 16;
	addr[1] = (tmp_addr & 0x0000FF00) >> 8;
	addr[2] = (tmp_addr & 0x000000FF);
	
	memset(buf,0,sizeof(uint8_t)*16);
	read_gt30l32(addr, buf, 16);
	return tmp_addr;
}

/*************************************************
 * transform_GB
 * 	transform a chinese word to OLED data
 *
 * 	word --> a chinese word(two bytes)
 * 	buf  --> a buffer of OLED data
 *************************************************/
uint32_t transform_GB(unsigned char *word, uint8_t *buf){
	uint8_t addr[3];
	uint32_t tmp_addr=0;
	
	if((*word >= 0xA1) && (*word <= 0xA9) && (*(word+1) >= 0xA1)){
		tmp_addr = ((94*(*word - 0xA1) + (*(word+1) - 0xA1)) << 5) + BASE_ADDR_GB;
	}
	else if((*word >= 0xB0) && (*word <= 0xF7) && (*(word+1) >= 0xA1)){
		tmp_addr = ((94*(*word - 0xB0) + (*(word+1) - 0xA1) + 846) << 5) + BASE_ADDR_GB;
	}
	else{
		printf("GB2312 chinese word range ERROR!(%s:0x%X 0x%X)\n",word,*word,*(word+1));
		return -1;
	}
	addr[0] = (tmp_addr & 0x00FF0000) >> 16;
	addr[1] = (tmp_addr & 0x0000FF00) >> 8;
	addr[2] = (tmp_addr & 0x000000FF);
	
	read_gt30l32(addr, buf, 32);
	return tmp_addr;
}
