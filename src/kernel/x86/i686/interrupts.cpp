#include <x86/registers.hpp>
#include <x86/ports.hpp>
#include <x86/interrupts.hpp>

#include <klog.hpp>
#include <panic.hpp>

using namespace Kernel;
using namespace x86;

const char *exception_messages[] =
{
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",

	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",

	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

namespace x86 {
void EnableInterrupts(bool on) {
	if(on) {
		asm("sti");
	} else {
		asm("cli");
	}
}
}

extern "C" void x86_interrupt_fault_handler(registers_t * r) {
    kLog.Fatal("fault", "========= Started Kernel Fault Handler =======");
    kLog.Fatal("fault", "num: %d (error %d, %s)",r->int_no,r->err_code,exception_messages[r->int_no]);
    kLog.Fatal("fault", "gs:  0x%02x  fs:  0x%02x   es:  0x%0x",r->gs,r->fs,r->es);
    kLog.Fatal("fault", "ds:  0x%02x  cs:  0x%02x   ss:  0x%0x",r->ds,r->cs,r->ss);
    kLog.Fatal("fault", "esp: 0x%08x ebp: 0x%08x uesp: 0x%08x",r->useless_value,r->ebp,r->useresp);
    kLog.Fatal("fault", "eax: 0x%08x ebx: 0x%08x ecx:  0x%08x edx:    0x%08x",r->eax,r->ebx,r->ecx,r->edx);
    kLog.Fatal("fault", "esi: 0x%08x edi: 0x%08x eip:  0x%08x eflags: 0x%x ",r->esi,r->edi,r->eip,r->eflags);
    kLog.Fatal("fault", "========== Ended Kernel Fault Handler ========");

    panic("Unhandled fault");
}

extern "C" void x86_interrupt_irq_handler(registers_t * r) {

	if(!interruptDispatch.Dispatch(r)) {
		kLog.Warning("int dispatch","Unhandled IRQ %d!", r->int_no);
	}

    // Inform slave
    if (r->int_no >= 40) {
        outb(0xA0, 0x20);
    }

    // Inform PIC
    outb(0x20, 0x20);
}
