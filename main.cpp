#include "Menu.h"

int main()
{
    SetWindowSize();
    SetScreenBufferSize();
    DisableResizeWindow();

    InGame::DrawGameBoard();

    cout << "\nPress Any key to Close window...";
    _getch();

    return 0;
}


