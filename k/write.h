#ifndef WRITE_H_
#define WRITE_H_

#include "k/types.h"

typedef int (*write_handler_t)(const char *buffer, size_t size);
void set_write_func(write_handler_t handler, write_handler_t *old);

#endif