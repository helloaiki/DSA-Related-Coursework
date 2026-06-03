#include<iostream>
#include<cmath>
//#include "MurmurHash3.h"
#include<typeinfo>
#include<string>
#include<cstring>
#include<random>
#include<chrono>
extern "C"
{
    #include"xxhash.h"
}
using namespace std;


//set up the table initailizers
int intialTableSize=13;
int loadFactor=0.5;
constexpr uint32_t SEED = 0x9747b28c;

random_device rd;
mt19937 gen
(
    static_cast<uint32_t>(chrono::high_resolution_clock::now().time_since_epoch().count())
);
uniform_int_distribution<>dis(1,1000);

//word generator

string wordGenerator(int n)
{
    
    string s="";
    for(int i=0;i<n;i++)
    {
        s+=(char)('a'+(dis(gen)%26));
    }


    return s;

}

//verify for prime
bool isPrime(int num)
{
    if(num<=1)
    {
        return false;
    }
    int limit=floor(sqrt(num));
    for(int i=2;i<=limit;i++)
    {
        if(num%i==0)
        {
            return false;
        }
    }


    return true;
}

//find next prime
int findPrime(int size,bool greater)
{
    int seed=size;
    if(greater)
    {
        for(int i=seed;;i++)
        {
            if(isPrime(i))
            {
                return i;
            }
        }
    }
    else
    {
        for(int i=seed;i>=2;i--)
        {
            if(isPrime(i))
            {
                return i;
            }
        }
    }

    return 0;
}




template<typename T,typename V>
class keyValuePair
{
    T key;
    V value;
    public:
    keyValuePair(T k,V v)
    {
        key=k;
        value=v;
    }

    T getKey()
    {
        return key;
    }

    V getValue()
    {
        return value;
    }
};

// template<typename T>
// uint32_t murmurHash(const T& key)
// {
//     uint32_t hash=0;
//     MurmurHash3_x86_32(&key,sizeof(T),SEED,&hash);
//     return hash;
// }

// template<>
// uint32_t murmurHash<string>(const string&key)
// {
//     uint32_t hash=0;
//     MurmurHash3_x86_32(key.c_str(),key.size(),SEED,&hash);
//     return hash;
// }

template<typename T>
uint64_t xxHash(const T& key)
{
    uint64_t hash;
    hash=XXH64(&key,sizeof(T),0);
    return hash;
}

template<>
uint64_t xxHash<string>(const string& key)
{
    uint64_t hash;
    hash=XXH64(key.c_str(),key.size(),0);
    return hash;
}




template<typename T,typename V>
class myHashTable
{
    int size;
    int currentSize;
    bool* hasBeenUsedOnce;
    keyValuePair<T,V>** table;

    int hashFunction1(T key,int in,int s)
    {
        return (xxHash<T>(key)+in)%s;
    }

    // int hashFunction2(T key,int in,int s)
    // {
    //     return (murmurHash<T>(key)+in)%s;
    // }



     void resizeTable(int newLimit,bool greater)
    {
        
        int newSize=findPrime(newLimit,greater);
        delete[]hasBeenUsedOnce;
        hasBeenUsedOnce=new bool[newSize];
        for(int i=0;i<newSize;i++)
        {
            hasBeenUsedOnce[i]=false;
        }
        keyValuePair<T,V>**newTable=new keyValuePair<T,V>*[newSize];
        for(int i=0;i<newSize;i++)
        {
            newTable[i]=nullptr;
        }
        for(int i=0;i<size;i++)
        {
            if(table[i]!=nullptr)
            {
                int newIndex;
                T k=table[i]->getKey();
                int increment=0;
                newIndex=this->hashFunction1(k,increment,newSize);
                while(newTable[newIndex]!=nullptr)
                {
                    increment++;
                    newIndex=this->hashFunction1(k,increment,newSize);
                }
                newTable[newIndex]=table[i];
                hasBeenUsedOnce[newIndex]=true;

            }
        }

        delete[]table;
        table=newTable;
        size=newSize;
    }


    public:
    myHashTable(int s=intialTableSize)
    {
        size=s;
        currentSize=0;
        table=new keyValuePair<T,V>*[size];
        hasBeenUsedOnce=new bool[size];
        for(int i=0;i<size;i++)
        {
            hasBeenUsedOnce[i]=false;
        }
        for(int i=0;i<size;i++)
        {
            table[i]=nullptr;
        }
    }

    void put(T k,V v)
    {
        //this condition is for checking if same key is used.If so,we reject
        int value=-1;
        int increment=0;
        int h1=this->hashFunction1(k,increment,size);
        while(!(table[h1]==nullptr && !hasBeenUsedOnce[h1]))
        {
            increment++;
            if(table[h1]!=nullptr)
            {
                T ourKey=table[h1]->getKey();
                if(ourKey==k)
                {
                    value=h1;
                    break;
                }

            }
            h1=this->hashFunction1(k,increment,size);
        }

        if(value!=-1)
        {
            return;
        }
        
        keyValuePair<T,V>*ob=new keyValuePair<T,V>(k,v);
        increment=0;
        h1=this->hashFunction1(k,increment,size);
        while(table[h1]!=nullptr)
        {
            increment++;
            h1=this->hashFunction1(k,increment,size);
        }
        table[h1]=ob;
        hasBeenUsedOnce[h1]=true;
        currentSize++;
        if(((double(currentSize))/size)>.5)
        {
            this->resizeTable(size*2,true);
        } 
    }

    int searchIndex(T key)
    {
        int value=-1;
        int increment=0;
        int h1=this->hashFunction1(key,increment,size);
        while(!(table[h1]==nullptr && !hasBeenUsedOnce[h1]))
        {
            increment++;
            if(table[h1]!=nullptr)
            {
                T ourKey=table[h1]->getKey();
                if(ourKey==key)
                {
                    value=h1;
                    break;
                }

            }
            h1=this->hashFunction1(key,increment,size);
        }
        return value;
    }

    V search(T key)
    {
        int index=this->searchIndex(key);
        if(index==-1)
        {
            throw runtime_error("Key not found");
        }

        return table[index]->getValue();
    }

    V remove(T key)
    {
        //key not found check
        int index=this->searchIndex(key);
        if(index==-1)
        {
            throw runtime_error("Key not found");
        }
        V val=table[index]->getValue();
        delete table[index];
        table[index]=nullptr;
        currentSize--;
        if((((double)currentSize)/size)<.25 && size>intialTableSize*2)//this stops the table from reducing to a size lower than inital value
        {
            this->resizeTable(size/2,false);
        }  

        return val;
    }

   
    void print()
    {
        for(int i=0;i<size;i++)
        {
            if(table[i]!=nullptr)
            {
                cout<<"Key: "<<table[i]->getKey()<<" Value: "<<table[i]->getValue()<<endl;
            }
        }
    }

    ~myHashTable()
    {
        for(int i=0;i<size;i++)
        {
            delete table[i];
        }

        delete[]table;
        delete[]hasBeenUsedOnce;
    }

};


int main()
{
    int n=5;
    myHashTable<string,int>ht;
    for(int i=0;i<100;i++)
    {
        ht.put(wordGenerator(n),i);
    }

    ht.print();
    
}


//g++ regular.cpp MurmurHash3.cpp -std=c++17 -O2 -o program
//.\program.exe
//Get-Content input.txt | .\program.exe

