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

#ifndef __ASSEMBLER__
#include "idt.h"
void set_irq();
typedef u32 (*irq_handler_t) (struct idt_registers *regs, u32 irqno, u32 code);
void set_irq_handler(u8 irqno, irq_handler_t handler, irq_handler_t *old);
#endif


#endif