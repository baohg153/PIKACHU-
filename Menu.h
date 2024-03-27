#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include "InGame.h"

using namespace std;

struct Menu
{
    static void DrawTextBox(string, int, int); //Vẽ TextBox trong Menu
    static void MenuCursor(string, int, int); //Di chuyển con trỏ đến (x, y) và tô màu TextBox tại đó
    static void DeleteMenuCursor(string, int, int); //Xóa màu TextBox tại (x, y), xóa con trỏ chỉ đến (x, y)

    static void FirstWindow(); 
    static void IntroWindow();
    static void MenuWindow();
    
    static void PlayWindow();
        static void ClassicWindow();
        
};

