#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    freopen("test_input_2.txt", "r", stdin); // Test Case 1
    // freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;
    //num of patients wont ever exceed N
    

    int time_stamp_array[10001]={-1};

    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        //sample line that will arrive
        //1 101 1
        //first indicates op num
        //second is the id
        //third is timestamp
        int operation_num;
        cin>>operation_num;
        int id_of_patient;
        int time_stamp;
        //first operation
        if(operation_num==1)
        {
            
            //samp output
            //Operation 1 (Arrival 101 1): randomQueue() called[this part is called in the function]
            cin>>id_of_patient;
            cin>>time_stamp;
            time_stamp_array[id_of_patient]=time_stamp;
            if(!Q->empty())
            {
                cout<<"Operation "<<i<<" (Arrival "<<id_of_patient<<" "<<time_stamp<<"): "<<endl;
                Q->enqueue(id_of_patient);
            }
            else
            {
                if(Q1->empty() && Q2->empty())
            {
                cout<<"Operation "<<i<<" (Arrival "<<id_of_patient<<" "<<time_stamp<<"): ";
                int rand_val=randomQueue();
                if(rand_val==1)
                {
                    Q1->enqueue(id_of_patient);
                }
                else
                {
                    Q2->enqueue(id_of_patient);
                }

            }
            else if(Q1->empty())
            {
                cout<<"Operation "<<i<<" (Arrival "<<id_of_patient<<" "<<time_stamp<<"): "<<endl;
                Q1->enqueue(id_of_patient);
            }
            else if(Q2->empty())
            {
                cout<<"Operation "<<i<<" (Arrival "<<id_of_patient<<" "<<time_stamp<<"): "<<endl;
                Q2->enqueue(id_of_patient);
            }
            else
            {
                //getting here means at least 2 things are present in both queues
                cout<<"Operation "<<i<<" (Arrival "<<id_of_patient<<" "<<time_stamp<<"): "<<endl;
                
                int queue_to_choose=time_stamp_array[Q1->back()]<time_stamp_array[Q2->back()]?1:2;
                if(queue_to_choose==1)
                Q1->enqueue(id_of_patient);
                else
                Q2->enqueue(id_of_patient);
                
                
            }
            }

            cout<<"Q1: "<<Q1->toString()<<endl;;
            cout<<"Q2: "<<Q2->toString()<<endl;
            cout<<"Q : "<<Q->toString()<<endl;
        }
        else if(operation_num==2)
        {
             cin>>id_of_patient;
             cin>>time_stamp;
             int len=Q1->size();
             for(int j=0;j<len;j++)
             {
                int value=Q1->dequeue();
                if(value!=id_of_patient)
                {
                    Q1->enqueue(value);
                    
                }

             }
             
             len=Q2->size();
             for(int j=0;j<len;j++)
             {
                int value=Q2->dequeue();
                if(value!=id_of_patient)
                {
                    Q2->enqueue(value);
                    
                }
                
             }
             
             len=Q->size();
             for(int j=0;j<len;j++)
             {
                int value=Q->dequeue();
                if(value!=id_of_patient)
                {
                    Q->enqueue(value);
                    
                }
               
             }
             time_stamp_array[id_of_patient]=-1;
             //sample output
             //Operation 4 (Leave 102 4):
             cout<<"Operation "<<i<<" (Leave "<<id_of_patient<<" "<<time_stamp<<"):"<<endl;
             cout<<"Q1: "<<Q1->toString()<<endl;;
             cout<<"Q2: "<<Q2->toString()<<endl;
             cout<<"Q : "<<Q->toString()<<endl;
        }
        else if(operation_num==3)
        {
            while(!Q1->empty() && !Q2->empty())
            {
                int v1=Q1->front();
                int v2=Q2->front();
                if(time_stamp_array[v1]<time_stamp_array[v2])
                {
                    Q->enqueue(v1);
                    Q1->dequeue();
                }
                else
                {
                    Q->enqueue(v2);
                    Q2->dequeue();
                }
            }
            while(!Q1->empty())
            {
                int v1=Q1->front();
                Q->enqueue(v1);
                Q1->dequeue();
            }
            while(!Q2->empty())
            {
                int v2=Q2->front();
                Q->enqueue(v2);
                Q2->dequeue();
            }
            Q1->clear();
            Q2->clear();
            cout<<"Operation "<<i<<" (Merge):"<<endl;
            cout<<"Q1: "<<Q1->toString()<<endl;;
            cout<<"Q2: "<<Q2->toString()<<endl;
            cout<<"Q : "<<Q->toString()<<endl;

        }
        else if(operation_num==4)
        {
             if(!Q->empty())
             {
                int len=Q->size();
                for(int j=0;j<len;j++)
                {
                    if((j+1)%2)
                    {
                        Q1->enqueue(Q->dequeue());
                    }
                    else
                    {
                        Q2->enqueue(Q->dequeue());
                    }
                }

                Q->clear();
             }

            cout<<"Operation "<<i<<" (Split):"<<endl;
            cout<<"Q1: "<<Q1->toString()<<endl;;
            cout<<"Q2: "<<Q2->toString()<<endl;
            cout<<"Q : "<<Q->toString()<<endl;

        }
        else
        {
            if(!Q->empty())
            {
                cout<<"Operation "<<i<<" (Departure): "<<endl;
                id_of_patient=Q->dequeue();
                time_stamp_array[id_of_patient]=-1;
                cout<<"Q1: "<<Q1->toString()<<endl;;
                cout<<"Q2: "<<Q2->toString()<<endl;
                cout<<"Q : "<<Q->toString()<<endl;
            }
            else
            {
                if(!Q1->empty() && !Q2->empty())
                {
                     cout<<"Operation "<<i<<" (Departure): ";
                    int queue_choice=randomQueue();
                    if(queue_choice==1)
                    {
                        id_of_patient=Q1->dequeue();
                        time_stamp_array[id_of_patient]=-1;
                    }
                    else
                    {
                        id_of_patient=Q2->dequeue();
                        time_stamp_array[id_of_patient]=-1;
                    }
                    cout<<"Q1: "<<Q1->toString()<<endl;;
                    cout<<"Q2: "<<Q2->toString()<<endl;
                    cout<<"Q : "<<Q->toString()<<endl;
                }
                else if(!Q1->empty())
                {
                    cout<<"Operation "<<i<<" (Departure): "<<endl;
                    id_of_patient=Q1->dequeue();
                    time_stamp_array[id_of_patient]=-1;
                    cout<<"Q1: "<<Q1->toString()<<endl;;
                    cout<<"Q2: "<<Q2->toString()<<endl;
                    cout<<"Q : "<<Q->toString()<<endl;
                }
                else if(!Q2->empty())
                {
                    cout<<"Operation "<<i<<" (Departure): "<<endl;
                    id_of_patient=Q2->dequeue();
                    time_stamp_array[id_of_patient]=-1;
                    cout<<"Q1: "<<Q1->toString()<<endl;;
                    cout<<"Q2: "<<Q2->toString()<<endl;
                    cout<<"Q : "<<Q->toString()<<endl;
                }
                
            }
            
        }

        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    return 0;
}