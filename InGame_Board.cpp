#include "InGame.h"

extern char** matrix;
extern int matrix_size;

int board_x = 5;
int board_y = 5;

void InGame::DrawGameBoard(int size = 5)
{
	// Draw top line
    matrix_size = size;
    size += 2;

    Cursor(board_x + 4, board_y + 2);
	putchar(201);
	for (int i = 4; i < size * 8 - 3; i++)
	{
		Sleep(5);
		putchar(205);
	}
	putchar(187);
	
	// Draw right line
	for (int i = 3; i < size * 4 - 2; i++)
	{
		Sleep(10);
		Cursor(size * 8 + board_x - 2, i + board_y);
		putchar(186);
	}
	Cursor(size * 8 + board_x - 2, size * 4 + board_y - 2);
	putchar(188);
	
	// Draw bottom line
	for (int i = 1; i < size * 8 - 6; i++)
	{
		Cursor(size * 8 + board_x - i - 2, size * 4 + board_y - 2);
		Sleep(5);
		putchar(205);
	}
	Cursor(board_x + 4, size * 4 + board_y - 2);
	putchar(200);
	
	// Draw left line
	for (int i = 1; i < size * 4 - 4; i++)
	{
		Sleep(10);
		Cursor(board_x + 4, size * 4 + board_y - i - 2); 
		putchar(186);
	}

	// Draw vertical lines
	for (int i = 4; i < (size - 1) * 4; i++)
	{
		for (int j = 8; j < size * 8; j += 8)
		{
			if (i % 4 != 0)
			{
				Cursor(j + board_x + 1, i + board_y);
				putchar(179);
			}
		}
		Sleep(10);
	}
	
	// Draw horizontal lines
	for (int i = 8; i < (size - 1) * 8; i++)
	{
		for (int j = 4; j < size * 4; j += 4)
		{
			Cursor(i + board_x + 1, j + board_y);
			if (i % 8 == 0)
				//putchar(197);
				putchar(32);
			else
				putchar(196);
		}
		Sleep(5);
	}

    size -= 2;
    InGame::CreateMatrix(size);

    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
        {
            Cursor(8*j + board_x + 5, 4*i + board_y + 2);
            cout << matrix[i][j];
        }
}

void InGame::DeleteSquare(int x, int y)
{
    for (int i = 1; i < 8; i++)
    {
        cout << 1;
    }
}
