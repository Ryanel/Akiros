#include <x86/gdt.hpp>
#include <klog.hpp>

extern "C" uintptr_t tls_bss_middle;

namespace x86 {
/// Manages the x86 GDT
namespace GDT {

struct gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
};

/// x86 GDT code stolen from sortie for debugging purposees
#define GRAN_64_BIT_MODE (1 << 5)
#define GRAN_32_BIT_MODE (1 << 6)
#define GRAN_4KIB_BLOCKS (1 << 7)

#define GDT_ENTRY(base, limit, access, granularity) \
	{ (limit) & 0xFFFF,                                /* limit_low */ \
	  (uint16_t) ((base) >> 0 & 0xFFFF),               /* base_low */ \
	  (uint8_t) ((base) >> 16 & 0xFF),                 /* base_middle */ \
	  (access) & 0xFF,                                 /* access */ \
	  ((limit) >> 16 & 0x0F) | ((granularity) & 0xF0), /* granularity */ \
	  (uint8_t) ((base) >> 24 & 0xFF),                 /* base_high */ }


extern "C" {
struct gdt_entry gdt[] =
{
	/* 0x00: Null segment */
	GDT_ENTRY(0, 0, 0, 0),

	/* 0x08: Kernel Code Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0x9A, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x10: Kernel Data Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0x92, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x18: User Code Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0xFA, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x20: User Data Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0xF2, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x28: F Segment. */
	GDT_ENTRY((uintptr_t)&tls_bss_middle, 0xFFFFFFFF, 0x93, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x30: G Segment. */
	GDT_ENTRY((uintptr_t)&tls_bss_middle, 0xFFFFFFFF, 0x93, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),
};

uint16_t gdt_size_minus_one = sizeof(gdt) - 1;
}
}}
