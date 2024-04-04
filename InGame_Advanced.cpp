#include "InGame.h"
#include <thread>
#include <atomic>
#include <mutex>

Node **arrList;
int* lenList;
extern char** matrix;
extern string* background;
extern int matrix_size;
extern int board_x;
extern int board_y;
extern Point HintA;
extern Point HintB;

extern int tracker;

extern std::mutex cursorMutex;
extern atomic<bool> thread1Finished;

extern Score ad_easy[9];
extern Score ad_medium[9];
extern Score ad_hard[9];

extern Time t;
extern string username;
extern string userID;

void  RemoveLinkedList(int row, int index)
{
    Node* pHead = arrList[row];
    
    if (index == 1)
    {
        Node* pCurr = pHead;
        arrList[row] = pCurr->next;
        lenList[row]--;
        delete pCurr;
        return;
    }

    for (int i = 0; i < index - 2; i++)
        pHead = pHead->next;

    Node* pCurr = pHead->next;
    pHead->next = pHead->next->next;
    delete pCurr;

    lenList[row]--;
}


void Advance::CreateList()
{
    arrList = new Node*[matrix_size + 1];
    lenList = new int[matrix_size + 1];
    for(int i = 1; i <= matrix_size; i++)
    {
        lenList[i] = matrix_size;
        for(int j = 1; j <= matrix_size; j++)
        {
            if(j != 1)
            {
                Node *pCurr = arrList[i];
                while(pCurr->next)
                    pCurr = pCurr->next;
                pCurr->next = new Node;
                pCurr = pCurr->next;
                pCurr->data = matrix[i][j];
                pCurr->next = NULL;
            }
            else
            {
                arrList[i] = new Node;
                arrList[i]->data = matrix[i][j];
                arrList[i]->next = NULL;
            }
        }
    }
}

void Advance::DrawList(int row)
{
   
        Node *pCurr = arrList[row];
        int t = 1;
        while(pCurr)
        {
            Cursor(8*t + board_x + 5, 4*row + board_y + 2);
            cout << pCurr->data;
            pCurr = pCurr->next;
            t++;
        }

        // Xóa đường ngang trên
        if (matrix[row - 1][(lenList[row] + 1)] == '.')
        {
            Cursor(8*(lenList[row] + 1) + board_x + 2, 4*row + board_y);
            for(int i = 1; i <= 7; i++)
                cout << background[(row - 1) * 4][((lenList[row] + 1) - 1) * 8 + i];
            // cout << "       ";
        }


        // Xóa đường ngang dưới
        if (matrix[row + 1][(lenList[row] + 1)] == '.')
        {
            Cursor(8*(lenList[row] + 1) + board_x + 2, 4*row + board_y + 4);
            for(int i = 1; i <= 7; i++)
                cout << background[row * 4][((lenList[row] + 1) - 1) * 8 + i];
            // cout << "       ";
        }

        // Xóa đường bên trái(chỉ cần xóa khi dãy không còn phần tử)
        if (lenList[row] == 0)
            for (int i = 1; i < 4; i++)
            {
                Cursor(8*(lenList[row] + 1) + board_x + 1, 4*row + board_y + i);
                cout << background[(row - 1) * 4 + i ][((lenList[row] + 1) - 1) * 8];
                // cout << " ";
            }

        // Xóa đường bên phải(không cần kiểm tra do nó luôn được lùi về)

            for (int i = 1; i < 4; i++)
            {
                Cursor(8*(lenList[row] + 1) + board_x + 9, 4*row + board_y + i);
                cout << background[(row - 1) * 4 + i][(lenList[row] + 1) * 8];
                // cout << " ";
            }
        
        for(int i = 1; i <= 3; i++)
        {
            Cursor(8*(lenList[row] + 1) + board_x + 2, 4*row + board_y + i);
            for(int j = 1; j <= 7; j++)
            {
                cout << background[(row - 1) * 4 + i][((lenList[row] + 1) - 1) * 8 + j];
            }
        }
}

