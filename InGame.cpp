#include "InGame.h"

extern char** matrix;
extern int matrix_size;

void Classic::Easy()
{
    InGame::DrawGameBoard(5);

    while (1)
    {
        Cursor(12, 33);
        cout << "Type (x1, y1) (x2, y2):                                     ";
        Cursor(36, 33);
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        if (x1 == -1)
            break;

        if (InGame::CheckPath(x1, y1, x2, y2, matrix[x1][y1], 2, -1, -1))
        {
            matrix[x1][y1] = '.';
            matrix[x2][y2] = '.';
            InGame::DeleteSquare(x1, y1);
            InGame::DeleteSquare(x2, y2);

            Cursor(0, 35);
            print(matrix_size);
        }
    }
}

void FillColor()
{
    Cursor(0, 0);
    SetTextColor(50);
    for (int i = 1; i < 10; i++)
        for (int j = 0; j < 3; j++)
        {
            Cursor(i, j);
            putchar(32);
        }
}