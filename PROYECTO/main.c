#include <easyPIO.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Prototipos de funciones
void auto_fantastico();
void choque();
void ambulancia();
int password();
int kbhit();

int main(void) {
    int option;
    int ctr;
    
    pioInit();
    pinMode(21, OUTPUT);
    
    for (int i = 0; i < 10; i++) {
        digitalWrite(21, 1);
        delayMillis(500); // 500 ms
        digitalWrite(21, 0);
        delayMillis(500); // 500 ms
    }

    for (int i = 0; i < 3; i++) {
        ctr = password();
        if (ctr == 1) break;
    }

    if (ctr != 1) {
        return 0;
    }

    while (1) {
        printf("Menu:\n");
        printf("1. Auto Fantastico\n");
        printf("2. Choque\n");
        printf("3. Ambulancia\n");
        printf("4. Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &option);

        switch (option) {
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
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }
}

int password() {
    int ctr = 0;
    char pass[5]; // Agrega espacio para el terminador nulo
    char pass2[5] = "1234";

    printf("Ingrese la contraseña: ");
    for (int i = 0; i < 4; i++) {
        pass[i] = getchar();
        printf("*");
    }
    pass[4] = '\0'; // Asegúrate de que la cadena esté terminada en nulo

    printf("\n");

    if (strcmp(pass, pass2) == 0) {
        printf("Contraseña correcta.\n");
        return 1;
    } else {
        printf("Contraseña incorrecta.\n");
        return 0;
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

int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
