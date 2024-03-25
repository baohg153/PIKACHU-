#include "InGame.h"

// bool checkPath(int i, int j, int x, int y, int eco, int prei, int prej, char c)
// {
    
//     char temp = b[i][j];
//     b[i][j] = '*';

//     if(i == x && j == y)
//     {
//         cout << "YES" << endl;
//         printArray(b, n);
//         b[i][j] = temp;
//         return true;
//     }

//     bool found = 0;
//     int tracker = 0;
//     for(int k = 0; k < 4; k++)
//     {
//         int it = i + dx[k];
//         int jt = j + dy[k];

//         if(it >= 0 && it <= n + 1 && jt >= 0 && jt <= n + 1 && (b[it][jt] == '.' || b[it][jt] == c))
//         {
//             if(b[it][jt] == c && (it != x || jt != y))
//                 continue;
//             int tempi = prei;
//             int tempj = prej;
//             if(prei == -1 && prej == -1 )
//             {
//                 prei = it;
//                 prej = jt;
//             }
//             if(prei != it && prej != jt)
//             {
//                 eco--;
//                 tracker = 1;
//             }
//             if(eco < 0)
//             {
//                 eco++;
//                 tracker = 0;
//                 continue;
//             }
//             prei = i;
//             prej = j;
//             if (checkPath(it, jt, x, y, eco, prei, prej, c))
//                 found = 1;
//             if(tracker)
//             {
//                 eco++;
//                 tracker = 0;
//             }
//             prei = tempi;
//             prej = tempj;
//         }
//     }
//     b[i][j] = temp;
//     if (found)
//         return found;
//     return false;
// }