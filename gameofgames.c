//Juan Gonzalez
//Game of Games
#include<stdio.h>
#include<stdlib.h>

int** startEnd;
int** travelT;

int** buildGrid(int row,int col);//build grid from virtual memory
void deleteArr(int** arr,int length);//deletes a 2d array
int check(int* order,int length,int timer);//determines if a time is possible
int maxPoss(int* order,int length);//determines the largest possible time in a set
int maxTime(int* order, int end,int k,int* used);//determines largest possible time for all sets

int main(void)
{
  int games,
      challenges;
  int* set,*used;

  scanf("%d", &games);//gets number of games
  while(games)//for each game, find max time you can play them
  {
    scanf("%d", &challenges);//houses to finish

    set=calloc(challenges+2,sizeof(int));//place to organize housses
    used=calloc(challenges+2,sizeof(int));//for permutation

    startEnd=buildGrid(challenges, 2);//gets start and end times
    travelT=buildGrid(challenges+1,challenges+1);//gets travel time between nodes
    printf("%d \n",maxTime(set,challenges+1,1, used));//print out the max time between nodes
    //free everything
    deleteArr(startEnd, challenges);
    deleteArr(travelT, challenges+1);
    free(set);
    free(used);
    //next game
    games--;
  }
  return 0;
}

int check(int* order,int length,int timer)
{
  int i,
  running=0;

  for(i=0;i<length-1;i++)
  {
    running+=travelT[ order[i] ][ order[i+1] ];//run to first place
    if(running<startEnd[ (order[i+1]-1) ][ 0 ])//if we're early just wait
      running=startEnd[ (order[i+1]-1) ][ 0 ];
    if(running>startEnd[ (order[i+1]-1) ][ 1 ])//we're late, this won't do!
      return 0;
    running+=timer;//wait the time required

  }
  return 1;
}

int maxPoss(int* order,int length)
{
  int high=200000, low=0;//range of bin search
  int mid[2];//array for checking past result to current
  mid[1]=0;//set differently from first so as to avoid accidental bails
  mid[0]=1;
  while(mid[1]!=mid[0])//when at repeat weve found it
  {
      mid[1]=mid[0];//set before switching
      mid[0]= (low+high)/2;//set mid

      if(check(order,length,mid[0]))
        low=mid[0];//move and look up higher if it was there

      else
        high=mid[0];//too high move down
  }

  return mid[0];//return largest possible
}

int maxTime(int* order, int end,int k,int* used)
{
  if(end==k) return maxPoss(order,end);
  int best=0, temp=0;
  int i;
  for(i=1;i<end;i++)//permutes 1 through n-1 items. home base is always starting and ending
  {
    if(!used[i])//already set that place in the list
    {
      used[i]=1;//set used
      order[k]=i;
      temp=maxTime(order, end, k+1,used);
      if(best<temp)//best was smaller than new best, change it up
        best=temp;
      used[i]=0;//unset for next permutation
    }
  }
  return best;
}

int** buildGrid(int row,int col)
{
    int i,j;

    int** grid =calloc(row,sizeof(int*));
    for(i=0;i<row;i++)//grid built from input
    {
        grid[i] =calloc(col,sizeof(int));
        for(j=0;j<col;j++)
          scanf("%d", &(grid[i][j]));
    }
    return grid;
}
void deleteArr(int** arr,int length)
{
  int i;
  for(i=0;i<length;i++)//delete dynamic memory in 2d array
      free(arr[i]);

  free(arr);
}
