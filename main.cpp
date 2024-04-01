#include "Menu.h"


int main()
{
    SetWindowSize();
    SetScreenBufferSize();
    DisableResizeWindow();


    // InGame::drawTime(5);
    // InGame::drawGuide(5);
    InGame::CreateColorBG();
    Menu::FirstWindow();
    

    //HideCursor();

    //Advance::AdEasy();

    //Menu::DrawTextBox("Start", 10, 10);
    //Menu::LeaderboardClassic();

    return 0;
}


