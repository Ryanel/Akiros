ENTRY(_start)

SECTIONS {
    KERNEL_VMA = 0;
    . = 1M;

    .boot :
    {
        /* ensure that the multiboot header is at the beginning */
        *(.multiboot)
    }

    .text :
    {
        *(.text)
        . = ALIGN(4096);
    }

    .data : {
        *(.data)
        . = ALIGN(4096);
    }

    .eh_frame : AT(ADDR(.eh_frame) - KERNEL_VMA)
    {
        _ehframe = .;
        *(.eh_frame)
        . = ALIGN(4096);
    }

    .bss : AT(ADDR(.bss) - KERNEL_VMA)
    {
        _bss = .;
        *(.bss)

        /*
        * You usually need to include generated COMMON symbols
        * under kernel BSS section or use gcc's -fno-common
        */

        *(COMMON)
        . = ALIGN(4096);
    }

    _end = .;

    /DISCARD/ :
    {
        *(.comment)
    }
}