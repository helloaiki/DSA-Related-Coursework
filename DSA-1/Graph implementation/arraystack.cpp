#include "stack.h"
#include <iostream>


// Constructor implementation
ArrayStack::ArrayStack(int initial_capacity) 
{
    // TODO: Initialize data members (data, capacity, current_size)
    // TODO: Allocate memory for the array with the specified initial capacity
    //the private members 
    // int* data;     // Pointer to dynamically allocated array
    // int capacity;  // Maximum number of elements the array can currently hold
    // int current_size;  // Number of elements currently in the stack
    //default size was told to kept 10
    data=new int[initial_capacity];
    current_size=0;
    capacity=initial_capacity;

    
}

// Destructor implementation
ArrayStack::~ArrayStack() 
{
    delete[]data;
    current_size=0;
    capacity=0;
    // TODO: Free the dynamically allocated memory for the array
}

// Push implementation
void ArrayStack::push(int item) 
{
    // TODO: Check if the array is 50% full (current_size >= capacity/2)
    // TODO: If 50% full, resize the array to double its current capacity
    // TODO: Add the new element to the top of the stack and increment current_size
    if(current_size >= capacity/2)
    resize(capacity*2);
    //capacity will be changed there
    //dont need to do that here
    data[current_size]=item;
    current_size++;

}

// Pop implementation
int ArrayStack::pop() 
{
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the top of the stack
    // TODO: If the array is less than 25% full, resize it to half its current capacity
    // TODO: Return the popped element
    if(empty())
    {
        //catch it in main()
        throw "Stack is empty";
    }
    int returnRemovedItem=data[current_size-1];
    current_size--;
    if(current_size<(capacity/4))
    resize(capacity/2);
    //capacity will be changed there

    return returnRemovedItem;
}

// Clear implementation
void ArrayStack::clear() 
{
    // TODO: Reset the stack to be empty (set current_size to 0)
    // TODO: No need to free memory, just logically clear the stack
    //as they did not say about changing the capacity, i will keep the current capacity
    current_size=0;
}

// Size implementation
int ArrayStack::size() const 
{
    // TODO: Return the number of elements currently in the stack (current_size)
    return current_size;
}

// Top implementation
int ArrayStack::top() const 
{
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Return the element at the top of the stack without removing it
    if(empty())
    {
        throw "Stack is empty";
    }
    int returnTopELement=data[current_size-1];

    return returnTopELement;
}

// Empty implementation
bool ArrayStack::empty() const 
{
    // TODO: Return whether the stack is empty (current_size == 0)
    if(current_size==0)
    return true;
    else
    return false;
}

// Print implementation
void ArrayStack::print() const 
{
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    if(!empty())
    {
        std::cout<<"|";
        for(int i=0;i<current_size-1;i++)
        std::cout<<data[i]<<", ";
        std::cout<<data[current_size-1]<<">"<<std::endl;
    }
    else
    {
        std::cout<<"|>";
    }

}

// Resize implementation
void ArrayStack::resize(int new_capacity) 
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    int *temp=new int[new_capacity];
    for(int i=0;i<current_size;i++)
    temp[i]=data[i];
    delete[]data;
    data=new int[new_capacity];
    for(int i=0;i<current_size;i++)
    data[i]=temp[i];
    capacity=new_capacity;
    delete[]temp;
}