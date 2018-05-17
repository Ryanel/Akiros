extern gdtptr
extern GDT_DoSetup
extern memset

extern tls_bss_bottom
extern tls_bss_middle
extern tls_bss_top

; Function: setupGDT
global setupGDT:function (setupGDT.end - setupGDT)
setupGDT:
    call GDT_DoSetup
    lgdt [gdtptr]
    
    mov ax, 0x28
    mov fs, ax
    mov ax, 0x30
    mov gs, ax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax

    jmp 0x08:.flush
.flush:
    ret
.end:

; Function: setupTLS
global setupTLS:function (setupTLS.end - setupTLS)
setupTLS:
    ; Clear tls with memset
    push dword 16384
    push dword 0
    push dword tls_bss_bottom

    call memset 

    add esp, 12

    ; Setup TLS
    mov dword [tls_bss_middle], tls_bss_middle
    ret
.end:

[global idt_flush]
idt_flush:
    mov eax, [esp+4]
    lidt [eax]
    ret
