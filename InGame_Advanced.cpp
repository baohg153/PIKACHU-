#include "InGame.h"

List *arrList;
extern char** matrix;
extern int matrix_size;


void Advance::CreateList()
{
    arrList = new List[matrix_size + 1];
    for(int i = 1; i <= matrix_size; i++)
    {
        for(int j = 1; j <= matrix_size; j++)
        {
            if(j != 1)
            {
                Node *pCurr = arrList[i].head;
                while(pCurr->next)
                    pCurr = pCurr->next;
                pCurr->next = new Node;
                pCurr = pCurr->next;
                pCurr->data = matrix[i][j];
                pCurr->next = NULL;
                arrList[i].tail = pCurr;
            }
            else
            {
                arrList[i].head = new Node;
                arrList[i].head->data = matrix[i][j];
                arrList[i].head->next = NULL;
                arrList[i].tail = arrList[i].head;
            }
        }
    }
}