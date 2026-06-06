#include<stdio.h>

char board[20][50];

void initBoard()
{
    int r, c;

    for(r = 0; r < 20; r++)
    {
        for(c = 0; c < 50; c++)
        {
            board[r][c] = '_';
        }
    }
}

void showBoard()
{
    int r, c;

    for(r = 0; r < 20; r++)
    {
        for(c = 0; c < 50; c++)
        {
            printf("%c", board[r][c]);
        }

        printf("\n");
    }
}

void drawRect(int sr, int sc, int w, int h)
{
    int r, c;

    for(r = sr; r < sr + h; r++)
    {
        for(c = sc; c < sc + w; c++)
        {
            if(r == sr || r == sr + h - 1 ||
               c == sc || c == sc + w - 1)
            {
                board[r][c] = '*';
            }
        }
    }
}

void drawHLine(int r, int sc, int len)
{
    int c;

    for(c = sc; c < sc + len; c++)
    {
        board[r][c] = '*';
    }
}

void drawVLine(int sr, int c, int len)
{
    int r;

    for(r = sr; r < sr + len; r++)
    {
        board[r][c] = '*';
    }
}

void drawTriangle(int sr, int sc, int h)
{
    int r, c;

    for(r = 0; r < h; r++)
    {
        for(c = 0; c <= r; c++)
        {
            board[sr + r][sc + c] = '*';
        }
    }
}

void drawCircle(int cr, int cc, int rad)
{
    int r, c;

    for(r = 0; r < 20; r++)
    {
        for(c = 0; c < 50; c++)
        {
            int dx = r - cr;
            int dy = c - cc;

            if(dx * dx + dy * dy <= rad * rad)
            {
                board[r][c] = '*';
            }
        }
    }
}

int main()
{
    int ch;

    initBoard();

    printf("1. Draw Rectangle\n");
    printf("2. Draw Horizontal Line\n");
    printf("3. Draw Vertical Line\n");
    printf("4. Draw Triangle\n");
    printf("5. Draw Circle\n");

    printf("Enter choice: ");
    scanf("%d", &ch);

    if(ch == 1)
    {
        int sr, sc, w, h;

        printf("Enter row: ");
        scanf("%d", &sr);

        printf("Enter column: ");
        scanf("%d", &sc);

        printf("Enter width: ");
        scanf("%d", &w);

        printf("Enter height: ");
        scanf("%d", &h);

        drawRect(sr, sc, w, h);
    }

    else if(ch == 2)
    {
        int r, sc, len;

        printf("Enter row: ");
        scanf("%d", &r);

        printf("Enter starting column: ");
        scanf("%d", &sc);

        printf("Enter length: ");
        scanf("%d", &len);

        drawHLine(r, sc, len);
    }

    else if(ch == 3)
    {
        int sr, c, len;

        printf("Enter starting row: ");
        scanf("%d", &sr);

        printf("Enter column: ");
        scanf("%d", &c);

        printf("Enter length: ");
        scanf("%d", &len);

        drawVLine(sr, c, len);
    }

    else if(ch == 4)
    {
        int sr, sc, h;

        printf("Enter starting row: ");
        scanf("%d", &sr);

        printf("Enter starting column: ");
        scanf("%d", &sc);

        printf("Enter height: ");
        scanf("%d", &h);

        drawTriangle(sr, sc, h);
    }

    else if(ch == 5)
    {
        int cr, cc, rad;

        printf("Enter center row: ");
        scanf("%d", &cr);

        printf("Enter center column: ");
        scanf("%d", &cc);

        printf("Enter radius: ");
        scanf("%d", &rad);

        drawCircle(cr, cc, rad);
    }

    showBoard();

    return 0;
}