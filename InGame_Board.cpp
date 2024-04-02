#include "InGame.h"
#include <iomanip>
#include <string>
#include <vector>

extern char** matrix;
extern string *background;
extern vector<pair<char, string> >colorBG;
extern int matrix_size;

int board_x = 5;
int board_y = 5;

extern std::mutex cursorMutex;
extern string username;
extern string userID;

void InGame::DrawGameBoard(int size, int num)
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

	SetTextColor(15);

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
    InGame::CreateMatrix(size, num);

    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
        {
            Cursor(8*j + board_x + 5, 4*i + board_y + 2);
            cout << matrix[i][j];
        }
}

void InGame::DeleteSquare(int x, int y)
{
	cursorMutex.lock();

    Cursor(8*y + board_x + 5, 4*x + board_y + 2);
    cout << " ";

	// Xóa đường ngang trên
    if (matrix[x - 1][y] == '.')
    {
        Cursor(8*y + board_x + 2, 4*x + board_y);
        for(int i = 1; i <= 7; i++)
			cout << background[(x - 1) * 4][(y - 1) * 8 + i];
		// cout << "       ";
    }

	// Xóa đường ngang dưới
    if (matrix[x + 1][y] == '.')
    {
        Cursor(8*y + board_x + 2, 4*x + board_y + 4);
        for(int i = 1; i <= 7; i++)
			cout << background[x * 4][(y - 1) * 8 + i];
		// cout << "       ";
    }

	// Xóa đường bên trái
    if (matrix[x][y - 1] == '.')
        for (int i = 1; i < 4; i++)
        {
            Cursor(8*y + board_x + 1, 4*x + board_y + i);
            cout << background[(x - 1) * 4 + i ][(y - 1) * 8];
			// cout << " ";
        }

	// Xóa đường bên phải
    if (matrix[x][y + 1] == '.')
        for (int i = 1; i < 4; i++)
        {
            Cursor(8*y + board_x + 9, 4*x + board_y + i);
            cout << background[(x - 1) * 4 + i][y * 8];
			// cout << " ";
        }
	
    for(int i = 1; i <= 3; i++)
	{
        Cursor(8*y + board_x + 2, 4*x + board_y + i);
		for(int j = 1; j <= 7; j++)
		{
			cout << background[(x - 1) * 4 + i][(y - 1) * 8 + j];
		}
	}

	cursorMutex.unlock();
}

void InGame::DrawTime(int size = 5)
{
    int x = board_x + 4 + (size + 2) * 8 - 4 - 4 + 1 + 5;
    int y = board_y + 2;
    Cursor(x + 1, y);
	putchar(218);
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		putchar(196);
	}
	putchar(191);
	
	// Draw right line
	for (int i = 1; i < size + size / 2 - 1; i++)
	{
		Cursor(size * 4 + size / 2 + x + 1, i + y);
		putchar(179);
	}
	Cursor(size * 4 + size / 2 + x + 1, size + size / 2 - 1 + y);
	putchar(217);
	
	// Draw bottom line
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		Cursor(size * 4 + size / 2 + x - i + 1, size + size / 2 - 1 + y);
		putchar(196);
	}
	Cursor(x + 1, size + size / 2 - 1 + y);
	putchar(192);
	
	// Draw left line 
	for (int i = 1; i < size + size / 2 - 1; i++)
	{
		Cursor(x + 1, size + size / 2 - 1 + y - i); 
		putchar(179);
	}  

	Cursor(size * 4 + x - size * 4 + 1, y + 2);
	putchar(195);
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		Cursor(size * 4 + size / 2 + x - i + 1, y + 2);
		putchar(196);
	}
	Cursor(size * 4 + size / 2 + x - 0 + 1, y + 2);
	putchar(180);

	SetTextColor(15);

    Cursor(x + (size * 4 + size / 2) / 2, y + 1);
    cout << "Time";

    // Time t;
    // while(1)
    // {
    //     CountingTime(x + 8, y + 4, t);
    //     if(t.hour == 0 && t.minute == 0 && t.second == -1)
    //     {
    //         Cursor(x + 7, y + 4);
    //         cout << "You lose!!!";
    //         break;
    //     }
    // }
}

