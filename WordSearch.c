//Juan Gonzalez
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define WORDLENGTH 19//maximum word length

#define DX_SIZE 8
//directional arrays
const int DX[] = {-1,-1,-1,0,0,1,1,1};
const int DY[] = {-1,0,1,-1,1,-1,0,1};

char** fToCharArr(FILE *,int);//convert file to character array
int strBinSearch(char*,char**,int);//performs binary search with string
char** buildGrid(int ,int );//builds a word search according to info fed in
void searchGrid(char**,char**,int,int,int);//searches the grid for words in dictionary


int main()
{
    FILE * fin;
    fin = fopen("dictionary.txt","r");
    char** dictionary;//stores dictionary
    char**  wordGrid;//stores word grid
    int wordCount,//word count from dictionary
    row,//length of row
    col,//length of column
    tests,i,j;//counters first storing the test cases

    if(fin==NULL)
    {
        printf("File not found.");
        return 1;
    }
    fscanf(fin,"%d",&wordCount);//get word count

    scanf("%d",&tests);//get number grids
    scanf("%d %d",&row,&col);//get size of grid

    dictionary=fToCharArr(fin, wordCount);//builds dictionary

    for(j=0;j<tests;j++)
    {
        printf("Words Found in Grid #%d:\n",j+1);

        wordGrid=buildGrid(row,col);//build grid
        searchGrid(wordGrid,dictionary,row,col,wordCount);//search it

        for(i=row;i;i--)
            free(wordGrid[i]);
        free(wordGrid);

        scanf("%d %d",&row,&col);
    }
    return 1;
}

char** fToCharArr(FILE * tempf,int words)
{
    int i;
    char** dictionary = calloc(sizeof(char*),words);//dynamic allocation of array

    for(i=0;i<words;i++)//string fed into array one by one
    {
        dictionary[i]=calloc(sizeof(char*),WORDLENGTH+1);
        fscanf(tempf,"%s",dictionary[i]);
    }
    return dictionary;
}

int strBinSearch(char* strTemp,char** dictTemp,int dictLength)//standard binary search
{
    int first=0,
    middle=dictLength/2,
    last=dictLength-1;
    while(first <= last)
    {

        if (strcmp(strTemp,dictTemp[middle]) > 0)
            first = middle + 1;

        else if (strcmp(strTemp,dictTemp[middle]) == 0)
            return 1;


        else
            last = middle - 1;

        middle = (first + last)/2;
    }
    return 0;
}
char** buildGrid(int row,int col)
{
    int i,j;

    char** grid =calloc(sizeof(char*),row);
    for(i=0;i<row;i++)//grid built from input
    {
        grid[i] =calloc(sizeof(char),col);
        scanf("%s",grid[i]);
    }
    return grid;
}

void searchGrid(char** grid,char** dict,int row,int col,int dictLength)
{
    int i,j,k,l,//counts row column placement on dxdy arrays
    m,n;//offset of i and j for linear search
    char* word =calloc(sizeof(char),WORDLENGTH+1);//temporary string to hold test cases
    for(i=0;i<row;i++)//goes through row
    {
        for(j=0;j<col;j++)//goes through row
        {
            for(k=0;k<DX_SIZE;k++)//moves across dx dy
            {
                word[0]='\0';//reset string for testing in new direction, redundant
                m=i;//reset offset to be at current position
                n=j;//^^^
                for(l=1; n>=0 && m>=0 && m<row && n<col && l<WORDLENGTH+1;l++)//limited by edge and the max word size
                {
                    word[l]='\0';//sets the end of a string
                    word[l-1]=grid[m][n];//places next character in
                    if(l>=4)//checks if string meets minimum
                    {
                        if(strBinSearch(word,dict,dictLength))//checks and prints test string
                        {
                            printf("%s\n",word);
                        }
                    }

                    m+=DX[k];//moves to get next char
                    n+=DY[k];//^^
                }
            }
        }
    }
    free(word);
}
