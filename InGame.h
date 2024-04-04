#include "Console.h"
#include <ctime>
#include <algorithm>
#include <random>
#include <thread>
#include <atomic>
#include <mutex>
#include <fstream>
#include <string>

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


struct Score
{
    Time time;
    string name;
    string ID;
};

struct Node
{
    char data;
    Node* next;
};

struct InGame 
{
    static void CreateMatrix(int, int);  //Create a random matrix and push it to a pointer variable
    static bool CheckPath(int, int, int, int, char, int, int, int);  //Check matching
    static void DeleteSquare(int, int);  //Delete piece when it's completed
    static bool AutomaticallyFinding(int, int); //Check if there are any possible pairs
    static void ShuffleBoard(int , int , unsigned int); //Shuffle the gameboard

    static void DrawGameBoard(int, int);  //Print the gameboard
    static void CountingTime(int , int , Time &);  //Makes the time countdown every second
    static void DrawTime(int); //Draw Time board
    static void DrawGuide(int);  //Draw Guide board
    static void DrawFinish(int);  //Draw ASCII art after completing the matrix
    static void DrawTimeUp(int);  //Draw ASCII art when time is up
    
    static void SquareCursor(int, int, int);  //Color the square where the cursor is at.
    static void DeleteSquareCursor(int, int);  //Delete color at the square which the old cursor pointed to
    static void CreateBackground(int); //Push the background to an array of string variables
    static void CreateColorBG();  //Create a vector including seperate colors for each character
    static void SquareColor(int, int); //Color a piece (use when the color mode is on)
};

void DeleteMatrix();  //Delete matrix pointer
void DeleteBackground();  //Delete background pointer
void DeleteList();  //Delete pointers in linked list

void DrawLeaderboard(string, Score, Score*, int, int);  //Draw leaderboard when game finishes
void DrawUserboard(string, Score, Score*, int, int);  //Draw userboard when game finishes

struct Classic
{
    static void ClassicGame(int);  //Run the classic game with the matrix's size as parameter
    static void Easy();  //Run classic easy game
    static void Medium();  //Run classic medium game
    static void Hard();  //Run classic hard game
};

struct Advance
{
    static void AdvanceGame(int);  //Run the advance game with the matrix's size as parameter
    static void AdEasy();  //Run advance easy game
    static void AdMedium();  //Run advance medium game
    static void AdHard();  //Run advance hard game

    static void CreateList();  //Create a random matrix and push it to linked lists
    static void DrawList(int);  //Draw gameboard
    static void UpdateMatrix(int, int, int, int);  //Update linked lists and redraw gameboard after 2 pieces disappear
    static void CopyList();  //Copy linked lists to a matrix pointer
};

//Functions about Score
void ReadScoreClassic();  //Read top classic scores from a file
void UpdateScoreClassic();  //Update top classic scores and push them to the file

void ReadScoreAdvance();  //Read top advance scores from a file
void UpdateScoreAdvance();  //Update top advance scores and push them to the file

bool CompareScores(Score, Score);  //Compare 2 scores
void RearrangeScore(Score[]);  //Rearrange an array of scores