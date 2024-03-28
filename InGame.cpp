#include "InGame.h"

extern char** matrix;
extern int matrix_size;



void Classic::ClassicGame(int size)
{
    system("cls");

    InGame::DrawGameBoard(size, 2 * size - 2);
    InGame::DrawTime(size);
    InGame::DrawGuide(size);

    int x1 = 1, y1 = 1, x2 = 1, y2 = 1, count = 0;
    while (1)
    {
        x1 = x2;
        y1 = y2;

        if (matrix[x1][y1] != '.')
            InGame::SquareCursor(x1, y1, WHITE);
        
        //Chọn (x1, y1)
        while (1)
        {
            int button = ConsoleInput();

            if (matrix[x1][y1] != '.')
                InGame::DeleteSquareCursor(x1, y1);

            //Kiểm tra phím mũi tên
            if (button == 2)
                x1 = (x1 + matrix_size - 2) % matrix_size + 1;
            else if (button == -2)
                x1 = x1 % matrix_size + 1;
            else if (button == -3)
                y1 = (y1 + matrix_size - 2) % matrix_size + 1;
            else if (button == 3)
                y1 = y1 % matrix_size + 1;

            //Kiểm tra phím Enter
            else if (button == 1 && matrix[x1][y1] != '.')
            {
                InGame::SquareCursor(x1, y1, WHITE);
                break;
            }

            //Kiểm tra phím Esc
            else if (button == 0)
            {
                DeleteMatrix();
                return;
            }

            if (matrix[x1][y1] != '.')
                InGame::SquareCursor(x1, y1, WHITE);
        }

        //Chọn (x2, y2)
        x2 = x1;
        y2 = y1;
        while (1)
        {
            int button = ConsoleInput();

            if ((x2 != x1 || y2 != y1) && matrix[x2][y2] != '.')
                InGame::DeleteSquareCursor(x2, y2);

            //Kiểm tra phím mũi tên
            if (button == 2)
                x2 = (x2 + matrix_size - 2) % matrix_size + 1;
            else if (button == -2)
                x2 = x2 % matrix_size + 1;
            else if (button == -3)
                y2 = (y2 + matrix_size - 2) % matrix_size + 1;
            else if (button == 3)
                y2 = y2 % matrix_size + 1;

            //Kiểm tra phím Enter
            else if (button == 1 && (x2 != x1 || y2 != y1) && matrix[x2][y2] != '.')
            {
                InGame::SquareCursor(x2, y2, WHITE);
                break;
            }

            //Kiểm tra phím Backspace
            else if (button == -1)
            {
                InGame::DeleteSquareCursor(x1, y1);

                if (matrix[x2][y2] != '.')
                    InGame::SquareCursor(x2, y2, WHITE);
                    
                x1 = -1;
                break;
            }

            //Kiểm tra phím Esc
            else if (button == 0)
            {
                DeleteMatrix();
                return;
            }

            if (matrix[x2][y2] != '.')
                InGame::SquareCursor(x2, y2, WHITE);
        }
        if (x1 == -1)
            continue;
        
        if (InGame::CheckPath(x1, y1, x2, y2, matrix[x1][y1], 2, -1, -1))
        {
            matrix[x1][y1] = '.';
            matrix[x2][y2] = '.';

            InGame::SquareCursor(x1, y1, GREEN);
            InGame::SquareCursor(x2, y2, GREEN);

            Sleep(50);
            
            InGame::DeleteSquareCursor(x1, y1);
            InGame::DeleteSquareCursor(x2, y2);

            InGame::DeleteSquare(x1, y1);
            InGame::DeleteSquare(x2, y2);

            count += 2;
        }
        else
        {
            InGame::SquareCursor(x1, y1, RED);
            InGame::SquareCursor(x2, y2, RED);

            Sleep(50);

            InGame::DeleteSquareCursor(x1, y1);
            InGame::DeleteSquareCursor(x2, y2);
        }

        if (count == matrix_size * matrix_size)
        {
            Sleep(1000);
            break;
        }
    }

    system("cls");
    Cursor(7, 7);
    cout << "YOU WIN";

    _getch();
    system("cls");
    return;
}

void Classic::Easy()
{
    Classic::ClassicGame(4);
}

void Classic::Medium()
{
    Classic::ClassicGame(6);
}

void Classic::Hard()
{
    Classic::ClassicGame(8);
}

