;-------------------------------------------
; Interrupt handlers.
;-------------------------------------------
extern x86_interrupt_fault_handler
extern x86_interrupt_irq_handler

%macro defineISR 1
global isr%1
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro defineISRE 1
global isr%1
isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

%macro defineIRQ 2
global irq%1
irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

%macro setupSegment 0
    mov ax, 0x28
    mov fs, ax
    mov ax, 0x30
    mov gs, ax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
%endmacro

defineISR 0     ;  0: Divide By Zero Exception
defineISR 1     ;  1: Debug Exception
defineISR 2     ;  2: Non Maskable Interrupt Exception
defineISR 3     ;  3: Int 3 Exception
defineISR 4     ;  4: INTO Exception
defineISR 5     ;  5: Out of Bounds Exception
defineISR 6     ;  6: Invalid Opcode Exception
defineISR 7     ;  7: Coprocessor Not Available Exception
defineISRE 8    ;  8: Double Fault Exception
defineISR 9     ;  9: Coprocessor Segment Overrun Exception
defineISRE 10   ; 10: Bad TSS Exception
defineISRE 11   ; 11: Segment Not Present Exception
defineISRE 12   ; 12: Stack Fault Exception
defineISRE 13   ; 13: General Protection Fault Exception
defineISRE 14   ; 14: Page Fault Exception
defineISR 15    ; 15: Reserved Exception
defineISR 16    ; 16: Floating Point Exception
defineISR 17    ; 17: Alignment Check Exception
defineISR 18    ; 18: Machine Check Exception
defineISR 19    ; 19: Reserved
defineISR 20    ; 20: Reserved
defineISR 21    ; 21: Reserved
defineISR 22    ; 22: Reserved
defineISR 23    ; 23: Reserved
defineISR 24    ; 24: Reserved
defineISR 25    ; 25: Reserved
defineISR 26    ; 26: Reserved
defineISR 27    ; 27: Reserved
defineISR 28    ; 28: Reserved
defineISR 29    ; 29: Reserved
defineISR 30    ; 30: Reserved
defineISR 31    ; 31: Reserved
defineIRQ 0,32  ; 32: IRQ0
defineIRQ 1,33  ; 33: IRQ1
defineIRQ 2,34  ; 34: IRQ2
defineIRQ 3,35  ; 35: IRQ3
defineIRQ 4,36  ; 36: IRQ4
defineIRQ 5,37  ; 37: IRQ5
defineIRQ 6,38  ; 38: IRQ6
defineIRQ 7,39  ; 39: IRQ7
defineIRQ 8,40  ; 40: IRQ8
defineIRQ 9,41  ; 41: IRQ9
defineIRQ 10,42 ; 42: IRQ10
defineIRQ 11,43 ; 43: IRQ11
defineIRQ 12,44 ; 44: IRQ12
defineIRQ 13,45 ; 45: IRQ13
defineIRQ 14,46 ; 46: IRQ14
defineIRQ 15,47 ; 47: IRQ15
 
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    setupSegment

    mov eax, esp
    push eax
    mov eax, x86_interrupt_fault_handler
    call eax
    pop eax
    
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    setupSegment

    mov eax, esp
    push eax
    mov eax, x86_interrupt_irq_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
