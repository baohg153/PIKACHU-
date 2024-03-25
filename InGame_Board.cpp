#include "InGame.h"

void InGame::DrawGameBoard()
{
	// Draw top line
    int size = 5;
    int x = 5;
    int y = 5;
    Cursor(x + 1, y);
	putchar(201);
	for (int i = 1; i < size * 8; i++)
	{
		Sleep(5);
		putchar(205);
	}
	putchar(187);
	
	// Draw right line
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(10);
		Cursor(size * 8 + x + 1, i + y);
		putchar(186);
	}
	Cursor(size * 8 + x + 1, size * 4 + y);
	putchar(188);
	
	// Draw bottom line
	for (int i = 1; i < size * 8; i++)
	{
		Cursor(size * 8 + x - i + 1, size * 4 + y);
		Sleep(5);
		putchar(205);
	}
	Cursor(x + 1, size * 4 + y);
	putchar(200);
	
	// Draw left line
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(10);
		Cursor(x + 1, size * 4 + y - i); 
		putchar(186);
	}

	// Draw vertical lines
	for (int i = 1; i < size * 4; i++)
	{
		for (int j = 8; j < size * 8; j += 8)
		{
			if (i % 4 != 0)
			{
				Cursor(j + x + 1, i + y);
				putchar(179);
			}
		}
		Sleep(10);
	}
	
	// Draw horizontal lines
	for (int i = 1; i < size * 8; i++)
	{
		for (int j = 4; j < size * 4; j += 4)
		{
			Cursor(i + x + 1, j + y);
			if (i % 8 == 0)
				//putchar(197);
				putchar(32);
			else
				putchar(196);
		}
		Sleep(5);
	}
}