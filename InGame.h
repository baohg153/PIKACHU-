#include "Console.h"
#include <ctime>
#include <algorithm>
#include <random>

struct InGame
{
    static void CreateMatrix(int);
    static bool CheckPath(int, int, int, int, char, int, int, int);
    static void DeleteSquare(int, int);

    static void DrawGameBoard(int);
};

void print(int);

struct Classic
{
    static void Easy();
};
