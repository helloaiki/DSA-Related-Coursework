#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    // TODO: Initialize current_size to 0
    //member variables
    // struct Node
    // {
    //     int data;   // Value stored in this node
    //     Node *next; // Pointer to the next node in the list

    //     /**
    //      * Node constructor
    //      * @param value The value to store in this node
    //      * @param next_node Pointer to the next node (default: nullptr)
    //      */
    //     Node(int value, Node *next_node = nullptr) : data(value), next(next_node) {}
    // };

    // Node *front_node; // Pointer to the front node of the queue
    // Node *rear_node;  // Pointer to the rear node of the queue
    // int current_size; // Number of elements currently in the queue
    current_size=0;
    front_node=nullptr;
    rear_node=nullptr;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    // TODO: Link the new node to the rear
    // TODO: Update the rear_node
    // TODO: Increment the current size
    Node *newItem=new Node(item);
    if(front_node==nullptr)
    front_node=newItem;
    else
    rear_node->next=newItem;

    rear_node=newItem;
    current_size++;
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Store the data from the front node
    // TODO: Update the front pointer to the next node
    // TODO: Update the rear pointer if the queue becomes empty
    // TODO: Delete the old front node
    // TODO: Decrement current_size
    // TODO: Return the stored data
    
        if(empty())
        {
            return -1;
        }
        int returnVal=front_node->data;
        Node *removeThisNode=front_node;
        if(size()==1)
        {
            front_node=nullptr;
            rear_node=nullptr;
        }
        else
        {
            front_node=front_node->next;
        }

        delete removeThisNode;
        current_size--;

        return returnVal;
   

}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0
    if(!empty())
    {
        for(int i=0;i<current_size;i++)
        {
            Node *temp=front_node;
            front_node=front_node->next;
            delete temp;
        }

        front_node=nullptr;
        rear_node=nullptr;
        current_size=0;
    }
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the front node without removing it
        if(empty())
        {
            return -1;
        }

        return front_node->data;
    
    
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the back node without removing it
   
    if(empty())
    {
        return -1;
    }


        return rear_node->data;
   
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    if(front_node==nullptr)
    return true;
    return false;
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
    string ans="<";
    Node *temp=front_node;
    for(int i=0;i<current_size;i++)
    {
        
        int ogNum=temp->data;
        int num=temp->data;
        int count=0;
        bool is_negative=false;
        if(num<0)
        {
            is_negative=true;
            ogNum=-ogNum;
            num=-num;
        }
        if(num==0)
        count=1;
        while(num)
        {
            count++;
            num/=10;
        }
        int *arr=new int [count];
        int id=0;
        if(ogNum==0)
        arr[id++]=ogNum;
        while(ogNum)
        {
            arr[id++]=ogNum%10;
            ogNum/=10;
        }
        if(is_negative)
        ans+="-";
        while(id>0)
        {
            ans+=(char)('0'+arr[--id]);
        }
        if(i!=size()-1)
        ans+=", ";
        delete[]arr;
        temp=temp->next;
    } 
    
    ans+="|";
    return ans;
}
