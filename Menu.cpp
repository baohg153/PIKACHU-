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
  ____ ___ _  __    _    ____ _   _ _   _ 
 |  _ \_ _| |/ /   / \  / ___| | | | | | |
 | |_) | || ' /   / _ \| |   | |_| | | | |
 |  __/| || . \  / ___ \ |___|  _  | |_| |
 |_|  |___|_|\_\/_/   \_\____|_| |_|\___/ 
	)";

    PrintMid(s, 41, 3);

    cout << "Print Any Key to Play...";
    _getch();
}









