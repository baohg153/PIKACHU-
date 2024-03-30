#include "InGame.h"
#include <string>
#include <fstream>
#include <iomanip>

char** matrix;
extern Node **arrList;
extern int* lenList;
int matrix_size;
string* background;
Point HintA;
Point HintB;


void print(int size)
{
    for (int i = 0; i < size + 2; i++)
    {
        for (int j = 0; j < size + 2; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }      
}

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
bool InGame::CheckPath(int i, int j, int x, int y, char c, int eco = 2, int prei = -1, int prej = -1)
{   
    int n = matrix_size;

    char temp = matrix[i][j];
    matrix[i][j] = '*';

    if(i == x && j == y)
    {
        matrix[i][j] = temp;
        return true;
    }

    bool found = 0;
    int tracker = 0;
    for(int k = 0; k < 4; k++)
    {
        int it = i + dx[k];
        int jt = j + dy[k];

        if(it >= 0 && it <= n + 1 && jt >= 0 && jt <= n + 1 && (matrix[it][jt] == '.' || matrix[it][jt] == c))
        {
            if(matrix[it][jt] == c && (it != x || jt != y))
                continue;
            int tempi = prei;
            int tempj = prej;
            if(prei == -1 && prej == -1 )
            {
                prei = it;
                prej = jt;
            }
            if(prei != it && prej != jt)
            {
                eco--;
                tracker = 1;
            }
            if(eco < 0)
            {
                eco++;
                tracker = 0;
                continue;
            }
            prei = i;
            prej = j;
            if (InGame::CheckPath(it, jt, x, y, c, eco, prei, prej))
                found = 1;
            if(tracker)
            {
                eco++;
                tracker = 0;
            }
            prei = tempi;
            prej = tempj;
        }
    }
    matrix[i][j] = temp;
    if (found)
        return found;
    return false;
}

void InGame::CreateMatrix(int size, int num)
{
    matrix_size = size;
    matrix = new char* [size + 2];
    for (int i = 0; i < size + 2; i++)
        matrix[i] = new char [size + 2];
    
    srand(time(NULL));
    char* matrix_line = new char [size * size];
    for (int i = 0; i < size * size; i += 2)
    {
        char temp = static_cast<char>(65 + rand() % num);
        matrix_line[i] = temp;
        matrix_line[i + 1] = temp;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(matrix_line, matrix_line + size*size, g);
    
    for (int i = 0; i < size + 2; i++)
    {
        matrix[i][0] = '.';
        matrix[i][size + 1] = '.';
    }

    for (int j = 0; j < size + 2; j++)
    {
        matrix[0][j] = '.';
        matrix[size + 1][j] = '.';
    }

    int index = 0;
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            matrix[i][j] = matrix_line[index++];
    
    delete [] matrix_line;
}

void DeleteMatrix()
{
    for (int i = 0; i < matrix_size + 2; i++)
        delete [] matrix[i];
    
    delete [] matrix;
}

void DeleteBackground()
{
    delete [] background;
}

void DeleteList()
{
    for(int i = 1; i <= matrix_size; i++)
    { 
        while(arrList[i])
        {
            Node* pCurr = arrList[i];
            arrList[i] = pCurr->next;
            delete pCurr;
            pCurr = NULL; 
        }
    }
    delete[] arrList;
}


void InGame::CreateBackground(int n)
{
    ifstream bg;
    if(n == 4)
        bg.open("easy.txt");
    else if(n == 6)
        bg.open("medium.txt");
    else if(n == 8)
        bg.open("hard.txt");
        
	background = new string[matrix_size * matrix_size + 1];
    int i = 0;
    while(!bg.eof())
    {
        string line;
        getline(bg, line);
        background[i] = line;
        i++;
    }
    bg.close();
}

void InGame::CountingTime(int x, int y, Time &t)
{
    Cursor(x, y);
    cout << setfill('0') << setw(2) << t.hour << ":";
    cout << setfill('0') << setw(2) << t.minute << ":";
    cout << setfill('0') << setw(2) << t.second--;
    if(t.second == -1)
    {
        if(t.minute > 0)
        {    
            t.second = 59;    
            t.minute--;
        }
        else if(t.hour > 0)
        {
            t.second = 59;
            t.minute = 59;
            t.hour--;
        }
    }
}

bool InGame::AutomaticallyFinding(int row, int col)
{
    Point a, b;
    for(int i = 1; i <= row; i++)
    {
        a.x = i;
        for(int j = 1; j <= col; j++)
        {
            a.y = j;
            if(matrix[a.x][a.y] != '.')
            {
                for(int k = 1; k <= row; k++)
                {
                    b.x = k;
                    for(int h = 1; h <= col; h++)
                    {
                        b.y = h;
                        if(a.x != b.x || a.y != b.y)
                        {
                            if(matrix[a.x][a.y] == matrix[b.x][b.y])
                            {
                                if(InGame::CheckPath(a.x, a.y, b.x, b.y, matrix[a.x][a.y] ,2, -1, -1))
                                {
                                    HintA.x = a.x;
                                    HintA.y = a.y;

                                    HintB.x = b.x;
                                    HintB.y = b.y;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void InGame::ShuffleBoard(int row, int col, unsigned int seed)
{
    // NHO KHAI BAO THU VIEN RANDOM 
    // Cú pháp khi sử dụng
    /*
        random_device rd;
        shuffleBoard(n, n, rd());
    */
    int valid_box = 0;
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            if(matrix[i][j] != '.')
                valid_box++;
        }
    }

    char* used_char = new char[valid_box];
    int k = 0;
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            if(matrix[i][j] != '.')
            {
                used_char[k++] = matrix[i][j];
            }
        }
    }

	k = 0;
    mt19937 g(seed);
	shuffle(used_char, used_char + valid_box,g);
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			if (matrix[i][j] != '.')
			{
				matrix[i][j] = used_char[k++];
			}
		}
	}
    // Delete array 
    delete[] used_char;
}

bool CompareScore(Score S1, Score S2)
{
    int time1 = (S1.time.hour) * 3600 + (S1.time.minute) * 60 + (S1.time.second);
    int time2 = (S2.time.hour) * 3600 + (S2.time.minute) * 60 + (S2.time.second);
    return (time1 >= time2);
}

void RearrangeScore(Score S[])
{
    sort(S, S+9, CompareScore);
}
