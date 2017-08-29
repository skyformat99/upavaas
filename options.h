#ifndef __upal_options_h__
#define __upal_options_h__

#include <stdint.h>

struct __attribute__ ((__packed__))
options
{
  uint32_t address;
  uint16_t port;
  char* directory;
};

int parse(int, char**, struct options*);

#endif