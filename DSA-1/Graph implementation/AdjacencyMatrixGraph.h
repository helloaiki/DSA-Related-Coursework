#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"
#include <queue>
#include "queue.h"
#include <stack>
#include "stack.h"
#include<iostream>


class AdjacencyMatrixGraph : public GraphADT
{
private:
    //TODO: Consider necessary private members as per your discretion
    
    int **arrayOfRows; 
    int numberOfRows;
    int currentRow;
    int *nodeValueArray;

    int returnIndex(int value)const
    {
        int index=-1;
        for(int i=0;i<currentRow;i++)
        { 
            if(nodeValueArray[i]==value)
            {
                index=i;
                break;
            }
        }

        return index;
    }

    void resizeMatrix()
    {
        //TODO: you need to resize your matrix when you will less data or more data
       
        if(currentRow>=numberOfRows)
        {

            int *tempNodeValueArray=new int[numberOfRows+1];
            for(int i=0;i<currentRow;i++)
            tempNodeValueArray[i]=nodeValueArray[i];
             
            if(nodeValueArray!=nullptr) 
               delete []nodeValueArray;
            nodeValueArray=tempNodeValueArray;
            numberOfRows+=1;
            int **tempArrayOfRows=new int*[numberOfRows];
            for(int i=0;i<numberOfRows;i++)
            {
                tempArrayOfRows[i]=new int[numberOfRows];
            }
            for(int i=0;i<currentRow;i++)
            {
                for(int j=0;j<currentRow;j++)
                {
                    tempArrayOfRows[i][j]=arrayOfRows[i][j];
                }
                for(int j=currentRow;j<numberOfRows;j++)
                {
                    tempArrayOfRows[i][j]=0;
                }
            }
            for(int i=currentRow;i<numberOfRows;i++)
            {
                for(int j=0;j<numberOfRows;j++)
                {
                     tempArrayOfRows[i][j]=0;
                }
            }

            if(arrayOfRows!=nullptr)
            {
                for(int i=0;i<currentRow;i++)
                {
                    delete []arrayOfRows[i];
                }

                delete[]arrayOfRows;
            }

            arrayOfRows=tempArrayOfRows;
            
        }
        else
        {
            int *tempNodeValueArray=new int[numberOfRows-1];
            for(int i=0;i<currentRow;i++)
            tempNodeValueArray[i]=nodeValueArray[i];

            delete []nodeValueArray;
            nodeValueArray=tempNodeValueArray;
            int **tempArray=new int*[numberOfRows-1];
            for(int i=0;i<currentRow;i++)
            {
                tempArray[i]=new int[numberOfRows-1];
            }
            for(int i=0;i<currentRow;i++)
            {
                for(int j=0;j<currentRow;j++)
                {
                    tempArray[i][j]=arrayOfRows[i][j];
                }
            }
            for(int i=0;i<numberOfRows;i++)
            {
                delete []arrayOfRows[i];
            }

            delete []arrayOfRows;

            arrayOfRows=tempArray;

            numberOfRows-=1;

        }

    }

public:

