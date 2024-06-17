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
    .extern srand
    .extern disp_binary
    .extern clearScreen
    .extern printString
    .extern refreshScreen

    .equ OUTPUT, 1
    .equ LED_PIN, 21
    
    
    


    .equ KEY_LEFT, 68
    .equ KEY_RIGHT, 67

auto_fantastico_asm:

    @ Inicialización de la interfaz
    bl pioInit
    ldr r0, =LED_PIN
    mov r1, #OUTPUT
    bl pinMode

    mov r3, #2000  @ Tiempo inicial
    mov r4, #0     @ Variable de tecla

    mov r0, #0     @ Limpiar la pantalla
    bl clearScreen

    @ Imprimir mensajes
    ldr r0, =msg_auto_fantastico
    bl printString
    ldr r0, =msg_salida
    bl printString
    ldr r0, =msg_aumentar
    bl printString
    ldr r0, =msg_disminuir
    bl printString

loop:
    mov r2, #0x80  @ Iniciar con 0x80 (desplazamiento a la derecha)
    mov r5, #8     @ Contador para el bucle exterior

outer_loop:
    @ Manejo de entrada del teclado
    bl kbhit
    cmp r0, #0     @ Verificar si hay una tecla presionada
    beq no_key_press

    bl getch       @ Obtener la tecla presionada
    mov r4, r0     @ Almacenar la tecla en r4

    cmp r4, #224   @ Verificar si es un código extendido
    bne no_key_press

    bl getch       @ Leer el siguiente byte del código extendido
    mov r4, r0     @ Almacenar el código extendido en r4

    cmp r4, #72    @ Tecla de flecha arriba
    beq key_up

    cmp r4, #75    @ Tecla de flecha izquierda (salida)
    beq key_left

    cmp r4, #80    @ Tecla de flecha abajo
    beq key_down

no_key_press:
    @ Mostrar el patrón actual en los LEDs
    mov r0, #LED_PIN
    mov r1, r2
    bl digitalWrite

    mov r0, r3     @ Delay según el tiempo actual
    bl delayMillis

    @ Desplazar el patrón a la derecha
    lsr r2, r2, #1

    subs r5, r5, #1
    bne outer_loop

    mov r2, #0x01  @ Iniciar con 0x01 (desplazamiento a la izquierda)
    mov r5, #6     @ Contador para el bucle interior

inner_loop:
    @ Manejo de entrada del teclado
    bl kbhit
    cmp r0, #0     @ Verificar si hay una tecla presionada
    beq no_key_press_inner

    bl getch       @ Obtener la tecla presionada
    mov r4, r0     @ Almacenar la tecla en r4

    cmp r4, #224   @ Verificar si es un código extendido
    bne no_key_press_inner

    bl getch       @ Leer el siguiente byte del código extendido
    mov r4, r0     @ Almacenar el código extendido en r4

    cmp r4, #72    @ Tecla de flecha arriba
    beq key_up

    cmp r4, #75    @ Tecla de flecha izquierda (salida)
    beq key_left

    cmp r4, #80    @ Tecla de flecha abajo
    beq key_down

no_key_press_inner:
    @ Mostrar el patrón actual en los LEDs
    mov r0, #LED_PIN
    mov r1, r2
    bl digitalWrite

    mov r0, r3     @ Delay según el tiempo actual
    bl delayMillis

    @ Desplazar el patrón a la izquierda
    lsl r2, r2, #1

    subs r5, r5, #1
    bne inner_loop

    b loop

key_up:
    add r3, r3, #500   @ Aumentar tiempo
    b loop

key_left:
    bx lr              @ Salir de la función

key_down:
    cmp r3, #500
    blt loop
    sub r3, r3, #500   @ Disminuir tiempo
    b loop

.data
msg_auto_fantastico: .asciz "Estás viendo el Auto Fantástico!\n"
msg_salida: .asciz "Presiona flechita izquierda para salir!\n"
msg_aumentar: .asciz "Presiona flechita arriba para aumentar la velocidad!\n"
msg_disminuir: .asciz "Presiona flechita abajo para disminuir la velocidad!\n"


     

   
choque_asm:
    @ Inicialización de la interfaz
    bl pioInit
    ldr r0, =LED_PIN
    mov r1, #OUTPUT
    bl pinMode

    mov r3, #2000  @ Tiempo inicial
    mov r4, #0     @ Variable de tecla

    mov r0, #0     @ Limpiar la pantalla
    bl clearScreen

    @ Imprimir mensajes
    ldr r0, =msg_choque
    bl printString
    ldr r0, =msg_salida
    bl printString
    ldr r0, =msg_aumentar
    bl printString
    ldr r0, =msg_disminuir
    bl printString

loop:
    mov r5, #8     @ Contador para el bucle exterior