void Advance::UpdateMatrix(int x1, int y1, int x2, int y2)
{
    if (y2 > y1)
    {
        int temp;
        temp = x1; x1 = x2; x2 = temp;
        temp = y1; y1 = y2; y2 = temp;
    }
    int track = 1;
    RemoveLinkedList(x1, y1);
    Node* pCurr = arrList[x1];
    for (int i = 1; i <= lenList[x1]; i++)
    {
        matrix[x1][i] = pCurr->data;
        pCurr = pCurr->next;
    }
    for (int i = lenList[x1] + 1; i <= matrix_size; i++)
        matrix[x1][i] = '.';

    if(x1 == x2)
    {
        track = 0;
        Advance::DrawList(x1);
    }
    
    RemoveLinkedList(x2, y2);
    pCurr = arrList[x2];
    for (int i = 1; i <= lenList[x2]; i++)
    {
        matrix[x2][i] = pCurr->data;
        pCurr = pCurr->next;
    }
    for (int i = lenList[x2] + 1; i <= matrix_size; i++)
        matrix[x2][i] = '.';
    
    if(track)
        Advance::DrawList(x1);
    Advance::DrawList(x2);

}


void Advance::CopyList()
{
    for(int i = 1; i <= matrix_size; i++)
    {
        int j = 1;
        Node* pCurr = arrList[i];
        while(pCurr)
        {
            pCurr->data = matrix[i][j];
            j++;
            pCurr = pCurr->next;
        }
    }
}