void InGame::DrawGuide(int size = 5)
{
    int x = board_x + 4 + (size + 2) * 8 - 4 - 4 + 1 + 5;
    int y = board_y + 2 + size + size / 2 - 1 + 2;
    Cursor(x + 1, y);
	putchar(218);
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		putchar(196);
	}
	putchar(191);
	
	// Draw right line
	for (int i = 1; i < size * 2 + size; i++)
	{
		Cursor(size * 4 + size / 2 + x + 1, i + y);
		putchar(179);
	}
	Cursor(size * 4 + size / 2 + x + 1, size * 2 + size + y);
	putchar(217);
	
	// Draw bottom line
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		Cursor(size * 4 + size / 2 + x - i + 1, size * 2 + size + y);
		putchar(196);
	}
	Cursor(x + 1, size * 2 + size + y);
	putchar(192);
	
	// Draw left line 
	for (int i = 1; i < size * 2 + size ; i++)
	{
		Cursor(x + 1, size * 2 + size + y - i); 
		putchar(179);
	}  

	Cursor(size * 4 + x - size * 4 + 1, y + 2);
	putchar(195);
	for (int i = 1; i < size * 4 + size / 2; i++)
	{
		Cursor(size * 4 + size / 2 + x - i + 1, y + 2);
		putchar(196);
	}
	Cursor(size * 4 + size / 2 + x - 0 + 1, y + 2);
	putchar(180);
    

	SetTextColor(15);

    Cursor(x + (size * 4 + size / 2) / 2 - 1, y + 1);
    cout << "Guide";

    Cursor(x + 2, y + 3);
    cout << "H: Hint";
    Cursor(x + 2, y + 3 + size / 2);
    cout << "Enter: Choose";
    Cursor(x + 2, y + 3 + size / 2 + size / 2);
    cout << "Backspace: Remove";
    Cursor(x + 2, y + 3 + size / 2 + size / 2 + size / 2);
	cout << "C: Color";
    Cursor(x + 2, y + 3 + size / 2 + size / 2 + size / 2 + size / 2);
    cout << "Esc: Escape";
}

void InGame::SquareCursor(int x, int y, int color)
{
	cursorMutex.lock();

    SetTextColor(color);
	for (int i = 1; i <= 3; i++)
	{
		Cursor(8*y + board_x + 3, 4*x + board_y + i);
		cout << "     ";
	}

	if (matrix[x][y] != '.')
	{	
		Cursor(8*y + board_x + 5, 4*x + board_y + 2);
		cout << matrix[x][y];
	}

	SetTextColor(15);

	cursorMutex.unlock();
}

void InGame::DeleteSquareCursor(int x, int y)
{
	InGame::SquareCursor(x, y, 15);
}

void InGame::DrawFinish(int n)
{
	int num = 2;
	string t;
	if(n == 4) // 4 x 4
	{
		t = R"(
                   ____                 _
                  / ___| ___   ___   __| |
                 | |  _ / _ \ / _ \ / _` |
                 | |_| | (_) | (_) | (_| |
                  \____|\___/ \___/ \__,_|
		)";
	}
	else if(n == 6) // 6 x 6
	{
		t = R"(

                         ____                _
                        / ___|_ __ ___  __ _| |_
                       | |  _| '__/ _ \/ _` | __|
                       | |_| | | |  __/ (_| | |_
                        \____|_|  \___|\__,_|\__|

		)";
	}
	else if(n == 8) // 8 x 8
	{
		t = R"(

                            _____              _ _            _
                           | ____|_  _____ ___| | | ___ _ __ | |_
                           |  _| \ \/ / __/ _ \ | |/ _ \ '_ \| __|
                           | |___ >  < (_|  __/ | |  __/ | | | |_
                           |_____/_/\_\___\___|_|_|\___|_| |_|\__|
		)";
	}

	while(num--)
	{
    	for (int i = 0; i < 15 ; i++)
    	{
        	Cursor(5, 0);
        	SetTextColor(i);
        	cout << t << "\n";
        	Sleep(120);
		}
	}
}

