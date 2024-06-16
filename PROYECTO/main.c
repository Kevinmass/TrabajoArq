#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "EasyPio.h"



// Definir los pines GPIO utilizados
const char led[] = {14, 15, 18, 23, 24, 25, 8, 7}; // Variable Global
unsigned char TablaCh[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};

int leds(int num);
void Disp_Binary(int);


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

int leds(int num) {
    int i, numval;
    for (i = 0; i < 8; i++) {
        numval = (num >> i) & 0x01;
        digitalWrite(led[i], numval);
    }
    return 0;
}

// Prototipos de las funciones
void common_sequence_1();
void common_sequence_2();
void custom_sequence_algorithm();
void custom_sequence_table();

void contrasena();
void menu();
void secuencia(int choice);

int main() {
    int aux = 0;
    pioInit();  // Inicializar EasyPIO
    aux = contrasena();
    if (aux == 0)
    {
        return 0;
    }
    
    int choice;

    while(1) {
        menu();
        printf("Seleccione una secuencia de luces: ");
        scanf("%d", &choice);
        
        if (choice == 5) {
            printf("Saliendo del programa.\n");
            break;
        }
        
        secuencia(choice);
    }

    return 0;
}

void menu() {
    clear(); 
    printf("Menu de Secuencias de Luces:\n");
    printf("1. auto fantastico \n");
    printf("2. choque \n");
    printf("3. ambulancia \n");
    printf("4. otra\n");
    printf("5. Salir\n");
}

