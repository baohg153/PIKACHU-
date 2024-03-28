#include "Menu.h"

int main()
{
    SetWindowSize();
    SetScreenBufferSize();
    DisableResizeWindow();

    // InGame::DrawGameBoard(5);
    // InGame::drawTime(5);
    // InGame::drawGuide(5);

    Menu::FirstWindow();
    //HideCursor();
    //Classic::Easy();
    //Menu::DrawTextBox("Start", 10, 10);

    //Menu::LeaderboardClassic();
    //_getch();

    return 0;
}


