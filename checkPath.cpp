#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
char arr[100][100];
int n;

struct Point{
    int x;
    int y;
};

void setRandom(char arr[][100], int n, int frequency[])
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            arr[i][j] = char(rand() % (67 - 65 + 1) + 65);
            while(frequency[(int(arr[i][j]) - 65)] <= 0)
                arr[i][j] = char(rand() % (67 - 65 + 1) + 65);
            frequency[(int(arr[i][j]) - 65)]--;
        }
    }

    for(int i = 0; i <= n; i++)
    {  
        arr[0][i] = '.';
        arr[i][0] = '.';
        arr[i][n + 1] = '.';
        arr[n + 1][i] = '.';
    }
    arr[n + 1][n + 1] = '.';
}

void printArray(char a[][100], int n)
{
    for(int i = 0; i <= n + 1; i++)
    {
        for(int j = 0; j <= n + 1; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool checkPath(int i, int j, int x, int y, int eco, int prei, int prej, char c)
{
    
    char temp = arr[i][j];
    arr[i][j] = '*';

    if(i == x && j == y)
    {
        cout << "YES" << endl;
        printArray(arr, n);
        arr[i][j] = temp;
        return true;
    }

    bool found = 0;
    int tracker = 0;
    for(int k = 0; k < 4; k++)
    {
        int it = i + dx[k];
        int jt = j + dy[k];

        if(it >= 0 && it <= n + 1 && jt >= 0 && jt <= n + 1 && (arr[it][jt] == '.' || arr[it][jt] == c))
        {
            if(arr[it][jt] == c && (it != x || jt != y))
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
            if (checkPath(it, jt, x, y, eco, prei, prej, c))
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
    arr[i][j] = temp;
    if (found)
        return found;
    return false;
}

bool automatically_finding(int row, int col)
{
    Point a, b;
    for(int i = 1; i <= row; i++)
    {
        a.x = i;
        for(int j = 1; j <= col; j++)
        {
            a.y = j;
            if(arr[a.x][a.y] != '.')
            {
                for(int k = 1; k <= row; k++)
                {
                    b.x = k;
                    for(int h = 1; h <= col; h++)
                    {
                        b.y = h;
                        if(a.x != b.x || a.y != b.y)
                        {
                            if(arr[a.x][a.y] == arr[b.x][b.y])
                            {
                                if(checkPath(a.x, a.y, b.x, b.y, 2, -1, -1, arr[a.x][a.y]))
                                {
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



void shuffleBoard(int row, int col, unsigned int seed)
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
            if(arr[i][j] != '.')
                valid_box++;
        }
    }

    char* used_char = new char[valid_box];
    int k = 0;
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            if(arr[i][j] != '.')
            {
                used_char[k++] = arr[i][j];
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
			if (arr[i][j] != '.')
			{
				arr[i][j] = used_char[k++];
			}
		}
	}
    // Delete array 
    delete[] used_char;
}




int main() {
    srand(time(NULL));

    cin >> n;
    
    int countN = (n * n) / 3;
    int frequency[3] = {countN, countN, countN};
    setRandom(arr, n, frequency);
    printArray(arr, n);
    while(1)
    {
        int i, j, x, y;
        cin >> i >> j >> x >> y;
        int eco = 2;
        if(checkPath(i, j, x, y, eco, - 1, - 1, arr[i][j]))
        {
            arr[i][j] = '.';
            arr[x][y] = '.';
        }
        cout << "---------------------------" << endl;
        printArray(arr, n);
    }

    return 0;
}