outer_loop:
    @ Manejo de entrada del teclado
    bl kbhit
    cmp r0, #0     @ Verificar si hay una tecla presionada
    beq no_key_press

    bl getch       @ Obtener la tecla presionada
    mov r4, r0     @ Almacenar la tecla en r4

    cmp r4, #224   @ Verificar si es un código extendido
    bne no_key_press

    bl getch       @ Leer el siguiente byte del código extendido
    mov r4, r0     @ Almacenar el código extendido en r4

    cmp r4, #72    @ Tecla de flecha arriba
    beq key_up

    cmp r4, #75    @ Tecla de flecha izquierda (salida)
    beq key_left

    cmp r4, #80    @ Tecla de flecha abajo
    beq key_down

no_key_press:
    @ Mostrar el patrón actual en los LEDs
    ldr r0, =TablaCh
    add r0, r0, r6, LSL #1   @ Calcular dirección de TablaCh[k]
    ldrb r1, [r0]            @ Cargar valor de TablaCh[k] (byte)
    mov r2, #2               @ Número de bits a mostrar
    bl disp_binary

    mov r0, r3     @ Delay según el tiempo actual
    bl delayMillis

    @ Incrementar contador y verificar fin del bucle exterior
    add r6, r6, #1
    cmp r6, #8
    blt outer_loop

    b loop

key_up:
    add r3, r3, #500   @ Aumentar tiempo
    b loop

key_left:
    bx lr              @ Salir de la función

key_down:
    cmp r3, #500
    blt loop
    sub r3, r3, #500   @ Disminuir tiempo
    b loop

.data
TablaCh: .byte 0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81
msg_choque: .asciz "Estás viendo el Choque!\n"
msg_salida: .asciz "Presiona flechita izquierda para salir!\n"
msg_aumentar: .asciz "Presiona flechita arriba para aumentar la velocidad!\n"
msg_disminuir: .asciz "Presiona flechita abajo para disminuir la velocidad!\n"






ambulancia_asm:
    @ Inicialización de la interfaz
    bl pioInit
    ldr r0, =LED_PIN
    mov r1, #OUTPUT
    bl pinMode

    mov r3, #2000  @ Tiempo inicial
    mov r4, #0     @ Variable de tecla

    mov r0, #0     @ Limpiar la pantalla
    bl clearScreen

    @ Imprimir mensajes
    ldr r0, =msg_ambulancia
    bl printString
    ldr r0, =msg_salida
    bl printString
    ldr r0, =msg_aumentar
    bl printString
    ldr r0, =msg_disminuir
    bl printString
    bl refreshScreen

    @ Bucle principal
loop:
    mov r5, #2     @ Contador para el bucle exterior

outer_loop:
    mov r6, #8     @ Contador para el bucle interior

inner_loop:
    @ Manejo de entrada del teclado
    bl kbhit
    cmp r0, #0     @ Verificar si hay una tecla presionada
    beq no_key_press

    bl getch       @ Obtener la tecla presionada
    mov r4, r0     @ Almacenar la tecla en r4

    cmp r4, #27    @ Verificar si es el código de escape
    bne no_key_press

    bl getch       @ Leer el siguiente byte del código extendido
    mov r4, r0     @ Almacenar el código extendido en r4

    bl getch       @ Leer el siguiente byte del código extendido
    mov r4, r0     @ Almacenar el código extendido en r4

    cmp r4, #65    @ Tecla de flecha arriba
    beq key_up

    cmp r4, #66    @ Tecla de flecha abajo
    beq key_down

    cmp r4, #68    @ Tecla de flecha izquierda (salida)
    beq key_left

no_key_press:
    @ Mostrar patrón en LEDs según dirección actual
    cmp r5, #2
    beq show_right_pattern

    show_left_pattern:
    ldr r0, =output_left_pattern
    bl shift_and_display
    b delay_between_patterns

    show_right_pattern:
    ldr r0, =output_right_pattern
    bl shift_and_display

delay_between_patterns:
    mov r0, r3     @ Delay entre patrones
    mul r0, r0, #1000
    bl usleep

    @ Final del bucle interior
    subs r6, r6, #1
    bne inner_loop

    @ Parpadeo de luces x2
    mov r0, #2
    bl parpadeo

    @ Final del bucle exterior
    subs r5, r5, #1
    bne outer_loop

    b loop

key_up:
    sub r3, r3, #500   @ Disminuir tiempo
    b loop

key_down:
    add r3, r3, #500   @ Aumentar tiempo
    b loop

key_left:
    bl endwin          @ Salir de la función
    bx lr

shift_and_display:
    ldrb r1, [r0]     @ Cargar valor de patrón (byte)
    mov r2, #8        @ Número de bits a mostrar

    @ Mostrar patrón en LEDs
    bl disp_binary
    bx lr

