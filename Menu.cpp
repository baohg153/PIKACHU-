#include "Menu.h"

void Menu::FirstWindow()
{
    cout << "Press Any key...";

    _getch();

    system("cls");
    Menu::MenuWindow();
}

void Menu::MenuWindow()
{
    string s = R"(
             _____  _____  _  __           _____  _    _  _    _ 
            |  __ \|_   _|| |/ /    /\    / ____|| |  | || |  | |
            | |__) | | |  | ' /    /  \  | |     | |__| || |  | |
            |  ___/  | |  |  <    / /\ \ | |     |  __  || |  | |
            | |     _| |_ | . \  / ____ \| |____ | |  | || |__| |
            |_|    |_____||_|\_\/_/    \_\\_____||_|  |_| \____/ 
	)";

    for (int i = 1; i < 14 ; i++)
    {
        Cursor(3, 3);
        SetTextColor(i);
        cout << s << "\n";
        Sleep(150);
    }

    SetTextColor(14);

    cout << "Print Any Key to Play...\n";
    _getch();
}









