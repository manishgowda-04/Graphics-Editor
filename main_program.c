#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>

#define BOARD_ROWS 20
#define BOARD_COLS 50

char board[BOARD_ROWS][BOARD_COLS];

// UI state
int cursorRow = 10;
int cursorCol = 25;

typedef enum {
    TOOL_DRAW,
    TOOL_ERASE,
    TOOL_RECTANGLE,
    TOOL_HLINE,
    TOOL_VLINE,
    TOOL_CIRCLE,
    TOOL_TRIANGLE
} ToolMode;

ToolMode currentTool = TOOL_DRAW;

// Two-point system for shapes
bool point1Set = false;
int p1Row = -1;
int p1Col = -1;

HANDLE hConsole;

void initBoard() {
    int r, c;
    for(r = 0; r < BOARD_ROWS; r++) {
        for(c = 0; c < BOARD_COLS; c++) {
            board[r][c] = '_';
        }
    }
}

void setupConsole() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Hide standard flashing cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void drawUI() {
    gotoxy(0, 0); // Start drawing at top-left
    
    setColor(11, 0); // Cyan text
    printf("====== 2D INTERACTIVE GRAPHICS EDITOR ======\n");
    setColor(15, 0); // White text
    
    for(int r = 0; r < BOARD_ROWS; r++) {
        for(int c = 0; c < BOARD_COLS; c++) {
            // Check if cursor is here
            if (r == cursorRow && c == cursorCol) {
                setColor(0, 14); // Black text, Yellow bg for cursor
                printf("+");
                setColor(15, 0);
            } 
            else if (point1Set && r == p1Row && c == p1Col) {
                setColor(0, 10); // Black text, Green bg for first point
                printf("o");
                setColor(15, 0);
            }
            else {
                if (board[r][c] == '*') {
                    setColor(12, 0); // Light Red for shapes
                    printf("%c", board[r][c]);
                    setColor(15, 0);
                } else {
                    setColor(8, 0); // Dark Gray for empty board
                    printf("%c", board[r][c]);
                    setColor(15, 0);
                }
            }
        }
        
        // Render Sidebar
        setColor(15, 0);
        if (r == 0) printf("   [ CONTROLS ]");
        else if (r == 1) printf("   Arrow Keys / WASD : Move Cursor");
        else if (r == 2) printf("   Space / Enter     : Select / Draw");
        else if (r == 3) printf("   C                 : Clear Board");
        else if (r == 4) printf("   Q / ESC           : Quit");
        else if (r == 6) printf("   [ TOOLS ] (Press 1-7)");
        else if (r == 7) printf("   %s 1. Freehand Draw", currentTool == TOOL_DRAW ? "->" : "  ");
        else if (r == 8) printf("   %s 2. Erase Point", currentTool == TOOL_ERASE ? "->" : "  ");
        else if (r == 9) printf("   %s 3. Rectangle", currentTool == TOOL_RECTANGLE ? "->" : "  ");
        else if (r == 10) printf("  %s 4. Horiz Line", currentTool == TOOL_HLINE ? "->" : "  ");
        else if (r == 11) printf("  %s 5. Vert Line", currentTool == TOOL_VLINE ? "->" : "  ");
        else if (r == 12) printf("  %s 6. Circle", currentTool == TOOL_CIRCLE ? "->" : "  ");
        else if (r == 13) printf("  %s 7. Triangle", currentTool == TOOL_TRIANGLE ? "->" : "  ");
        else if (r == 15) printf("   [ STATUS ]");
        else if (r == 16) printf("   Cursor: (%2d, %2d)", cursorCol, cursorRow);
        else if (r == 17) {
            if (currentTool >= TOOL_RECTANGLE) {
                if (point1Set) printf("   Action: Select End Point...");
                else printf("   Action: Select Start Point...");
            } else {
                printf("   Action: Moving/Drawing...");
            }
        }

        // Clear remaining characters on the line
        printf("                                    \n");
    }
}

void drawRect(int sr, int sc, int er, int ec) {
    if (sr > er) { int temp = sr; sr = er; er = temp; }
    if (sc > ec) { int temp = sc; sc = ec; ec = temp; }
    
    for(int r = sr; r <= er; r++) {
        for(int c = sc; c <= ec; c++) {
            if(r == sr || r == er || c == sc || c == ec) {
                if(r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS)
                    board[r][c] = '*';
            }
        }
    }
}

void drawHLine(int r, int sc, int ec) {
    if (sc > ec) { int temp = sc; sc = ec; ec = temp; }
    for(int c = sc; c <= ec; c++) {
        if(r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS)
            board[r][c] = '*';
    }
}

