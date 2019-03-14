#ifndef __GPIOU_H
#define __GPIOU_H
///////////////////////////////////////////
// This File Built by Ray Wang
// 2019.03.12 Version 0.1
///////////////////////////////////////////
#include <stdint.h>

#define GPIO_DEVICE	"/dev/gpiochip0"
#define DC		17
#define RES		18


int gpio_init();

/******************************************
 * gpio_rw(u8 pin, u8 status)
 ******************************************/
int gpio_rw(uint8_t, uint8_t);

#endif
