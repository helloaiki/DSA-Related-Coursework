#include <stdio.h>
#include <stdlib.h>



typedef struct node
{
    int element;
    //to make node aware of node
    struct node* next;
    struct node* prev;
} node;

typedef struct 
{
    // declare head, tail, cur and other variables you need
    node *head;
    node *tail;
    node *curr;
    int length;

} linkedList;

void init(linkedList* list)
{
    // implement initialization
    list->head=NULL;
    list->tail=NULL;
    list->length=0;
    list->curr=NULL;
}

void free_list(linkedList* list)
{
    // implement destruction of list
    //pointer to keep track of node
    //node pointer called becz all these are NODES
    node *pointerToCurrentElement=list->head;
    while(pointerToCurrentElement!=NULL)
    {
        //saves next node and assigns it to the other after freeing 
        node *savePointer=pointerToCurrentElement->next;
        free(pointerToCurrentElement);
        pointerToCurrentElement=savePointer;
    }
   
    list->head=NULL;
    list->tail=NULL;
    list->length=0;
    list->curr=NULL;

}

void print(linkedList* list)
{
    // implement list printing
    //sample for containing some item [1 3| 4]
    //empty [ . ]
    //create node so that head is not lost
    if(list->length==0)
    printf("[ . ]");
    else
    {
        node *currentPointer=list->head;
        
        printf("[ ");
        while(currentPointer!=NULL)
        {
            printf("%d",currentPointer->element);
            if(currentPointer==list->curr)
            printf("| ");
            else
            printf(" ");
            currentPointer=currentPointer->next;
        }
        printf("]");
    }

    printf("\n");
}

void insert(int item, linkedList* list)
{
    // implement insert function
    //inserts at curr
    //curr advances
    //if length is 0,initialize head and tail
    if(list->length==0)
    {
        node* newNode=(node*)malloc(sizeof(node));
        newNode->element=item;
        newNode->prev=NULL;
        newNode->next=NULL;
        list->head=newNode;
        list->tail=newNode;
        list->curr=newNode;
        list->length=list->length+1;
    }
    else
    {
        if (list->curr == NULL)
        {
            printf("Curr is NULL.\n");
            return;
        }
        
        //create a new node to store our "new thing"
        node* newNode = (node*)malloc(sizeof(node));
        newNode->element = item;
        newNode->next = list->curr->next;
        newNode->prev = list->curr;
        //checks whether curr is tail
        if (list->curr->next != NULL)
        {
            list->curr->next->prev = newNode;
        }
        else
        {
            list->tail=newNode;
        }
        list->curr->next = newNode;
        list->curr = newNode; // move curr to the new node
        list->length++;

        
        //plan to follow
        //1. currPointer's next value should be assigned to newNode's next
        //2. newItem's prev should point to currPointer
        //3. currPointer's next is newItem
        //4. currPointers prev successor's prev should be newItem
        //5. increment curr and length
       

    }
    print(list);

}

int delete_cur(linkedList* list)
{
    // implement deletion of current index function
    //if length is more than or equal to one
    if(list->curr==NULL)
    {
        printf("Curr is Null\n");
        return -1;
    }

    if(list->length==0)
    {
        printf("List is empty\n");
        return -1;
    }
   //problem zone
   //solution found****
   if(list->length>=1)
   {
      int deletedItem=(list->curr)->element;
      if(list->length==1)
      {

        node *nodeToDelete=list->curr;
        list->head=NULL;
        list->tail=NULL;
        list->curr=NULL;
        list->length=0;
        free(nodeToDelete);
        
      }
      else if(list->curr==list->head)
      {
        //checks if curr is head
        //advances head to the next
         list->head=list->head->next;
         list->head->prev=NULL;
         //frees curr
         free(list->curr);

         //reassigns curr to present head
         list->curr=list->head;
         list->length=list->length-1;
      }
      else if(list->curr==list->tail)
      {
        //checks if curr is our tail
        //backs tail
        list->tail=(list->tail)->prev;
        list->tail->next=NULL;
        //frees curr
        free(list->curr);
        //reassigns curr
        list->curr=list->tail;
        list->length=list->length-1;
      }
      else
      {
          //assigns curr's ancestor to curr's successor
          list->curr->prev->next=list->curr->next;
          //assigns curr's successor to curr's ancestor
          list->curr->next->prev=list->curr->prev;
          //stores next curr value
          node *reassignValue=list->curr->next;
          //frees curr
          free(list->curr);
          //reassigns curr
          list->curr=reassignValue;
          list->length=list->length-1;
      }
      
      print(list);
      return deletedItem;
   }
}

