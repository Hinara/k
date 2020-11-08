#include "io.h"
#include "pic8259.h"
#include "irq.h"
#include "idt.h"
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

void pic_init(u8 offset1, u8 offset2)
{
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_CASCADE | ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_CASCADE | ICW1_ICW4);
	outb(PIC1_DATA, offset1);	// ICW2: Master PIC vector offset
	outb(PIC2_DATA, offset2);	// ICW2: Slave PIC vector offset
	outb(PIC1_DATA, 0b00000100);	// ICW3: tell Master PIC that there is a slave PIC at IRQ2
	outb(PIC2_DATA, 0b00000010);	// ICW3: tell Slave PIC its cascade identity
	outb(PIC1_DATA, ICW4_BUF_NONE | ICW4_NORMAL | ICW4_8086);
	outb(PIC2_DATA, ICW4_BUF_NONE | ICW4_NORMAL | ICW4_8086);
}

void pic_remap(u32 offset1, u32 offset2)
{
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);	// save masks
	a2 = inb(PIC2_DATA);
	pic_init(offset1, offset2);
	outb(PIC1_DATA, a1);	// restore saved masks.
	outb(PIC2_DATA, a2);
}

void pic_mask_irq(u8 irqno)
{
	if (irqno < 8) {
		outb(PIC1_DATA, inb(PIC1_DATA) | (1 << (irqno - 0)));
	} else {
		outb(PIC2_DATA, inb(PIC2_DATA) | (1 << (irqno - 8)));
	}
}

void pic_unmask_irq(u8 irqno)
{
	if (irqno < 8) {
		outb(PIC1_DATA, inb(PIC1_DATA) & (~(1 << (irqno - 0))));
	} else {
		outb(PIC2_DATA, inb(PIC2_DATA) & (~(1 << (irqno - 8))));
	}
}

irq_handler_t irq_handler_table[16];

void irq_eoi(u8 irqno)
{
	if (irqno >= 8) {
		outb(PIC2_COMMAND, PIC_EOI);
	}
	outb(PIC1_COMMAND, PIC_EOI);
}

void irq_handler(struct idt_registers *regs, u32 interrupt, u32 code)
{
	u8 irqno = 0;
	if (interrupt >= IRQ_0_BASE && interrupt < IRQ_0_BASE + 8) {
		irqno = interrupt - IRQ_0_BASE + 0;
	} else if (interrupt >= IRQ_8_BASE && interrupt < IRQ_8_BASE + 8) {
		irqno = interrupt - IRQ_8_BASE + 8;
	} else {
		printf("ERROR !\r\nIRQ Unknown Interrupt no:%d\r\n", interrupt);
		return;
	}
	irq_handler_t handler = irq_handler_table[irqno];
	if (handler == NULL) {
		printf("ERROR !\r\nIRQ: %d called without handler\r\n", interrupt);
	} else {
		u32 error = handler(regs, irqno, code);
		if (error == 0) {
			irq_eoi(irqno);
		}
	}
}

void set_irq()
{
	pic_init(IRQ_0_BASE, IRQ_8_BASE);
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
	for (u8 i = 0; i < ARRAY_SIZE(irq_handler_table); i++) {
		irq_handler_table[i] = NULL;
	}
	for (u8 interrupt = IRQ_0_BASE; interrupt < IRQ_0_BASE + 8; interrupt++) {
		register_handler(interrupt, irq_handler, NULL);
	}
	for (u8 interrupt = IRQ_8_BASE; interrupt < IRQ_8_BASE + 8; interrupt++) {
		register_handler(interrupt, irq_handler, NULL);
	}
	asm volatile("sti");
}

void set_irq_handler(u8 irqno, irq_handler_t handler, irq_handler_t *old)
{
	irq_handler_t old_handler;

	if (irqno >= ARRAY_SIZE(irq_handler_table)) {
		return;
	}
	old_handler = irq_handler_table[irqno];
	if (old != NULL) {
		*old = old_handler;
	}
	if (old_handler == NULL && handler != NULL) {
		pic_unmask_irq(irqno);
	} else if (old_handler != NULL && handler == NULL) {
		pic_mask_irq(irqno);
	}
	irq_handler_table[irqno] = handler;
}