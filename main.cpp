#include "Menu.h"
#include "Board.h"
#include "InGame.h"
#include "test.h"

int main()
{
    SetWindowSize();
    SetScreenBufferSize();
    DisableResizeWindow();

    //Menu::FirstWindow();
    CreateMatrix(4);

    cout << "\nPress Any key to Close window...";
    _getch();

    return 0;
}


