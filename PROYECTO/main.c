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

    for (int k = 0; k < 8; k++) {
        pinMode(led[i], OUTPUT); // Configuro los 8 pines para los Leds como salidas en main
    }
    leds(0xFF);

    initscr(); //ni idea que hace esto, averiguar si es de ncurses
    cbreak();
    noecho();

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
    int key;
    int tiempo = 2000; // Tiempo inicial
    clear(); 
    printf("Estás viendo el Auto Fantástico!\n");
    printf("Presiona flechita izquierda para salir!\n");
    printf("Presiona flechita arriba para aumentar la velocidad!\n");
    printf("Presiona flechita abajo para disminuir la velocidad!\n");

    do {
        output = 0x80; 
        for (int k = 0; k < 8; k++) {
            if (_kbhit())
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
            if (_kbhit())
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

void choque() {
    clear(); 
    int tiempo = 2000;
    int key;
    printf("Estás viendo el Choque!\n");
    printf("Presiona flechita izquierda para salir!\n");
    printf("Presiona flechita arriba para aumentar la velocidad!\n");
    printf("Presiona flechita abajo para disminuir la velocidad!\n");

    while (1) {
        for (int k = 0; k < 8; k++) {
            if (_kbhit())
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
            disp_binary(TablaCh[i], 2);
            delayMillis(tiempo); // Usar delayMillis en lugar de usleep
        }
    }
}

void ambulancia() {
    clear(); 
    int tiempo = 2000;
    int key;

    printf("Estás viendo la Ambulancia!\n");
    printf("Presiona flechita izquierda para salir!\n");
    printf("Presiona flechita arriba para aumentar la velocidad!\n");
    printf("Presiona flechita abajo para disminuir la velocidad!\n");
    do {
    for (int j = 0; j < 2; j++)
    {
       output = 0x80; 
        for (int k = 0; k < 8; k++) {
            if (_kbhit())
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
            if (_kbhit())
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
        //parpadeo de las luces x2
        for (int j = 0; j < 2; j++)
        {
            output = 0x80; 
        for (int k = 0; k < 8; k++)
        {
            digitalWrite(21, (output & 0x01) != 0);
            output >> 1; 
        }
            delayMillis(tiempo); 
            output = 0x01; 
        for (int k = 0; k < 6; k++)
        {
            digitalWrite(21, (output & 0x01) != 0);
            output << 1; 
        }
            delayMillis(tiempo); 
        }
        
        
    }
    
        
        
    } while (1);
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


//..............................................................................


