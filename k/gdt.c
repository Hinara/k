#include "gdt.h"
#include "k/compiler.h"
#include "k/types.h"
struct gdt_ptr {
	u16 len;
	u32 ptr;
} __attribute__((packed));

static const u64 gdt_array[] __attribute__((aligned(16))) = {
	#define GDT_FULL_ENTRY(x,y) [x] = y,
	#include "gdt_table.def"
	#undef GDT_FULL_ENTRY
};

static const struct gdt_ptr gdt = {
	.ptr = (u32) gdt_array,
	.len = sizeof(gdt_array) - 1
};
static void load_gdt(const struct gdt_ptr *ptr)
{
	asm volatile("lgdt (%0)" : : "a"(ptr));
}

static void flush_segment()
{
	asm volatile("ljmp $" XSTR(GDT_KERNEL_CS) ", $.flush;.flush:");
	asm volatile("mov %0, %%ds" : : "a"(GDT_KERNEL_DS));
	asm volatile("mov %0, %%es" : : "a"(GDT_KERNEL_DS));
	asm volatile("mov %0, %%fs" : : "a"(GDT_KERNEL_DS));
	asm volatile("mov %0, %%gs" : : "a"(GDT_KERNEL_DS));
	asm volatile("mov %0, %%ss" : : "a"(GDT_KERNEL_DS));
}
void set_gdt() {

	load_gdt(&gdt);
	flush_segment();
}
