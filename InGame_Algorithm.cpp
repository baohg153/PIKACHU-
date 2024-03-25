#include "InGame.h"

char** matrix;
int matrix_size;

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
        print(n);
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

void InGame::CreateMatrix(int size)
{
    matrix_size = size;
    matrix = new char* [size + 2];
    for (int i = 0; i < size + 2; i++)
        matrix[i] = new char [size + 2];
    
    srand(time(NULL));
    char* matrix_line = new char [size * size];
    int num = 7;
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


