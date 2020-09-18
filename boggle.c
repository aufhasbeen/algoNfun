//Juan Gonzalez
// Boggle
#include<stdlib.h>
#include <stdio.h>
#include<string.h>

struct trie//trie nodes
{
  int word;
  struct trie* next[26];
};

typedef struct trie Trie;

const int DX[]={0,0,1,1,1,-1,-1,-1};//search directions
const int DY[]={1,-1,1,-1,0,1,-1,0};//search directions

Trie* init();//initialize a node
Trie* buildTrie(FILE* fp);//build the trie from file
void insert(Trie* node, char* temp, int i);//place a character in the trie
void phaseOne(char** boggle,Trie* node);//look at the top of each boggle piece, first letter
void phaseTwo(Trie* node,char** boggle,char* word, int row,int col, int count);//find all possible words
int find(Trie* node, char* temp, int i);//see if its in the trie
char** buildGrid(int row,int col);//build a dynamic grid

int main(void)
{
  char** boggle;//board
  FILE* fp= fopen("dictionary.txt","r");//open file for reading
  Trie* head;
  int games, j;

  scanf("%d",&games);//gets number of games to play
  head=buildTrie(fp);//create trie dictionary
  fclose(fp);//dont need file anymore
  for(j=0;j<games;j++)
  {
    boggle= buildGrid(4,5);//read in boggle board
    printf("Words for Game #%d:\n",j+1);
    phaseOne(boggle,head);//find all words
    int i;
    for(i=0;i<4;i++)//free board up for next use
      free(boggle[i]);
    free(boggle);
  }

  return 0;
}

void phaseTwo(Trie* node,char** boggle,char* word, int row,int col, int count)
{
  if(count>16)//word is to big cant insert here
    return;
  if(row>=4 || row<0 || col>=4 || col<0)//not inbounds of board
    return;
  if(boggle[row][col]=='#')//weve already been at this letter
    return;

  char hold;//temporarily holds onto characters
  word[count]=boggle[row][col];//extends word
  word[count+1]='\0';//marks end of line to make usre no errors encountered

  if(count>=2)//only uses words larger than 2 characters
  {
    int ret=find(node, word, 0);//stores result of search
    if(ret==-1)//no possible combination
    {
      return;
    }
    if(ret==1)//word was found hooray
      printf("%s\n",word);
  }

  hold=boggle[row][col];//keeps character for placing back in alter
  boggle[row][col]='#';//marked as visited

  int i;
  for(i=0;i<8;i++)
  {
    phaseTwo(node,boggle,word,row+DX[i],col+DY[i],count+1);//recursive call to itslef continues adding in
  }

  boggle[row][col]=hold;//unmark as visited
  word[count]='\0';//makes no end of line for when we go back
}

void phaseOne(char** boggle,Trie* node)
{
  int i,j;
  char word[17];
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      phaseTwo(node,boggle,word, i, j, 0);//gives first letter to search
    }
  }
}

char** buildGrid(int row,int col)
{
    int i;

    char** grid =calloc(row,sizeof(char*));
    for(i=0;i<row;i++)//grid built from input
    {
        grid[i] =calloc(col,sizeof(char));
        scanf("%s",grid[i]);
    }
    return grid;
}
Trie* init()//basic initillization, values set to default
{
  int i;
  Trie* temp = malloc(sizeof(Trie));
  temp->word = 0;

  for (i=0; i<26; i++)
    temp->next[i] = NULL;

  return temp;
}

Trie* buildTrie(FILE* fp)
{
  int inserts,i;
  Trie* head=init();//head is set to something
  char word[17];
  fscanf(fp,"%d",&inserts);// find out how many are needed
  for(i=0;i<inserts; i++)
  {
    fscanf(fp,"%s",word);//scan from file
    insert(head,word,0);//place in as new path
  }
  return head;
}

void insert(Trie* node, char* temp, int i)//finds proper location and places in character
{
  int index;
  if (i == strlen(temp))//stop when reached end of word
  {
    node->word = 1;
    return;
  }
  index = temp[i] - 'a';

  if (node->next[index] == NULL)//if link was invalid then assign as new link
    node->next[index] = init();

  insert(node->next[index], temp, i+1);
}

int find(Trie* node, char* temp, int i)
{
  int index;
  if (i == strlen(temp))//found or not 1 or 0
    return node->word;

  index = temp[i] - 'a';
  if (node->next[index] == NULL)//-1 returned to signify invalid search
    return -1;
  return find(node->next[index], temp, i+1);
}
