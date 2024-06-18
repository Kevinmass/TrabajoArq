#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "EasyPio.h"



// Definir los pines GPIO utilizados
const char led[] = {14, 15, 18, 23, 24, 25, 8, 7}; // Variable Global
unsigned char TablaCh[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
int leds(int num);
void Disp_Binary(int);

// Funciones en Assembly
void auto_fantastico_asm();
void choque_asm();
void ambulancia_asm();
void Juego_asm();

int tiempo_global = 2000; // Tiempo global


void disp_binary(int i, int option) {
    leds(i); // Actualiza los LEDs
    move(0, 0); // Mueve el cursor al inicio de la pantalla
    for (int t = 128; t > 0; t = t / 2) {
        if (i & t) {
            printw("*");
        } else {
            printw("_");
        }
    }
    printw("\n");
    refresh();
}

int kbhit(void)
{

    int ch = getch();

    if (ch != ERR)
    {

        ungetch(ch); // Vuelve a poner el carácter en la cola de entrada

        return 1;
    }

    return 0;
}

int leds(int num) {
    int i, numval;
    for (i = 0; i < 8; i++) {
        numval = (num >> i) & 0x01;
        digitalWrite(led[i], numval);
    }
    return 0;
}

// Prototipos de las funciones
void auto_fantastico();
void choque();
void ambulancia();
void Juego();

int contrasena();
void menu();
void secuencia(int choice);
void parpadeo();
void mostrar_patron(unsigned char pattern);

int main() {
    int aux = 0;
    pioInit();  // Inicializar EasyPIO

    for (int k = 0; k < 8; k++) {
        pinMode(led[k], OUTPUT); // Configuro los 8 pines para los Leds como salidas en main
    }
    leds(0xFF);

    initscr(); //Inicializa ncurses
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);

    aux = contrasena();
    if (aux == 0)
    {
        return 0;
    }
    
    int choice;

    while(1) {
        menu();
        printw("Seleccione una secuencia de luces: ");
        scanf("%d", &choice);
        
        if (choice == 5) {
            printw("Saliendo del programa.\n");
            break;
        }
        
        secuencia(choice);
    }

    return 0;
}

void menu() {
    clear(); 
    printw("Menu de Secuencias de Luces:\n");
    printw("1. auto fantastico \n");
    printw("2. choque \n");
    printw("3. ambulancia \n");
    printw("4. otra\n");
    printw("5. Salir\n");
}

int contrasena() {
    char contra[20];
    char correct_contra[] = "1234"; // Contraseña predefinida
    int cont = 1;
    while (1) {
        printw("Intento Nro: %d\n", cont);
        printw("Ingrese la contraseña: ");
        scanf("%s", contra);

        if (strcmp(contra, correct_contra) == 0) {
            printw("Acceso concedido.\n");
            return 1;
        } else {
            printw("Contraseña incorrecta. Intente de nuevo.\n");
        }
        cont++;
        if (cont > 3) {
            printw("Demasiados intentos fallidos.\n");
            return 0;
        }
    }
}

void secuencia(int choice) {
    switch (choice) {
        case 1:
           auto_fantastico();
            break;
        case 2:
            choque();
            break;
        case 3:
            ambulancia();
            break;
        case 4:
            Juego();
            break;
        default:
            printw("Opción inválida.\n");
    }
}

 void auto_fantastico_asm(){
__asm(
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
    )
}

