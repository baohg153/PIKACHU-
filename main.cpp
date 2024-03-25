#include "Menu.h"
#include "Board.h"

int main()
{
    SetWindowSize();
    SetScreenBufferSize();
    DisableResizeWindow();

    Menu::FirstWindow();

    cout << "\nPress Any key to Close window...";
    _getch();

    return 0;
}
