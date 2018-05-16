; Declare constants for the multiboot header.
; ==========================================================
; Multiboot
; ==========================================================
MBALIGN  equ  1<<0              ; align loaded modules on page boundaries
MEMINFO  equ  1<<1              ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

;===========================================================
; Paging
;===========================================================

KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)  ; Page directory index of kernel's 4MB PTE.
 
section .data
align 0x1000

BootPageDirectory:
    ; This page directory entry identity-maps the first 4MB of the 32-bit physical address space.
    ; All bits are clear except the following:
    ; bit 7: PS The kernel page is 4MB.
    ; bit 1: RW The kernel page is read/write.
    ; bit 0: P  The kernel page is present.
    ; This entry must be here -- otherwise the kernel will crash immediately after paging is
    ; enabled because it can't fetch the next instruction! It's ok to unmap this page later.
    dd 0x00000083
    times (KERNEL_PAGE_NUMBER - 1) dd 0                 ; Pages before kernel space.
    ; This page directory entry defines a 4MB page containing the kernel.
    dd 0x00000083
    dd 0x00010083
    times (1024 - KERNEL_PAGE_NUMBER - 2) dd 0  ; Pages after the kernel image.
 
;===========================================================
; Stack
;===========================================================
section .bss
align 16
stack_bottom:
resb 32384 ; 32 KB
stack_top:

section .bss
global tls_bss_middle
align 16
tls_bss_bottom:
resb 8192 ; 8 KB
tls_bss_middle:
resb 8192 ; 8 KB
tls_bss_top:

;===========================================================
; Code
;===========================================================
section .text
align 4

extern kStart
extern _init
extern _fini

extern gdt_size_minus_one
extern gdt

; Function: _start
global start
start equ (_start - 0xC0000000)

global _start:function (_start.end - _start)
_start:
    cli

	mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE)
    mov cr3, ecx                                        ; Load Page Directory Base Register.
 
    mov ecx, cr4
    or ecx, 0x00000010                          ; Set PSE bit in CR4 to enable 4MB pages.
    mov cr4, ecx
 
    mov ecx, cr0
    or ecx, 0x80000000                          ; Set PG bit in CR0 to enable paging.
    mov cr0, ecx
    
    ; Start fetching instructions in kernel space.
    ; Since eip at this point holds the physical address of this command (approximately 0x00100000)
    ; we need to do a long jump to the correct virtual address of StartInHigherHalf which is
    ; approximately 0xC0100000.
    lea ecx, [_kernelInit]
    jmp ecx                                                     ; NOTE: Must be absolute jump!
.end:

_kernelInit:
	mov dword [BootPageDirectory], 0 ; Unmap first page (4MB) of memory.
    invlpg [0] ; Refresh TLB

    mov esp, stack_top ; Set stack
    push ebx ; Push Multiboot info structure -- physical address, may be unmapped 
	push eax  ; Push multiboot magic number


extern memset

gdt_init:
    ; Construct GDT pointer
    sub esp, 6
    mov eax, gdt_size_minus_one
    mov [esp], eax
    mov ecx, gdt
    mov [esp + 2], ecx
    lgdt [esp] ; Load GDT
    add esp, 6

    ; Set segment registers
    mov ax, 0x28
    mov fs, ax
    mov ax, 0x30
    mov gs, ax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax

    ; Clear tls with memset
    push dword 16384
    push dword 0
    push dword tls_bss_bottom

    call memset 

    add esp, 12

    ; Setup TLS
    mov dword [tls_bss_middle], tls_bss_middle

init_kernel:

	call _init ; Init kernel Global Constructors
	call kStart ; Start kernel
	call _fini ; At this point, we're shutting down the kernel. Call deconstructors.
    call kHang

; Function: kHang
global kHang:function (kHang.end - kHang)
kHang:
	cli
.hang:	hlt
	jmp .hang
.end: