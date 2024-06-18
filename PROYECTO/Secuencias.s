.global auto_fantastico_asm
.global choque_asm
.global ambulancia_asm
.global Juego_asm

.extern pioInit
.extern pinMode
.extern digitalWrite
.extern delayMillis
.extern usleep
.extern endwin
.extern kbhit
.extern getch
.extern rand
.extern srand
.extern time
.extern disp_binary
.extern clearScreen
.extern printString
.extern refreshScreen

.equ OUTPUT, 1
.equ LED_PIN, 21
.equ KEY_LEFT, 68
.equ KEY_RIGHT, 67

.data
msg_salirS: .asciz "Presiona 's' para salir.\n"
msg_aumentar: .asciz "Presiona flechita arriba para aumentar la velocidad.\n"
msg_disminuir: .asciz "Presiona flechita abajo para disminuir la velocidad.\n"
msg_auto_fantastico: .asciz "Estás viendo el Auto Fantástico!\n"
msg_salidaI: .asciz "Presiona flechita izquierda para salir!\n"
TablaCh: .byte 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81
msg_choque: .asciz "Estás viendo el Choque!\n"
msg_ambulancia: .asciz "Estás viendo la Ambulancia!\n"
output_left_pattern: .byte 0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0xE0, 0xC0, 0x80
output_right_pattern: .byte 0x01, 0x03, 0x07, 0x0F, 0x0F, 0x07, 0x03, 0x01

.text
.auto_fantastico_asm:
    bl pioInit
    ldr r0, =LED_PIN
    mov r1, #OUTPUT
    bl pinMode
    mov r3, #2000
    mov r4, #0
    mov r0, #0
    bl clearScreen
    ldr r0, =msg_auto_fantastico
    bl printString
    ldr r0, =msg_salidaI
    bl printString
    ldr r0, =msg_aumentar
    bl printString
    ldr r0, =msg_disminuir
    bl printString

.loop:
    mov r2, #0x80
    mov r5, #8

.outer_loop1:
    bl kbhit
    cmp r0, #0
    beq .no_key_press
    bl getch
    mov r4, r0
    cmp r4, #224
    bne .no_key_press
    bl getch
    mov r4, r0
    cmp r4, #72
    beq .key_up
    cmp r4, #75
    beq .key_left
    cmp r4, #80
    beq .key_down

.no_key_press:
    mov r0, #LED_PIN
    mov r1, r2
    bl digitalWrite
    mov r0, r3
    bl delayMillis
    lsr r2, r2, #1
    subs r5, r5, #1
    bne .outer_loop1
    mov r2, #0x01
    mov r5, #6

.inner_loop:
    bl kbhit
    cmp r0, #0
    beq .no_key_press_inner
    bl getch
    mov r4, r0
    cmp r4, #224
    bne .no_key_press_inner
    bl getch
    mov r4, r0
    cmp r4, #72
    beq .key_up
    cmp r4, #75
    beq .key_left
    cmp r4, #80
    beq .key_down

.no_key_press_inner:
    mov r0, #LED_PIN
    mov r1, r2
    bl digitalWrite
    mov r0, r3
    bl delayMillis
    lsl r2, r2, #1
    subs r5, r5, #1
    bne .inner_loop
    b .loop

.key_up:
    add r3, r3, #500
    b .loop

.key_left:
    bx lr

.key_down:
    cmp r3, #500
    blt .loop
    sub r3, r3, #500
    b .loop

.choque_asm:
    bl pioInit
    ldr r0, =LED_PIN
    mov r1, #OUTPUT
    bl pinMode
    mov r3, #2000
    mov r4, #0
    mov r0, #0
    bl clearScreen
    ldr r0, =msg_choque
    bl printString
    ldr r0, =msg_salidaI
    bl printString
    ldr r0, =msg_aumentar
    bl printString
    ldr r0, =msg_disminuir
    bl printString

.loop:
    mov r5, #8

.outer_loop2:
    bl kbhit
    cmp r0, #0
    beq .no_key_press
    bl getch
    mov r4, r0
    cmp r4, #224
    bne .no_key_press
    bl getch
    mov r4, r0
    cmp r4, #72
    beq .key_up
    cmp r4, #75
    beq .key_left
    cmp r4, #80
    beq .key_down

