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
static void set_gdt() {
	static const u64 gdt_array[] __attribute__((aligned(16))) = {
		#include "gdt_table.h"
	};
	static const struct gdt_ptr gdt = {
		.ptr = (u32) gdt_array,
		.len = sizeof(gdt_array) - 1
	};
	printf("Flush GDT\r\n");
	gdt_flush(&gdt);
	printf("GDT Flushed\r\n");
}

void TEST() {
	printf("TEST\r\n");
	asm volatile ("int $0x07");
	printf("TEST2\r\n");
	//asm volatile("mov %0, %%gs" : : "a"(50));
	printf("TEST3\r\n");
}
void k_main(unsigned long magic, multiboot_info_t *info)
{
	(void)magic;
	(void)info;

	char star[4] = "|/-\\";
	char *fb = (void *)0xb8000;

	printf("HELLO\r\n");
	set_gdt();
	printf("?\r\n");
	set_idt();
	printf("OK\r\n");
	TEST();
	for (unsigned i = 0; ; ) {
		*fb = star[i++ % 4];
	}
	for (;;)
		asm volatile ("hlt");
}
