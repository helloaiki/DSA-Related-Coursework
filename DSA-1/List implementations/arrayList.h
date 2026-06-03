#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *array;
    // declare variables you need
    //length to keep track of current elements
    int length;
    //length to change it based on the circumstances
    int maxlength;
    int curr;

} arrayList;

void init(arrayList* list)
{
    // implement initialization
    //initialized it to carry 2 items
    list->array=(int*)malloc(sizeof(int)*2);
    //current length is 0
    list->length=0;
    //fix maxlength to 2
    list->maxlength=2;
    //curr stays at -1
    list->curr=-1;
    //checks if memory allocation was successful
    if(list->array==NULL)
    {
        printf("Memory Allocation Not Possible\n");
        exit(1);
    }

}

void free_list(arrayList* list)
{
    // implement destruction of list
    //deletes the list array
    free(list->array);

}

//the conditions for the below functions will be provided in the later functions

void increase_capacity(arrayList* list)
{
    // implement capacity increase
    //increases capacity maxlength times two
    //allocates mem for that temp pointer
    printf("Capacity increased from %d to %d\n",list->maxlength,list->maxlength*2);
    arrayList *tempList=(arrayList*)malloc(sizeof(arrayList));
    //makes list's maxlength twice
    list->maxlength=list->maxlength*2;
    tempList->array=(int*)malloc(sizeof(int)*list->maxlength);
    if(tempList->array==NULL)
    {
        printf("Memory Allocation Not Possible\n");
        exit(1);
    }
    for(int i=0;i<list->length;i++)
    *((tempList->array)+i)=*((list->array)+i);
    //free that list using our function
    //that function only erases the array not any info about length and maxlength
    free_list(list);
    list->array=(int*)malloc(sizeof(int)*list->maxlength);
    //copy that back 
    for(int i=0;i<list->length;i++)
    *((list->array)+i)=*((tempList->array)+i);
    free_list(tempList);
    free(tempList);
}

void decrease_capacity(arrayList* list)
{
    // implement capacity decrease
    //decreases maxlength to half
    printf("Capacity decreased from %d to %d\n",list->maxlength,list->maxlength/2);
    list->maxlength=(list->maxlength)/2;
    arrayList *tempList=(arrayList*)malloc(sizeof(arrayList));
    tempList->array=(int*)malloc(sizeof(int)*list->maxlength);
    if(tempList->array==NULL)
    {
        printf("Memory Allocation Not Possible\n");
        exit(1);
    }
    for(int i=0;i<list->length;i++)
    *((tempList->array)+i)=*((list->array)+i);
    //free that list using our function
    free_list(list);
    list->array=(int*)malloc(sizeof(int)*list->maxlength);
    //copy that back 
    for(int i=0;i<list->length;i++)
    *((list->array)+i)=*((tempList->array)+i);
    free_list(tempList);
    free(tempList);
}

void print(arrayList* list)
{
    // implement list printing
    //sample
    //[ 1 2| ]
    printf("[ ");
    if(list->length==0)
    printf(". ");
    else
    {
        for(int i=0;i<list->length;i++)
        {
            printf("%d",*((list->array)+i));
            if(i==(list->curr))
            printf("|");
            printf(" ");
        }
    }

    printf("]\n");
}


void insert(int item, arrayList* list)
{
    // implement insert function
    //condition to check whether need to resize
    //this func inserts at the pos after the | sign
    //the sign also follows
    list->length=list->length+1;
    list->curr=list->curr+1;
    //checks for resize
    if(((list->length))>((list->maxlength)/2))
    increase_capacity(list);
    if(list->length==1)
    {
        *((list->array)+0)=item;
    }
    else
    {
        for(int i=list->length-2;i>=list->curr;i--)
        {
           *((list->array)+i+1)=*((list->array)+i);
        }
        
        *((list->array)+list->curr)=item;
    }
    //increases length by 1
    //maxlength is handled by the other function
    //curr advances 
    
     print(list);

}

