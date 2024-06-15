#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main(){
    int a= 0;
    do
{
    Sleep(500); // Espera unidades de tiempo
    printf("\e[1;1H\e[2J"); // Limpia la pantalla
    if (a == 0)
    {
         printf("a");

    }else printf("b");
       
            if (_kbhit()) { // Si se presiona una tecla
                char ch = _getch(); // Guarda la tecla presionada
                if (ch == 'a') {
                    printf("Salida detectada\n");
                    return 0; // Salir si se presiona 'a'
                }
                if (ch == 's')
                {
                    a= 0;
                }
                if (ch == 'd')
                {
                    a= 1;
                }
                
            }
        
} while (1);

    
}