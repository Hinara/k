#include "gdt.h"

void set_gdt() {
	static const u64 gdt_array[] __attribute__((aligned(16))) = {
		#include "gdt_table.h"
	};
	static const struct gdt_ptr gdt = {
		.ptr = (u32) gdt_array,
		.len = sizeof(gdt_array) - 1
	};
	gdt_flush(&gdt);
}