void InGame::DrawTimeUp(int n)
{
	int num = 2;
	string t;
	if(n == 4) // 4 x 4
	{
		t = R"(
                   _____ _                _                   
                  |_   _(_)_ __ ___   ___( )___   _   _ _ __  
                    | | | | '_ ` _ \ / _ \// __| | | | | '_ \
                    | | | | | | | | |  __/ \__ \ | |_| | |_) |
                    |_| |_|_| |_| |_|\___| |___/  \__,_| .__/ 
                                                       |_|    
  
		)";
	}
	else if(n == 6) // 6 x 6
	{
		t = R"(
                               _____ _                _                   
                              |_   _(_)_ __ ___   ___( )___   _   _ _ __  
                                | | | | '_ ` _ \ / _ \// __| | | | | '_ \
                                | | | | | | | | |  __/ \__ \ | |_| | |_) |
                                |_| |_|_| |_| |_|\___| |___/  \__,_| .__/ 
                                                                   |_|   
		)";
	}
	else if(n == 8) // 8 x 8
	{
		t = R"(
                                       _____ _                _                   
                                      |_   _(_)_ __ ___   ___( )___   _   _ _ __  
                                        | | | | '_ ` _ \ / _ \// __| | | | | '_ \
                                        | | | | | | | | |  __/ \__ \ | |_| | |_) |
                                        |_| |_|_| |_| |_|\___| |___/  \__,_| .__/ 
                                                                           |_|   
		)";
	}

	while(num--)
	{
    	for (int i = 0; i < 11 ; i++)
    	{
        	Cursor(5, 0);
        	SetTextColor(red * (i % 2) + light_red * !(i % 2));
        	cout << t << "\n";
        	Sleep(100);
		}
	}
	
	Cursor(4 * matrix_size + board_x, 4 * matrix_size + board_y + 9);
	cout << "Press any key...";
}

void DrawLeaderboard(string text, Score you, Score* S, int x, int y)
{
    Cursor(x - 2, y - 1);
    putchar(218);
    for (int i = 0; i < 46; i++)
        putchar(196);
    putchar(191);

    Cursor(x - 2, y + 18);
    putchar(192);
    for (int i = 0; i < 46; i++)
        putchar(196);
    putchar(217);

    for (int i = 0; i <= 17; i++)
    {
        Cursor(x - 2, y + i);
        putchar(179);
        Cursor(x + 45, y + i);
        putchar(179);
    }

    Cursor(x + 22 - text.length() / 2, y);
    cout << text;

	for (int i = 1; i <= 8; i++)
    {
        Score temp = S[i - 1];
        Cursor(x + 1, y + 2*i);
        cout << i << "> ";              
    }

	SetTextColor(15);
	for (int i = 1; i <= 8; i++)
    {
        Score temp = S[i - 1];
		if((you.ID.compare(temp.ID) == 0 && you.time.second == temp.time.second && you.time.minute == temp.time.minute) || (you.time.second == -29 && you.ID.compare(temp.ID) == 0))
			SetTextColor(light_blue);
        Cursor(x + 4, y + 2*i);
    	cout << setfill('0') << setw(2) << temp.time.hour << " : ";
    	cout << setfill('0') << setw(2) << temp.time.minute << " : ";
    	cout << setfill('0') << setw(2) << temp.time.second;
		cout << " (" << temp.name << " - " << temp.ID << ")";
		SetTextColor(15);
    }	
}


