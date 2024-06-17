#include <stdio.h>
#include <conio.h>
#include <windows.h>

extern void print(void);
int main()
{
    int key;
    int a = 0;
    do
    {
        Sleep(500);             // Espera unidades de tiempo
        printf("\e[1;1H\e[2J"); // Limpia la pantalla
        print();
        if (a == 0)
        {
            printf("a");
        }
        else
            printf("b");

        if (_kbhit())
        {
            key = getch();
            if (key == 224)
            {
                do
                {
                    key = getch();
                } while (key == 224);

                switch (key)
                {
                case 72:
                    printf("up");
                    break;
                case 75:
                    printf("left");
                    break;
                case 77:
                    printf("right");
                    break;
                case 80:
                    printf("down");
                    break;
                }
            }
        }
    } while (1);
    return 0;
}

