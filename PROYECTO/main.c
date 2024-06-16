#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "EasyPIO.h"



// Definir los pines GPIO utilizados
#define LED1 17
#define LED2 18
#define LED3 27
#define LED4 22


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
    printf("Menu de Secuencias de Luces:\n");
    printf("1. Secuencia Comun 1 (common_sequence_1)\n");
    printf("2. Secuencia Comun 2 (common_sequence_2)\n");
    printf("3. Secuencia Personalizada Algoritmo (custom_sequence_algorithm)\n");
    printf("4. Secuencia Personalizada Tabla (custom_sequence_table)\n");
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
            delayMillis(tiempo); // Usar delayMillis en lugar de usleep
            output >>= 1; // Desplaza a la derecha
        }
    } while (1);
}

void choque() {
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

void custom_sequence_table() {
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