void DrawUserboard(string text, Score you, Score* S, int x, int y)
{
    Cursor(x - 2, y - 1);
    putchar(218);
    for (int i = 0; i < 46; i++)
        putchar(196);
    putchar(191);

    Cursor(x - 2, y + 18);
    putchar(192);
    for (int i = 0; i < 46; i++)
        putchar(196);
    putchar(217);

    for (int i = 0; i <= 17; i++)
    {
        Cursor(x - 2, y + i);
        putchar(179);
        Cursor(x + 45, y + i);
        putchar(179);
    }

    Cursor(x + 22 - text.length() / 2, y);
    cout << text;

    Cursor(x + 1, y + 2*1);
    cout << "Name: ";
    Cursor(x + 1, y + 2*2);
	cout << "ID  : ";
	Cursor(x + 1, y + 2*3);
	cout << "Time: ";

	Cursor(x + 1, y + 2*7 + 1);
	cout << "Developed by: ";
	Cursor(x + 1, y + 2*8);
	cout << "From: ";
	
	SetTextColor(purple);
	Cursor(x + 15, y + 2*7 + 1);
	cout << "HGB and LMT";
	Cursor(x + 7, y + 2*8);
	cout <<"23CLC05 - K23 - HCMUS";

	SetTextColor(15);
    Cursor(x + 7, y + 2*1);
    cout << you.name;
    Cursor(x + 7, y + 2*2);
	cout << you.ID;
	Cursor(x + 7, y + 2*3);
    cout << setfill('0') << setw(2) << you.time.hour << ":";
    cout << setfill('0') << setw(2) << you.time.minute << ":";
    cout << setfill('0') << setw(2) << you.time.second;

	int order = 0;
	for(int i = 0; i <= 7; i++)
	{
		if(you.ID.compare(S[i].ID) == 0 && you.time.second == S[i].time.second && you.time.minute == S[i].time.minute)
		{
			SetTextColor(light_blue);
			Cursor(x, 0);
			string temp = R"(
                         _____                                    _           _         _    _               
                        /  __ \                                  | |         | |       | |  (_)              
                        | /  \/  ___   _ __    __ _  _ __   __ _ | |_  _   _ | |  __ _ | |_  _   ___   _ __  
                        | |     / _ \ | '_ \  / _` || '__| / _` || __|| | | || | / _` || __|| | / _ \ | '_ \
                        | \__/\| (_) || | | || (_| || |   | (_| || |_ | |_| || || (_| || |_ | || (_) || | | |
                         \____/ \___/ |_| |_| \__, ||_|    \__,_| \__| \__,_||_| \__,_| \__||_| \___/ |_| |_|
                                               __/ |                                                         
                                              |___/                                                                                               
			)";
			order = i + 1;
			cout << temp;
			SetTextColor(15);
			break;
		}
	}

	string quote1;
	string quote2;
	int distance;
	if(order != 0)
	{
		if(order == 1)
		{
			// Chèn sound cho người về nhất

			quote1 = "Congratulations on coming first!!!";
    		for (int i = 0; i < 15 ; i++)
    		{
				Cursor(x + 46/2 - quote1.length()/2 - 1, y + 2*4 + 1);
        		SetTextColor(i);
				cout << quote1;
        		Sleep(120);
			}
			quote2 = "Your efforts will be recorded";
			Cursor(x + 46/2 - quote2.length()/2 - 1, y + 2*4 + 2);
			cout << quote2;
		}
		else
		{
			distance = (S[order - 2].time.hour * 3600 + S[order - 2].time.minute * 60 + S[order - 2].time.second) - (S[order - 1].time.hour * 3600 + S[order - 1].time.minute * 60 + S[order - 1].time.second);
			quote1 = "Fighting!!! you just need faster ";
			Cursor(x + 46/2 - quote1.length()/2 - 1, y + 2*4 + 1);
			cout << quote1;

			quote2 = "";
			quote2 += to_string(distance);
			quote2 += " second to overcome the ";
			if(order == 2)
				quote2 += "1st";
			else if(order == 3)
				quote2 += "2nd";
			else if(order == 4)
				quote2 += "3rd";
			else
			{
				quote2 += to_string((order - 1)) + "th";
			}
			quote2 += " person";
			Cursor(x + 46/2 - quote2.length()/2 - 1, y + 2*4 + 2);
			cout << quote2;
		}
	}
	else
	{
			SetTextColor(light_blue);
			Cursor(x, 0);
			string temp = R"(
             _____                 _            _    _                                     _      _    _                  
            |_   _|               | |          | |  | |                                   | |    | |  (_)                 
              | |   _ __  _   _   | |__    ___ | |_ | |_   ___  _ __    _ __    ___ __  __| |_   | |_  _  _ __ ___    ___ 
              | |  | '__|| | | |  | '_ \  / _ \| __|| __| / _ \| '__|  | '_ \  / _ \\ \/ /| __|  | __|| || '_ ` _ \  / _ \
              | |  | |   | |_| |  | |_) ||  __/| |_ | |_ |  __/| |     | | | ||  __/ >  < | |_   | |_ | || | | | | ||  __/
              \_/  |_|    \__, |  |_.__/  \___| \__| \__| \___||_|     |_| |_| \___|/_/\_\ \__|   \__||_||_| |_| |_| \___|
                           __/ |                                                                                          
                          |___/                                                                                                                                                        
			)";
			cout << temp;
			SetTextColor(15);
		distance =  (S[7].time.hour * 3600 + S[7].time.minute * 60 + S[7].time.second) - (you.time.hour * 3600 + you.time.minute * 60 + you.time.second);
		quote1 = "Come on, the distance between";
		Cursor(x + 46/2 - quote1.length()/2 - 1, y + 2*4 + 1);
		cout << quote1;
		
		quote2 = "a loser and successful person is ";
		quote2 += to_string(distance);
		quote2 += " second";
		Cursor(x + 46/2 - quote2.length()/2 - 1, y + 2*4 + 2);
		cout << quote2;
	}

}

