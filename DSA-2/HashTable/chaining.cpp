#include<iostream>
#include<cmath>
#include "MurmurHash3.h"
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

template<typename T>
uint32_t murmurHash(const T& key)
{
    uint32_t hash=0;
    MurmurHash3_x86_32(&key,sizeof(T),SEED,&hash);
    return hash;
}

template<>
uint32_t murmurHash<string>(const string&key)
{
    uint32_t hash=0;
    MurmurHash3_x86_32(key.c_str(),key.size(),SEED,&hash);
    return hash;
}

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
    vector<keyValuePair<T,V>*>*table;

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
        currentSize=0;
        vector<keyValuePair<T,V>*>* newTable=new vector<keyValuePair<T,V>*>[newSize];
        
        for(int i=0;i<size;i++)
        {
            if(table[i].size()!=0)
            {
                for(int j=0;j<table[i].size();j++)
                {
                    int newIndex;
                    T k=table[i][j]->getKey();
                    int increment=0;
                    newIndex=this->hashFunction1(k,increment,newSize);
                    newTable[newIndex].push_back(table[i][j]);
                }
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
        table=new vector<keyValuePair<T,V>*>[size];
    }

    void put(T k,V v)
    {
        //this condition is for checking if same key is used.If so,we reject
        int value=-1;
        int increment=0;
        int h1=this->hashFunction1(k,increment,size);
        if(table[h1].size()!=0)
        {
            for(int i=0;i<table[h1].size();i++)
            {
                if(table[h1][i]->getKey()==k)
                {
                    value=h1;
                    break;
                }
            }
        }

        if(value!=-1)
        {
            return;
        }
        
        keyValuePair<T,V>*ob=new keyValuePair<T,V>(k,v);
        table[h1].push_back(ob);
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
        if(table[h1].size()!=0)
        {
            value=h1;
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

        for(int i=0;i<table[index].size();i++)
        {
            if(table[index][i]->getKey()==key)
            {
                return table[index][i]->getValue();
            }
        }

        throw runtime_error("Key not found");
    }

    V remove(T key)
    {
        //key not found check
        int index=this->searchIndex(key);
        int val=0;
        if(index==-1)
        {
            throw runtime_error("Key not found");
        }
        int indexInList=-1;
        keyValuePair<T,V>*ob;
        for(int i=0;i<table[index].size();i++)
        {
            if(table[index][i]->getKey()==key)
            {
                ob=table[index][i];
                val=table[index][i]->getValue();
                indexInList=i;
                break;
            }
        }
        if(indexInList==-1)
        {
            throw runtime_error("Key not found");
        }
        table[index].erase(table[index].begin()+indexInList);
        delete ob;
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
            if(table[i].size()!=0)
            {
                for(int j=0;j<table[i].size();j++)
                {
                    cout<<"Key: "<<table[i][j]->getKey()<<" Value: "<<table[i][j]->getValue()<<endl;
                }
            }
        }
    }

    ~myHashTable()
    {
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<table[i].size();j++)
            {
                delete table[i][j];
            }
            table[i].clear();
        }

        delete[]table;
    }

};


int main()
{

    

    
    return 0;
}
