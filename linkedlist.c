//Juan Gonzalez
#ifndef FUNCTIONS_C
#define FUNCTIONS_C
#include <stdio.h>
#include <stdlib.h>

struct node//nodes in the linked list
{
    int priority;//priority of list
    char name[20];//name of item to be held in list
    struct node* next;//pointer to the next node
};

typedef struct node Node;

void printList(Node* newHead)//prints out the list with names and priority
{

    while(newHead!= NULL)
    {
        printf("\nName: %s\n", newHead->name);
        printf("Priority: %d\n", newHead->priority);
        newHead=newHead->next;
    }
}

void save(Node* head, char filename[])//saves current list to file
{
    FILE* fout= fopen(filename,"w");
    if (fout==NULL)
    {
        printf("\nFile error\n");
        fclose(fout);
        return;
    }
    while(head!= NULL)//safeguard against empty list and end of list
    {
        fprintf(fout,"%s", head->name);
        fprintf(fout," %d\n", head->priority);
        head=head->next;
    }
    fclose(fout);
}

Node* load(char filename[])//loads the text file into a linked list
{
    FILE* fin;
    fin= fopen(filename, "r");
    Node* head = malloc(sizeof(Node));
    Node* temp = head;

    if (fin == NULL || head==NULL )//guards against bad files and lists
    {
        printf("\nFile error or empty list\n");
        fclose(fin);
        return;
    }

    fscanf(fin,"%s ", head->name);
    fscanf(fin,"%d\n", &(head->priority));

    while(!feof(fin))//reads until end of list
    {
        temp->next=malloc(sizeof(Node));//creates the nodes in list
        temp=temp->next;//moves the list along
        fscanf(fin,"%s %d \n", temp->name, &(temp->priority));
        temp->next=NULL;//ends always set to null
    }
    fclose(fin);
    return head;
}

Node* searcher(char* key, Node* newHead)//searches for a name in a linked list
{
    while(newHead!= NULL)//goes through list until it hist null or found
    {
        if(strcmp(key,newHead->name)==0)
            return newHead;//returns the element when found

         newHead=newHead->next;
    }
    return NULL;//returns null if not
}

void serveSome(Node* some)//prints out one member from the list
{
    char name[20];

    printf("Name: ");
    scanf("%s", name);

    some=searcher(name,some);
    if(some ==NULL)
    {
        printf("Check your spelling, this was not part of the list.\n\n");
        return;
    }

    printf("\n\nName: %s\n", some->name);
    printf("Priority: %d\n\n\n", some->priority);
}
void insertSome(Node** headp)//inserts a new item into the list
{
    Node* post=*headp;
    Node* temp= malloc(sizeof(Node));
    Node* prior=*headp;

    printf("Name: ");
    scanf("%s",temp->name);
    printf("Priority: ");
    scanf("%d",&(temp->priority));
    temp->next=NULL;

    if(temp->priority >= (*headp)->priority)//beginning of list
    {
        temp->next=*headp;
        *headp=temp;
    }
    else
    {
        post=post->next;
        while( post!=NULL && temp->priority < post->priority  )//moves along list until arrived at location
        {
            prior=prior->next;
            post=post->next;
        }

        if(post==NULL)//places at end
            prior->next=temp;

        else//places in middle
        {
            temp->next=post;
            prior->next=temp;
        }
    }

}

void deleteSome(Node** newHead)//deletes something from list
{
    Node* prior=*newHead;
    Node* post= (*newHead)->next;

    char name[20];

    printf("Name: ");//get name of what needs deleting
    scanf("%s", name);

    if(strcmp(name,prior->name)==0)//deletes from beginning
    {
        *newHead=(*newHead)->next;
        free(prior);
    }

    else
    {
        while(post->next!= NULL && strcmp(name,post->name)!=0)//moves until either at end or found
        {
            post=post->next;
            prior=prior->next;
        }
        if (strcmp(name,post->name)==0)//deletes from end and middle
        {
            prior->next=post->next;
            free(post);//frees memory
        }
    }
}
#endif // FUNCTIONS_C