void threadMoveAdvance() {
    int color = 0;
    int x1 = 1, y1 = 1, x2 = 1, y2 = 1, count = 0;
    while (1)
    {
        if (thread1Finished) {
            break;
        }
        
        if(HintA.x == -1 || matrix[HintA.x][HintA.y] == '.' ||  matrix[HintB.x][HintB.y] == '.'  ||  matrix[HintA.x][HintA.y] != matrix[HintB.x][HintB.y])
        {
            while(InGame::AutomaticallyFinding(matrix_size, matrix_size) == false)
            {

                for(int i = 1; i <= matrix_size; i++)
                {
                    for(int j = 1; j <= matrix_size; j++)
                    {
                        if(matrix[i][j] != '.')
                        {
                            if(color)
                            {
                                InGame::DeleteSquareCursor(i, j);
                            }
                            Cursor(8*j + board_x + 5, 4*i + board_y + 2);
                            cout << " ";
                        }
                    }
                }

                random_device rd;
                InGame::ShuffleBoard(matrix_size, matrix_size, rd());

                // cursorMutex.lock(); 
                for (int i = 1; i <= matrix_size; i++)
                {
                    for (int j = 1; j <= matrix_size; j++)
                    {
                        if(matrix[i][j] != '.')
                        {
                            if(color)
                            {
                                InGame::SquareColor(i, j);
                            }
                            else
                            {
                                cursorMutex.lock();
                                Cursor(8*j + board_x + 5, 4*i + board_y + 2);
                                cout << matrix[i][j];
                                cursorMutex.unlock();
                            }
                            Sleep(40);
                        }
                    }
                }
                // cursorMutex.unlock();              
            }
        }

        x1 = x2;
        y1 = y2;

        InGame::SquareCursor(x1, y1, WHITE);
        
        //Chọn (x1, y1)
        while (1)
        {
            if (thread1Finished)
                break;

            int button = ConsoleInput();

            if(color)
                InGame::SquareColor(x1, y1);
            else
                InGame::DeleteSquareCursor(x1, y1);
            if (matrix[x1][y1] == '.')
                InGame::DeleteSquare(x1, y1);

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
                thread1Finished = true;
                tracker = 1;
                return;
            }
            // Move Suggestion
            else if(button == 10)
            {
                if(color)
                {
                    InGame::SquareCursor(HintA.x, HintA.y, WHITE);
                    InGame::SquareCursor(HintB.x, HintB.y, WHITE);
                }
                else
                {
                    InGame::SquareCursor(HintA.x, HintA.y, GREEN);
                    InGame::SquareCursor(HintB.x, HintB.y, GREEN);
                }       

                cursorMutex.lock();
                int hint_second = (matrix_size - 3) * 4;

                t.minute -= (t.second - hint_second) < 0;
                t.second = (t.second - hint_second + 60) % 60;

                SetTextColor(red);
                int x = board_x + 4 + (matrix_size + 2) * 8 - 4 - 4 + 1 + 5;
                int y = board_y + 2;
                Cursor(x + (matrix_size * 4 + matrix_size / 2) / 2 - 3, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2);
                cout << "   - " << hint_second << "   ";
                SetTextColor(15);

                // t.minute -= (t.second - hint_second) < 0;
                // t.second = (t.second - hint_second + 60) % 60;
                Sleep(200);
                cursorMutex.unlock();
            }

            else if(button == 2729)
            {
                if(color)
                {
                    for (int i = 1; i <= matrix_size; i++)
                    {
                        for (int j = 1; j <= matrix_size; j++)
                        {
                            if(matrix[i][j] != '.')
                            {
                                InGame::DeleteSquareCursor(i, j);
                            }
                        }
                    }                
                    color = 0;
                }
                else 
                {
                    for (int i = 1; i <= matrix_size; i++)
                    {
                        for (int j = 1; j <= matrix_size; j++)
                        {
                            if(matrix[i][j] != '.')
                            {
                                InGame::SquareColor(i, j);
                            }
                        }
                    }
                    color = 1;
                }
            }
            InGame::SquareCursor(x1, y1, WHITE);
        }

        //Chọn (x2, y2)
        x2 = x1;
        y2 = y1;
        while (1)
        {
            if (thread1Finished)
                break;

            int button = ConsoleInput();

            if (x2 != x1 || y2 != y1)
            {
                if(color)
                    InGame::SquareColor(x2, y2);
                else
                    InGame::DeleteSquareCursor(x2, y2);
            }
            if (matrix[x2][y2] == '.')
                InGame::DeleteSquare(x2, y2);

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
            else if (button == 1 && (x2 != x1 || y2 != y1))
            {
                InGame::SquareCursor(x2, y2, WHITE);
                if(color)
                {
                    InGame::SquareColor(HintA.x, HintA.y);
                    InGame::SquareColor(HintB.x, HintB.y);
                }
                else
                {
                    InGame::DeleteSquareCursor(HintA.x, HintA.y);
                    InGame::DeleteSquareCursor(HintB.x, HintB.y);
                }
                break;
            }

            //Kiểm tra phím Backspace
            else if (button == -1)
            {
                x2 = -1;
                break;
            }

            //Kiểm tra phím Esc
            else if (button == 0)
            {
                thread1Finished = true;
                tracker = 1;
                return;
            }
            // Move Suggestion
            else if(button == 10)
            {
                if(color)
                {
                    InGame::SquareCursor(HintA.x, HintA.y, WHITE);
                    InGame::SquareCursor(HintB.x, HintB.y, WHITE);
                }
                else
                {
                    InGame::SquareCursor(HintA.x, HintA.y, GREEN);
                    InGame::SquareCursor(HintB.x, HintB.y, GREEN);
                }         

                cursorMutex.lock();
                int hint_second = (matrix_size - 3) * 4;

                t.minute -= (t.second - hint_second) < 0;
                t.second = (t.second - hint_second + 60) % 60;

                SetTextColor(red);
                int x = board_x + 4 + (matrix_size + 2) * 8 - 4 - 4 + 1 + 5;
                int y = board_y + 2;
                Cursor(x + (matrix_size * 4 + matrix_size / 2) / 2 - 3, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2);
                cout << "   - " << hint_second << "   ";
                SetTextColor(15);

                // t.minute -= (t.second - hint_second) < 0;
                // t.second = (t.second - hint_second + 60) % 60;
                Sleep(200);
                cursorMutex.unlock();  
            }

            else if(button == 2729)
            {
                if(color)
                {
                    for (int i = 1; i <= matrix_size; i++)
                    {
                        for (int j = 1; j <= matrix_size; j++)
                        {
                            if(matrix[i][j] != '.')
                            {
                                InGame::DeleteSquareCursor(i, j);
                            }
                        }
                    }                
                    color = 0;
                }
                else 
                {
                    for (int i = 1; i <= matrix_size; i++)
                    {
                        for (int j = 1; j <= matrix_size; j++)
                        {
                            if(matrix[i][j] != '.')
                            {
                                InGame::SquareColor(i, j);
                            }
                        }
                    }
                    color = 1;
                }
            }

            InGame::SquareCursor(x2, y2, WHITE);
        }
        if (x2 == -1)
        {
            x2 = x1;
            y2 = y1;
            continue;
        }
        
        if (InGame::CheckPath(x1, y1, x2, y2, matrix[x1][y1], 2, -1, -1))
        {
            InGame::SquareCursor(x1, y1, GREEN);
            InGame::SquareCursor(x2, y2, GREEN);

            Sleep(50);

            InGame::DeleteSquareCursor(x1, y1);
            InGame::DeleteSquareCursor(x2, y2);

            Advance::UpdateMatrix(x1, y1, x2, y2);
            if(color)
            {
                // if(x1 != x2)
                // {
                //     for(int j = y1; j <= lenList[x1]; j++)
                //         InGame::SquareColor(x1, j);
                //     for(int j = y2; j <= lenList[x2]; j++)
                //         InGame::SquareColor(x2, j);
                // }
                // else
                // {
                //     int temp = y2 > y1 ? y1 : y2;
                //     for(int j = temp; j <= lenList[x1]; j++)
                //         InGame::SquareColor(x1, j);
                // }

                for (int i = 1; i <= lenList[x1]; i++)
                    InGame::SquareColor(x1, i);
                for (int i = 1; i <= lenList[x2]; i++)
                    InGame::SquareColor(x2, i);
            }

            // InGame::SquareCursor(x2, y2, WHITE);
            cursorMutex.lock();
            int right_second = (matrix_size - 3);

            SetTextColor(green);
            int x = board_x + 4 + (matrix_size + 2) * 8 - 4 - 4 + 1 + 5;
            int y = board_y + 2;
            Cursor(x + (matrix_size * 4 + matrix_size / 2) / 2 - 3, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2);
            cout << "   + " << right_second << "   ";
            SetTextColor(15);

            t.minute += (t.second + right_second) > 60;
            t.second = (t.second + right_second) % 60;
            Sleep(200);
            cursorMutex.unlock();

            count += 2;
        }
        else
        {
            InGame::SquareCursor(x1, y1, RED);
            InGame::SquareCursor(x2, y2, RED);

            Sleep(50);
            if(color)
            {
                InGame::SquareColor(x1, y1);
                InGame::SquareColor(x2, y2);
            }
            else
            {
                InGame::DeleteSquareCursor(x1, y1);
                InGame::DeleteSquareCursor(x2, y2);
            }

            cursorMutex.lock();
            int hint_second = (matrix_size - 3) * 2;

            t.minute -= (t.second - hint_second) < 0;
            t.second = (t.second - hint_second + 60) % 60;
            
            SetTextColor(red);
            int x = board_x + 4 + (matrix_size + 2) * 8 - 4 - 4 + 1 + 5;
            int y = board_y + 2;
            Cursor(x + (matrix_size * 4 + matrix_size / 2) / 2 - 3, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2);
            cout << "   - " << hint_second << "   ";
            SetTextColor(15);
                
            Sleep(200);
            cursorMutex.unlock();  
        }

        if (count == matrix_size * matrix_size)
        {
            thread1Finished = true;
            tracker = 2;
            Sleep(1000);
            // InGame::DrawFinish(matrix_size);
            break;
        }
    }
}

