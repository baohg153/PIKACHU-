#include "Menu.h"

string pikachu_logo = R"(
                     _____  _____  _  __           _____  _    _  _    _ 
                    |  __ \|_   _|| |/ /    /\    / ____|| |  | || |  | |
                    | |__) | | |  | ' /    /  \  | |     | |__| || |  | |
                    |  ___/  | |  |  <    / /\ \ | |     |  __  || |  | |
                    | |     _| |_ | . \  / ____ \| |____ | |  | || |__| |
                    |_|    |_____||_|\_\/_/    \_\\_____||_|  |_| \____/ 
	)";


void Menu::FirstWindow()
{
    cout << "Press Any key...";

    _getch();

    system("cls");
    Menu::IntroWindow();
}

void Menu::IntroWindow()
{
    for (int i = 1; i < 14 ; i++)
    {
        Cursor(3, 3);
        SetTextColor(i);
        cout << pikachu_logo << "\n";
        Sleep(120);
    }

    SetTextColor(14);
    Cursor(26, 11);
    cout << "A game by Huynh Gia Bao and Le Minh Tri\n";

    Sleep(500);

    SetTextColor(light_blue);
    Cursor(31, 13);
    cout << "Press any key to go to Menu...";
    _getch();

    system("cls");
    Menu::MenuWindow();
}

void Menu::MenuWindow()
{
    Cursor(1, 1);
    SetTextColor(green);
    cout << pikachu_logo;

    //Sleep(700);
    Cursor(42, 10);
    SetTextColor(light_yellow);
    cout << "Play";

    //Sleep(300);
    Cursor(39, 12);
    cout << "Leaderboard";

    //Sleep(300);
    Cursor(39, 14);
    cout << "Change Info";
    
    //Sleep(300);
    Cursor(39, 16);
    cout << "Instruction";

    //Sleep(300);
    Cursor(42, 18);
    cout << "Exit";

    //Sleep(700);
    Cursor(42, 10);
    SetTextColor(green);
    cout << "Play";

    _getch();
    system("cls");
    Menu::PlayWindow();
}

void Menu::PlayWindow()
{
    Cursor(1, 1);
    SetTextColor(green);
    cout << pikachu_logo;

    Cursor(41, 10);
    cout << "Classic";

    SetTextColor(light_yellow);
    Cursor(41, 12);
    cout << "Advanced";

    Cursor(42, 14);
    cout << "Exit";

    _getch();

    system("cls");
    Menu::ClassicWindow();
}

void Menu::ClassicWindow()
{
    Cursor(1, 1);
    SetTextColor(green);
    cout << pikachu_logo;

    Cursor(42, 10);
    SetTextColor(green);
    cout << "Easy";

    SetTextColor(light_yellow);
    Cursor(41, 12);
    cout << "Medium";

    Cursor(42, 14);
    cout << "Hard";

    Cursor(42, 16);
    //SetTextColor(red);
    cout << "Exit";

    _getch();

    //Classic::Easy();
}







