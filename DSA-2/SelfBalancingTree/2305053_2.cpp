#include<iostream>
#include<string>
#include<queue>
using namespace std;


template<typename T,typename V>
class Node
{
    T key;
    V value;
    public: 

    Node<T,V>* left;
    Node<T,V>* right;
    Node<T,V>* parent;
    int height;

    Node(T k, V v,Node<T,V>* l=nullptr,Node<T,V>*r=nullptr,Node<T,V>*p=nullptr)
    {
        key=k;
        value=v;
        left=l;
        right=r;
        height=0;
        parent=p;
    }

    T getKey()
    {
        return key;
    }

    V getValue()
    {
        return value;
    }

    void setHeight(int h)
    {
        height=h;
    }

    int getHeight()
    {
        return height;
    }

    void setKey(T k)
    {
        key=k;
    }

    void setValue(V v)
    {
        value=v;
    }


};

template<typename T,typename V,typename Compare=less<T>>
class AVL
{
    Node<T,V>* root;
    Compare cmp;
    bool compare(const T& a,const T& b)//compares less than-true
    {
        return cmp(a,b);
    }

    void  fixHeight(Node<T,V>*r)//fixes the height of a node based on the heights of the children
    {
        if(r==nullptr)
        {
            return;
        }

        r->height=max(r->left==nullptr?-1:r->left->height,r->right==nullptr?-1:r->right->height)+1;
    }

    void leftRotation(Node<T,V>*r)
    {
        if(r==nullptr ||r->right==nullptr)
        {
            return;
        }
        Node<T,V>*newRoot=r->right;
        r->right = newRoot->left;
        if (newRoot->left != nullptr)
        {
            newRoot->left->parent = r;
        }

        newRoot->parent = r->parent;

        if (r->parent == nullptr)
        {
            root = newRoot;
        }
        else if (r == r->parent->left)
        {
            r->parent->left = newRoot;
        }
        else
        {
            r->parent->right = newRoot;
        }

        newRoot->left = r;
        r->parent = newRoot;
        r->height=max(r->left==nullptr?-1:r->left->height,r->right==nullptr?-1:r->right->height)+1;
        if(newRoot!=nullptr)
        {
            newRoot->height=max(newRoot->left==nullptr?-1:newRoot->left->height,newRoot->right==nullptr?-1:newRoot->right->height)+1; 
        }
    }

    void rightRotation(Node<T,V>*r)
    {
        if(r==nullptr ||r->left==nullptr)
        {
            return;
        }
        Node<T,V>*newRoot=r->left;
        r->left = newRoot->right;
        if (newRoot->right != nullptr)
        {
            newRoot->right->parent = r;
        }

        newRoot->parent = r->parent;

        if (r->parent == nullptr)
        {
            root = newRoot;
        }
        else if (r == r->parent->left)
        {
            r->parent->left = newRoot;
        }
        else
        {
            r->parent->right = newRoot;
        }

        newRoot->right = r;
        r->parent = newRoot;
        r->height=max(r->left==nullptr?-1:r->left->height,r->right==nullptr?-1:r->right->height)+1;
        if(newRoot!=nullptr)
        {
            newRoot->height=max(newRoot->left==nullptr?-1:newRoot->left->height,newRoot->right==nullptr?-1:newRoot->right->height)+1; 
        }
    }

    void fixNode(Node<T,V>*node)
    {
        if(node==nullptr)
        {
            return;
        }
        int lHeight=node->left==nullptr?-1:node->left->height;
        int rHeight=node->right==nullptr?-1:node->right->height;
        if(lHeight>=rHeight)//left heavy
        {
            lHeight=node->left->left==nullptr?-1:node->left->left->height;
            rHeight=node->left->right==nullptr?-1:node->left->right->height;
            if(lHeight>=rHeight)
            {
                rightRotation(node);
            }
            else
            {
                leftRotation(node->left);
                rightRotation(node);
            }
        }
        else
        {
            lHeight=node->right->left==nullptr?-1:node->right->left->height;
            rHeight=node->right->right==nullptr?-1:node->right->right->height;
            if(rHeight>=lHeight)
            {
                leftRotation(node);
            }
            else
            {
                rightRotation(node->right);
                leftRotation(node);
            }
        }
    }

    void preOrder(Node<T,V>*r)
    {
        if(r==nullptr)
        {
            return;
        }
        cout<<r->getKey()<<' '<<r->getValue()<<' ';
        preOrder(r->left);
        preOrder(r->right);
    }

    void inOrder(Node<T,V>*r)
    {
        if(r==nullptr)
        {
            return;
        }
        inOrder(r->left);
        cout<<r->getKey()<<' '<<r->getValue()<<' ';
        inOrder(r->right);
    }

    void postOrder(Node<T,V>*r)
    {
        if(r==nullptr)
        {
            return;
        }
        postOrder(r->left);
        postOrder(r->right);
        cout<<r->getKey()<<' '<<r->getValue()<<' ';
    }

    void levelOrder(Node<T,V>*r)
    {
        queue<Node<T,V>*>q;
        q.push(r);
        while(!q.empty())
        {
            Node<T,V>*curr=q.front();
            q.pop();
            cout<<curr->getKey()<<' '<<curr->getValue()<<' ';
            if(curr->left!=nullptr)
            {
                q.push(curr->left);
            }
            if(curr->right!=nullptr)
            {
                q.push(curr->right);
            }

        }
    }

