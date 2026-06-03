#include <iostream>
#include <fstream>
#include <string>
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
        return 1;
    }

    BST<string, int> *bst1 = new ListBST<string, int>();
    if (!bst1) {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>();
    if (!bst2) {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Phil's words
        // Start your code here
        string word;
        in_file>>word;
        if(!bst1->insert(word,1))
        {
            int get_val=bst1->get(word);
            get_val+=1;
            bst1->update(word,get_val);
        }
        // End your code here
    }
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Claire's words
        // Start your code here
        string word;
        in_file>>word;
        if(!bst2->insert(word,1))
        {
            int get_val=bst2->get(word);
            get_val+=1;
            bst2->update(word,get_val);
        }

        // End your code here
    }

    // TODO: Implement the logic to print the initial state of both hands
    // Start your code here
    cout<<"Phil's words: "<<endl;
    cout<<"BST (In-order): ";
    bst1->print('I');
    cout<<endl;
    cout<<endl;
    cout<<endl;
    
    cout<<"Claire's words: "<<endl;
    cout<<"BST (In-order): ";
    bst2->print('I');
    cout<<endl;

    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";

    while (true) {
        string word;
        in_file >> word;
        
        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here
        if(bst1->find(word))
        {
            cout<<"Phil has "<<word<<"!"<<endl;

            int get_val=bst1->get(word);
            get_val-=1;
            bst1->update(word,get_val);
            if(get_val==0)
            bst1->remove(word);
        }
        if(bst2->find(word))
        {
            cout<<"Claire has "<<word<<"!"<<endl;
            int get_val=bst2->get(word);
            get_val-=1;
            bst2->update(word,get_val);
            if(get_val==0)
            bst2->remove(word);
        }
        if(bst1->empty()||bst2->empty())
        {
            if(bst1->empty()&&bst2->empty())
            {
                cout<<"It's a tie!";
            }
            else if(bst1->empty())
            {
                cout<<"Phil wins!";
            }
            else
            {
                cout<<"Claire wins!";
            }

            break;
        }
        cout<<endl;
        cout<<endl;
        cout<<"Phil's remaining words:"<<endl;
        cout<<"BST (In-order): ";
        bst1->print('I');
        cout<<endl;
        cout<<"Claire's remaining words:"<<endl;
        cout<<"BST (In-order): ";
        bst2->print('I');
        cout<<endl;
        cout<<endl;
        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}