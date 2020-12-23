#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "equ.h"
#include "calculate.c"

#define dmax (pow(2,63)-1)
    double doublebuffer[50];
    char operationbuffer[50];
    double result[50];

    void Init()
    {

        for (i = 0; i < 50; i++)
        {
            equ.func[i] = '\0';
            operationbuffer[i] = '\0';
            doublebuffer[i] = -1;
            result[i] = '\0';
        }
}

int main()
{
    while (1)
    {

        Init();
        gets(equ.func);
        printf("%s", equ.func);

        //getBuffer(equ.func, doublebuffer, operationbuffer);
        //calculateEx(doublebuffer, operationbuffer, (result));
        double res = eval(equ.func);
        printf("\n");
        double c = doublebuffer[0];
        printf("ans:  %lf", res);
        printf("\n");
        for (int i = 0; i < 10; i++)
        {
            printf("%c", operationbuffer[i]);
            printf("%lf", doublebuffer[i]);
        }
        printf("\n");
    }
    system("pause");
    return 0;
}
