#include "timer8254.h"
#include "io.h"
#include "irq.h"
#include "k/compiler.h"
#include "k/kstd.h"
#include "syscall.h"

static u32 tickcount = 0;

static u32 sys_gettick(struct x86_registers *regs)
{
	(void) regs;
	return tickcount;
}

static u32 timer_irq_handler()
{
	tickcount += 1;
	return 0;
}

static void init_timer()
{
	u16 divider = TIMER_MAX_FREQUENCY / TIMER_DESIRED_FREQUENCY;
	outb(PIT_PORT, TIMER_BINARY_COUNTER |
		TIMER_MODE(2) |
		TIMER_RW_LSB_MSB |
		TIMER_COUNTER_SETUP(0));
	outb(PIT_COUNTER0, GET_U16_LSB(divider));
	outb(PIT_COUNTER0, GET_U16_MSB(divider));
}

void set_timer()
{
	set_syscall_handler(SYSCALL_GETTICK, sys_gettick, NULL);
	set_irq_handler(IRQ_TIMER, timer_irq_handler, NULL);
	init_timer();
}
