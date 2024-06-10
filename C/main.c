#include "EasyPIO.h"
#include <stdio.h>
#include <conio.h>
#define port_out 0x208
#define port_in  0x209
//
void disp_binary (int);
void delay (int);
//
void main (void)
{
   const unsigned char led[] = {14, 15, 18, 23, 24, 25, 8, 7};
const unsigned char sw[] = {12, 16, 20, 21};

   pioInit();
   //Set GPIO 21 as outputs
   pinMode(21, OUTPUT);
   int i;
   for (i=1; i<=10; i++) {
     digitalWrite(21,1);
     delayMillis(500);
     digitalWrite(21,0);
     delayMillis(500);
  }
int option;
int ctr;
for (int i = 0; i < 3; i++)
{
   ctr = password();
}
   if (ctr != 1)
   {
      return 0;
   }
   
   printf("Menu:\n");
   printf("1. Auto Fantastico\n");
   printf("2. Choque\n");
   printf("3. Option 3\n");
   printf("4. Option 4\n");
   printf("5. Exit\n");
   scanf("%d", &option);

   switch (option) {
      case 1:
         auto_fantastico();
         break;
      case 2:
         choque();
         break;
      case 3:
         // Code for Option 3
         break;
      case 4:
         // Code for Option 4
         break;
      case 5:
         printf("Saliendo...\n");
         return 0;
      default:
         printf("Opcion invalida.\n");
         break;
   }
}

int password(){
   int ctr = 0;
   char pass[4];
   char pass2[4] = {'1', '2', '3', '4'};
   printf("Ingrese la contrasena: ");
   for (int i = 0; i < 4; i++)
   {
      pass[i] = getch();
      printf("*");
   }
   printf("\n");
   for (int i = 0; i < 4; i++)
   {
      if (pass[i] == pass2[i])
      {
         ctr++;
      }
   }
   if (ctr == 4)
   {
      printf("Contrasena correcta.\n");
      return 1;
   }
   else
   {
      printf("Contrasena incorrecta.\n");
      return 0;
   }
}

void auto_fantastico() {
    unsigned char output;
    int tiempo = 2000; // Tiempo inicial

    printf("Estas viendo el Auto Fantastico!\n");
    printf("Presione la tecla 'a' si quiere salir!\n");
    printf("Presione la tecla 'u' para aumentar la velocidad!\n");
    printf("Presione la tecla 'd' para disminuir la velocidad!\n");

    do {
        output = 0x80; 
        for (int t = 0; t < 8; t++) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 'a') {
                    printf("Salida detectada\n");
                    return; 
                }
                if (ch == 'u') {
                    if (tiempo > 500) tiempo -= 500; // Aumenta la velocidad (disminuye el tiempo)
                }
                if (ch == 'd') {
                    tiempo += 500; // Disminuye la velocidad (aumenta el tiempo)
                }
            }

            disp_binary(output, 1);
            delay(tiempo); 
            output = output >> 1; // Desplaza a la derecha
        }

        output = 0x01; 
        for (int t = 0; t < 6; t++) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 'a') {
                    printf("Salida detectada\n");
                    return; // Salir si se presiona 'a'
                }
                if (ch == 'u') {
                    if (tiempo > 500) tiempo -= 500; // Aumenta la velocidad (disminuye el tiempo)
                }
                if (ch == 'd') {
                    tiempo += 500; // Disminuye la velocidad (aumenta el tiempo)
                }
            }

            disp_binary(output, 1); 
            delay(tiempo); 
            output = output << 1; // Desplaza a la Izquierda
        }
    } while (1);
}

void choque() {
    int tiempo = 2000; // Tiempo inicial

    printf("Estas viendo el Choque!\n");
    printf("Presione la tecla 'a' si quiere salir!\n");
    printf("Presione la tecla 'u' para aumentar la velocidad!\n");
    printf("Presione la tecla 'd' para disminuir la velocidad!\n");

    while (1) {
        for (int i = 0; i < 8; i++) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 'a') {
                    printf("Salida detectada\n");
                    return; 
                }
                if (ch == 'u') {
                    if (tiempo > 500) tiempo -= 500; // Aumenta la velocidad (disminuye el tiempo)
                }
                if (ch == 'd') {
                    tiempo += 500; // Disminuye la velocidad (aumenta el tiempo) 
                }
            }

            disp_binary(TablaCh[i], 2);
            delay(tiempo); 
            }
}
}