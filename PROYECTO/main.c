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

// Funciones en Assembly
extern void auto_fantastico_asm();
extern void choque_asm();
extern void ambulancia_asm();
extern void Juego_asm();

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

void contrasena() {
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
                parpadeo()
            }
        }
    } while (1);
}

void show_pattern(unsigned char pattern) {
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
        show_pattern(pattern); // Mostrar el patrón en los LEDs

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


//..............................................................................


