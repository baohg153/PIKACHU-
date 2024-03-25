#include "InGame.h"

extern char** matrix;
extern int matrix_size;

void Classic::Easy()
{
    InGame::DrawGameBoard(5);
    
    Cursor(0, 40);

    print(5);

    while (1)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        if (x1 == -1)
            break;
        
        cout << matrix[x1][y1] << " " << matrix[x2][y2] << endl;

        if (InGame::CheckPath(x1, y1, x2, y2, matrix[x1][y1], 2, -1, -1))
        {
            matrix[x1][y1] = '.';
            matrix[x2][y2] = '.';

            cout << 1;
        }
        else
            cout << 0;
    }
}