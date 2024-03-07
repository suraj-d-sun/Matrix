#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int main()
{
    int size = 10;
    int **x = (int **)malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++)
    {
        x[i] = (int *)malloc(sizeof(int) * size);
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            x[i][j] = i * j;
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << setw(4) << x[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < size; i++)
    {
        free(x[i]);
    }
    free(x);
    return 0;
}