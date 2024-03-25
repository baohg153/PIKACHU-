#include "Menu.h"

int main()
{
    SetWindowSize();
    SetScreenBufferSize();
    DisableResizeWindow();

    InGame::DrawGameBoard(5);
    //Menu::FirstWindow();
    //Classic::Easy();

    cout << "\nPress Any key to Close window...";
    _getch();

    return 0;
}