void InGame::SquareColor(int x, int y)
{
	cursorMutex.lock();
	string colorCode = "";
	for(int i = 0; i < 14; i++)
	{
		if(colorBG[i].first == matrix[x][y])
		{
			colorCode += colorBG[i].second;
			break;
		}
	}

	for (int i = 1; i <= 3; i++)
	{
		Cursor(8*y + board_x + 3, 4*x + board_y + i);
		if(i == 2)
		{
			string t = "  ";
			t = t + matrix[x][y] + "  ";
			cout << colorCode << t << "\033[0m"; // Đặt màu và in văn bản, sau đó đặt lại màu về mặc định
		}
		else 
			cout << colorCode << "     " << "\033[0m";
	}

	// if (matrix[x][y] != '.')
	// {	
	// 	Cursor(8*y + board_x + 5, 4*x + board_y + 2);
	// 	cout << matrix[x][y];
	// }


	cursorMutex.unlock();
}

// void InGame::DeleteSquareColor(int x, int y)
// {
// 	InGame::SquareColor(x, y);
// }

// void InGame::SquareCursor(int x, int y, int color)
// {
// 	cursorMutex.lock();

//     SetTextColor(color);
// 	for (int i = 1; i <= 3; i++)
// 	{
// 		Cursor(8*y + board_x + 3, 4*x + board_y + i);
// 		cout << "     ";
// 	}

// 	if (matrix[x][y] != '.')
// 	{	
// 		Cursor(8*y + board_x + 5, 4*x + board_y + 2);
// 		cout << matrix[x][y];
// 	}

// 	SetTextColor(15);

// 	cursorMutex.unlock();
// }

// void InGame::DeleteSquareCursor(int x, int y)
// {
// 	InGame::SquareCursor(x, y, 15);
// }

