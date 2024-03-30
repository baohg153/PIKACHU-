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
                random_device rd;
                InGame::ShuffleBoard(matrix_size, matrix_size, rd());
                Advance::CopyList();
                // cursorMutex.lock(); 
                for (int i = 1; i <= matrix_size; i++)
                {
                    for (int j = 1; j <= matrix_size; j++)
                    {
                        std::lock_guard<std::mutex> lock(cursorMutex);
                        Cursor(8*j + board_x + 5, 4*i + board_y + 2);
                        if(matrix[i][j] != '.')
                        {
                            std::cout << matrix[i][j];
                            Sleep(200);
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
            int button = ConsoleInput();

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
                InGame::SquareCursor(HintA.x, HintA.y, GREEN);
                InGame::SquareCursor(HintB.x, HintB.y, GREEN);       
            }

            InGame::SquareCursor(x1, y1, WHITE);
        }

        //Chọn (x2, y2)
        x2 = x1;
        y2 = y1;
        while (1)
        {
            int button = ConsoleInput();

            if (x2 != x1 || y2 != y1)
                InGame::DeleteSquareCursor(x2, y2);
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
                InGame::DeleteSquareCursor(HintA.x, HintA.y);
                InGame::DeleteSquareCursor(HintB.x, HintB.y); 
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
                InGame::SquareCursor(HintA.x, HintA.y, GREEN);
                InGame::SquareCursor(HintB.x, HintB.y, GREEN);       
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
            // matrix[x1][y1] = '.';
            // matrix[x2][y2] = '.';

            InGame::SquareCursor(x1, y1, GREEN);
            InGame::SquareCursor(x2, y2, GREEN);

            Sleep(50);
            
            InGame::DeleteSquareCursor(x1, y1);
            InGame::DeleteSquareCursor(x2, y2);

            Advance::UpdateMatrix(x1, y1, x2, y2);

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
            thread1Finished = true;
            Sleep(1000);
            InGame::DrawFinish(matrix_size);
            break;
        }
    }
}

void threadTimeAdvance() {
    Time t;
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

        if(t.hour == 0 && t.minute == 0 && t.second == -1)
        {
            Cursor(x + (matrix_size * 4 + matrix_size / 2) / 2 - 3, y + 2 + (matrix_size + matrix_size / 2  - 3) / 2);
            thread1Finished = true;
            std::cout << "You lose!!!";
            break;
        }

        Sleep(1000);
    }
}


void Advance::AdvanceGame(int size)
{
    system("cls");
    InGame::DrawGameBoard(size, 2 * size - 2);
    InGame::DrawTime(size);
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
    if(tracker)
    {
        tracker = 0;
        return;
    }
}


void Advance::AdEasy()
{
    Advance::AdvanceGame(4);
}

void Advance::AdMedium()
{
    Advance::AdvanceGame(6);
}

void Advance::AdHard()
{
    Advance::AdvanceGame(8);
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

