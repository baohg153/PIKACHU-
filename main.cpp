#include "Menu.h"

int main()
{
    SetWindowSize();
    SetScreenBufferSize();
    DisableResizeWindow();

    InGame::DrawGameBoard(4);
    InGame::drawTime(4);
    InGame::drawGuide(4);
    //Menu::FirstWindow();
    // Classic::Easy();

    _getch();

    return 0;
}


