#ifndef __upal_event_h__
#define __upal_event_h__

#include <stdint.h>

int startsvr(uint32_t, uint16_t);
int initevl(void);
int startevl(void);

void evclean(int);

#endif