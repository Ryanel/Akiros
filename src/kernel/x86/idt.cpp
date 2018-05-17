#include <x86/idt.hpp>
#include <x86/ports.hpp>
#include <string.h>
#include <klog.hpp>

using namespace x86;
using namespace Kernel;

void IDT::Setup() {
    // Setup PTR and idt
    idtptr.limit = sizeof(struct idt_entry) * 256 - 1;
    idtptr.base = (uint32_t)&idt;

    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    // Setup ISR's
    SetGate(0, (uintptr_t)isr0, 0x08, 0x8E);
	SetGate(1, (uintptr_t)isr1, 0x08, 0x8E);
	SetGate(2, (uintptr_t)isr2, 0x08, 0x8E);
	SetGate(3, (uintptr_t)isr3, 0x08, 0x8E);
	SetGate(4, (uintptr_t)isr4, 0x08, 0x8E);
	SetGate(5, (uintptr_t)isr5, 0x08, 0x8E);
	SetGate(6, (uintptr_t)isr6, 0x08, 0x8E);
	SetGate(7, (uintptr_t)isr7, 0x08, 0x8E);

	SetGate(8, (uintptr_t)isr8, 0x08, 0x8E);
	SetGate(9, (uintptr_t)isr9, 0x08, 0x8E);
	SetGate(10, (uintptr_t)isr10, 0x08, 0x8E);
	SetGate(11, (uintptr_t)isr11, 0x08, 0x8E);
	SetGate(12, (uintptr_t)isr12, 0x08, 0x8E);
	SetGate(13, (uintptr_t)isr13, 0x08, 0x8E);
	SetGate(14, (uintptr_t)isr14, 0x08, 0x8E);
	SetGate(15, (uintptr_t)isr15, 0x08, 0x8E);

	SetGate(16, (uintptr_t)isr16, 0x08, 0x8E);
	SetGate(17, (uintptr_t)isr17, 0x08, 0x8E);
	SetGate(18, (uintptr_t)isr18, 0x08, 0x8E);
	SetGate(19, (uintptr_t)isr19, 0x08, 0x8E);
	SetGate(20, (uintptr_t)isr20, 0x08, 0x8E);
	SetGate(21, (uintptr_t)isr21, 0x08, 0x8E);
	SetGate(22, (uintptr_t)isr22, 0x08, 0x8E);
	SetGate(23, (uintptr_t)isr23, 0x08, 0x8E);

	SetGate(24, (uintptr_t)isr24, 0x08, 0x8E);
	SetGate(25, (uintptr_t)isr25, 0x08, 0x8E);
	SetGate(26, (uintptr_t)isr26, 0x08, 0x8E);
	SetGate(27, (uintptr_t)isr27, 0x08, 0x8E);
	SetGate(28, (uintptr_t)isr28, 0x08, 0x8E);
	SetGate(29, (uintptr_t)isr29, 0x08, 0x8E);
	SetGate(30, (uintptr_t)isr30, 0x08, 0x8E);
	SetGate(31, (uintptr_t)isr31, 0x08, 0x8E);

    // Remap PIC
    outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Setup IRQ's
    SetGate(32, (uintptr_t)irq0, 0x08, 0x8E);
	SetGate(33, (uintptr_t)irq1, 0x08, 0x8E);
	SetGate(34, (uintptr_t)irq2, 0x08, 0x8E);
	SetGate(35, (uintptr_t)irq3, 0x08, 0x8E);
	SetGate(36, (uintptr_t)irq4, 0x08, 0x8E);
	SetGate(37, (uintptr_t)irq5, 0x08, 0x8E);
	SetGate(38, (uintptr_t)irq6, 0x08, 0x8E);
	SetGate(39, (uintptr_t)irq7, 0x08, 0x8E);
	SetGate(40, (uintptr_t)irq8, 0x08, 0x8E);
	SetGate(41, (uintptr_t)irq9, 0x08, 0x8E);
	SetGate(42, (uintptr_t)irq10, 0x08, 0x8E);
	SetGate(43, (uintptr_t)irq11, 0x08, 0x8E);
	SetGate(44, (uintptr_t)irq12, 0x08, 0x8E);
	SetGate(45, (uintptr_t)irq13, 0x08, 0x8E);
	SetGate(46, (uintptr_t)irq14, 0x08, 0x8E);
    SetGate(47, (uintptr_t)irq15, 0x08, 0x8E);

    idt_flush((uintptr_t)&idtptr);

	kLog.Log(LOG_DEBUG, "x86", "IDT configured");
}

void IDT::SetGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}
