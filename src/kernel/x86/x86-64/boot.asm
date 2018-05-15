section .text
bits 64

extern _init
extern _fini

extern kStart
global long_mode_start

long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov rax, 0x2f592f412f4b2f4f
    mov qword [0xb8000], rax


    call _init
    call kStart
    call _fini

    mov rax, 0x2f592f412f4b2f4f
    mov qword [0xb8008], rax
    hlt

global kHang

kHang:
    cli
    hlt