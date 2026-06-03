#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value> {
private:
    /**
     * Node class for the binary search tree
     */
    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;
    
    // TODO: Implement private helper functions as needed
    // Start your private helper functions here

    //the first one helper func im gonna declare is for destructor as i need recursion for it and obv cant recursively call destructor
    void delete_nodes(struct Node *tree_element)
    {
        if(tree_element==nullptr)
        return;
           
        delete_nodes(tree_element->left);
        delete_nodes(tree_element->right);

        delete tree_element;
        
    }

    //second helper that will help me search for key
    struct Node* key_present (struct Node *tree_element,Key target)const
    {
        if(tree_element==nullptr || tree_element->key==target)
        return tree_element;
        if(target<tree_element->key)
        return key_present(tree_element->left,target);
        else
        return key_present(tree_element->right,target);
    }
    

    struct Node* find_parent(struct Node *tree_element,Key target)
    {
        if(tree_element==nullptr || tree_element->key==target)
        return nullptr;
        if((tree_element->left && tree_element->left->key==target)||(tree_element->right && tree_element->right->key==target))
        return tree_element;

        struct Node*left_side=find_parent(tree_element->left,target);
        if(left_side!=nullptr)
        return left_side;

        return find_parent(tree_element->right,target);
    }

    void default_traverse (struct Node*tree_element)const
    {
        if(tree_element==nullptr)
        {
            return;
        }
        std::cout<<"("<<tree_element->key<<":"<<tree_element->value;
        if(tree_element->left==nullptr &&tree_element->right!=nullptr)
        {
            std::cout<<"()";
            default_traverse(tree_element->right);
        }
        else
        {
            default_traverse(tree_element->left);
            default_traverse(tree_element->right);
        }
        std::cout<<")";

    }

    void inorder_traverse (struct Node*tree_element)const
    {
        if(tree_element==nullptr)
        return;
        inorder_traverse(tree_element->left);
        std::cout<<"("<<tree_element->key<<":"<<tree_element->value<<")";
        inorder_traverse(tree_element->right);
    }

    void preorder_traverse (struct Node*tree_element)const
    {
        if(tree_element==nullptr)
        return;
        std::cout<<"("<<tree_element->key<<":"<<tree_element->value<<")";
        preorder_traverse(tree_element->left);
        preorder_traverse(tree_element->right);
    }
    void postorder_traverse(struct Node*tree_element)const
    {
        if(tree_element==nullptr)
        return;
        postorder_traverse(tree_element->left);
        postorder_traverse(tree_element->right);
        std::cout<<"("<<tree_element->key<<":"<<tree_element->value<<")";
    }

    void inRange(struct Node*tree_element,Key r1,Key r2,int &count)
    {
        if(tree_element==nullptr)
           return;
        
        if(tree_element->key>=r1 &&tree_element->key<=r2)
           count++;
        inRange(tree_element->left,r1,r2,count);
        inRange(tree_element->right,r1,r2,count);
    }

    void  returnCountAtDepth(struct Node*tree_element,int depth,int layer,int &count)
    {
        if(tree_element==nullptr)
          return;
        if(layer==depth)
        {
            std::cout<<tree_element->key<<' ';
            count++;
            return;
        }
        returnCountAtDepth(tree_element->left,depth,layer+1,count);
        returnCountAtDepth(tree_element->right,depth,layer+1,count);
    }

    Key countOfLeafs(struct Node*tree_element)
    {
        if(tree_element==nullptr)
           return 0;
        if(tree_element->left==nullptr && tree_element->right==nullptr)
           return tree_element->key;
        
        return countOfLeafs(tree_element->left)+countOfLeafs(tree_element->right);
    }

    //countLevelRange(root,l1,l2,0,count);

    void countLevelRange(struct Node*tree_element,int l1,int l2,int layer,int &count)
    {
        if(tree_element==nullptr)
           return;
        
        if(layer>=l1 && layer<=l2)
           count++;
        
        if(layer==l2)
           return;
        
        countLevelRange(tree_element->left,l1,l2,layer+1,count);
        countLevelRange(tree_element->right,l1,l2,layer+1,count);
        
    }



    
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}
    
    /**
     * Destructor
     */
    ~ListBST() {
        // TODO: Implement destructor to free memory

        delete_nodes(root);
        root=nullptr;
        node_count=0;

    }
    
    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override {
        // TODO: Implement insertion logic
        //first check whether can find that key in the tree via helper func
        //if false return false here
        //if true, do insertion and return true

        if(root==nullptr)
        {
            struct Node *newItem=new Node(key,value);
            newItem->left=nullptr;
            newItem->right=nullptr;
            root=newItem;
            node_count++;

            return true;

        }

        struct Node* itemExist=key_present(root,key);
        if(itemExist!=nullptr)
        {
            return false;
        }

    

        struct Node *newItem=new Node(key,value);
        newItem->left=nullptr;
        newItem->right=nullptr;


        struct Node*parent=nullptr;
        struct Node*traverser=root;

        while(traverser!=nullptr)
        {
            parent=traverser;
            if(traverser->key>key)
            {
                traverser=traverser->left;
            }
            else
            {
                traverser=traverser->right;
            }
        }

        if(key<parent->key)
        parent->left=newItem;
        else
        parent->right=newItem;

        node_count++;

        return true;
    }
    
    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override {
        // TODO: Implement removal logic
        //steps
        //1. find key. my func will return nullptr if key not found
        //2.delete that node
        //3.make parent's that pointer point to one of either 3 cases
        struct Node *req_key=key_present(root,key);

        if(req_key==nullptr)
        return false;

        if(req_key==root && req_key->left==nullptr && req_key->right==nullptr)//root deletion with no children, made so root can be nullptr
        {
            root=nullptr;
            delete req_key;
        }
        else if(req_key->left==nullptr&&req_key->right==nullptr)//leaf node
        {
            struct Node*parent=find_parent(root,req_key->key);
            if(parent->left==req_key)
            {
                parent->left=nullptr;
            }
            else
            {
                parent->right=nullptr;
            }
            delete req_key;
        }
        else if(req_key->left==nullptr||req_key->right==nullptr)//only one side has subtree
        {
            struct Node*parent=find_parent(root,req_key->key);
            if(parent==nullptr)
            {
                 if(req_key->left==nullptr)
                 {
                    root=req_key->right;
                 }
                 else
                 {
                    root=req_key->left;
                 }
            }
            else
            {
                if(parent->left==req_key)
                {
                    if(req_key->left==nullptr)
                    {
                        parent->left=req_key->right;
                    }
                    else
                    {
                        parent->left=req_key->left;
                    }
                }
                else
                {
                    if(req_key->left==nullptr)
                    {
                        parent->right=req_key->right;
                    }
                    else
                    {
                        parent->right=req_key->left;
                    }
                }

            }
            delete req_key;

        }
        else//has both subtree
        {
             //gain successor
             //put successor key to del node key
             //then remove successor key via one subtree only method
             struct Node*successor=req_key->right;
             while(successor->left!=nullptr)
             {
                successor=successor->left;
             }

             //update the "node to be deleted"with successor values
             //now gotta delete successor
             //successor can have two cases
             //either leaf or has one subtree on it's right
             //no left subtree otherwise it would not be successor

            struct Node*parent=find_parent(root,successor->key);
            //first check for leaf
            if(successor->right==nullptr)
            {
                if(parent->left==successor)
                parent->left=nullptr;
                else
                parent->right=nullptr;
            }
            else
            {
                if(parent->left==successor)
                parent->left=successor->right;
                else
                parent->right=successor->right;
            }
            
            req_key->key=successor->key;
            req_key->value=successor->value;

            delete successor;

        }

        node_count--;
        return true;

    }
    
    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override {
        // TODO: Implement find logic
        struct Node *req_key=key_present(root,key);

        if(req_key==nullptr)
        return false;
        
        return true;

    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override {
        // TODO: Implement get logic
        if(find(key))
        {
            struct Node *req_key=key_present(root,key);

            return req_key->value;
        }
        else
        {

                
            throw std::runtime_error("");
           
            
        }

    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override {
        // TODO: Implement update logic
        if(find(key))
        {
            struct Node *req_key=key_present(root,key);
            req_key->value=value;
        }
        else
        {
           
                
            throw std::runtime_error("");
            
        }

    }

    /**
     * Clear all elements from the BST
     */
    void clear() override {
        // TODO: Implement clear logic

        delete_nodes(root);
        root=nullptr;
        node_count=0;

    }
    
    /**
     * Get the number of keys in the BST
     */
    size_t size() const override {
        // TODO: Implement size logic

        return node_count;

    }
    
    /**
     * Check if the BST is empty
     */
    bool empty() const override {
        // TODO: Implement empty check logic
        if(root==nullptr &&node_count==0)
        return true;
        return false;

    }
    
    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override {
        // TODO: Implement find_min logic
        //will perform SEARCH_MIN algo
        //helper func
        
        if(empty())
           throw std::runtime_error("Tree is currently empty");
        else
        {
            struct Node*traveller=root;
            while(traveller->left!=nullptr)
            {
                traveller=traveller->left;
            }

            return traveller->key;

        }
    

    }
    
    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override {
        // TODO: Implement find_max logic
       
        if(empty())
        {
            throw std::runtime_error("Tree is currently empty");
        }
        else
        {
            struct Node*traveller=root;
            while(traveller->right!=nullptr)
            {
                traveller=traveller->right;
            }

            return traveller->key;

        }
    

    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override {
        // TODO: Implement print logic
        //the values
        //     Character indicating traversal type:
        //  *                        'D' or 'd' = Default (nested parentheses) 
        //  *                        'I' or 'i' = In-order 
        //  *                        'P' or 'p' = Pre-order
        //  *                        'O' or 'o' = Post-order
        if(traversal_type>='a'&&traversal_type<='z')
        traversal_type=(char)(traversal_type-('a'-'A'));
        if(traversal_type=='D'||traversal_type=='I'||traversal_type=='P'||traversal_type=='O')
        {
            if(traversal_type=='D')
            {
                 default_traverse(root);
            }
            else if(traversal_type=='I')
            {
                
                 inorder_traverse(root);
            }
            else if(traversal_type=='P')
            {
                
                preorder_traverse(root);
            }
            else
            {
             
                postorder_traverse(root);
            }

        }
        else
        {
            throw std::invalid_argument("Invalid argument");
        }
          
        
    }

    Key getLCA(Key rootValue,Key subjectA,Key subjectB)
    {
        struct Node *temp=root;
        
        while((subjectA<temp->key && subjectB<temp->key)||(subjectA>temp->key && subjectB>temp->key))
        {
            if(subjectA<temp->key)
            {
                temp=temp->left;
            }
            else
            {
                temp=temp->right;
            }
        }
        
        return temp->key;

    }

    Key getSecondLargest()
    {

       if(root==nullptr ||size()==1)
       {
           return -1;
       }
        Key largestValue=find_max();
        struct Node *temp=key_present(root,largestValue);
        
        if(temp->left==nullptr)
        {
            struct Node *parent=find_parent(root,temp->key);
            return parent->key;
        }
        
        temp=temp->left;
        while(temp->right!=nullptr)
        {
            temp=temp->right;
        }

        return temp->key;

        
    }

    int countInRange(Key range1, Key range2)
    {
        int count=0;
        inRange(root,range1,range2,count);

        return count;
    }

    int countAtDepth(int d)
    {
        int count=0;
        returnCountAtDepth(root,d,0,count);

        return count;
    }

    Key leafSum()
    {
        Key sum=countOfLeafs(root);
        return sum;
    }

    int countInLevelRange(int l1,int l2)
    {
        int count=0;
        countLevelRange(root,l1,l2,0,count);
        return count;
    }

    
};

#endif // LISTBST_H