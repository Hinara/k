#include "irq.h"
#include "keyboard8042.h"
#include "io.h"
#include "k/kstd.h"
#include "stdio.h"
#include "syscall.h"

u8 woffset = 0;
u8 roffset = 0;
u8 buffer[256];

int get_from_buffer(u8 *value)
{
	if (woffset == roffset) {
		return -1;
	}
	*value = buffer[roffset];
	roffset = (roffset + 1) % sizeof(buffer);
	return 0;
}

void put_into_buffer(u8 value)
{
	buffer[woffset] = value;
	woffset = (woffset + 1) % sizeof(buffer);
}

u32 keyboard_handler()
{
	u8 key = inb(KEYBOARD_IO_BUFFER_PORT);
	if (KEYBOARD_IS_PRESSED(key)) {
		put_into_buffer(KEYBOARD_GET_KEYNUMBER(key));
	}
	return 0;
}

u32 sys_getkey(struct x86_registers *regs)
{
	(void) regs;
	u8 key;
	int error = get_from_buffer(&key);

	if (error) {
		return -EAGAIN;
	} else {
		return key;
	}
}
void set_keyboard()
{
	set_irq_handler(1, keyboard_handler, NULL);
	set_syscall_handler(SYSCALL_GETKEY, sys_getkey, NULL);
}
