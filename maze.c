//Juan Gonzalez
#include <stdlib.h>
#include <stdio.h>

struct node
{
  int location;
  int dist;
  struct node* next;
};

struct queue
{
  struct node* beggining;
  struct node* end;
};

typedef struct queue q;
typedef struct node Node;

const int DX[] = {1,0,-1,0};//x movement array 4 directions
const int DY[] = {0,1,0,-1};//y movement array 4 directions

int breadthFirst(char**, int,int,int);//searches through array for an end
char** buildGrid(int, int, int*);//builds the grid according to input
void enqueue(q*, int, int);//adds a member to the queue
Node* dequeue(q* );//removes a member for use

int main (int argc,char** args)
{
  char** board=NULL;

  int cases,//puzzles to solve
      rows,//rows of board
      columns,//columns of board
      start,//location of s
      i;

  scanf("%d",&cases);//read in cases

  while(cases)
  {
    scanf("%d %d",&rows,&columns);
    board=buildGrid(rows, columns,&start);
    printf("%d\n",breadthFirst(board,start,rows,columns));//prints the shortest path
    cases--;

    for(i=0;i<rows;i++)//clear board
      free(board[i]);
    free(board);
  }
  return 0;
}

int breadthFirst(char** arr, int start, int row, int col )
{
  q left;// queue to manage
  Node* hold;//holds current node
  char peek;//looks one over to see if valid path
  int lowest=-1,//smallest step to take
      x=0, y=0,//current location
      i;//just a counter

  left.beggining=NULL;//set the queue to be empty
  left.end=NULL;//set the queue to be empty
  enqueue(&left, start, 0);//place first element down

  while( ( hold=dequeue(&left) ) !=NULL)//go through the whole queue
  {
    x=(hold->location)%1000;//get current location
    y=(hold->location)/1000;//get current location
    arr[y][x]='V';//set it as 'V'isited
    for(i=0;i<4;i++)//looks in all directions
    {
      if(y+DY[i] < row && x+DX[i] < col)
      {
        peek= arr[y+DY[i]][x+DX[i]];
        switch(peek)
        {
          case '-' :
          enqueue(&left, ( y+DY[i])*1000+(x+DX[i]), hold->dist+1);//set it as next path if walkable
          arr[y+DY[i]][x+DX[i]]='V';//set the next one as having been visited. just to be safe
          break;

          case '~' ://at end, but we replace if its the smallest path
          if(lowest > hold->dist+1 || lowest==-1)
            lowest =hold->dist+1;
          break;
        }
      }
    }
    free(hold);//frees current member when we're done to avoid trouble
  }
  return lowest;
}

char** buildGrid(int row,int col,int* start)
{
    int i,j;

    char** grid =calloc(sizeof(char*),row);
    for(i=0;i<row;i++)//grid built from input
    {
        grid[i] =calloc(sizeof(char),col);
        for(j=0;j<col;j++)
        {
          scanf(" %c", &grid[i][j]);//error kept arising without space at the front, no idea why
          if (grid[i][j]=='S')//when we find the start save the location
            *start=i*1000+j;
        }
    }
    return grid;
}

void enqueue(q* insert, int val, int distance)
{
  Node* temp=malloc(sizeof(Node));//make a new node
  temp->location=val;//set location
  temp->dist=distance;//set total distance from source
  temp->next=NULL;//make sure there is an end

  if(insert->beggining==NULL)//inserting to an empty list
    insert->beggining=temp;
  else
    insert->end->next=temp;//not empty set the current end to point to new end

  insert->end=temp;//move end over to new end
}

Node* dequeue(q* val)
{
  Node* temp=val->beggining;//set to beginning
  if(val->beggining!=NULL)//queue is not empty
  {
    val->beggining=val->beggining->next;
    temp->next=NULL;
  }
  if(val->beggining==NULL)//was last node in list
    {
      val->end=NULL;//set list to empty
    }
  return temp;
}
