#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct
{
    uint8_t **arr;
    size_t len;
    size_t boxlen;
} Sudoku;

void initSudoku(Sudoku *sd, size_t size)
{
    sd->len = size;
    sd->boxlen = floor(sqrt(size));
    sd->arr = (uint8_t **)calloc(size, sizeof(uint8_t *));
    for (int i = 0; i < size; ++i)
    {

        sd->arr[i] = (uint8_t *)calloc(size, sizeof(uint8_t));
    }
}

void printSudoku(Sudoku *sd)
{
    for (size_t x = 0; x < sd->len; x++)
    {
        if (x % 3 == 0)
        {
            printf("\n");
        }
        for (size_t y = 0; y < sd->len; y++)
        {
            if (y % 3 == 0)
            {
                printf(" ");
            }
            if (sd->arr[x][y] == 0)
            {
                printf("_ ");
            }
            else
            {
                printf("%d ", sd->arr[x][y]);
            }
        }
        printf("\n");
    }
}

void copySudoko(Sudoku *sd_dest, Sudoku *sd_source)
{
    for (size_t x = 0; x < sd_dest->len; x++)
    {
        for (size_t y = 0; y < sd_dest->len; y++)
        {
            sd_dest->arr[x][y] = sd_source->arr[x][y];
        }
    }
}

void fillWithExampleSodoku(Sudoku *sd)
{
    sd->arr[0][0] = 0;
    sd->arr[0][1] = 9;
    sd->arr[0][2] = 4;
    sd->arr[0][3] = 2;
    sd->arr[0][4] = 0;
    sd->arr[0][5] = 6;
    sd->arr[0][6] = 0;
    sd->arr[0][7] = 8;
    sd->arr[0][8] = 0;

    sd->arr[1][0] = 6;
    sd->arr[1][1] = 0;
    sd->arr[1][2] = 1;
    sd->arr[1][3] = 8;
    sd->arr[1][4] = 0;
    sd->arr[1][5] = 4;
    sd->arr[1][6] = 2;
    sd->arr[1][7] = 3;
    sd->arr[1][8] = 9;

    sd->arr[2][0] = 0;
    sd->arr[2][1] = 7;
    sd->arr[2][2] = 0;
    sd->arr[2][3] = 3;
    sd->arr[2][4] = 9;
    sd->arr[2][5] = 1;
    sd->arr[2][6] = 0;
    sd->arr[2][7] = 6;
    sd->arr[2][8] = 0;

    sd->arr[3][0] = 0;
    sd->arr[3][1] = 6;
    sd->arr[3][2] = 5;
    sd->arr[3][3] = 0;
    sd->arr[3][4] = 2;
    sd->arr[3][5] = 0;
    sd->arr[3][6] = 8;
    sd->arr[3][7] = 4;
    sd->arr[3][8] = 0;

    sd->arr[4][0] = 9;
    sd->arr[4][1] = 0;
    sd->arr[4][2] = 0;
    sd->arr[4][3] = 6;
    sd->arr[4][4] = 0;
    sd->arr[4][5] = 5;
    sd->arr[4][6] = 0;
    sd->arr[4][7] = 0;
    sd->arr[4][8] = 1;

    sd->arr[5][0] = 0;
    sd->arr[5][1] = 2;
    sd->arr[5][2] = 3;
    sd->arr[5][3] = 0;
    sd->arr[5][4] = 1;
    sd->arr[5][5] = 0;
    sd->arr[5][6] = 9;
    sd->arr[5][7] = 5;
    sd->arr[5][8] = 0;

    sd->arr[6][0] = 0;
    sd->arr[6][1] = 8;
    sd->arr[6][2] = 0;
    sd->arr[6][3] = 1;
    sd->arr[6][4] = 6;
    sd->arr[6][5] = 2;
    sd->arr[6][6] = 0;
    sd->arr[6][7] = 9;
    sd->arr[6][8] = 0;

    sd->arr[7][0] = 2;
    sd->arr[7][1] = 3;
    sd->arr[7][2] = 9;
    sd->arr[7][3] = 5;
    sd->arr[7][4] = 0;
    sd->arr[7][5] = 7;
    sd->arr[7][6] = 6;
    sd->arr[7][7] = 0;
    sd->arr[7][8] = 8;

    sd->arr[8][0] = 0;
    sd->arr[8][1] = 1;
    sd->arr[8][2] = 0;
    sd->arr[8][3] = 9;
    sd->arr[8][4] = 0;
    sd->arr[8][5] = 3;
    sd->arr[8][6] = 4;
    sd->arr[8][7] = 7;
    sd->arr[8][8] = 0;
}
bool checkIfFree(Sudoku *sd, uint8_t numbr, size_t zeile, size_t spalte)
{
    size_t boxIndex[2] = {zeile / sd->boxlen, spalte / sd->boxlen};

    if (sd->arr[zeile][spalte] != 0)
    {
        return false;
    }

    for (size_t i = 0; i < sd->len; i++)
    {
        //Zeile
        if (sd->arr[zeile][i] == numbr)
        {
            return false;
        }

        //Spalte
        if (sd->arr[i][spalte] == numbr)
        {
            return false;
        }
    }
    //Box
    for (size_t i = sd->boxlen * boxIndex[0]; i < sd->boxlen * boxIndex[0] + sd->boxlen; i++)
    {
        for (size_t j = sd->boxlen * boxIndex[1]; j < sd->boxlen * boxIndex[1] + sd->boxlen; j++)
        {
            if (sd->arr[i][j] == numbr)
            {
                return false;
            }
        }
    }
    return true;
}

bool checkSudokuZeros(Sudoku *sd)
{
    for (size_t i = 0; i < sd->len; i++)
    {
        for (size_t j = 0; j < sd->len; j++)
        {
            if (sd->arr[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(Sudoku *sd)
{
    int errCount = 0;
    int nmbrCount = 0;
    uint8_t nmbr = 0;

    while (!checkSudokuZeros(sd))
    {
        for (size_t i = 0; i < sd->len; i++)
        {
            for (size_t j = 0; j < sd->len; j++)
            {
                if (sd->arr[i][j] == 0)
                {
                    nmbrCount = 0;

                    for (size_t k = 1; k <= sd->len; k++)
                    {
                        if (i == 0 && j == 3)
                        {
                        }
                        if (checkIfFree(sd, k, i, j))
                        {
                            nmbr = k;
                            nmbrCount++;
                        }
                    }

                    if (nmbrCount == 1)
                    {
                       
                        sd->arr[i][j] = nmbr;
                    }
                }
            }
        }
        errCount++;
        if (errCount > 100)
        {
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    Sudoku sd;
    initSudoku(&sd, 9);
    fillWithExampleSodoku(&sd);
    printSudoku(&sd); 

    solveSudoku(&sd);
    printf("Solve Finnish\n");
    printSudoku(&sd);
    printf("\n");
    //printSudoku(&sd);

    return 0;
}
