#include "Menu.h"


int main()
{
    SetWindowSize();
    SetScreenBufferSize();
    DisableResizeWindow();

    InGame::CreateColorBG();
    Menu::FirstWindow();

    return 0;
}


