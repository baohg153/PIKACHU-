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
    static void CreateMatrix(int);
    static bool CheckPath(int, int, int, int, char, int, int, int);
    static void DeleteSquare(int, int);

    static void DrawGameBoard(int);
    static void CountingTime(int , int , Time &);
    static void drawTime(int);
    static void drawGuide(int);
    
};

void print(int);

struct Classic
{
    static void Easy();
};