    //cant add const and destr
    //update can add them
    AdjacencyMatrixGraph()
    {
        // int **arrayOfRows; 
        // int numberOfRows;
        // int currentRow;
        // int *nodeValueArray;
        arrayOfRows=nullptr;
        numberOfRows=0;
        currentRow=0;
        nodeValueArray=nullptr;
    }
    ~AdjacencyMatrixGraph()
    {
        if(arrayOfRows!=nullptr)
        {
            for(int i=0;i<currentRow;i++)
            {
                delete[]arrayOfRows[i];
            }
            delete[]arrayOfRows;
        }
        numberOfRows=0;
        currentRow=0;
        if(nodeValueArray!=nullptr)
        {
            delete[]nodeValueArray;
        }
        
    }
    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if(currentRow>=numberOfRows)
        resizeMatrix();
        nodeValueArray[currentRow++]=v;

    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        int index1=-1,index2=-1;
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==v)
            {
                index2=i;
                break;
            }
        }

        if(index1<0 || index2<0)
        {
            if(index1<0)
               AddNode(u);
            if(index2<0)
               AddNode(v);
        }

        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==v)
            {
                index2=i;
                break;
            }
        }

        arrayOfRows[index1][index2]=1;
        arrayOfRows[index2][index1]=1;

    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        int index1=-1,index2=-1;
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==v)
            {
                index2=i;
                break;
            }
        }

        if(index1<0 || index2<0)
        {
            return false;
        }
        if(arrayOfRows[index1][index2]==1 && arrayOfRows[index2][index1]==1)
           return true;
        
        return false;
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        int index=-1;
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==v)
            {
                index=i;
                break;
            }
        }

        if(index<0)
        {
            std::cout<<"Cannot find the nodes"<<std::endl;
            return;
        }

        for(int i=index+1;i<currentRow;i++)
        {
            nodeValueArray[i-1]=nodeValueArray[i];
        }

        for(int i=index+1;i<currentRow;i++)
        {
            for(int j=0;j<currentRow;j++)
            {
                arrayOfRows[j][i-1]=arrayOfRows[j][i];
            }
        }


        for(int i=index+1;i<currentRow;i++)
        {
            for(int j=0;j<currentRow;j++)
            {
                 arrayOfRows[i-1][j]=arrayOfRows[i][j];
            }
        }
        
        
        currentRow-=1;
        if(currentRow>=0)
           resizeMatrix();

    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        int index1=-1,index2=-1;
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==v)
            {
                index2=i;
                break;
            }
        }

        if(index1<0 || index2<0)
        {
            std::cout<<"Cannot find the nodes"<<std::endl;
            return;
        }

        arrayOfRows[index1][index2]=0;
        arrayOfRows[index2][index1]=0;
    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        int index1=-1,index2=-1;
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==v)
            {
                index2=i;
                break;
            }
        }

        if(index1<0||index2<0)
        {
            return false;
        }

        if(index1==index2)
        {
            if(arrayOfRows[index1][index1]==1)
            {
                return true;
            }
        }

        int *colorForNode=new int[currentRow];
        bool foundViaCycle=false;

        for(int i=0;i<currentRow;i++)
        {
            colorForNode[i]=1;
        }

        colorForNode[index1]=2;

        ListQueue *listQueue=new ListQueue();

        listQueue->enqueue(nodeValueArray[index1]);
        while(!(listQueue->empty()))
        {
            int dequeuedValue=listQueue->dequeue();
            int indexOfDequeuedValue=returnIndex(dequeuedValue);
            
            for(int i=0;i<currentRow;i++)
            {
                if(arrayOfRows[indexOfDequeuedValue][i]==1)
                {
                    int neighbour=nodeValueArray[i];
                    int indexOfNeighbour=returnIndex(neighbour);
                    if(colorForNode[indexOfNeighbour]==1)
                    {
                        colorForNode[indexOfNeighbour]=2;
                        listQueue->enqueue(neighbour);
                    }
                    if(neighbour==u && neighbour==v)
                    {
                        foundViaCycle=true;
                        break;
                    }
                }
            }

            colorForNode[indexOfDequeuedValue]=3;
            if(foundViaCycle)
            {
                break;
            }

        }

        if(u==v)
        {
            delete listQueue;
            delete[]colorForNode;
            if(foundViaCycle)
               return true;
            return false; 
        }
        

        bool isTrue=false;

        if(colorForNode[index2]!=1)
           isTrue=true;
        
        
        delete listQueue;
        delete[]colorForNode;

        return isTrue;


    }

    void FindShortestPath(int u, int v) const override
    {
        //TODO: Find the shortest path between the nodes u and v and print it.
        int index1=-1,index2=-1;
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==v)
            {
                index2=i;
                break;
            }
        }

        if(index1<0||index2<0)
        {
            std::cout<<"No path exists"<<std::endl;
            return;
        }

        if(index1==index2)
        {
            if(arrayOfRows[index1][index1]==1)
            {
                std::cout<<"Shortest Path: "<<u<<' '<<u<<std::endl;
                return;
            }

        }

        int *colorForNode=new int[currentRow];
        int *parent=new int[currentRow];
        bool foundViaCycle=false;
        int traceBack=-1;

        for(int i=0;i<currentRow;i++)
        {
            colorForNode[i]=1;
            parent[i]=-1;
        }

        colorForNode[index1]=2;
        ListQueue *listQueue=new ListQueue();
        bool found=false;
        listQueue->enqueue(nodeValueArray[index1]);
        while(!(listQueue->empty()))
        {
            int dequeuedValue=listQueue->dequeue();
            int indexOfDequeuedValue=returnIndex(dequeuedValue);
            
            for(int i=0;i<currentRow;i++)
            {
                if(arrayOfRows[indexOfDequeuedValue][i]==1)
                {
                    int neighbour=nodeValueArray[i];
                    int indexOfNeighbour=returnIndex(neighbour);
                    if(colorForNode[indexOfNeighbour]==1)
                    {
                        colorForNode[indexOfNeighbour]=2;
                        parent[indexOfNeighbour]=dequeuedValue;
                        listQueue->enqueue(neighbour);
                        if(neighbour==v)
                        {
                            found=true;
                            break;
                        }
                    }
                    if(neighbour==u && neighbour==v)
                    {
                        foundViaCycle=true;
                        traceBack=dequeuedValue;
                        break;
                    }
                }
            }

            colorForNode[indexOfDequeuedValue]=3;
            if(found)
               break;
            if(foundViaCycle)
               break;

        }

        delete listQueue;
        delete[]colorForNode;

        if(foundViaCycle)
        {
            ListStack *listStack=new ListStack();

            int traverser=traceBack;
            while(traverser!=-1)
            {
                listStack->push(traverser);
                traverser=parent[returnIndex(traverser)];
            }

            delete[]parent;
            std::cout<<"Shortest Path: ";
            while(!(listStack->empty()))
            {
                std::cout<<listStack->pop()<<' ';
            }
            std::cout<<u<<std::endl;

            delete listStack;
            return;
        }

        if(!found)
        {
            delete[]parent;
            std::cout<<"No path exists"<<std::endl;
            return;
        }

        
        ListStack *listStack=new ListStack();

        int traverser=v;
        while(traverser!=-1)
        {
            listStack->push(traverser);
            traverser=parent[returnIndex(traverser)];
        }

        delete[]parent;
        std::cout<<"Shortest Path: ";
        while(!(listStack->empty()))
        {
            std::cout<<listStack->pop()<<' ';
        }
        std::cout<<std::endl;

        delete listStack;

    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        int index1=-1,index2=-1;
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<currentRow;i++)
        {
            if(nodeValueArray[i]==v)
            {
                index2=i;
                break;
            }
        }

        if(index1<0||index2<0)
        {
            return -1;
        }

        if(index1==index2)
        {
            if(arrayOfRows[index1][index1]==1)
            {
                return 1;
            }
        }

        int *colorForNode=new int[currentRow];
        int *parent=new int[currentRow];
        bool foundViaCycle=false;
        int traceBack=-1;

        for(int i=0;i<currentRow;i++)
        {
            colorForNode[i]=1;
            parent[i]=-1;
        }

        colorForNode[index1]=2;
        ListQueue *listQueue=new ListQueue();
        bool found=false;
        listQueue->enqueue(nodeValueArray[index1]);
        while(!(listQueue->empty()))
        {
            int dequeuedValue=listQueue->dequeue();
            int indexOfDequeuedValue=returnIndex(dequeuedValue);
            
            for(int i=0;i<currentRow;i++)
            {
                if(arrayOfRows[indexOfDequeuedValue][i]==1)
                {
                    int neighbour=nodeValueArray[i];
                    int indexOfNeighbour=returnIndex(neighbour);
                    if(colorForNode[indexOfNeighbour]==1)
                    {
                        colorForNode[indexOfNeighbour]=2;
                        parent[indexOfNeighbour]=dequeuedValue;
                        listQueue->enqueue(neighbour);
                        if(neighbour==v)
                        {
                            found=true;
                            break;
                        }
                    }
                    if(neighbour==u && neighbour==v)
                    {
                        foundViaCycle=true;
                        traceBack=dequeuedValue;
                        break;
                    }
                }
            }

            colorForNode[indexOfDequeuedValue]=3;
            if(found)
               break;
            if(foundViaCycle)
               break;

        }

        delete listQueue;
        delete[]colorForNode;
        if(foundViaCycle)
        {
            ListStack *listStack=new ListStack();

            int traverser=traceBack;
            while(traverser!=-1)
            {
                listStack->push(traverser);
                traverser=parent[returnIndex(traverser)];
            }

            delete[]parent;
            int length=listStack->size();

            delete listStack;
            return length;
        }
        if(!found)
        {
            delete[]parent;
            return -1;
        }
        ListStack *listStack=new ListStack();

        int traverser=v;
        while(traverser!=-1)
        {
            listStack->push(traverser);
            traverser=parent[returnIndex(traverser)];
        }

        delete[]parent;
        int length=listStack->size()-1;
        delete listStack;

        return length;
    }
    ListQueue* GetNeighbors(int u) const override
    {
        //TODO return a list of neighbors of node u
        ListQueue *listQueue=new ListQueue();
        int index=returnIndex(u);
        if(index<-1)
          return listQueue;
        
        for(int i=0;i<currentRow;i++)
        {
            if(arrayOfRows[index][i]==1)
            {
                listQueue->enqueue(nodeValueArray[i]);
            }
        }

        return listQueue;

    }

};

#endif // ADJACENCY_MATRIX_GRAPH_H
