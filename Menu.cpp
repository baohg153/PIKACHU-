#include "Menu.h"

string username;
string userID;

Score cl_easy[9];
Score cl_medium[9];
Score cl_hard[9];
Score ad_easy[9];
Score ad_medium[9];
Score ad_hard[9];

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

void Menu::DrawInfoBox(int x, int y)
{
    Cursor(x - 2, y - 1);
    putchar(218);
    for (int i = 0; i < 30; i++)
        putchar(196);
    putchar(191);

    Cursor(x - 2, y + 3);
    putchar(192);
    for (int i = 0; i < 30; i++)
        putchar(196);
    putchar(217);

    for (int i = 0; i <= 2; i++)
    {
        Cursor(x - 2, y + i);
        putchar(179);
        Cursor(x + 29, y + i);
        putchar(179);
    }
    
    Cursor(x, y);
    cout << "Username: ";
    Cursor(x, y + 2);
    cout << "   ID   : ";
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
    SetTextColor(blue);
    Cursor(15, 3);
    cout << R"(
               _____                   _                               _       ___      
              |_   _| _ _  ___  ___   |_| ___    _ _  ___  _ _  ___   |_| ___ |  _| ___ 
                | |  | | || . || -_|  | ||   |  | | || . || | ||  _|  | ||   ||  _|| . |
                |_|  |_  ||  _||___|  |_||_|_|  |_  ||___||___||_|    |_||_|_||_|  |___|
                     |___||_|                   |___|       
                =========================================================================                          
    )";

    SetTextColor(light_yellow);
    Menu::DrawInfoBox(33, 11);

    SetTextColor(15);
    Cursor(43, 11);
    getline(cin, username);

    //Xoa cac khoang trang trong username
    username.erase(remove_if(username.begin(), username.end(), ::isspace), username.end());
    Cursor(43, 11);
    cout << "                   ";
    Cursor(43, 11);
    cout << username;

    Cursor(43, 13);
    cin >> userID;
    cin.ignore();

    Menu::IntroWindow();
}

void Menu::IntroWindow()
{
    system("cls");
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
                        Menu::LeaderboardWindow();
                        break;
                    }
                    case 2:
                    {
                        Menu::ChangeInfoWindow();
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

        MenuCursor("Classic", 44, 10);

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
                        Menu::AdvanceWindow();
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

        Menu::MenuCursor("Easy", 44, 10);

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
                        Classic::Medium();
                        break;
                    }
                    case 2:
                    {
                        Classic::Hard();
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

void Menu::AdvanceWindow()
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

        Menu::MenuCursor("Easy", 44, 10);

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
                        Advance::AdEasy();
                        break;
                    }
                    case 1:
                    {
                        Advance::AdMedium();
                        break;
                    }
                    case 2:
                    {
                        Advance::AdHard();
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

void Menu::LeaderboardWindow()
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

        Menu::MenuCursor("Classic", 44, 10);

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
                        Menu::LeaderboardClassic();
                        break;
                    }
                    case 1:
                    {
                        //Menu::LeaderboardAdvance();
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

void Menu::ChangeInfoWindow()
{
    system("cls");
    ShowCursor();

    SetTextColor(blue);
    Cursor(15, 3);
    cout << R"(
               _____                   _                               _       ___      
              |_   _| _ _  ___  ___   |_| ___    _ _  ___  _ _  ___   |_| ___ |  _| ___ 
                | |  | | || . || -_|  | ||   |  | | || . || | ||  _|  | ||   ||  _|| . |
                |_|  |_  ||  _||___|  |_||_|_|  |_  ||___||___||_|    |_||_|_||_|  |___|
                     |___||_|                   |___|       
                =========================================================================                          
    )";

    SetTextColor(light_yellow);
    Menu::DrawInfoBox(33, 11);

    SetTextColor(15);
    Cursor(43, 11);
    getline(cin, username);

    //Xoa cac khoang trang trong username
    username.erase(remove_if(username.begin(), username.end(), ::isspace), username.end());
    Cursor(43, 11);
    cout << "                   ";
    Cursor(43, 11);
    cout << username;

    Cursor(43, 13);
    cin >> userID;
    cin.ignore();

    HideCursor();

    return;
}

void Menu::LeaderboardClassic()
{
    system("cls");
    ReadScoreClassic();

    Cursor(1, 3);
    SetTextColor(light_yellow);
    cout << R"(
                                                     _      _____   ___  ______  _____ ______ ______  _____   ___  ______ ______ 
                                                    | |    |  ___| / _ \ |  _  \|  ___|| ___ \| ___ \|  _  | / _ \ | ___ \|  _  \
                                                    | |    | |__  / /_\ \| | | || |__  | |_/ /| |_/ /| | | |/ /_\ \| |_/ /| | | |
                                                    | |    |  __| |  _  || | | ||  __| |    / | ___ \| | | ||  _  ||    / | | | |
                                                    | |____| |___ | | | || |/ / | |___ | |\ \ | |_/ /\ \_/ /| | | || |\ \ | |/ / 
                                                    \_____/\____/ \_| |_/|___/  \____/ \_| \_|\____/  \___/ \_| |_/\_| \_||___/                                                                                                                                                      
    )";

    SetTextColor(15);
    DrawLeaderboard("EASY", cl_easy, 12, 13);
    DrawLeaderboard("MEDIUM", cl_medium, 67, 13);
    DrawLeaderboard("HARD", cl_hard, 122, 13);

    _getch();
}


