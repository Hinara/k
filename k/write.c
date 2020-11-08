
#include <stddef.h>
#include "write.h"

static write_handler_t write_handler = NULL;

void set_write_func(write_handler_t handler, write_handler_t *old)
{
	if (old != NULL) {
		*old = write_handler;
	}
	write_handler = handler;
}

int write(const char *buf, size_t size) {
	if (write_handler == NULL) {
		return -1;
	}
	return write_handler(buf, size);
}
