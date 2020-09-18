//Juan Gonzalez
#include <stdio.h>
#include <stdlib.h>

void quicksort(int*, int,int);//basic quicksort meant to sort armies
int partition(int*, int,int);//splits an array by sorting one number
int* fillarr(int);//fills array according to input
int optimize(int*,int*,int);//returns wins by comparing 2 sorted arrays

int main()
{
    int cases,//cases to test
        hold, // holds value of wins
        armiesPer;//armies per side
    int* defenders=NULL;//defending army
    int* attackers=NULL;

    scanf("%d",&cases);//take in test cases

    while(cases)
    {
        scanf("%d",&armiesPer);//take in army count

        attackers=fillarr(armiesPer);//fills in attacking army
        defenders=fillarr(armiesPer);//fills in defending army

        quicksort(defenders,0,armiesPer-1);//sorts attacking army
        quicksort(attackers,0,armiesPer-1);//sorts defending army

        hold=optimize(defenders,attackers,armiesPer);//gets optimized wins
        printf("%d\n",hold);

        free(defenders);
        free(attackers);
        cases--;
    }
    return 0;
}

int* fillarr(int count)
{
    int i;
    int* temp=malloc(count*sizeof(int));
    for(i=0;i<count;i++)
    {
        scanf("%d",&temp[i]);
    }

    return temp;
}

int optimize(int* def,int* att,int size)
{
    int i,j,win=0;
    for(i=size-1,j=size-1;i+1;i--)//iterates through all cells in att
    {
        if(def[j]>=att[i])//compares both, if its a victory adds to win and moves defense along
        {
            win++;
            j--;
        }
    }
    return win;
}

void quicksort(int*arr, int low,int high)
{
    int i=0;
    if(high>low)
    {
        i=partition(arr,low,high);//find partition
        quicksort(arr,low,i-1);//sorts lower half of partition
        quicksort(arr,i+1,high);//sorts upper half of partition
    }

}

int partition(int* arr,int low,int high)
{
    int temp=0 ,pivot= low;//sets pivot as first value in array
    low++;//moves over so as not to read pivot

    while(low<=high)//loops until low and high cross
    {
        while(low<=high && arr[low] <= arr[pivot])//moves until we find a low in the wrong place
        {
            low++;
        }
        while(low<=high && arr[high] > arr[pivot])//moves along until find a high in the wrong place
        {
            high--;
        }
        if(low<high)//swaps if both are in the wrong place
        {
            temp=arr[high];
            arr[high]=arr[low];
            arr[low]=temp;
        }
    }
    temp=arr[high];//swaps afterwards regardless to place pivot in the right spot
    arr[high]=arr[pivot];
    arr[pivot]=temp;
    return high;
}
