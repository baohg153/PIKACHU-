#include "Console.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cursorInfo;

void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void SetWindowSize()
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = ConsoleWidth;
    WindowSize.Bottom = ConsoleHeight;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void SetConsoleSize()
{
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, static_cast<SHORT>(ConsoleWidth - 1), static_cast<SHORT>(ConsoleHeight - 1)};

    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    COORD bufferSize = {static_cast<SHORT>(ConsoleWidth), static_cast<SHORT>(ConsoleHeight)};
    SetConsoleScreenBufferSize(hConsole, bufferSize);
}

void SetScreenBufferSize()
{
    SHORT width = ConsoleWidth;
    SHORT height = ConsoleHeight;

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hConsole, NewSize);
}

void Cursor(int x, int y)
{
    SetConsoleCursorPosition(hConsole, COORD{(SHORT)x, (SHORT)y});
}

void SetTextColor(int color)
{
    SetConsoleTextAttribute(hConsole, color);
}

void HideCursor()
{
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void ShowCursor()
{
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int ConsoleInput()
{
    int temp = _getch();

    if (temp == 0 || temp == 224)
    {
        int temp2 = _getch();
        if (temp2 == 72)      //up
            return 2;
        else if (temp2 == 80) //down
            return -2;
        else if (temp2 == 75) //left
            return -3;
        else if (temp2 == 77) //right
            return 3;
    }
    
    if (temp == 27)           //esc
        return 0;
    
    if (temp == 8)            //backspace
        return -1;
    
    if (temp == 13)           //enter
        return 1;

    return 10;
}