#include "Menu.h"
#include "Board.h"

int main()
{
    //Menu::FirstWindow();

    // string s = "hello";
    // FixSizeWindow();

    // Print::PrintMid();

    SetWindowSize(200, 160);
    DisableResizeWindow();
    Print::PrintMid();

    cout << "Press Any key to Close window...";
    _getch();

    return 0;
}
