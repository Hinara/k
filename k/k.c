/*
 * Copyright (c) LSE
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY LSE AS IS AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL LSE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <k/kstd.h>
#include <stdio.h>
#include "multiboot.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "keyboard8042.h"
#include "syscall.h"
#include "timer8254.h"
#include "write.h"
#include "serial.h"

static inline u32 syscall0(u32 syscall)
{
	u32 res;
	
	asm volatile ("int $0x80" : "=a"(res) : "a"(syscall));
	return (int) res;
}
static int getkey(void)
{
	return ((int)syscall0(SYSCALL_GETKEY));
}

static unsigned long gettick(void)
{
	return ((unsigned long)syscall0(SYSCALL_GETTICK));
}


static int com1_write(const char *buf, size_t size)
{
	for (size_t count = 0; count < size; count++) {
		send_com(COM1_BASE, buf[count]);
	}
	return size;
}

static void star_loader() {
	char star[4] = "|/-\\";
	char *fb = (void *)0xb8000;
	u32 tick = 0;
	u32 newtick = 0;

	for (unsigned i = 0; ; ) {
		*fb = star[i++ % 4];
		int key = getkey();
		if (key >= 0) {
			printf("%d\r\n", key);
		}
		newtick = gettick() / 1000;
		if (newtick != tick) {
			printf("Tick:%ld\r\n", newtick);
		}
		tick = newtick;
	}
}

void k_main(unsigned long magic, multiboot_info_t *info)
{
	(void)magic;
	(void)info;

	init_serial(COM1_BASE);
	set_write_func(com1_write, NULL);
	set_gdt();
	set_idt();
	set_irq();
	set_syscalls();
	set_keyboard();
	set_timer();
	star_loader();
	asm volatile ("hlt");
}
