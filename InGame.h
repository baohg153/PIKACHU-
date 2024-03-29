#include "Console.h"
#include <ctime>
#include <algorithm>
#include <random>
#include <thread>
#include <atomic>
#include <mutex>

struct Time
{
    int hour;
    int minute;
    int second;
    Time(): hour(0), minute(1), second(0) {}
};

struct Point
{
    int x;
    int y; 
};

struct Node
{
    char data;
    Node* next;
};

// struct List
// {
//     Node *head;
//     Node *tail;
// };


struct InGame
{
    static void CreateMatrix(int, int);
    static bool CheckPath(int, int, int, int, char, int, int, int);
    static void DeleteSquare(int, int);
    static bool AutomaticallyFinding(int, int);
    static void ShuffleBoard(int , int , unsigned int);

    static void DrawGameBoard(int, int);
    static void CountingTime(int , int , Time &);
    static void DrawTime(int);
    static void DrawGuide(int);
    static void DrawFinish(int);
    
    static void SquareCursor(int, int, int);
    static void DeleteSquareCursor(int, int);
    static void CreateBackground(int);
};

void print(int);
void DeleteMatrix();
void DeleteBackground();
void DeleteList();

struct Classic
{
    static void ClassicGame(int);
    static void Easy();
    static void Medium();
    static void Hard();
};

struct Advance
{
    static void AdvanceGame(int);
    static void AdEasy();
    static void AdMedium();
    static void AdHard();

    static void CreateList();
    static void DrawList(int);
    static void UpdateMatrix(int, int, int, int);
    static void CopyList();
};