void drawVLine(int sr, int er, int c) {
    if (sr > er) { int temp = sr; sr = er; er = temp; }
    for(int r = sr; r <= er; r++) {
        if(r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS)
            board[r][c] = '*';
    }
}

void drawCircle(int cr, int cc, int radius) {
    for(int r = 0; r < BOARD_ROWS; r++) {
        for(int c = 0; c < BOARD_COLS; c++) {
            int dx = r - cr;
            int dy = c - cc;
            // Ellipse approx: terminal characters are usually twice as tall as they are wide.
            if(dx * dx * 4 + dy * dy <= radius * radius) {
                board[r][c] = '*';
            }
        }
    }
}

void drawTriangle(int sr, int sc, int er, int ec) {
    int h = er - sr;
    if (h < 0) h = -h;
    if (h == 0) h = 1;
    
    for(int r = 0; r <= h; r++) {
        for(int c = -r; c <= r; c++) {
            int dr = sr < er ? sr + r : sr - r;
            int dc = sc + c;
            if(dr >= 0 && dr < BOARD_ROWS && dc >= 0 && dc < BOARD_COLS)
                board[dr][dc] = '*';
        }
    }
}

void handleAction() {
    if (currentTool == TOOL_DRAW) {
        board[cursorRow][cursorCol] = '*';
    } else if (currentTool == TOOL_ERASE) {
        board[cursorRow][cursorCol] = '_';
    } else {
        if (!point1Set) {
            p1Row = cursorRow;
            p1Col = cursorCol;
            point1Set = true;
        } else {
            switch(currentTool) {
                case TOOL_RECTANGLE:
                    drawRect(p1Row, p1Col, cursorRow, cursorCol);
                    break;
                case TOOL_HLINE:
                    drawHLine(cursorRow, p1Col, cursorCol);
                    break;
                case TOOL_VLINE:
                    drawVLine(p1Row, cursorRow, cursorCol);
                    break;
                case TOOL_CIRCLE:
                {
                    int dx = cursorRow - p1Row;
                    int dy = cursorCol - p1Col;
                    int radius = (int)sqrt((double)(dx * dx * 4 + dy * dy));
                    drawCircle(p1Row, p1Col, radius);
                    break;
                }
                case TOOL_TRIANGLE:
                    drawTriangle(p1Row, p1Col, cursorRow, cursorCol);
                    break;
                default:
                    break;
            }
            point1Set = false;
        }
    }
}

int main() {
    initBoard();
    setupConsole();
    
    // Clear screen once
    system("cls");

    bool running = true;
    while(running) {
        drawUI();
        
        int ch = _getch();
        
        // Handle extended keys (arrow keys)
        if (ch == 0 || ch == 224) {
            ch = _getch(); // read actual key code
            switch(ch) {
                case 72: // Up
                    if (cursorRow > 0) cursorRow--;
                    break;
                case 80: // Down
                    if (cursorRow < BOARD_ROWS - 1) cursorRow++;
                    break;
                case 75: // Left
                    if (cursorCol > 0) cursorCol--;
                    break;
                case 77: // Right
                    if (cursorCol < BOARD_COLS - 1) cursorCol++;
                    break;
            }
        } else {
            switch(ch) {
                case 'w': case 'W':
                    if (cursorRow > 0) cursorRow--;
                    break;
                case 's': case 'S':
                    if (cursorRow < BOARD_ROWS - 1) cursorRow++;
                    break;
                case 'a': case 'A':
                    if (cursorCol > 0) cursorCol--;
                    break;
                case 'd': case 'D':
                    if (cursorCol < BOARD_COLS - 1) cursorCol++;
                    break;
                case '1': currentTool = TOOL_DRAW; point1Set = false; break;
                case '2': currentTool = TOOL_ERASE; point1Set = false; break;
                case '3': currentTool = TOOL_RECTANGLE; point1Set = false; break;
                case '4': currentTool = TOOL_HLINE; point1Set = false; break;
                case '5': currentTool = TOOL_VLINE; point1Set = false; break;
                case '6': currentTool = TOOL_CIRCLE; point1Set = false; break;
                case '7': currentTool = TOOL_TRIANGLE; point1Set = false; break;
                case ' ': // Space
                case 13:  // Enter
                    handleAction();
                    break;
                case 'c': case 'C': // Clear
                    initBoard();
                    point1Set = false;
                    break;
                case 'q': case 'Q': case 27: // ESC
                    running = false;
                    break;
            }
        }
    }
    
    system("cls");
    setColor(15, 0);
    printf("Exiting Graphics Editor...\n");
    return 0;
}