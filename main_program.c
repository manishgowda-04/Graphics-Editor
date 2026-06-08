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

    printf("\n");

    for(r = 0; r < 20; r++)
    {
        for(c = 0; c < 50; c++)
        {
            printf("%c", board[r][c]);
        }

        printf("\n");
    }

    printf("\n");
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

void eraseArea(int sr, int sc, int w, int h)
{
    int r, c;

    for(r = sr; r < sr + h; r++)
    {
        for(c = sc; c < sc + w; c++)
        {
            board[r][c] = '_';
        }
    }
}

void modifyRectangle()
{
    int oldSr, oldSc, oldW, oldH;
    int newSr, newSc, newW, newH;

    printf("Enter old row: ");
    scanf("%d", &oldSr);

    printf("Enter old column: ");
    scanf("%d", &oldSc);

    printf("Enter old width: ");
    scanf("%d", &oldW);

    printf("Enter old height: ");
    scanf("%d", &oldH);

    eraseArea(oldSr, oldSc, oldW, oldH);

    printf("Enter new row: ");
    scanf("%d", &newSr);

    printf("Enter new column: ");
    scanf("%d", &newSc);

    printf("Enter new width: ");
    scanf("%d", &newW);

    printf("Enter new height: ");
    scanf("%d", &newH);

    drawRect(newSr, newSc, newW, newH);
}

int main()
{
    int ch = 0;

    initBoard();

    while(ch != 9)
    {
        printf("====== 2D GRAPHICS EDITOR ======\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Horizontal Line\n");
        printf("3. Draw Vertical Line\n");
        printf("4. Draw Triangle\n");
        printf("5. Draw Circle\n");
        printf("6. Delete Area\n");
        printf("7. Modify Rectangle\n");
        printf("8. Display Board\n");
        printf("9. Exit\n");

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

        else if(ch == 6)
        {
            int sr, sc, w, h;

            printf("Enter starting row: ");
            scanf("%d", &sr);

            printf("Enter starting column: ");
            scanf("%d", &sc);

            printf("Enter width: ");
            scanf("%d", &w);

            printf("Enter height: ");
            scanf("%d", &h);

            eraseArea(sr, sc, w, h);
        }

        else if(ch == 7)
        {
            modifyRectangle();
        }

        else if(ch == 8)
        {
            showBoard();
        }

        else if(ch == 9)
        {
            printf("Exiting Program...\n");
        }

        else
        {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}