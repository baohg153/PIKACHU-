#include "Console.h"
#include <ctime>
#include <algorithm>
#include <random>

struct Time
{
    int hour;
    int minute;
    int second;
    Time(): hour(0), minute(1), second(0) {}
};

struct InGame
{
    static void CreateMatrix(int, int);
    static bool CheckPath(int, int, int, int, char, int, int, int);
    static void DeleteSquare(int, int);

    static void DrawGameBoard(int, int);
    static void CountingTime(int , int , Time &);
    static void DrawTime(int);
    static void DrawGuide(int);
    
    static void SquareCursor(int, int, int);
    static void DeleteSquareCursor(int, int);

};

void print(int);
void DeleteMatrix();

struct Classic
{
    static void ClassicGame(int);
    static void Easy();
    static void Medium();
    static void Hard();
};
