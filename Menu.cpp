#include "Menu.h"

string pikachu_logo = R"(
                     _____  _____  _  __           _____  _    _  _    _ 
                    |  __ \|_   _|| |/ /    /\    / ____|| |  | || |  | |
                    | |__) | | |  | ' /    /  \  | |     | |__| || |  | |
                    |  ___/  | |  |  <    / /\ \ | |     |  __  || |  | |
                    | |     _| |_ | . \  / ____ \| |____ | |  | || |__| |
                    |_|    |_____||_|\_\/_/    \_\\_____||_|  |_| \____/ 
	)";

void Menu::DrawTextBox(string text, int x, int y)
{
    int len = text.length() / 2;
    Cursor(x - len, y);
        cout << text;

    Cursor(x - 8, y - 1);
    putchar(218);
    for (int i = 0; i < 14; i++)
        putchar(196);
    putchar(191);

    Cursor(x - 8, y + 1);
    putchar(192);
    for (int i = 0; i < 14; i++)
        putchar(196);
    putchar(217);


    Cursor(x - 8, y);
    putchar(179);
    Cursor(x + 7, y);
    putchar(179);
}

void Menu::MenuCursor(string s, int x, int y)
{
    SetTextColor(green);
    Menu::DrawTextBox(s, x, y);

    Cursor(x - 12, y);
    cout << ">>>";
    Cursor(x + 9, y);
    cout << "<<<";

    SetTextColor(15);
}

void Menu::DeleteMenuCursor(string s, int x, int y)
{
    SetTextColor(light_yellow);
    DrawTextBox(s, x, y);
    
    Cursor(x - 12, y);
    cout << "   ";
    Cursor(x + 9, y);
    cout << "   ";

    SetTextColor(15);
}

void Menu::FirstWindow()
{
    cout << "Press Any key...";

    _getch();

    system("cls");
    Menu::IntroWindow();
}

void Menu::IntroWindow()
{
    HideCursor();
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
    while (1)
    {
        system("cls");
        string options[4] = {"Play", "Leaderboard", "Change Info", "Exit"};

        Cursor(1, 1);
        SetTextColor(green);
        cout << pikachu_logo;

        SetTextColor(light_yellow);
        Menu::DrawTextBox("Play", 44, 10);
        Menu::DrawTextBox("Leaderboard", 44, 13);
        Menu::DrawTextBox("Change Info", 44, 16);
        Menu::DrawTextBox("Exit", 44, 19);

        Menu::MenuCursor("Play", 44, 10);

        int current_option = 0;
        while (1)
        {
            int button = ConsoleInput();

            Menu::DeleteMenuCursor(options[current_option], 44, 10 + 3 * (current_option % 4));

            if (button == 2)
                current_option = (current_option + 3) % 4;
            else if (button == -2)
                current_option = (current_option + 1) % 4;

            else if (button == 1)
            {
                switch (current_option)
                {
                    case 0:
                    {
                        Menu::PlayWindow();
                        break;
                    }
                    case 1:
                    {

                        break;
                    }
                    case 2:
                    {
                        
                        break;
                    }
                    case 3:
                    {

                        break;
                    }

                }

                break;
            }
                    
            Menu::MenuCursor(options[current_option], 44, 10 + 3 * (current_option % 4));
        }
    }
}

void Menu::PlayWindow()
{
    while(1)
    {
        system("cls");
        string options[3] = {"Classic", "Advanced", "Exit"};

        Cursor(1, 1);
        SetTextColor(green);
        cout << pikachu_logo;

        Menu::DrawTextBox("Classic", 44, 10);
        SetTextColor(light_yellow);
        Menu::DrawTextBox("Advanced", 44, 13);
        Menu::DrawTextBox("Exit", 44, 16);

        int current_option = 0;
        while (1)
        {
            int button = ConsoleInput();

            Menu::DeleteMenuCursor(options[current_option], 44, 10 + 3 * (current_option % 3));

            if (button == 2)
                current_option = (current_option + 2) % 3;
            else if (button == -2)
                current_option = (current_option + 1) % 3;

            else if (button == 1)
            {
                switch (current_option)
                {
                    case 0:
                    {
                        Menu::ClassicWindow();
                        break;
                    }
                    case 1:
                    {

                        break;
                    }
                    case 2:
                        return;
                }
                break;
            }

            Menu::MenuCursor(options[current_option], 44, 10 + 3 * (current_option % 3));
        }
    }
}

void Menu::ClassicWindow()
{
    while (1)
    {
        system("cls");
        string options[4] = {"Easy", "Medium", "Hard", "Exit"};

        Cursor(1, 1);
        SetTextColor(green);
        cout << pikachu_logo;

        Menu::DrawTextBox("Easy", 44, 10);
        SetTextColor(light_yellow);
        Menu::DrawTextBox("Medium", 44, 13);
        Menu::DrawTextBox("Hard", 44, 16);
        Menu::DrawTextBox("Exit", 44, 19);

        int current_option = 0;
        while (1)
        {
            int button = ConsoleInput();

            Menu::DeleteMenuCursor(options[current_option], 44, 10 + 3 * (current_option % 4));

            if (button == 2)
                current_option = (current_option + 3) % 4;
            else if (button == -2)
                current_option = (current_option + 1) % 4;

            else if (button == 1)
            {
                switch (current_option)
                {
                    case 0:
                    {
                        Classic::Easy();
                        break;
                    }
                    case 1:
                    {

                        break;
                    }
                    case 2:
                    {
                        
                        break;
                    }
                    case 3:
                        return;

                }

                break;
            }
                    
            Menu::MenuCursor(options[current_option], 44, 10 + 3 * (current_option % 4));
        }        
    }
}







