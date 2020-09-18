//Juan Gonzalez
//Sudokode
//1/24/16
//Cop 3223


#include <stdio.h>
#include <stdlib.h>
#define SIZE 9

int fill2DArr(int ***, int, int);//fills one board with all values from cmd using its column & row sizes respectively
int checkCol(int **, int, int);//checks all columns for repetition needs column and row
int checkRow(int **, int, int);//checks all rows for repetition needs column and row
int checkSub(int **, int, int);//checks 3x3 sections for repetition needs column and row
void free2D(int **, int);//frees the memory in a 2d array needs size of array

int main()
{
    int n=0;//holds test cases
    int ** SoduBoard;//sudoku board 2d array

    scanf("%d \n",&n);// gets test cases
    while(n>0)//runs through all test cases
    {
        SoduBoard= NULL;
        fill2DArr(&SoduBoard, SIZE,SIZE);
        //checks for a valid sudoku board
        if( checkRow(SoduBoard,SIZE,SIZE) &&
            checkCol(SoduBoard,SIZE,SIZE) &&
            checkSub(SoduBoard,SIZE,SIZE))
        {
            printf("YES \n");
        }
        else
        {
            printf("NO \n");
        }
        free2D(SoduBoard,SIZE);//frees at end to fill with new array
        n--;
    }
}

int fill2DArr(int *** arr,int row,int col)
{
    int i=0,n=0;// counters of column & row position respectively
    int **tempArr= NULL;//temporary array to make changes to
    char some;

    tempArr = (int **)calloc( sizeof(int*), row );//fill first dimension

    for(i=0;i<row;i++)
    {
        tempArr[i]= (int *)calloc( sizeof(int), col );//fills second dimension

        for(n=0; n<col;n++)
        {
           scanf("%c /n",&(some));//sets values of array
           tempArr[i][n]=(some-'0');
        }
    }
    *arr=tempArr;//assigns the temporary to the permanent array
}

int checkCol(int ** arr,int row, int col)
{
    int i, n;// counters of row & column position respectively
    int *freArr = calloc(sizeof(int), col);//frequency array set to the size of column

    for(i=0;i<row;i++)//go through each row
    {
        for(n=0;n<col;n++)//go throw the columns
        {
            freArr[arr[i][n]-1]++;//set frequency of each number in array
        }

        for(i=0;i<col;i++)
        {
            if(freArr[i]>1)// check that each numbered did not repeat
            {
                free(freArr);//free the frequency
                return 0;//false
            }
        }
    }
    free(freArr);
    return 1;//all columns check out
}

int checkRow(int ** arr,int row, int col)
{
    int i, n;// counters of row & column position respectively
    int *freArr = calloc(sizeof(int), row);//frequency array set to the size of row
    for(n=0;n<col;n++)//go through the columns
    {
        for(i=0;i<row;i++)//go through each row
        {
            freArr[arr[i][n]-1]++;//set frequency of each number in array
        }
        for(i=0;i<row;i++)//test frequency
        {
            if(freArr[i]>1)
            {
                free(freArr);
                return 0;
            }
            freArr[i]=0;//reset frequency
        }
    }

    free(freArr);
    return 1;
}

int checkSub(int ** arr,int row, int col)
{
    int i, n, i2, n2;//column, row, sub-column, sub-row
    int *freArr = calloc(sizeof(int), SIZE);

    for(i=0;i<col;i+=3)//position on correct column
    {
        for(n=0;n<row;n+=3)//positions on correct row
        {
            for(i2=i;i2<i+3;i2++)//goes through sub-column
            {
                for(n2=n;n2<n+3;n2++)//goes through sub-row
                {
                    freArr[arr[n2][i2]-1]++;//frequency array assigned frequencies based on values read
                }
            }

            for(i2=0; i2<SIZE; i2++)//tests if each sub section holds
            {
                if(freArr[i2]>1)
                {
                    free(freArr);
                    return 0;
                }
                freArr[i2]=0;//reset frequency
            }
        }
    }
    free(freArr);
    return 1;

}

void free2D(int ** arr, int row)
{
    for(row--; row>0; row--)//free all columns
    {
        free(arr[row]);
    }
    free(arr);//free all rows
}
