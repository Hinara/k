#ifndef IDT_H_
#define IDT_H_

#define IDT_ENTRY(offset, selector, attributes) \
	((((offset)     & 0xffff0000ULL) << (48 - 16)) |	\
	 (((attributes) & 0x000000ffULL) << 40) | \
	 (0ULL << 32) | \
	 (((selector)   & 0x0000ffffULL) << 16) | \
	 (((offset)     & 0x0000ffffULL)))

#define IDT_ATTRIBUTE_PRESENT		0b10000000
#define IDT_ATTRIBUTE_RING0		0b00000000
#define IDT_ATTRIBUTE_RING1		0b00100000
#define IDT_ATTRIBUTE_RING2		0b01000000
#define IDT_ATTRIBUTE_RING3		0b01100000
#define IDT_ATTRIBUTE_STORAGE_SEGMENT	0b00010000
#define IDT_ATTRIBUTE_GATE_32TASK	0b00000101
#define IDT_ATTRIBUTE_GATE_16INT	0b00000110
#define IDT_ATTRIBUTE_GATE_16TRAP	0b00000111
#define IDT_ATTRIBUTE_GATE_32INT	0b00001110
#define IDT_ATTRIBUTE_GATE_32TRAP	0b00001111

#define ISR_ALIGN 4

#ifndef __ASSEMBLER__
# include <k/types.h>

struct idt_ptr {
	u16 len;
	u32 ptr;
} __attribute__((packed));

struct idt_registers {
// General registers
	u32	eax;
	u32	ebx;
	u32	ecx;
	u32	edx;
	u32	esi;
	u32	edi;
	u32	ebp;
	u32	esp;
// Segment registers
	u16	cs;
	u16	ds;
	u16	ss;
	u16	es;
	u16	fs;
	u16	gs;
// Other registers
	u32	eip;
	u32	eflags;
};

struct idt_params {
	struct idt_registers regs;
	u32 interrupt;
	u32 code;
};

typedef void (*interupt_handler_t)();

struct idt_base_entry {
	const char *name;
	interupt_handler_t handler;
	u16 selector;
	u8 attributes;
};
typedef void (*int_handler)(struct idt_registers *regs, u32 interrupt, u32 code);

int register_handler(u32 interrupt, int_handler handler, int_handler *old);
void set_idt();
#endif

#endif /* IDT_H_ */