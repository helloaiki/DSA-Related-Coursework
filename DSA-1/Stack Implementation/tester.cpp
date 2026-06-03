#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "stack.h"
using namespace std;


int main()
{
    int num;
    cout<<"Enter a number: ";
    cin>>num;

    if(num<=2)
    cout<<"Fibonacci was called 1 time"<<endl;
    else
    {
        bool canContinue=true;
        ListStack list;
        int sum=1;
        list.push(num-2);
        list.push(num-1);
        sum+=2;
        while(true)
        {
            ListStack revStack;
            bool valid=false;
            while(!list.empty())
            {
                int val=list.pop();
                revStack.push(val);
                if(val>2)
                {
                    valid=true;
                }
            }
            if(!valid)
            break;
            while(!revStack.empty())
            {
                int test=revStack.pop();
                if(test>=3)
                {
                    list.push(test-2);
                    list.push(test-1);
                    sum+=2;
                }
                else
                list.push(test);
            }
               
        }


        cout<<"Fibonacci has been called on num "<<sum<<" times"<<endl;

    }



    

   

    return 0;
}