void threadTimeAdvance() {

    int x = 5 + 4 + (matrix_size + 2) * 8 - 4 - 4 + 1 + 5;
    int y = 5 + 2;

    while(1)
    {
        if (thread1Finished) {
            break;
        }

        cursorMutex.lock();  


        InGame::CountingTime(x + (matrix_size * 4 + matrix_size / 2) / 2 - 2, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2, t);
        cursorMutex.unlock();  

        if(t.hour == 0 && t.minute == 0 && t.second == 10)
        {
            SoundOff();
            SoundOn("ticktock");
        }

        if(t.hour == 0 && t.minute < 0)
        {
            SoundOff();
            SoundOn("reng");
            thread1Finished = true;    
            Cursor(x + (matrix_size * 4 + matrix_size / 2) / 2 - 3, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2);
            std::cout << "You lose!!!";
            InGame::DrawTimeUp(matrix_size);
            tracker = -2;
            break;
        }

        Sleep(1000);
    }
}


void Advance::AdvanceGame(int size)
{
    system("cls");
    SoundOff();
    if(size == 4)
        SoundOn("play1");
    else if(size == 6)
        SoundOn("play2");
    else if(size == 8)
        SoundOn("play3");

    int temp_color = (size == 4)*light_green + (size == 6)*light_yellow + (size == 8)*light_red;
    SetTextColor(temp_color);
    InGame::DrawGameBoard(size, 2 * size - 2);

    SetTextColor(temp_color);
    InGame::DrawTime(size);

    SetTextColor(temp_color);
    InGame::DrawGuide(size);
    
    InGame::CreateBackground(size);
    Advance::CreateList();

    HintA.x = -1;
    HintA.y = -1;
    HintB.x = -1;
    HintB.y = -1;

    int minute = size - 3;
    t.hour = 0;
    t.minute = minute;
    t.second = 0;

    thread t1(threadMoveAdvance);
    Sleep(500);
    thread t2(threadTimeAdvance);

    t1.join();
    t2.join();

    DeleteMatrix();
    DeleteBackground();
    DeleteList();

    if (thread1Finished) {
        thread1Finished = false;
    }
    if(tracker == 1)
    {
        SoundOff();
        SoundOn("menu");
        tracker = 0;
        return;
    }
}


