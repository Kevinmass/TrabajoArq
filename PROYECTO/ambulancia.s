.global ambulancia
.extern encender_led
.extern apagar_led
.extern prenderTodos
.extern apagarTodos
.extern delayMicro
.extern display_binary

ambulancia:
    push {lr}              // Guardar el valor del enlace de retorno en la pila
//    mov r4, #10             // Repetir 10 veces la secuencia completa
    mov r6, #600
    LDR R9, =tabla


repetir_secuencia:
    mov r7, #5
    mov r5, #5            // Repetir n veces la secuencia de encender y apagar extremos
    mov r6, #600
    mov r8, #5

//    MOV r3, #5             // Repetir n veces prender y apagar todos

repetir_todos:
    BL prenderTodos
    BL delay               // Esperar 1 segundo
    BL apagarTodos
    BL delay               // Esperar 1 segundo
    BL apagarTodos
    BL delay               // Esperar 1 segundo

    LDR R9, =tabla
    MOV R10, #1
    LDRB R0, [R9, R10]
    BL display_binary
    SUBS r7, r7, #1   
    BGT repetir_todos


//    mov r3, #5 	//repetir n veces ida_vuelta
    
repetir_ida_vuelta:

ida: 
	LDR R9, =tabla
	mov r6, #50

	mov r0, #1
	bl encender_led
	MOV R10, #2
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #2
	bl encender_led
	MOV R10, #3
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #3
	bl encender_led
	MOV R10, #4
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #4
	bl encender_led
	MOV R10, #5
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #5
	bl encender_led
	MOV R10, #6
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #6
	bl encender_led
	MOV R10, #7
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #7
	bl encender_led
	MOV R10, #8
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #8
	bl encender_led
	MOV R10, #9
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	
vuelta:
	LDR R9, =tabla

	mov r0, #8
	bl encender_led
	MOV R10, #9
	LDRB R0, [R9, R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #7
	bl encender_led
	MOV R10, #8
	LDRB R0, [R9,R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #6
	bl encender_led
	MOV R10, #7
	LDRB R0, [R9,R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #5
	bl encender_led
	MOV R10, #6
	LDRB R0, [R9,R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #4
	bl encender_led
	MOV R10, #5
	LDRB R0, [R9,R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #3
	bl encender_led
	MOV R10, #4
	LDRB R0, [R9,R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	mov r0, #2
	bl encender_led
	MOV R10, #3
	LDRB R0, [R9,R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay
	
	mov r0, #1
	bl encender_led
	MOV R10, #2
	LDRB R0, [R9,R10]
	BL display_binary
	bl delay
	bl apagar_led
	bl delay

	subs r8, r8, #1
	
	bgt repetir_ida_vuelta
//	subs r4, r4, #1
	b repetir_secuencia


pop {lr}               // Recuperar el valor del enlace de retorno de la pila
mov pc, lr             // Regresar al llamador

//funcion delay

delay:
    push {lr}              // Guardar el valor del enlace de retorno en la pila
    mov r0, r6
    LDR r1, =110
    MUL r0, r0, r1
    bl delayMicro
    pop {lr}               // Recuperar el valor del enlace de retorno de la pila
    mov pc, lr             // Regresar al llamador

//tabla de pines, cambiar en caso de usar otra raspberry
tabla:
	.byte 0xC3,0xFF,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01