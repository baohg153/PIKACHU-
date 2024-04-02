#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <mmsystem.h>
#include <string>
#include <thread>

#pragma comment(lib, "Winmm.lib")

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

#define BG_BLACK    "\033[40m"      // Đen
#define BG_RED      "\033[41m"      // Đỏ
#define BG_GREEN    "\033[42m"      // Xanh lá cây
#define BG_YELLOW   "\033[43m"      // Vàng
#define BG_BLUE     "\033[44m"      // Xanh dương
#define BG_MAGENTA  "\033[45m"      // Tím
#define BG_CYAN     "\033[46m"      // Xanh lam
#define BG_WHITE    "\033[47m"      // Trắng
#define BG_ORANGE   "\033[48;5;202m"// Cam
#define BG_PURPLE   "\033[48;5;129m"// Tím
#define BG_PINK     "\033[48;5;205m"// Hồng
#define BG_BROWN    "\033[48;5;94m" // Nâu
#define BG_GRAY     "\033[48;5;245m" // Xám
#define BG_LIME     "\033[48;5;118m" // Xanh dương nhạt
#define BG_AQUA     "\033[48;5;45m"  // Xanh ngọc
#define BG_SILVER   "\033[48;5;250m" // Bạc
#define BG_OLIVE    "\033[48;5;58m"  // Ô liu
#define BG_TEAL     "\033[48;5;23m"  // Xanh biển
#define BG_NAVY     "\033[48;5;17m"  // Navy
#define BG_MAROON   "\033[48;5;88m"  // Maroon


void DisableResizeWindow();

void SetWindowSize();
void SetConsoleSize();
void SetScreenBufferSize();

void Cursor(int, int);

void SetTextColor(int);

void HideCursor();
void ShowCursor();

int ConsoleInput();

void SoundOn(string);
void SoundOff();
LPCWSTR strToW(const std::string& str);
