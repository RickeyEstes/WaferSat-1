/*
Varun Iyer
*/

#ifndef __SD_H__
#define __SD_H__
#include "ff.h"
uint8_t sd_init(void);
uint8_t sd_write(FIL* fil, char* string); 
uint8_t sd_test(void);
#endif
