#include "InGame.h"

char** matrix;
int matrix_size;

//bool checkPath(int i, int j, int x, int y, int eco, int prei, int prej, char c);

void CreateMatrix(int size)
{
    matrix_size = size;
    matrix = new char* [size];
    for (int i = 0; i < size; i++)
        matrix[i] = new char [size];
    
    srand(time(NULL));
    char* matrix_line = new char [size * size];
    int num = 7;
    for (int i = 0; i < size * size; i+= 2)
    {
        char temp = static_cast<char>(65 + rand() % num);
        matrix_line[i] = temp;
        matrix_line[i + 1] = temp;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(matrix_line, matrix_line + size*size, g);

    int index = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = matrix_line[index++];
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    delete [] matrix_line;
    for (int i = 0; i < size; i++)
        delete [] matrix[i];
    delete [] matrix;
}

// void Classic::Easy()
// {
//     cout << 1;
// }