void contrasena() {
    char contra[20];
    char correct_contra[] = "1234"; // Contraseña predefinida
    int cont = 1;
    while (1) {
        printf("Intento Nro: %d\n", cont);
        printf("Ingrese la contraseña: ");
        scanf("%s", contra);

        if (strcmp(contra, correct_contra) == 0) {
            printf("Acceso concedido.\n");
            return 1;
        } else {
            printf("Contraseña incorrecta. Intente de nuevo.\n");
        }
        cont++;
        if (cont > 3) {
            printf("Demasiados intentos fallidos.\n");
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
            custom_sequence_table();
            break;
        default:
            printf("Opción inválida.\n");
    }
}



void auto_fantastico() {
    unsigned char output;
    int tiempo = 2000; // Tiempo inicial
    clear(); 
    printf("Estás viendo el Auto Fantástico!\n");
    printf("Presiona 'a' para salir!\n");
    printf("Presiona 'u' para aumentar la velocidad!\n");
    printf("Presiona 'd' para disminuir la velocidad!\n");

    do {
        output = 0x80; 
        for (int t = 0; t < 8; t++) {
            if (kbhit()) {
                char ch = getchar();
                if (ch == 'a') return;
                if (ch == 'u' && tiempo > 500) tiempo -= 500;
                if (ch == 'd') tiempo += 500;
            }
            digitalWrite(21, (output & 0x01) != 0);
            delayMillis(tiempo); 
            output >>= 1; // Desplaza a la derecha
        }
    } while (1);
}

void choque() {
    clear(); 
    int tiempo = 2000;

    printf("Estás viendo el Choque!\n");
    printf("Presiona 'a' para salir!\n");
    printf("Presiona 'u' para aumentar la velocidad!\n");
    printf("Presiona 'd' para disminuir la velocidad!\n");

    while (1) {
        for (int i = 0; i < 8; i++) {
            if (kbhit()) {
                char ch = getchar();
                if (ch == 'a') return;
                if (ch == 'u' && tiempo > 500) tiempo -= 500;
                if (ch == 'd') tiempo += 500;
            }
            digitalWrite(21, i % 2);
            delayMillis(tiempo); // Usar delayMillis en lugar de usleep
        }
    }
}

void ambulancia() {
    clear(); 
    int tiempo = 2000;

    printf("Estás viendo la Ambulancia!\n");
    printf("Presiona 'a' para salir!\n");
    printf("Presiona 'u' para aumentar la velocidad!\n");
    printf("Presiona 'd' para disminuir la velocidad!\n");

    while (1) {
        for (int i = 0; i < 8; i++) {
            if (kbhit()) {
                char ch = getchar();
                if (ch == 'a') return;
                if (ch == 'u' && tiempo > 500) tiempo -= 500;
                if (ch == 'd') tiempo += 500;
            }
            digitalWrite(21, i % 2);
            delayMillis(tiempo); // Usar delayMillis en lugar de usleep
        }
    }
}

void custom_sequence_table() { //no hace nada esta de standby
clear(); 
    printf("Ejecutando Secuencia Personalizada Tabla\n");
    // Configurar pines como salida
    pioInit();
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    // Secuencia personalizada por tabla
    int sequence[] = {LED1, LED2, LED3, LED4};
    int size = sizeof(sequence) / sizeof(sequence[0]);

    for(int i = 0; i < size; i++) {
        digitalWrite(sequence[i], 1);
        delayMillis(500);
        digitalWrite(sequence[i], 0);
    }
}





int delay(int *tiempo)
int leds(int num);
void Disp_Binary(int);

#define ENTER 10
#define BACKSPACE 127

const char led[] = {14, 15, 18, 23, 24, 25, 8, 7}; // Variable Global
unsigned char TablaCh[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
unsigned char TablaMecha[] = {0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01};

int tiempo_global = 2000; // Tiempo global

int delay(int *tiempo) {
    clock_t start_time = clock();
    timeout(0); // No bloquear getch
    while ((clock() - start_time) < *tiempo * CLOCKS_PER_SEC / 1000) {
        int ch = getch();
        if (ch != ERR) {
            if (ch == 'a') {
                timeout(-1); // Volver a bloqueo
                return 1; // Regresar al menu principal
            } else if (ch == 'u') {
                if (*tiempo > 200) *tiempo -= 200;
            } else if (ch == 'd') {
                *tiempo += 200;
            }
        }
    }
    timeout(-1); // Volver a bloqueo
    return 0; // Continuar en la función actual
}

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

int leds(int num) {
    int i, numval;
    for (i = 0; i < 8; i++) {
        numval = (num >> i) & 0x01;
        digitalWrite(led[i], numval);
    }
    return 0;
}

int ingreso() {
    int intentos = 3;
    char inputPassword[6];
    int resultado = -1, i;

    while (intentos > 0) {
        clear(); // Limpia la pantalla antes de imprimir
        printw("Ingrese su password de 5 digitos: ");
        refresh();
        i = 0;
        while (i < 5) {
            int ch = getch();
            if (ch == ENTER) {
                break;
            } else if (ch != BACKSPACE) {
                inputPassword[i++] = ch;
                printw("*");
            } else if (i > 0) {
                printw("\b \b");
                i--;
            }
            refresh();
        }
        inputPassword[i] = '\0';

        resultado = strcmp(inputPassword, "admin");

        printw("\n");
        refresh();

        if (resultado == 0) {
            return 1;
        } else {
            printw("Password no valida!\n");
            refresh();
            intentos--;
        }
    }

    return 0;
}

void autoFantastico() {
    unsigned char output;
    int salir;
    do {
        clear(); // Limpia la pantalla antes de imprimir
        printw("Estas viendo el Auto Fantastico!\n");
        printw("Presione la tecla 'a' si quiere salir!\n");
        printw("Presione la tecla 'u' para aumentar la velocidad!\n");
        printw("Presione la tecla 'd' para disminuir la velocidad!\n");
        refresh();

        output = 0x80; 
        for (int t = 0; t < 8; t++) { 
            disp_binary(output, 1);
            salir = delay(&tiempo_global); 
            if (salir) return; // Salir de la función si se presionó 'a'
            output = output >> 1; // Desplaza a la derecha
        }

        output = 0x01; 
        for (int t = 0; t < 6; t++) {
            disp_binary(output, 1); 
            salir = delay(&tiempo_global); 
            if (salir) return; // Salir de la función si se presionó 'a'
            output = output << 1; // Desplaza a la Izquierda
        }
    } while (1);
}

void ChoqueT() {
    int salir;
    while (1) {
        clear(); // Limpia la pantalla antes de imprimir
        printw("Estas viendo el Choque!\n");
        printw("Presione la tecla 'a' si quiere salir!\n");
        printw("Presione la tecla 'u' para aumentar la velocidad!\n");
        printw("Presione la tecla 'd' para disminuir la velocidad!\n");
        refresh();

        for (int i = 0; i < 8; i++) {
            disp_binary(TablaCh[i], 2);
            salir = delay(&tiempo_global); 
            if (salir) return; // Salir de la función si se presionó 'a'
        }
    }
}

void Mecha() {
    int salir;
    while (1) {
        clear(); // Limpia la pantalla antes de imprimir
        printw("Estas viendo el Patrón de Espiral!\n");
        printw("Presione la tecla 'a' si quiere salir!\n");
        printw("Presione la tecla 'u' para aumentar la velocidad!\n");
        printw("Presione la tecla 'd' para disminuir la velocidad!\n");
        refresh();

        for (int i = 0; i < 8; i++) {
            disp_binary(TablaMecha[i], 3); 
            salir = delay(&tiempo_global); 
            if (salir) return; // Salir de la función si se presionó 'a'
        }
    }
}

void Tiroalblanco() {
    unsigned char output = 0xFF; // Inicialmente todos los bits en 1
    int salir;
    do {
        clear(); // Limpia la pantalla antes de imprimir
        printw("Estas viendo el Tiro al Blanco!\n");
        printw("Presione la tecla 'a' si quiere salir!\n");
        printw("Presione la tecla 'u' para aumentar la velocidad!\n");
        printw("Presione la tecla 'd' para disminuir la velocidad!\n");
        printw("\n");
        printw("###Presione un numero del 0 al 7 para apuntar###\n");
        disp_binary(output, 4);
        refresh();
        int ch = getch();
        if (ch == 'a') {
            return; // Salir de la función si se presionó 'a'
        }
        if (ch >= '0' && ch <= '7') {
            int bitPos = ch - '0'; // Convierte el caracter a número
            int totalBits = sizeof(output) * 8; // Calcula el total de bits del tipo de dato
            int invertedBitPos = totalBits - 1 - bitPos; // Invierte el orden del bit
            output &= ~(1 << invertedBitPos); // Pone en 0 el bit correspondiente
        }
    } while (1);
}

int main() {
    pioInit();
    for (int i = 0; i < 8; i++) {
        pinMode(led[i], OUTPUT); // Configuro los 8 pines para los Leds como salidas en main
    }
    leds(0xFF);

    initscr();
    cbreak();
    noecho();

    if (ingreso() == 0) {
        printw("Haz sido bloqueado del sistema\n");
        refresh();
        endwin();
        return 0;
    }

    printw("Bienvenido al sistema!\n");
    refresh();

    while (1) {
        clear(); // Limpia la pantalla antes de imprimir
        printw("Elija la secuencia que quiere ver:\n");
        printw("1. Auto fantastico\n");
        printw("2. Choque\n");
        printw("3. La mecha\n");
        printw("4. Tiro al blanco\n");
        printw("0. Salir\n");
        refresh();

        int opcion = getch();

        switch (opcion) {
            case '1':
                autoFantastico();
                break;
            case '2':
                ChoqueT();
                break;
            case '3':
                Mecha();
                break;
            case '4':
                Tiroalblanco();
                break;
            case '0':
                printw("Adios!\n");
                refresh();
                endwin();
                return 0;
            default:
                printw("Ingrese una opcion valida!\n");
                refresh();
                break;
        }
    }

    endwin();
    return 0;
}