#include <Windows.h>
#include <iostream>
#include <conio.h>

using namespace std;

#define ConsoleWidth 240
#define ConsoleHeight 200

// TEXT COLOR
#define black 0
#define blue 1
#define green 2
#define aqua 3
#define red 4
#define purple 5
#define yellow 6
#define white 7
#define gray 8
#define light_blue 9
#define light_green 10
#define light_aqua 11
#define light_red 12
#define light_purple 13
#define light_yellow 14
#define bright_white 15

//BACKGROUND COLOR
#define WHITE 115
#define GREEN 35
#define RED 75

void DisableResizeWindow();

void SetWindowSize();
void SetConsoleSize();
void SetScreenBufferSize();

void Cursor(int, int);

void SetTextColor(int);

void HideCursor();
void ShowCursor();

int ConsoleInput();