#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "InGame.h"

using namespace std;

struct Menu
{
    static void DrawTextBox(string, int, int); //Draw TextBox in Menu
    static void DrawInfoBox(int, int);  //Draw Log-in box

    static void MenuCursor(string, int, int); //Color the option where the Menu cursor is pointing to
    static void DeleteMenuCursor(string, int, int); //Uncolor the option where the Menu cursor is pointing to

    static void FirstWindow();  //First window appear when openning the game
    static void IntroWindow();  //Intro window
    static void MenuWindow();  //Menu window
    
    static void PlayWindow();  //Play window
        static void ClassicWindow();  
        static void AdvanceWindow();
    static void LeaderboardWindow();  //Leaderboard window
        static void LeaderboardClassic(); 
        static void LeaderboardAdvance();
    static void ChangeAccountWindow();  //Change account window
        
};