void Advance::AdEasy()
{
    Advance::AdvanceGame(4);
    system("cls");

    if (tracker == 2)
    {
        SoundOff();
        SoundOn("winner");
        ReadScoreAdvance();
        
        Score you;
        you.time = t;
        you.name = username;
        you.ID = userID;

        ad_easy[8].time = t;
        ad_easy[8].name = username;
        ad_easy[8].ID = userID;

        RearrangeScore(ad_easy);

        SetTextColor(light_green);
        DrawUserboard("RESULT", you, ad_easy, 20, 11);
        SetTextColor(light_green);
        DrawLeaderboard("LEADERBOARD", you ,ad_easy, 20 + 50, 11);

        UpdateScoreAdvance();

        _getch();
    }
    else if (tracker == -2)
    {
        SoundOff();
        SoundOn("loser");
        ReadScoreAdvance();
        
        Score you;
        you.time.hour = 0;
        you.time.minute = 0;
        you.time.second = 0;
        you.name = username;
        you.ID = userID;

        SetTextColor(light_green);
        DrawUserboard("RESULT", you, ad_easy, 20, 11);
        SetTextColor(light_green);
        DrawLeaderboard("LEADERBOARD", you ,ad_easy, 20 + 50, 11);

        _getch();
    }

    tracker = 0;
    SoundOff();
    SoundOn("menu");
}

void Advance::AdMedium()
{
    Advance::AdvanceGame(6);
    system("cls");

    if (tracker == 2)
    {
        SoundOff();
        SoundOn("winner");
        ReadScoreAdvance();
        
        Score you;
        you.time = t;
        you.name = username;
        you.ID = userID;

        ad_medium[8].time = t;
        ad_medium[8].name = username;
        ad_medium[8].ID = userID;

        RearrangeScore(ad_medium);

        SetTextColor(light_yellow);
        DrawUserboard("RESULT", you, ad_medium, 20, 11);
        SetTextColor(light_yellow);
        DrawLeaderboard("LEADERBOARD", you ,ad_medium, 20 + 50, 11);

        UpdateScoreAdvance();

        _getch();
    }
    else if (tracker == -2)
    {
        SoundOff();
        SoundOn("loser");
        ReadScoreAdvance();
        
        Score you;
        you.time.hour = 0;
        you.time.minute = 0;
        you.time.second = 0;
        you.name = username;
        you.ID = userID;

        SetTextColor(light_green);
        DrawUserboard("RESULT", you, ad_medium, 20, 11);
        SetTextColor(light_green);
        DrawLeaderboard("LEADERBOARD", you ,ad_medium, 20 + 50, 11);

        _getch();
    }

    tracker = 0;
    SoundOff();
    SoundOn("menu");
}

