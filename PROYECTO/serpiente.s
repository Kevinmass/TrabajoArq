.extern ledTable
.extern prenderTodos
.extern apagarTodos
.extern delayMicro
.extern display_binary
.global relevo
relevo:
	PUSH {R4, R5, R6, LR}
	 MOV R8, #600
	LDR R4, =table

cont_1:
	MOV R6, #0

ida:
	LDRB R5, [R4, R6]
	MOV R0, R5
	BL ledTable
	MOV R0, R5
	BL display_binary
	MOV R0, R8
	BL delay
	ADD R6, R6, #1
	CMP R6, #29
	BNE ida
	MOV R6, #1
	LDR R4, =table
	B ida

delay:
	PUSH {LR}
	MOV R0, R8
	LDR R1, =110
	MUL R0, R0, R1
	BL delayMicro
	POP {LR}
	MOV PC, LR


.data
table:
	.byte 0x01, 0x81, 0x41, 0x21, 0x11, 0x09, 0x05, 0x03, 0x01, 0x03, 0x05, 0x09, 0x11, 0x21, 0x41, 0x81, 0x82, 0x84, 0x88, 0x90, 0xA0, 0xC0, 0x80, 0xC0, 0xA0, 0x90, 0x88, 0x84, 0x82, 0x81

