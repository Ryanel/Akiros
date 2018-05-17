ENTRY(_start)

KERNEL_VMA = 0xC0000000;

SECTIONS {
    . = 0xC0100000;

    .text : AT(ADDR(.text) - KERNEL_VMA) {
        *(.multiboot)
        *(.text)
        *(.text*)
    }

    .rodata ALIGN (0x1000) : AT(ADDR(.rodata) - KERNEL_VMA) {
        *(.rodata*)
    }

    .data ALIGN (0x1000) : AT(ADDR(.data) - KERNEL_VMA) {
        *(.data)
    }

    .eh_frame ALIGN (0x1000) : AT(ADDR(.eh_frame) - KERNEL_VMA)
    {
        _ehframe = .;
        *(.eh_frame)
    }

    .bss ALIGN (0x1000) : AT(ADDR(.bss) - KERNEL_VMA) {
        _sbss = .;
        *(COMMON)
        *(.bss)
        _ebss = .;
    }

    /DISCARD/ :
    {
        *(.comment)
    }
}