int delete_cur(arrayList* list)
{
    // implement deletion of current index function
    int itemToReturn=*((list->array)+list->curr);
    arrayList *tempList=(arrayList*)malloc(sizeof(arrayList));
    tempList->array=(int*)malloc(sizeof(int)*(list->maxlength));
    int id=0;
    for(int i=0;i<list->length;i++)
    {
        if(i!=(list->curr))
        {
            *((tempList->array)+id)=*((list->array)+i);
            id++;
        }
    }
    int l=list->length-1;
    free_list(list);
    //allocates list again
    list->array=(int*)malloc(sizeof(int)*list->maxlength);
    for(int i=0;i<l;i++)
    *((list->array)+i)=*((tempList->array)+i);
    //fixes list's length to length-1
    list->length=list->length-1;
    //checks if it could meet the condition to decrease size
    if(l<((list->maxlength)/4))
    decrease_capacity(list);
    free_list(tempList);
    free(tempList);
    if(list->curr<list->length)
    list->curr++;
    else
    list->curr=list->length-1;
    print(list);
    return itemToReturn;

}

void append(int item, arrayList* list)
{
    // implement append function
    //this will append to the end
    if(list->length==0)
    insert(item,list);
    else
    {
        list->length++;
        if(((list->length))>((list->maxlength)/2))
        increase_capacity(list);
        //no need to change curr as it will change with insert
        *((list->array)+list->length-1)=item; 
        print(list);
    }
}

int size(arrayList* list)
{
    // implement size function
    return list->length;
}

void prev(int n, arrayList* list)
{
    // implement prev function
    if((list->curr)-n>=0)
    list->curr=list->curr-n;
    else
    list->curr=0;
    print(list);
}

void next(int n, arrayList* list)
{
    // implement next function
    if((list->curr+n)<list->length)
    list->curr=list->curr+n;
    else
    list->curr=list->length-1;
    print(list);
}

int is_present(int n, arrayList* list)
{
    // implement presence checking function
    int isHere=0;
    for(int i=0;i<list->length;i++)
    {
        if(n==*((list->array)+i))
        {
            isHere=1;
            break;
        }
    }
    
    return isHere;
}

void clear(arrayList* list)
{
    // implement list clearing function
    free_list(list);
    list->length=0;
    list->maxlength=2;
    list->curr=-1;
    print(list);
}

void delete_item(int item, arrayList* list)
{
    // implement item deletion function
    int index=-1;
    for(int i=0;i<list->length;i++)
    {
        if(item==*((list->array)+i))
        {
            index=i;
            break;
        }
    }
    if(index<0)
    printf("%d not found\n",item);
    else
    {
        
        arrayList *tempList=(arrayList*)malloc(sizeof(arrayList));
        tempList->array=(int*)malloc(sizeof(int)*(list->maxlength));
        int id=0;
        for(int i=0;i<list->length;i++)
        {
            if(i!=index)
            {
                *((tempList->array)+id)=*((list->array)+i);
                id++;
            }
        }
        int l=list->length-1;
        free_list(list);
        //allocates list again
        list->array=(int*)malloc(sizeof(int)*list->maxlength);
        for(int i=0;i<l;i++)
        *((list->array)+i)=*((tempList->array)+i);
        //fixes list's length to length-1
        list->length=list->length-1;
        //checks if it could meet the condition
        if(l<((list->maxlength)/4))
        decrease_capacity(list);
        free_list(tempList);
        free(tempList);
        if(list->curr>=index)
        {
            if(list->curr<list->length)
            list->curr++;
            else
            list->curr=list->length-1;
        }
        print(list);
    }
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    if((ind1>=0 && ind1<list->length)&&(ind2>=0 && ind2<list->length))
    {
        int temp=*((list->array)+ind1);
        *((list->array)+ind1)=*((list->array)+ind2);
        *((list->array)+ind2)=temp;
        print(list);
    }
    else
    {
        printf("Invalid indices\n");
    }
}

// you can define helper functions you need