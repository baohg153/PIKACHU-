#include "Board.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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

void Cursor(short x, short y)
{
    SetConsoleCursorPosition(hConsole, COORD{(SHORT)x, (SHORT)y});
}

void SetTextColor(int color)
{
    SetConsoleTextAttribute(hConsole, color);
}