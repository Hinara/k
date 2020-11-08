#include "timer8254.h"
#include "idt.h"
#include "io.h"
#include "syscall.h"
#include "k/kstd.h"
#include "irq.h"

u32 tickcount = 0;
u32 sys_gettick(struct idt_registers *regs)
{
	(void) regs;
	return tickcount;
}
u32 timer_irq_handler()
{
	tickcount += 1;
	return 0;
}

void set_timer()
{
	u16 divider = TIMER_MAX_FREQUENCY / TIMER_DESIRED_FREQUENCY;
	u8 lsb = divider & 0xff;
	u8 msb = (divider >> 8) & 0xff;
	printf("Divider:%d\r\n", divider);
	outb(PIT_PORT, TIMER_BINARY_COUNTER |
		TIMER_MODE(2) |
		TIMER_RW_LSB_MSB |
		TIMER_COUNTER_SETUP(0));
	outb(PIT_COUNTER0, lsb);
	outb(PIT_COUNTER0, msb);
	set_syscall_handler(SYSCALL_GETTICK, sys_gettick, NULL);
	set_irq_handler(0, timer_irq_handler, NULL);
}
