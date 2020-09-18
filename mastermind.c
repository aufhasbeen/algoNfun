//Juan Gonzalez
#include <stdlib.h>
#include <stdio.h>

int** feedback;//array of current guesses
int correct=0,//correct possibilities
    n,//number of pegs
    m;//number of guesses

int** buildGrid(int ,int );//dynamic grid, reads in inputs as well
void speedometer(int* ,int ,int );//basic speedometer code for all possible combos
int whiteCheck(int* ,int );//checks white count... but its really the total
int blackCheck(int* );//checks black count

int main()
{
    int tests,
        k,//number of colors
        i;
    int* tempArray;//used to kick off speedometer

    scanf("%d",&tests);//scan in amount to test

    while(tests)
    {
        scanf("%d %d %d", &n, &k, &m);

        tempArray= calloc(sizeof(int), n+2);//calloc used for zeroing too
        feedback=buildGrid(m,n+2);//insert values for guesses
        speedometer(tempArray,n,k);

        tests--;

        printf("%d \n", correct);
        //reseting necessary values
        correct =0;

        for(i=m-1;i;i--)
            free(feedback[i]);
        free(feedback);
        free(tempArray);
        ///////////////////////////
    }
}

int** buildGrid(int row,int col)
{
    int i,j;

    int** grid =calloc(sizeof(int*),row);

    for(i=0;i<row;i++)//grid built from input
    {
        grid[i] =calloc(sizeof(int),col);

        for(j=0;j<col;j++)
        {
            scanf("%d",&grid[i][j]);//reads in integers
        }

    }
    return grid;
}

void speedometer(int* arr,int digit,int k)
{
    if(digit==0)//reached base case, array filled
    {
        if(whiteCheck(arr,k) && blackCheck(arr))//send array off to be checked
            ++correct;//if check passed add one to correct
        return;//return regardless
    }

    int i;

    for(i=0;i<k;i++)// goes through all combos
    {
        arr[digit-1]=i;
        speedometer(arr,digit-1,k);
    }
}
int whiteCheck(int* arr, int k)
{
    int i,j,
    whiteCount=0;//tally of passed checks
    int* feedFreq;//frequency of feedback
    int* arrFreq;//frequency of test array

    for(i=0;i<m;i++)//check against all test cases
    {
        feedFreq=calloc(sizeof(int),k);//zeros out array and build new one
        arrFreq=calloc(sizeof(int),k);//zeros out array and build new one

        for(j=0;j<n;j++)//sets values for frequency array
        {
            feedFreq[feedback[i][j]]++;
            arrFreq[arr[j]]++;
        }

        for(j=0;j<k;j++)//sets white count to lowest of two values in frequency array
        {
            if(arrFreq[j]<feedFreq[j])
                whiteCount+=arrFreq[j];
            else
                whiteCount+=feedFreq[j];

        }

        if(whiteCount!=feedback[i][n]+feedback[i][n+1])//makes sure white count is possible b and w are in position n and n+1
        {
            free(feedFreq);
            free(arrFreq);
            return 0;
        }
        //reset for next loop
        free(feedFreq);
        free(arrFreq);
        whiteCount=0;

    }

    return 1;//everything checked out
}
int blackCheck(int* arr)
{
    int i,j,
    blackCount;//running count of possibilities


    for(i=0;i<m;i++)//goes through all possibilities
    {
        blackCount=0;// resets count per possibility
        for(j=0;j<n;j++)
        {
            if(arr[j]==feedback[i][j])//counts black pieces
                blackCount++;
        }

        if(blackCount!=feedback[i][n])//ends if it is possible
            return 0;
    }
    return 1;//was possible
}
