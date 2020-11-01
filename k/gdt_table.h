#include "gdt.h"
# define GDT_FULL_ENTRY(x,y) [x] = y,

GDT_FULL_ENTRY(0, GDT_ENTRY(0, 0, 0))
GDT_FULL_ENTRY(GDT_KERNEL_CS, GDT_ENTRY(0, 0xfffff, GDT_KERNEL_CS_FLAGS))
GDT_FULL_ENTRY(GDT_KERNEL_DS, GDT_ENTRY(0, 0xfffff, GDT_KERNEL_DS_FLAGS))
GDT_FULL_ENTRY(GDT_USER_CS, GDT_ENTRY(0, 0xfffff, GDT_USER_CS_FLAGS))
GDT_FULL_ENTRY(GDT_USER_DS, GDT_ENTRY(0, 0xfffff, GDT_USER_DS_FLAGS))
