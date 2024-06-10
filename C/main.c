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
