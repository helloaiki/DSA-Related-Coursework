#include "stack.h"
#include <iostream>



// Constructor implementation
ListStack::ListStack() 
{
    // TODO: Initialize head to nullptr
    // TODO: Initialize current_size to 0
    //the private members
    //  struct Node {
    //     int data;    // Value stored in this node
    //     Node* next;  // Pointer to the next node in the list
        
    //     /**
    //      * Node constructor
    //      * @param value The value to store in this node
    //      * @param next_node Pointer to the next node (default: nullptr)
    //      */
    //     Node(int value, Node* next_node = nullptr) : data(value), next(next_node) {}
    // };

    // Node* head;     // Pointer to the top node of the stack
    // int current_size;       // Number of elements currently in the stack
    head=nullptr;
    current_size=0;
    

}

// Destructor implementation
ListStack::~ListStack() 
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();

}

// Push implementation
void ListStack::push(int item) 
{
    // TODO: Create a new node with the given item
    // TODO: Make the new node point to the current head
    // TODO: Update head to point to the new node
    // TODO: Increment current_size
    //new element' next is nullptr
    struct Node *newItem=new Node(item);
    if(head==nullptr)
    head=newItem;
    else
    {
        newItem->next=head;
        head=newItem;
    }

    current_size++;

}

// Pop implementation
int ListStack::pop() 
{
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Store the data from the head node
    // TODO: Update head to point to the next node
    // TODO: Delete the old head node
    // TODO: Decrement current_size
    // TODO: Return the stored data
    if(current_size==0)
    {
        //throw implementation
        throw "Stack is empty";
    }
    int returnPopValue=head->data;
    if(current_size==1)
    {
        //basically does the same thing
        clear();
    }
    else
    {
        struct Node *tempPointer=head->next;
        delete head;
        head=tempPointer;
        current_size--;
    }

    return returnPopValue;
}

// Clear implementation
void ListStack::clear() 
{
    // TODO: Traverse the linked list, deleting each node
    // TODO: Reset head to nullptr
    // TODO: Reset current_size to 0
    for(int i=0;i<current_size;i++)
    {
        struct Node *tempPointer=head->next;
        delete head;
        head=tempPointer;
    }
    //during the last assignment, head auto gets pointed to nullptr
    //but just for clarity
    head=nullptr;
    current_size=0;
}

// Size implementation
int ListStack::size() const 
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Top implementation
int ListStack::top() const 
{
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Return the data from the head node without removing it
    if(!current_size)
    {
        //throw block
        //catch it in main()
        throw "Stack is empty";
    }
    
    int returnTop=head->data;
    return returnTop;
}

// Empty implementation
bool ListStack::empty() const 
{
    // TODO: Return whether head is nullptr
    if(head==nullptr)
    return true;
    else
    return false;
}

// Print implementation
void ListStack::print() const 
{
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    // TODO: Traverse the linked list from head, printing each node's data
    //if no elements ,prints |>
    struct Node *traversalPointer=head;
    std::cout<<"|";
    if(traversalPointer!=nullptr)
    {
         while(traversalPointer->next!=nullptr)
        {
         std::cout<<traversalPointer->data<<", ";
         traversalPointer=traversalPointer->next;
        }
    }
    std::cout<<traversalPointer->data<<">"<<std::endl;

}