#include<stdio.h>

char graphics[20][50];

void initializeGraphics()
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

void displayGraphics()
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

void drawRectangle(int row, int col, int width, int height)
{
    int i, j;

    for(i = row; i < row + height; i++)
    {
        for(j = col; j < col + width; j++)
        {
            if(i == row || i == row + height - 1 ||
               j == col || j == col + width - 1)
            {
                graphics[i][j] = '*';
            }
        }
    }
}

int main()
{
    int r, c, width, height;

    initializeGraphics();

    printf("Enter row: ");
    scanf("%d", &r);

    printf("Enter column: ");
    scanf("%d", &c);

    printf("Enter width: ");
    scanf("%d", &width);

    printf("Enter height: ");
    scanf("%d", &height);

    drawRectangle(r, c, width, height);

    displayGraphics();

    return 0;
}