void auto_fantastico() {
    do
    {
    printw("Quieres la version de C o de Assembly?\n");
    printw("1. C\n");
    printw("2. Assembly\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 2) {
        auto_fantastico_asm();
        return;
    } else {
        printw("Opción inválida.\n");
    }   
    } while (1);
    
    unsigned char output;
    int key;
    int tiempo = 2000; // Tiempo inicial

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);

     pioInit();
    pinMode(21, OUTPUT);
    clear(); 
    printw("Estás viendo el Auto Fantástico!\n");
    printw("Presiona flechita izquierda para salir!\n");
    printw("Presiona flechita arriba para aumentar la velocidad!\n");
    printw("Presiona flechita abajo para disminuir la velocidad!\n");

    do {
        output = 0x80; 
        for (int k = 0; k < 8; k++) {
            if (kbhit())
                {                     
                key=getch();
                if (key == 224) {
                        do {
                            key=getch();
                        } while(key==224);
                        
                        switch (key) {
                            case 72:
                                tiempo += 500;
                                break;
                            case 75:
                                return; //flecha izquierda
                                break;
                            case 80:
                            if (tiempo > 500)
                            {
                                tiempo -= 500;
                            }
                                break;         
                        }
                    }
                }

            digitalWrite(21, (output & 0x01) != 0);
            delayMillis(tiempo); 
            output >> 1; // Desplaza a la derecha
        }
         output = 0x01; 
        for (int k = 0; k < 6; k++)
        {
            if (kbhit())
                {                     
                key=getch();
                if (key == 224) {
                        do {
                            key=getch();
                        } while(key==224);
                        
                        switch (key) {
                            case 72:
                                tiempo += 500;
                                break;
                            case 75:
                                return; //flecha izquierda
                                break;
                            case 80:
                            if (tiempo > 500)
                            {
                                tiempo -= 500;
                            }
                                break;         
                        }
                    }
                }
            digitalWrite(21, (output & 0x01) != 0);
            delayMillis(tiempo); 
            output << 1; // Desplaza a la izquierda
        }
        
    } while (1);
}


void choque_asm(){

__asm (
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
    b .loop)
}

void choque() {
    do
    {
    printw("Quieres la version de C o de Assembly?\n");
    printw("1. C\n");
    printw("2. Assembly\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 2) {
        choque_asm();
        return;
    } else {
        printw("Opción inválida.\n");
    }   
    } while (1);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);

     pioInit();
    pinMode(21, OUTPUT);

    clear(); 
    int tiempo = 2000;
    int key;
    printw("Estás viendo el Choque!\n");
    printw("Presiona flechita izquierda para salir!\n");
    printw("Presiona flechita arriba para aumentar la velocidad!\n");
    printw("Presiona flechita abajo para disminuir la velocidad!\n");

    while (1) {
        for (int k = 0; k < 8; k++) {
            if (kbhit())
                {                     
                key=getch();
                if (key == 224) {
                        do {
                            key=getch();
                        } while(key==224);
                        
                        switch (key) {
                            case 72:
                                tiempo += 500;
                                break;
                            case 75:
                                return; //flecha izquierda
                                break;
                            case 80:
                            if (tiempo > 500)
                            {
                                tiempo -= 500;
                            }
                                break;         
                        }
                    }
                }
            disp_binary(TablaCh[k], 2);
            delayMillis(tiempo); // Usar delayMillis en lugar de usleep
        }
    }
}


 void ambulancia_asm(){
    __asm(

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
    )
}

void ambulancia() {
    do
    {
    printw("Quieres la version de C o de Assembly?\n");
    printw("1. C\n");
    printw("2. Assembly\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 2) {
        ambulancia_asm();
        return;
    } else {
        printw("Opción inválida.\n");
    }   
    } while (1);

    unsigned char output;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);

    pioInit();
    pinMode(21, OUTPUT);

    clear(); 
    int tiempo = 2000;
    int key;

    printw("Estás viendo la Ambulancia!\n");
    printw("Presiona flechita izquierda para salir!\n");
    printw("Presiona flechita arriba para aumentar la velocidad!\n");
    printw("Presiona flechita abajo para disminuir la velocidad!\n");
    refresh();

    do {
        for (int j = 0; j < 2; j++) {
            output = 0x80;
            for (int k = 0; k < 8; k++) {
                if (kbhit()) {
                    key = getch();
                    if (key == 27) { // Detectar flechas
                        key = getch();
                        key = getch();
                        switch (key) {
                            case 65: // Flecha arriba
                                tiempo -= 500;
                                break;
                            case 66: // Flecha abajo
                                tiempo += 500;
                                break;
                            case 68: // Flecha izquierda
                                endwin();
                                return;
                        }
                    }
                }
                digitalWrite(21, (output & 0x80) != 0);
                usleep(tiempo * 1000);
                output >>= 1; // Desplaza a la derecha
            }
            output = 0x01;
            for (int k = 0; k < 6; k++) {
                if (kbhit()) {
                    key = getch();
                    if (key == 27) { // Detectar flechas
                        key = getch();
                        key = getch();
                        switch (key) {
                            case 65: // Flecha arriba
                                tiempo -= 500;
                                break;
                            case 66: // Flecha abajo
                                tiempo += 500;
                                break;
                            case 68: // Flecha izquierda
                                endwin();
                                return;
                        }
                    }
                }
                digitalWrite(21, (output & 0x01) != 0);
                usleep(tiempo * 1000);
                output <<= 1; // Desplaza a la izquierda
            }
            // Parpadeo de las luces x2
            for (int j = 0; j < 2; j++) {
                parpadeo();
            }
        }
    } while (1);
}