void Advance::AdHard()
{
    Advance::AdvanceGame(8);
    system("cls");

    if (tracker == 2)
    {
        SoundOff();
        SoundOn("winner");
        ReadScoreAdvance();
        
        Score you;
        you.time = t;
        you.name = username;
        you.ID = userID;

        ad_hard[8].time = t;
        ad_hard[8].name = username;
        ad_hard[8].ID = userID;

        RearrangeScore(ad_hard);

        SetTextColor(light_red);
        DrawUserboard("RESULT", you, ad_hard, 20, 11);
        SetTextColor(light_red);
        DrawLeaderboard("LEADERBOARD", you ,ad_hard, 20 + 50, 11);

        UpdateScoreAdvance();

        _getch();
    }
    else if (tracker == -2)
    {
        SoundOff();
        SoundOn("loser");
        ReadScoreAdvance();
        
        Score you;
        you.time.hour = 0;
        you.time.minute = 0;
        you.time.second = 0;
        you.name = username;
        you.ID = userID;

        SetTextColor(light_green);
        DrawUserboard("RESULT", you, ad_hard, 20, 11);
        SetTextColor(light_green);
        DrawLeaderboard("LEADERBOARD", you ,ad_hard, 20 + 50, 11);

        _getch();
    }

    tracker = 0;
    SoundOff();
    SoundOn("menu");
}

void ReadScoreAdvance()
{
    ifstream ifs;
    ifs.open("advance.txt");

    string temp;
    
    //Nhap diem Advance Easy
    ifs >> temp;
    for (int i = 0; i < 8; i++)
    {
        ifs >> ad_easy[i].time.hour >> ad_easy[i].time.minute >> ad_easy[i].time.second;
        ifs >> ad_easy[i].name >> ad_easy[i].ID;
    }

    //Nhap diem Advance Medium
    ifs >> temp;
    for (int i = 0; i < 8; i++)
    {
        ifs >> ad_medium[i].time.hour >> ad_medium[i].time.minute >> ad_medium[i].time.second;
        ifs >> ad_medium[i].name >> ad_medium[i].ID;
    }

    //Nhap diem Advance Hard
    ifs >> temp;
    for (int i = 0; i < 8; i++)
    {
        ifs >> ad_hard[i].time.hour >> ad_hard[i].time.minute >> ad_hard[i].time.second;
        ifs >> ad_hard[i].name >> ad_hard[i].ID;
    }

    ifs.close();
}

void UpdateScoreAdvance()
{
    ofstream ofs("advance.txt", ofstream::trunc);
    
    ofs << "EASY\n";
    for (int i = 0; i < 8; i++)
    {
        ofs << ad_easy[i].time.hour << " " 
            << ad_easy[i].time.minute << " "
            << ad_easy[i].time.second << " "
            << ad_easy[i].name << " "
            << ad_easy[i].ID << endl;
    }

    ofs << "MEDIUM\n";
    for (int i = 0; i < 8; i++)
    {
        ofs << ad_medium[i].time.hour << " " 
            << ad_medium[i].time.minute << " "
            << ad_medium[i].time.second << " "
            << ad_medium[i].name << " "
            << ad_medium[i].ID << endl;
    }

    ofs << "HARD\n";
    for (int i = 0; i < 8; i++)
    {
        ofs << ad_hard[i].time.hour << " " 
            << ad_hard[i].time.minute << " "
            << ad_hard[i].time.second << " "
            << ad_hard[i].name << " "
            << ad_hard[i].ID << endl;
    }

    ofs.close();
}