void append(int item, linkedList* list)
{
    // implement append function
    //append to end
    //basically to the end of tail
    //curr doesnt change with append function
    if(list->length==0)
    {
        //calls insert function for this one
        node* newNode=(node*)malloc(sizeof(node));
        newNode->element=item;
        newNode->prev=NULL;
        newNode->next=NULL;
        list->head=newNode;
        list->tail=newNode;
        list->curr=newNode;
        list->length=list->length+1;
    }
    else
    {
        //assigns memory
        node *newNode=(node*)malloc(sizeof(node));
        //adds el val to newNode
        newNode->element=item;
        //newNode's prev is tail
        newNode->prev=list->tail;
        //newNode's next is null
        newNode->next=NULL;
        //tail's next is newNode
        list->tail->next=newNode;
        //reassign tail
        list->tail=newNode;
        //change length
        list->length=list->length+1;
    }
    print(list);
}

int size(linkedList* list)
{
    // implement size function
    return list->length;
}

void prev(int n, linkedList* list)
{
    // implement prev function
    if(list->length==0 || n<0)
    return ;
    int count=0;
    //either count reaches n or we reach head
    while(count!=n && list->curr!=list->head)
    {
        list->curr=(list->curr)->prev;
        count++;
    }
    print(list);
}

void next(int n, linkedList* list)
{
    if(list->length==0 || n<0)
    return ;
    // implement next function
    int count=0;
    while(count!=n && list->curr!=list->tail)
    {
        list->curr=(list->curr)->next;
        count++;
    }

    print(list);
    
}

int is_present(int n, linkedList* list)
{
    // implement presence checking function
    node *pointerToCurrent=list->head;
    for(int i=0;i<list->length;i++)
    {
        if(n==(pointerToCurrent->element))
        {
            return 1;
        }
        pointerToCurrent=pointerToCurrent->next;
    }

    return 0;
}

void clear(linkedList* list)
{
    // implement list clearing function
    //idk how to decipher between both 
    //will change later if needed **************************
    free_list(list);
    print(list);
}

void delete_item(int item, linkedList* list)
{
    // implement item deletion function
    int found=0;
    node *pointerToCurrent=list->head;
    while(pointerToCurrent!=NULL)
    {
        if(item==pointerToCurrent->element)
        {
            found=1;
            if(list->length==1)
            {
                //basically does the same thing that I was about to do
                free_list(list);
            }
            else if(pointerToCurrent==list->head)
            {
                if(pointerToCurrent==list->curr)
                list->curr=(list->curr)->next;
                list->head=(list->head)->next;
                (list->head)->prev=NULL;
                free(pointerToCurrent);
                list->length=list->length-1;
            }
            else if(pointerToCurrent==list->tail)
            {
                if(pointerToCurrent==list->curr)
                list->curr=(list->curr)->prev;
                list->tail=(list->tail)->prev;
                (list->tail)->next=NULL;
                free(pointerToCurrent);
                list->length=list->length-1;
            }
            else
            {
                (pointerToCurrent->prev)->next=pointerToCurrent->next;
                (pointerToCurrent->next)->prev=pointerToCurrent->prev;
                if (pointerToCurrent == list->curr) 
                {
                    // If we're deleting curr, reassign it to the next node
                    list->curr = pointerToCurrent->next;
                }
                free(pointerToCurrent);
                list->length=list->length-1;
            }
            break;
        }
        pointerToCurrent=pointerToCurrent->next;
    }
    if(!found)
    printf("%d not found\n",item);
    else
    print(list);
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    // implement swap function
    if((ind1>=0 && ind1<list->length) &&(ind2>=0 && ind2<list->length))
    {
        node *firstElementInSwap=list->head;
        node *secondElementInSwap=list->head;
        int count=0;
        //finding the first one in swap op
        while(count!=ind1)
        {
            firstElementInSwap=firstElementInSwap->next;
            count++;
        }
        count=0;
        //finding second
        while(count!=ind2)
        {
            secondElementInSwap=secondElementInSwap->next;
            count++;
        }
        //swap
        int temp=firstElementInSwap->element;
        firstElementInSwap->element=secondElementInSwap->element;
        secondElementInSwap->element=temp;
        print(list);
    }
    else
    printf("Invalid indices\n");
}

// // you can define helper functions you need