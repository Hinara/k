#ifndef IRQ_H_
#define IRQ_H_

#define IRQ_0_BASE	0x20
#define IRQ_8_BASE	0x28

#define IRQ_0_INT	(IRQ_0_BASE + 0)
#define IRQ_1_INT	(IRQ_0_BASE + 1)
#define IRQ_2_INT	(IRQ_0_BASE + 2)
#define IRQ_3_INT	(IRQ_0_BASE + 3)
#define IRQ_4_INT	(IRQ_0_BASE + 4)
#define IRQ_5_INT	(IRQ_0_BASE + 5)
#define IRQ_6_INT	(IRQ_0_BASE + 6)
#define IRQ_7_INT	(IRQ_0_BASE + 7)
#define IRQ_8_INT	(IRQ_8_BASE + 0)
#define IRQ_9_INT	(IRQ_8_BASE + 1)
#define IRQ_10_INT	(IRQ_8_BASE + 2)
#define IRQ_11_INT	(IRQ_8_BASE + 3)
#define IRQ_12_INT	(IRQ_8_BASE + 4)
#define IRQ_13_INT	(IRQ_8_BASE + 5)
#define IRQ_14_INT	(IRQ_8_BASE + 6)
#define IRQ_15_INT	(IRQ_8_BASE + 7)

#define IRQ_TIMER		0
#define IRQ_KEYBOARD		1
#define IRQ_CASCADE		2
#define IRQ_SERIAL_PORT2	3
#define IRQ_SERIAL_PORT1	4
#define IRQ_PARALLEL_PORT23	5
#define IRQ_PARALLEL_PORT2	5
#define IRQ_PARALLEL_PORT3	5
#define IRQ_FLOPPY_DISK_DRIVE	6
#define IRQ_PARALLEL_PORT1	7
#define IRQ_RTC			8
#define IRQ_ACPI		9
#define IRQ_MOUSE		12
#define IRQ_CPU_COPROCESSOR	13
#define IRQ_PRIMARY_ATA		14
#define IRQ_SECUNDARY_ATA	15



#ifndef __ASSEMBLER__
#include "idt.h"
void set_irq();
typedef u32 (*irq_handler_t)();
void set_irq_handler(u8 irqno, irq_handler_t handler, irq_handler_t *old);
#endif


#endif