void mostrar_patron(unsigned char pattern) {
    disp_binary(pattern, 0xFF); // Mostrar el patrón en los LEDs
}

// Función para generar un patrón aleatorio en un extremo de los LEDs
unsigned char generate_pattern() {
    return (rand() % 2 == 0) ? 0x80 : 0x01; // Generar aleatoriamente en el extremo izquierdo (0x80) o derecho (0x01)
}

// Función para parpadear todos los LEDs una vez
void parpadeo() {
    disp_binary(0xFF, 0x00); // Apagar todos los LEDs
    delayMillis(500);
    disp_binary(0x00, 0xFF); // Encender todos los LEDs
    delayMillis(500);
    disp_binary(0xFF, 0x00); // Apagar todos los LEDs
}

// Función principal del juego
void Juego() {
    do
    {
    printw("Quieres la version de C o de Assembly?\n");
    printw("1. C\n");
    printw("2. Assembly\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 2) {
        Juego_asm();
        return;
    } else {
        printw("Opción inválida.\n");
    }   
    } while (1);

    int key;
    int tiempo = 3000; // Tiempo inicial entre patrones (en milisegundos)
    unsigned char pattern;
    int correct_answer;
    
    printw("Presiona 's' para salir.\n");
    printw("Presiona flechita arriba para aumentar la velocidad.\n");
    printw("Presiona flechita abajo para disminuir la velocidad.\n");
    refresh();

    while (1) {
        pattern = generate_pattern(); // Generar patrón aleatorio
        mostrar_patron(pattern); // Mostrar el patrón en los LEDs

        correct_answer = (pattern == 0x80) ? KEY_LEFT : KEY_RIGHT; // Determinar la respuesta correcta

        // Esperar la respuesta del usuario
        int timer = 0;
        while (timer < 3000) {
            if (kbhit()) {
                key = getch();
                if (key == 27) { // Detectar flechas
                    key = getch();
                    switch (key) {
                        case 65: // Flecha arriba
                            tiempo -= 500;
                            break;
                        case 66: // Flecha abajo
                            tiempo += 500;
                            break;
                        case 67: // Flecha derecha
                            if (key == correct_answer) {
                            parpadeo(); // Parpadear LEDs una vez si la respuesta es correcta
                           }
                        break;
                        case 68: // Flecha izquierda
                            if (key == correct_answer) {
                            parpadeo(); // Parpadear LEDs una vez si la respuesta es correcta
                            }
                        break;
                    }
                } else if (key == 's' || key == 'S') { // Salir del juego con 's' o 'S'
                    endwin();
                    return;
                }
            }
            delayMillis(100); // Esperar 100 milisegundos
            timer += 100;
        }

        if (timer >= 3000) {
            // Se acabó el tiempo, parpadear LEDs tres veces
            for (int i = 0; i < 3; ++i) {
                parpadeo();
            }
        }

        delayMillis(tiempo); // Esperar antes de mostrar el siguiente patrón
    }
}

void Juego_asm(){
    __asm(
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
    )
}
//..............................................................................