.no_key_press:
    ldr r0, =TablaCh
    add r0, r0, r6, LSL #1
    ldrb r1, [r0]
    mov r2, #2
    bl disp_binary
    mov r0, r3
    bl delayMillis
    add r6, r6, #1
    cmp r6, #8
    blt .outer_loop2
    b .loop

.key_up:
    add r3, r3, #500
    b .loop

.key_left:
    bx lr

.key_down:
    cmp r3, #500
    blt .loop
    sub r3, r3, #500
    b .loop

.ambulancia_asm:
    bl pioInit
    ldr r0, =LED_PIN
    mov r1, #OUTPUT
    bl pinMode
    mov r3, #2000
    mov r4, #0
    mov r0, #0
    bl clearScreen
    ldr r0, =msg_ambulancia
    bl printString
    ldr r0, =msg_salidaI
    bl printString
    ldr r0, =msg_aumentar
    bl printString
    ldr r0, =msg_disminuir
    bl printString
    bl refreshScreen

.loop:
    mov r5, #2

.outer_loop3:
    mov r6, #8

.inner_loop:
    bl kbhit
    cmp r0, #0
    beq .no_key_press
    bl getch
    mov r4, r0
    cmp r4, #27
    bne .no_key_press
    bl getch
    mov r4, r0
    bl getch
    mov r4, r0
    cmp r4, #65
    beq .key_up
    cmp r4, #66
    beq .key_down
    cmp r4, #68
    beq .key_left

.no_key_press:
    cmp r5, #2
    beq .show_right_pattern

.show_left_pattern:
    ldr r0, =output_left_pattern
    bl shift_and_display
    b .delay_between_patterns

.show_right_pattern:
    ldr r0, =output_right_pattern
    bl shift_and_display

.delay_between_patterns:
    mov r0, r3
    mul r0, r0, #1000
    bl usleep
    subs r6, r6, #1
    bne .inner_loop
    b .loop

.key_up:
    sub r3, r3, #500
    b .loop

.key_down:
    add r3, r3, #500
    b .loop

.key_left:
    bl endwin
    bx lr

.shift_and_display:
    ldrb r1, [r0]
    mov r2, #8
    bl disp_binary
    bx lr

.Juego_asm:
    bl pioInit
    ldr r0, =LED_PIN
    mov r1, #OUTPUT
    bl pinMode
    mov r3, #3000
    mov r4, #0
    mov r5, #0
    mov r0, #0
    bl clearScreen
    ldr r0, =msg_salirS
    bl printString
    ldr r0, =msg_aumentar
    bl printString
    ldr r0, =msg_disminuir
    bl printString
    bl refreshScreen
    bl time
    mov r6, r0
    bl srand
    mov r0, r6

.loop:
    bl generate_pattern
    bl show_pattern
    cmp r0, #0x80
    moveq r5, #KEY_LEFT
    movne r5, #KEY_RIGHT
    mov r7, #0

.wait_key:
    bl kbhit
    cmp r0, #0
    beq .no_key_press
    bl getch
    mov r4, r0
    cmp r4, #27
    bne .no_key_press
    bl getch
    mov r4, r0
    bl getch
    mov r4, r0
    cmp r4, #65
    beq .key_up
    cmp r4, #66
    beq .key_down
    cmp r4, #67
    cmp r4, r5
    bne .wait_key
    bl parpadeo
    b .loop
    cmp r4, #68
    cmp r4, r5
    bne .wait_key
    bl parpadeo
    b .loop
    cmp r4, #'s'
    cmp r4, #'S'
    bne .wait_key
    bl endwin
    bx lr

.no_key_press:
    mov r0, #3
    bl parpadeo
    b .loop

.key_up:
    sub r3, r3, #500
    b .loop

.key_down:
    add r3, r3, #500
    b .loop

.generate_pattern:
    bl rand
    and r0, r0, #1
    cmp r0, #0
    moveq r0, #0x80
    movne r0, #0x01
    bx lr

.show_pattern:
    ldr r1, =LED_PIN
    ldrb r2, [r0]
    bl disp_binary
    bx lr

.parpadeo:
    ldr r0, =0xFF
    ldr r1, =0x00
    bl disp_binary
    mov r0, #500
    bl delayMillis
    ldr r0, =0x00
    ldr r1, =0xFF
    bl disp_binary
    mov r0, #500
    bl delayMillis
    ldr r0, =0xFF
    ldr r1, =0x00
    bl disp_binary
    bx lr
