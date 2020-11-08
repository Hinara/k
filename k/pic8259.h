#ifndef PIC8259_H_
#define PIC8259_H_

// Address of PIC8259
#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	(PIC1+0)
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	(PIC2+0)
#define PIC2_DATA	(PIC2+1)


// ICW1
#define ICW1_ICW4	(1 << 0)		/* ICW4 present */
// Cascade or single mode
#define ICW1_CASCADE	(0 << 1)		/* Cascade mode */
#define ICW1_SINGLE	(1 << 1)		/* Single mode */
// Address interval (unused under x86)
#define ICW1_INTERVAL8	(0 << 2)		/* Call address interval 8 */
#define ICW1_INTERVAL4	(1 << 2)		/* Call address interval 4 */
// Trigger Mode
#define ICW1_EDGE	(0 << 3)		/* Edge triggered mode */
#define ICW1_LEVEL	(1 << 3)		/* Level triggered mode */
// Init
#define ICW1_INIT	(1 << 4)		/* Initialization - required! */
// End ICW1

// ICW4
#define ICW4_8086	(1 << 0)		/* 8086/88 (MCS-80/85) mode */
// EOI Mode
#define ICW4_AUTO	(1 << 1)		/* Auto EOI */
#define ICW4_NORMAL	(0 << 1)		/* Normal EOI */
// Buffering mode
#define ICW4_BUF_NONE	(0 << 2)		/* No Buffered mode */
#define ICW4_BUF_SLAVE	(1 << 2)		/* Buffered mode slave */
#define ICW4_BUF_MASTER	(3 << 2)		/* Buffered mode master */
// Special mode
#define ICW4_SFNM	(1 << 4)		/* Special fully nested */
// End ICW4

#define PIC_EOI		0x20		/* End-of-interrupt command code */

#endif