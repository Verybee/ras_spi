#ifndef __GT30L32_H
#define __GT30L32_H
///////////////////////////////////////////
// This File Built by Ray Wang
// 2019.03.12 Version 0.1
///////////////////////////////////////////
#include <stdint.h>

#define READ_COM	0x03
#define BASE_ADDR_AS	0x1DD780
#define BASE_ADDR_GB	0x02C9D0

int read_gt30l32(uint8_t *, uint8_t *, uint8_t);
uint32_t transform_word(unsigned char, uint8_t *);
uint32_t transform_GB(unsigned char *, uint8_t *);

#endif