.data
msg_ambulancia: .asciz "Estás viendo la Ambulancia!\n"
msg_salida: .asciz "Presiona flechita izquierda para salir!\n"
msg_aumentar: .asciz "Presiona flechita arriba para aumentar la velocidad!\n"
msg_disminuir: .asciz "Presiona flechita abajo para disminuir la velocidad!\n"
output_left_pattern: .byte 0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0xE0, 0xC0, 0x80
output_right_pattern: .byte 0x01, 0x03, 0x07, 0x0F, 0x0F, 0x07, 0x03, 0x01




Juego_asm:
    @ Inicialización de la interfaz
    bl pioInit
    ldr r0, =LED_PIN
    mov r1, #OUTPUT
    bl pinMode

    mov r3, #3000   @ Tiempo inicial entre patrones (en milisegundos)
    mov r4, #0      @ Variable para tecla
    mov r5, #0      @ Respuesta correcta

    mov r0, #0      @ Limpiar la pantalla
    bl clearScreen

    @ Imprimir mensajes
    ldr r0, =msg_salir
    bl printString
    ldr r0, =msg_aumentar
    bl printString
    ldr r0, =msg_disminuir
    bl printString
    bl refreshScreen

    @ Configurar semilla aleatoria basada en el tiempo actual
    bl time
    mov r6, r0       @ Obtener el tiempo actual
    bl srand
    mov r0, r6       @ Semilla para la generación aleatoria

    @ Bucle principal del juego
loop:
    @ Generar patrón aleatorio y mostrarlo en los LEDs
    bl generate_pattern
    bl show_pattern

    @ Determinar la respuesta correcta
    cmp r0, #0x80
    moveq r5, #KEY_LEFT
    movne r5, #KEY_RIGHT

    @ Esperar la respuesta del usuario
    mov r7, #0       @ Timer
wait_key:
    @ Verificar si hay una tecla presionada
    bl kbhit
    cmp r0, #0
    beq no_key_press

    @ Obtener la tecla presionada
    bl getch
    mov r4, r0       @ Almacenar la tecla en r4

    cmp r4, #27      @ Verificar si es el código de escape
    bne no_key_press

    @ Leer el siguiente byte del código extendido
    bl getch
    mov r4, r0       @ Almacenar el código extendido en r4

    cmp r4, #65      @ Tecla de flecha arriba
    beq key_up

    cmp r4, #66      @ Tecla de flecha abajo
    beq key_down

    cmp r4, #67      @ Tecla de flecha derecha (respuesta correcta)
    cmp r4, r5
    bne wait_key
    bl parpadeo      @ Parpadear LEDs una vez si la respuesta es correcta
    b loop

    cmp r4, #68      @ Tecla de flecha izquierda (respuesta correcta)
    cmp r4, r5
    bne wait_key
    bl parpadeo      @ Parpadear LEDs una vez si la respuesta es correcta
    b loop

    cmp r4, #'s'     @ Salir del juego con 's'
    cmp r4, #'S'
    bne wait_key
    bl endwin        @ Salir de la función
    bx lr

no_key_press:
    @ Se acabó el tiempo, parpadear LEDs tres veces
    mov r0, #3
    bl parpadeo
    b loop

key_up:
    sub r3, r3, #500   @ Disminuir tiempo de espera
    b loop

key_down:
    add r3, r3, #500   @ Aumentar tiempo de espera
    b loop

generate_pattern:
    bl rand            @ Generar número aleatorio
    and r0, r0, #1     @ Tomar el módulo 2 del número aleatorio
    cmp r0, #0
    moveq r0, #0x80    @ Si es 0, devolver 0x80 (izquierda)
    movne r0, #0x01    @ Si es 1, devolver 0x01 (derecha)
    bx lr

show_pattern:
    ldr r1, =LED_PIN   @ Pin de los LEDs
    ldrb r2, [r0]      @ Cargar el patrón
    bl disp_binary     @ Mostrar el patrón en los LEDs
    bx lr

parpadeo:
    ldr r0, =0xFF      @ Apagar todos los LEDs
    ldr r1, =0x00
    bl disp_binary
    mov r0, #500       @ Delay de 500 milisegundos
    bl delayMillis
    ldr r0, =0x00      @ Encender todos los LEDs
    ldr r1, =0xFF
    bl disp_binary
    mov r0, #500       @ Delay de 500 milisegundos
    bl delayMillis
    ldr r0, =0xFF      @ Apagar todos los LEDs nuevamente
    ldr r1, =0x00
    bl disp_binary
    bx lr

.data
msg_salir: .asciz "Presiona 's' para salir.\n"
msg_aumentar: .asciz "Presiona flechita arriba para aumentar la velocidad.\n"
msg_disminuir: .asciz "Presiona flechita abajo para disminuir la velocidad.\n"
