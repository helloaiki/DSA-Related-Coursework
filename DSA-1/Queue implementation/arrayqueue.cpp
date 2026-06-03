#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity
    //members
    // int *data;     
    // int capacity;  
    // int front_idx; 
    // int rear_idx; 
    data=new int[initial_capacity];
    capacity=initial_capacity;
    front_idx=0;
    rear_idx=0;
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[]data;
    data=nullptr;
    capacity=0;
    front_idx=0;
    rear_idx=0;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
    
    if((rear_idx+1)%capacity==front_idx)
    {
        resize(capacity*2);
    }
    data[rear_idx]=item;
    rear_idx=(rear_idx+1)%capacity;
    //capacity var is doubled there
    
    
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the front of the queue
    // TODO: Update front index
    // TODO: Return the dequeued element
    //will later throw this in a try statement
    
         if(empty())
        {
            return -1;
        }
        
        int returnData=data[front_idx];
        front_idx=(front_idx+1)%capacity;
        //capacity will get decreased if the size is less or equal to .25 and cap is more than 2
        if(size()<=capacity/4 && capacity>2)
        resize(capacity/2);
        if(capacity==size())
        rear_idx=(rear_idx-1)%capacity;
        //again capacity will get decreased there
        return returnData;

  
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    //put capacity=10
    delete[]data;
    data=new int[2];
    capacity=2;
    front_idx=0;
    rear_idx=0;
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    int length;

    if(rear_idx>=front_idx)
    length=rear_idx-front_idx;
    else
    {
        length=rear_idx+capacity-front_idx;
    }

    return length;

}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
    
         if(empty())
        {
            return -1;
        }

        return data[front_idx];
    
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
    
         if(empty())
        {
            return -1;
        }



        return data[(rear_idx-1+capacity)%capacity];
   
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    if(front_idx==rear_idx)
    return true;

    return false;

}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    string ans="<";
    for(int i=0;i<size();i++)
    {
        int index=(i+front_idx)%capacity;
        int ogNum=data[index];
        int num=data[index];
        int count=0;
        bool is_negative=false;
        if(data[index]<0)
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
    } 
    
    ans+="|";
    return ans;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices
    int *temp=new  int[new_capacity];
    for(int i=0;i<size();i++)
    {
        int index=(i+front_idx)%capacity;
        temp[i]=data[index];
    }
    delete[]data;
    data=temp;
    rear_idx=size();
    front_idx=0;
    capacity=new_capacity;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}