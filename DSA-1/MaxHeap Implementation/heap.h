#ifndef HEAP_H
#define HEAP_H
#include<vector>
#include<iostream>

using namespace std;

class Heap
{
    int *arrayOfElements=nullptr;
    int capacity=2;
    int currentSize=0;

    void resize(int newCapacity)
    {
        int *tempArrayOfElements=new int[newCapacity];
        for(int i=0;i<currentSize;i++)
        {
            tempArrayOfElements[i]=arrayOfElements[i];
        }

        capacity=newCapacity;
        if(arrayOfElements!=nullptr)
           delete[]arrayOfElements;
        arrayOfElements=tempArrayOfElements;
    }
    //as index is starting from 0 and I am not taking any empty gaps into consideration
    //if parent i, left child=2i+1, right child=2i+2
    //child i, if i is odd, add 1, then parent=(i)/2-1
    void maxHeapify(int index)
    {
        int left=2*index+1;
        int right=2*index+2;
        int maxIndex=index;
        if(left<currentSize && arrayOfElements[left]>arrayOfElements[index])
        {
            maxIndex=left;
        }
        if(right<currentSize && arrayOfElements[right]>arrayOfElements[maxIndex])
        {
            maxIndex=right;
        }

        if(maxIndex!=index)
        {
            int temp=arrayOfElements[index];
            arrayOfElements[index]=arrayOfElements[maxIndex];
            arrayOfElements[maxIndex]=temp;
            maxHeapify(maxIndex);
        }
       
    }

    //child i, if i is odd, add 1, then parent=(i)/2-1
    //when inserting, if element defies the maxheap property,then this function bubbles them up by comparing with parent

    void ensureMaxHeap(int index)
    {
        while(index!=0)
        {
            int parentIndex;
            if(index%2)
            {
                parentIndex=((index+1)/2)-1;
            }
            else
            {
                parentIndex=(index/2)-1;
            }

            if(arrayOfElements[parentIndex]<arrayOfElements[index])
            {
                int temp=arrayOfElements[parentIndex];
                arrayOfElements[parentIndex]=arrayOfElements[index];
                arrayOfElements[index]=temp;
            }
            else
            {
                break;
            }
            index=parentIndex;
        }
        
    }

    public:
    Heap(int givenSize)
    {
       resize(givenSize);
    }
    Heap(vector<int>numberList)
    {
        resize(numberList.size());

        for(int i=0;i<numberList.size();i++)
        {
            arrayOfElements[i]=numberList[i];
            currentSize++;
        }
        
        //this calculates index of last node which has children
        int lastInternalNode=(currentSize/2)-1;
        for(int i=lastInternalNode;i>=0;i--)
        {
            maxHeapify(i);
        }
    }

    ~Heap()
    {
        if(arrayOfElements!=nullptr)
           delete[]arrayOfElements;
        currentSize=0;
        capacity=0;
    }

    void insert(int element)
    {
        if(currentSize>=capacity)
        {
            resize(capacity*2);
        }
        //have to make sure whether that last element inserted follows max heap principles
        arrayOfElements[currentSize++]=element;
        ensureMaxHeap(currentSize-1);
    }

    int size()const
    {
        return currentSize;
    }

    int getMax()const
    {
       if(currentSize==0)
       {
           cout<<"Heap is currently empty"<<endl;
           return -1;
       }
       return arrayOfElements[0];
    }
    int deleteKey()
    {
            if(currentSize==0)
            {
                cout<<"Heap is currently empty"<<endl;
                return -1;
            } 

            int maxElement=arrayOfElements[0];

            arrayOfElements[0]=arrayOfElements[currentSize-1];
            currentSize-=1;
            if(currentSize<(capacity/4) && capacity>2)
            {
                resize(capacity/2);
            }

            maxHeapify(0);

            return maxElement;
    }
};

//have to define this function which will use my heap class 
//it takes a vector<int> as a parameter(reference as we will be changing that vector)
//returns nothing as we change inside the vector
//will be descending order
//heapsort(numbers)


void heapsort(vector<int>&v)
{
    Heap h(v);   

    v.clear();

    while(h.size()!=0)
    {
        int element=h.deleteKey();
        v.push_back(element);
    }
}
























#endif // HEAP_H