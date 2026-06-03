#include<stdio.h>

char graphics[20][50];

void initializeCanvas()
{
    int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 50; j++)
        {
            graphics[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i, j;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 50; j++)
        {
            printf("%c", graphics[i][j]);
        }

        printf("\n");
    }
}

int main()
{
    initializeCanvas();

    displayCanvas();

    return 0;
}