    void deleteNode(Node<T,V>*r)
    {
        if(r==nullptr)
        {
            return;
        }
        deleteNode(r->left);
        deleteNode(r->right);
        delete r;
    }


    public:

    AVL()
    {
        root=nullptr;
    }

    int insert(T key,V value)
    {
        
        Node<T,V>*parent=nullptr;
        Node<T,V>*curr=root;
        while(curr!=nullptr)
        {
            if(curr->getKey()==key)
            {
                return 0;
            }
            parent=curr;
            if(compare(curr->getKey(),key))
            {
                curr=curr->right;
            }
            else
            {
                curr=curr->left;
            }
        }

        Node<T,V>* node=new Node<T,V>(key,value);
        if(root==nullptr)
        {
            root=node;
            return 1;
        }


        if(compare(parent->getKey(),key))
        {
            parent->right=node;
        }
        else
        {
            parent->left=node;
        }
        node->parent=parent;

        //insertion part complete

        //fixing height

        Node<T,V>*nodeToFix=parent;
        while(nodeToFix!=nullptr)
        {
            fixHeight(nodeToFix);
            int leftHeight=-1;
            int rightHeight=-1;
            if(nodeToFix->left!=nullptr)
            {
                leftHeight=nodeToFix->left->height;
            }
            if(nodeToFix->right!=nullptr)
            {
                rightHeight=nodeToFix->right->height;
            }
            if(abs(leftHeight-rightHeight)<=1)
            {
                nodeToFix=nodeToFix->parent;
            }
            else
            {
                Node<T,V>*temp=nodeToFix->parent;
                fixNode(nodeToFix);//fixing a particular subtree
                nodeToFix=temp;
            }
        }

        return 1;
        
    }

    int remove(T key)
    {
        Node<T,V>* curr=root;
        Node<T,V>*parent=nullptr;
        while(curr!=nullptr)
        {
            if(curr->getKey()==key)
            {
                break;
            }

            parent=curr;
            if(compare(curr->getKey(),key))
            {
                curr=curr->right;
            }
            else
            {
                curr=curr->left;
            }
            
        }

        if(curr==nullptr)
        {
            return 0;
        }

        

        if(curr->left==nullptr && curr->right==nullptr)
        {
            if(parent==nullptr)
            {
                root=nullptr;
            }
            else
            {
                if(parent->left==curr)
                {
                    parent->left=nullptr;
                }
                else
                {
                    parent->right=nullptr;
                }
            }

        }
        else if(curr->left==nullptr || curr->right==nullptr)
        {
            if(curr->left==nullptr)
            {
                if(parent!=nullptr)
                {
                    if(parent->left==curr)
                    {
                        parent->left=curr->right;
                    }
                    else
                    {
                        parent->right=curr->right;
                    }
                }
                else
                {
                    root=curr->right;
                }
                curr->right->parent=parent;
            }
            else
            {
                if(parent!=nullptr)
                {
                    if(parent->left==curr)
                    {
                        parent->left=curr->left;
                    }
                    else
                    {
                        parent->right=curr->left;
                    }
                }
                else
                {
                   root=curr->left;
                }
                curr->left->parent=parent;
            }
        }
        else
        {
            Node<T,V>*replacement=curr->right;
            while(replacement->left!=nullptr)
            {
                replacement=replacement->left;
            }
            curr->setKey(replacement->getKey());
            curr->setValue(replacement->getValue());
            Node<T,V>*replacementRight=replacement->right;
            Node<T,V>*replacementParent=replacement->parent;
            if(replacementParent->left==replacement)
            {
                replacementParent->left=replacementRight;
            }
            else
            {
                replacementParent->right=replacementRight;
            }
            if(replacementRight!=nullptr)
            {
                replacementRight->parent=replacementParent;
            }
            parent=replacementParent;
            curr=replacement;
        }

        delete curr;


        Node<T,V>*nodeToFix=parent==nullptr?root:parent;
        while(nodeToFix!=nullptr)
        {
            fixHeight(nodeToFix);
            int leftHeight=-1;
            int rightHeight=-1;
            if(nodeToFix->left!=nullptr)
            {
                leftHeight=nodeToFix->left->height;
            }
            if(nodeToFix->right!=nullptr)
            {
                rightHeight=nodeToFix->right->height;
            }
            if(abs(leftHeight-rightHeight)<=1)
            {
                nodeToFix=nodeToFix->parent;
            }
            else
            {
                Node<T,V>*temp=nodeToFix->parent;
                fixNode(nodeToFix); //fixing a particular subtree
                nodeToFix=temp;
            }
        }

        return 1;

    }

    void traversal(int in)
    {
        if(in==1)
        {
            preOrder(root);
        }
        else if(in==2)
        {
            inOrder(root);
        }
        else if(in==3)
        {
            postOrder(root);
        }
        else
        {
            levelOrder(root);
        }
    }

    ~AVL()
    {
        deleteNode(root);
    }

   

};


int main()
{
    AVL<int,int>av;

    int commands;
    cin>>commands;
    cout<<commands<<endl;
    for(int i=0;i<commands;i++)
    {
        int e,x;
        cin>>e>>x;
        if(e==1)
        {
            int r=av.insert(x,x);
            cout<<e<<' '<<x<<' '<<r<<endl;
        }
        else if(e==0)
        {
            int r=av.remove(x);
            cout<<e<<' '<<x<<' '<<r<<endl;
        }
        else if(e==2)
        {
            av.traversal(x);
            cout<<endl;
        }

    }

    return 0;
}
