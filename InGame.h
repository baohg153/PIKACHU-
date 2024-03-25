#include "Console.h"
#include <ctime>
#include <algorithm>
#include <random>

struct InGame
{
    static void CreateMatrix(int);
    static bool CheckPath(int, int, int, int, int, int, int, char);

    static void DrawGameBoard();
};

struct Classic
{
    static void Easy();
};
