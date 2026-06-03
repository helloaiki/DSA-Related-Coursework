#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"
#include <queue>
#include "queue.h"
#include <stack>
#include "stack.h"
#include <iostream>


class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members
    struct Node
    {
        int data;
        Node* next;
    };

    Node **arrayOfLinkedList=nullptr;
    int numberOfLinkedList=0;
    int returnIndex(int value) const
    {
        int index=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==value)
            {
                index=i;
                break;
            }
        }

        return index;
    }

public:
     AdjacencyListGraph() : arrayOfLinkedList(nullptr), numberOfLinkedList(0) {}

    ~AdjacencyListGraph() {
        for(int i = 0; i < numberOfLinkedList; i++) {
            Node* current = arrayOfLinkedList[i];
            while(current != nullptr) {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
        delete[] arrayOfLinkedList;
    }
    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        Node **tempArrayOfLinkedList=new Node*[numberOfLinkedList+1];
        for(int i=0;i<numberOfLinkedList;i++)
        {
            tempArrayOfLinkedList[i]=arrayOfLinkedList[i];
        }
        Node* newItem=new Node;
        newItem->data=v;
        newItem->next=nullptr;
        tempArrayOfLinkedList[numberOfLinkedList]=newItem;
        if (arrayOfLinkedList != nullptr) 
        {
        delete[] arrayOfLinkedList;
        }
        
        arrayOfLinkedList=tempArrayOfLinkedList;
        numberOfLinkedList++;
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        if(u==v)
        {
            int id=-1;
            for(int i=0;i<numberOfLinkedList;i++)
            {
                if(arrayOfLinkedList[i]->data==u)
                {
                    id=i;
                    break;
                }
            }

            if(id<0)
            {
                AddNode(u);
                id=returnIndex(u);
            }
            //checks if edge present
            Node* temp = arrayOfLinkedList[id]->next;
            while (temp != nullptr) 
            {
                if (temp->data == v) 
                return; // Edge already exists
                temp = temp->next;
            }

            Node *newItem1=new Node;
            newItem1->data=v;
            newItem1->next=nullptr;

            temp=arrayOfLinkedList[id];
            while(temp->next!=nullptr)
            {
                temp=temp->next;
            }

            temp->next=newItem1;



        }
        else
        {
            int index1=-1,index2=-1;
            for(int i=0;i<numberOfLinkedList;i++)
            {
                if(arrayOfLinkedList[i]->data==u)
                {
                    index1=i;
                    break;
                }
            }
            for(int i=0;i<numberOfLinkedList;i++)
            {
                if(arrayOfLinkedList[i]->data==v)
                {
                    index2=i;
                    break;
                }
            }

            if(index1<0 || index2<0)
            {
            if(index1<0)
            {
                AddNode(u);
            }
            if(index2<0)
            {
                AddNode(v);
            }
            }



            // Recompute indexes
        for (int i = 0; i < numberOfLinkedList; i++) 
        {
            if (arrayOfLinkedList[i]->data == u) 
            index1 = i;
            if (arrayOfLinkedList[i]->data == v) 
            index2 = i;
        }

        // Check if edge already exists
        Node* temp = arrayOfLinkedList[index1]->next;
        while (temp != nullptr) 
        {
            if (temp->data == v) 
            return; // Edge already exists
            temp = temp->next;
        }

            Node *newItem1=new Node;
            newItem1->data=v;
            newItem1->next=nullptr;

            temp=arrayOfLinkedList[index1];
            while(temp->next!=nullptr)
            {
                temp=temp->next;
            }

            temp->next=newItem1;

            Node *newItem2=new Node;
            newItem2->data=u;
            newItem2->next=nullptr;

            temp=arrayOfLinkedList[index2];
            while(temp->next!=nullptr)
            {
                temp=temp->next;
            }

            temp->next=newItem2;


        }
       
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
         int index1=-1,index2=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==v)
            {
                index2=i;
                break;
            }
        }

        if(index1<0 || index2<0)
        {
            return false;
        }

        Node *temp=arrayOfLinkedList[index1];
        while(temp!=nullptr)
        {
            if(temp->data==v)
            return true;
            temp=temp->next;
        }

        return false;

    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.

        int index=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==v)
            {
                index=i;
                break;
            }
        }

        if(index<0)
        {
            std::cout<<"Node not found"<<std::endl;
            return ;
        }

        Node *temp=arrayOfLinkedList[index];

        for(int i=index+1;i<numberOfLinkedList;i++)
        {
            arrayOfLinkedList[i-1]=arrayOfLinkedList[i];
        }

        while(temp!=nullptr)
        {
            Node *holder=temp->next;
            delete temp;
            temp=holder;
        }


        Node **tempArrayOfLinkedList=new Node*[numberOfLinkedList-1];
        for(int i=0;i<numberOfLinkedList-1;i++)
        {
            tempArrayOfLinkedList[i]=arrayOfLinkedList[i];
        }
        delete[]arrayOfLinkedList;
        arrayOfLinkedList=tempArrayOfLinkedList;
        numberOfLinkedList--;

        

        for(int i=0;i<numberOfLinkedList;i++)
        {
            Node *traverser=arrayOfLinkedList[i];
            Node *prev=nullptr;
            while(traverser!=nullptr)
            {
                prev=traverser;
                traverser=traverser->next;
                if(traverser!=nullptr && traverser->data==v)
                {
                    break;
                }
            }
            if(traverser!=nullptr && prev!=nullptr)
            {
                prev->next=traverser->next;
                delete traverser;
            }
        }


    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        int index1=-1,index2=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==u)
            {
                index1=i;
                break;
            }
        }
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==v)
            {
                index2=i;
                break;
            }
        }

        if(index1<0 || index2<0)
        {
            std::cout<<"Node not found"<<std::endl;
            return;
        }

        Node *temp1=arrayOfLinkedList[index1];
        Node *prev=nullptr;
        while(temp1!=nullptr)
        {
            prev=temp1;
            temp1=temp1->next;
            if(temp1!=nullptr && temp1->data==v)
            {
                break;
            }
        }
        if(temp1!=nullptr)
        {
            prev->next=temp1->next;
            delete temp1;
        }

        Node *temp2=arrayOfLinkedList[index2];
        prev=nullptr;
        while(temp2!=nullptr)
        {
            prev=temp2;
            temp2=temp2->next;
            if(temp2!=nullptr && temp2->data==u)
            {
                break;
            }
        }
        if(temp2!=nullptr)
        {
            prev->next=temp2->next;
            delete temp2;
        }


    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        int index=returnIndex(u);
        int indexToReach=returnIndex(v);
        if(index<0 || indexToReach<0)//means that the node isn't even present. So why search for it. return false
           return false;
        
        
        //set up color for each node
        //1 for white
        //2 for grey
        //3 for black
        int *colorForNodes=new int[numberOfLinkedList];
        //initializing each node's color to white 
        for(int i=0;i<numberOfLinkedList;i++)
        {
            colorForNodes[i]=1;
        }
        //coloring source node grey
        colorForNodes[index]=2;
        ListQueue *listQueue=new ListQueue();
        bool foundViaCycle=false;
        listQueue->enqueue(arrayOfLinkedList[index]->data);
        while(!(listQueue->empty()))
        {
            int nodeToBeInspected=listQueue->dequeue();
            int indexOfNodeToBeInspected=returnIndex(nodeToBeInspected);
            Node *temp=arrayOfLinkedList[indexOfNodeToBeInspected];
            temp=temp->next;
            while(temp!=nullptr)
            {
                int checkIndex=returnIndex(temp->data);
                if(checkIndex>=0 && colorForNodes[checkIndex]==1)
                {
                    colorForNodes[checkIndex]=2;
                    listQueue->enqueue(temp->data);
                }
                if(temp->data==u && temp->data==v)
                {
                    foundViaCycle=true;
                    break;
                }
                
                temp=temp->next;
            }
            colorForNodes[indexOfNodeToBeInspected]=3;
            if(foundViaCycle)
               break;

        }

        delete listQueue;

        //by this point, if the nodes had a path in between the node color should be not white//aka black
        //so now we search the index and compare

        
        if(foundViaCycle)
        {
            delete[]colorForNodes;
            return true;
        }
        else
        {
            int indexForSecond=returnIndex(v);
            bool isTrue=false;

            if(colorForNodes[indexForSecond]!=1)
                isTrue=true;

            delete[]colorForNodes;

            return isTrue;
        }


    }

    void FindShortestPath(int u, int v) const override
    {
        //TODO: Find the shortest path between the nodes u and v and print it.
        int index1=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==u)
            {
                index1=i;
                break;
            }
        }
        int index2=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==v)
            {
                index2=i;
                break;
            }
        }
        if(index1<0 || index2<0)//means that the node isn't even present
        {
            std::cout<<"No such path exists as nodes aren't present"<<std::endl;
            return;
        }
        
        int *colorForNode=new int[numberOfLinkedList];
        int *parent=new int[numberOfLinkedList];
        bool foundViaCycle=false;
        int traceBackParentIfLoop=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            colorForNode[i]=1;
            parent[i]=-1;
        }

        colorForNode[index1]=2;
        bool found=false;
        ListQueue *listQueue=new ListQueue();
        listQueue->enqueue(arrayOfLinkedList[index1]->data);
        while(!(listQueue->empty()))
        {
            int nodeToBeInspected=listQueue->dequeue();
            int indexOfNodeToBeInspected=returnIndex(nodeToBeInspected);
            Node *temp=arrayOfLinkedList[indexOfNodeToBeInspected];
            temp=temp->next;
            while(temp!=nullptr)
            {
                int dataToInspect=temp->data;
                int indexDataToInspect=returnIndex(dataToInspect);
                
                if(colorForNode[indexDataToInspect]==1)
                {
                    colorForNode[indexDataToInspect]=2;
                    listQueue->enqueue(dataToInspect);
                    parent[indexDataToInspect]=nodeToBeInspected;
                    if(dataToInspect==v)
                    {
                        found=true;
                        break;
                    }
                }

                if(temp->data==u && temp->data==v)
                {
                    foundViaCycle=true;
                    traceBackParentIfLoop=nodeToBeInspected;
                    break;
                }

                temp=temp->next;
                
            }
            colorForNode[indexOfNodeToBeInspected]=3;
            if(found)
               break;
            if(foundViaCycle)
               break;
        }

        delete listQueue;

         if(foundViaCycle)
        {
             ListStack *listStack=new ListStack();
            int pathTracker=traceBackParentIfLoop;
            while(pathTracker!=-1)
            {
                listStack->push(pathTracker);
                pathTracker=parent[returnIndex(pathTracker)];
            }

            std::cout<<"Shortest Path: ";
            while(!(listStack->empty()))
            {
                std::cout<<listStack->pop()<<' ';
            }
            std::cout<<v;

            std::cout<<std::endl;
            delete[]colorForNode;
            delete[]parent;

            delete listStack;
            return;
        }


        if(!found)
        {
            delete[]colorForNode;
            delete[]parent;
            std::cout<<"No path exists"<<std::endl;
            return;
        }

       
        ListStack *listStack=new ListStack();
        int pathTracker=v;
        while(pathTracker!=-1)
        {
             listStack->push(pathTracker);
             pathTracker=parent[returnIndex(pathTracker)];
        }

        std::cout<<"Shortest Path: ";
        while(!(listStack->empty()))
        {
             std::cout<<listStack->pop()<<' ';
        }

        std::cout<<std::endl;

        delete[]colorForNode;
        delete[]parent;

        delete listStack;
        

    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        int index1=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==u)
            {
                index1=i;
                break;
            }
        }
        int index2=-1;
        for(int i=0;i<numberOfLinkedList;i++)
        {
            if(arrayOfLinkedList[i]->data==v)
            {
                index2=i;
                break;
            }
        }
        if(index1<0 || index2<0)//means that the node isn't even present
        {
            return -1;
        }

        if(!CheckPath(u,v))
           return -1;
        
        int *colorForNode=new int[numberOfLinkedList];
        int *parent=new int[numberOfLinkedList];
        for(int i=0;i<numberOfLinkedList;i++)
        {
            colorForNode[i]=1;
            parent[i]=-1;
        }

        colorForNode[index1]=2;
        bool found=false;
        ListQueue *listQueue=new ListQueue();
        bool foundViaCycle=false;
        int traceBackIfLoop=-1;
        listQueue->enqueue(arrayOfLinkedList[index1]->data);
        while(!(listQueue->empty()))
        {
            int nodeToBeInspected=listQueue->dequeue();
            int indexOfNodeToBeInspected=returnIndex(nodeToBeInspected);
            Node *temp=arrayOfLinkedList[indexOfNodeToBeInspected];
            temp=temp->next;
            while(temp!=nullptr)
            {
                int dataToInspect=temp->data;
                int indexDataToInspect=returnIndex(dataToInspect);
                if(colorForNode[indexDataToInspect]==1)
                {
                    colorForNode[indexDataToInspect]=2;
                    parent[indexDataToInspect]=nodeToBeInspected;
                    listQueue->enqueue(dataToInspect);
                    if(dataToInspect==v)
                    {
                        found=true;
                        break;
                    }
                }

                if(temp->data==u && temp->data==v)
                {
                    foundViaCycle=true;
                    break;
                }

                temp=temp->next;
                
            }
            colorForNode[indexOfNodeToBeInspected]=3;
            if(found)
               break;
            if(foundViaCycle)
            {
                traceBackIfLoop=nodeToBeInspected;
                break;
            }
        }

        delete listQueue;

        if(foundViaCycle)
        {
            ListStack *listStack=new ListStack();
            int pathTracker=traceBackIfLoop;
            while(pathTracker!=-1)
            {
                listStack->push(pathTracker);
                pathTracker=parent[returnIndex(pathTracker)];
            }
        
            int length=listStack->size();

            delete[]parent;
            delete[]colorForNode;
            delete listStack;

            return length;
        }

        if(!found)
        {
            return -1;
        }

        

        ListStack *listStack=new ListStack();
        int pathTracker=v;
        while(pathTracker!=-1)
        {
             listStack->push(pathTracker);
             pathTracker=parent[returnIndex(pathTracker)];
        }
       
        int length=listStack->size()-1;

        delete[]parent;
        delete[]colorForNode;
        delete listStack;

        return length;
        


    }

    ListQueue* GetNeighbors(int u) const override
    {
        //TODO: Return the list of neighbors.
        int index=returnIndex(u);
        ListQueue *listQueue=new ListQueue();
        if(index<0)
           return listQueue;
        Node *temp=arrayOfLinkedList[index];
        temp=temp->next;
        while(temp!=nullptr)
        {
            listQueue->enqueue(temp->data);
            temp=temp->next;
        }

        return listQueue;

    }

};

#endif // ADJACENCY_LIST_GRAPH_H
