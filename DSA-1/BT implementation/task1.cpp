#include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst) {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c) {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here
        //symbols and their meanings  and what to expect
        //F find int
        //E empty just itself
        //I insert int
        //M Min/Max str
        //D del int
        //S size nothing
        //T traversal str
        if(c=='F')
        {
            in_file>>val;
            if(!bst->find(val))
            {
                cout<<"Key "<<val<<" not found in BST"<<endl;
            }
            else
            {
                cout<<"Key "<<val<<" found in BST"<<endl;
            }
        }
        else if(c=='E')
        {
            if(bst->empty())
            {
                cout<<"Empty"<<endl;
            }
            else
            {
                cout<<"Not empty"<<endl;
            }
        }
        else if(c=='I')
        {
            in_file>>val;
            //i guess both are the same
            if(bst->insert(val,val))
            {
                //Key 8 inserted into BST, BST (Default): (8:8)
                cout<<"Key "<<val<<" inserted into BST, ";
                //*** 
                cout<<"BST (Default): ";
                bst->print('D');
                cout<<endl;
            }
            else
            {
                //Insertion failed! Key 3 already exists in BST, BST (Default): (8:8 (3:3 (1:1)) (10:10 () (14:14)))
                cout<<"Insertion failed! Key "<<val<<" already exists in BST, ";
                //*** 
                cout<<"BST (Default): ";
                bst->print('D');
                cout<<endl;
            }
        }
        else if(c=='D')
        {
            in_file>>val;
            if(bst->remove(val))
            {
                //Key 3 removed from BST, BST (Default): (8:8 (1:1) (10:10 () (14:14)))
                cout<<"Key "<<val<<" removed from BST, ";
                //*
                cout<<"BST (Default): ";
                bst->print('D');
                cout<<endl;
            }
            else
            {
                //Removal failed! Key 10 not found in BST, BST (Default): (9:9 (1:1 () (7:7 (4:4))) (14:14 (13:13)))
                cout<<"Removal failed! Key "<<val<<" not found in BST, ";
                //*
                cout<<"BST (Default): ";
                bst->print('D');
                cout<<endl;
            }
        }
        else if(c=='S')
        {
            cout<<"Size: "<<bst->size()<<endl;
        }
        else if(c=='M')
        {
            in_file>>str;
            if(str[0]=='M' && str[1]=='a'||str[2]=='x'||str[3]=='\0')
            {
                try
                {
                    cout<<"Maximum value: "<<bst->find_max()<<endl;
                }
                catch(const runtime_error&r)
                {
                    cout<<"Key "<<val<<" not found in BST"<<endl;
                }
            }
            else
            {
                try
                {
                    cout<<"Minimum value: "<<bst->find_min()<<endl;
                }
                catch(const runtime_error&r)
                {
                    cout<<"Key "<<val<<" not found in BST"<<endl;
                }
            }
        }
        else
        {
            in_file>>str;
            if(str[0]=='P' && str[1]=='r'||str[2]=='e'||str[3]=='\0')
            {
                cout<<"BST (Pre-order): ";
                bst->print('P');
                cout<<endl;
            }
            else if(str[0]=='P' && str[1]=='o'||str[2]=='s'||str[3]=='t'||str[4]=='\0')
            {
                cout<<"BST (Post-order): ";
                bst->print('O');
                cout<<endl;
            }
            else
            {
                cout<<"BST (In-order): ";
                bst->print('I');
                cout<<endl;
            }
        }

        
    }
    in_file.close();
    delete bst;
    return 0;
}
