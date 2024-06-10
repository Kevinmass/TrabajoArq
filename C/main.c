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
int option;

   printf("Menu:\n");
   printf("1. Auto Fantastico\n");
   printf("2. Choque\n");
   printf("3. Option 3\n");
   printf("4. Option 4\n");
   printf("5. Exit\n");
   scanf("%d", &option);

   switch (option) {
      case 1:
         // Code for Option 1
         break;
      case 2:
         // Code for Option 2
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
