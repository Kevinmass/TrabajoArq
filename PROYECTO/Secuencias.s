    .global custom_sequence_algorithm_asm
    .global custom_sequence_table_asm
    .extern pioInit
    .extern pinMode
    .extern digitalWrite
    .extern sleep

#define OUTPUT 1
#define LED1 17
#define LED2 18
#define LED3 27
#define LED4 22

; Función de secuencia personalizada por algoritmo
custom_sequence_algorithm_asm:
    // Inicializar EasyPIO
    bl pioInit

    ; Configurar pines como salida
    ldr r0, =LED1
    mov r1, #OUTPUT
    bl pinMode
    ldr r0, =LED2
    mov r1, #OUTPUT
    bl pinMode
    ldr r0, =LED3
    mov r1, #OUTPUT
    bl pinMode
    ldr r0, =LED4
    mov r1, #OUTPUT
    bl pinMode

    ; Secuencia personalizada por algoritmo
    ldr r0, =LED1
    mov r1, #1
    bl digitalWrite
    mov r0, #1
    bl sleep
    ldr r0, =LED1
    mov r1, #0
    bl digitalWrite
    ldr r0, =LED2
    mov r1, #1
    bl digitalWrite
    mov r0, #1
    bl sleep
    ldr r0, =LED2
    mov r1, #0
    bl digitalWrite

    bx lr

; Función de secuencia personalizada usando tabla de datos
custom_sequence_table_asm:
    // Inicializar EasyPIO
    bl pioInit
    
	; Configurar pines como salida
    ldr r0, =LED1
    mov r1, #OUTPUT
    bl pinMode
    ldr r0, =LED2
    mov r1, #OUTPUT
    bl pinMode
    ldr r0, =LED3
    mov r1, #OUTPUT
    bl pinMode
    ldr r0, =LED4
    mov r1, #OUTPUT
    bl pinMode

    ; Tabla de secuencias
    ldr r2, =sequence
    mov r3, #4  ; Número de LEDs

loop:
    ldr r0, [r2], #4
    mov r1, #1
    bl digitalWrite
    mov r0, #1
    bl sleep
    mov r1, #0
    bl digitalWrite
    subs r3, r3, #1
    bne loop

    bx lr

.data
sequence:
    .word LED1
    .word LED2
    .word LED3
    .word LED4
