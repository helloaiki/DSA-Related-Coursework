#include<iostream>
#include "listBST.hpp"

using namespace std;


int main()
{
    BST<int, int> *bst = new ListBST<int, int>();
    bst->insert(5,5);
    bst->insert(3,3);
    bst->insert(7,7);
    bst->insert(1,1);
    bst->insert(4,4);
    bst->insert(6,6);
    bst->insert(8,8);

    cout<<"Sum of leaves: "<<bst->leafSum();
    cout<<"Number of nodes in between 1 and 2 level: "<<bst->countInLevelRange(1,2);
    


}
