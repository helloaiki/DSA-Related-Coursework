#include<iostream>
#include<queue>
using namespace std;


template<typename T>
class Node
{
    T value;
    public:
    Node<T>*parent;
    Node<T>*right;
    Node<T>*left;
    int color;
    int size;
    Node(T k,int c=2,Node<T>*p=nullptr,Node<T>*r=nullptr,Node<T>*l=nullptr)
    {
        value=k;
        parent=p;
        right=r;
        left=l;
        color=c;
        size=1;
    }
    T getValue()
    {
        return value;
    }
    void setValue(T x)
    {
        value=x;
    }
};

template<typename T,typename Compare=less<T>>
class RedBlack
{
    Node<T>*root;
    Compare cmp;
    
    bool compare(const T& a,const T& b)
    {
        return cmp(a,b);
    }


    void deleteNodes(Node<T>*r)
    {
        if(r==nullptr)
        {
            return;
        }

        deleteNodes(r->left);
        deleteNodes(r->right);
        delete r;
    }


    int count(Node<T>*r,int v)
    {
        if(r==nullptr)
        {
            return 0;
        }

        if(v<=r->getValue())
        {
            return count(r->left,v);
        }

        return 1+(r->left==nullptr?0:r->left->size)+count(r->right,v);
    }

    Node<T>*findParentSibling(Node<T>*r)
    {
        if(!r || !r->parent || !r->parent->parent)
            return nullptr;
        Node<T>*parent=r->parent;
        Node<T>*grandParent=parent->parent;
        if(grandParent->left==parent)
        {
            return grandParent->right;
        }
        else
        {
            return grandParent->left;
        }
    }

    void rightRotation(Node<T>*r)
    {
        if (r == nullptr || r->left == nullptr)
            return;

        Node<T>* newRoot = r->left;

    
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
    }

    void leftRotation(Node<T>* r)
    {
        if (r == nullptr || r->right == nullptr)
            return;

        Node<T>* newRoot = r->right;

    
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
    }



    void  fixSize(Node<T>*r)//fixes the size of a node based on the size of the children
    {
        if(r==nullptr)
        {
            return;
        }

        r->size=(r->left==nullptr?0:r->left->size)+(r->right==nullptr?0:r->right->size)+1;
    }

    void fixNode(Node<T>*r)
    {
        if(!r || !r->parent || !r->parent->parent)
        return;
        if(r->parent->parent->left==r->parent)
        {
            if(r->parent->right==r)
            {
                this->leftRotation(r->parent);
                r=r->left;
                Node<T>*c=r;
                fixSize(c);
                fixSize(c->parent);
            }
            Node<T>*parentSib=this->findParentSibling(r);
            int parentSiblingColor=parentSib==nullptr?1:parentSib->color;
            if(parentSiblingColor==1)
            {
                Node<T>*c=r->parent->parent;
                this->rightRotation(r->parent->parent);
                r->parent->color=1;
                r->parent->right->color=2;
                fixSize(c);
                fixSize(c->parent);
            }
            else
            {
                if(r->parent->parent==root)
                {
                    r->parent->parent->color=1;
                }
                else
                {
                    r->parent->parent->color=2;
                }
                r->parent->color=1;
                if(parentSib!=nullptr)
                {
                    parentSib->color=1;
                }
                if(r->parent->parent->parent!=nullptr)
                {
                    if(r->parent->parent->parent->color==2 && r->parent->parent->color==2)
                    {
                        this->fixNode(r->parent->parent);
                    }
                }
            }
        }
        else
        {
            if(r->parent->left==r)
            {
                this->rightRotation(r->parent);
                r=r->right;
                Node<T>*c=r;
                fixSize(c);
                fixSize(c->parent);
            }
            Node<T>*parentSib=this->findParentSibling(r);
            int parentSiblingColor=parentSib==nullptr?1:parentSib->color;
            if(parentSiblingColor==1)
            {
                Node<T>*c=r->parent->parent;
                this->leftRotation(r->parent->parent);
                r->parent->color=1;
                r->parent->left->color=2;
                fixSize(c);
                fixSize(c->parent);
            }
            else
            {
                if(r->parent->parent==root)
                {
                    r->parent->parent->color=1;
                }
                else
                {
                    r->parent->parent->color=2;
                }
                r->parent->color=1;
                if(parentSib!=nullptr)
                {
                    parentSib->color=1;
                }
                if(r->parent->parent->parent!=nullptr)
                {
                    if(r->parent->parent->parent->color==2 && r->parent->parent->color==2)
                    {
                        this->fixNode(r->parent->parent);
                    }
                }
            }
        }
            

    }

    void deleteFix(Node<T>*x,Node<T>*parent)
    {
        
        while(x!=root && (x==nullptr || x->color==1))
        {
            if((parent?parent->left:nullptr)==x)
            {
                Node<T>*w=parent->right;
                if((w==nullptr?1:w->color)==2)//sibling of x(regardless of it being null) is red --case 1
                {
                    if(w!=nullptr)
                    {
                        w->color=1;
                    }
                    parent->color=2;
                    leftRotation(parent);
                    fixSize(parent);
                    if(parent!=nullptr)
                    {
                        fixSize(parent->parent);
                    }
                    w=parent->right;
                }
                if((w==nullptr?1:(w->left==nullptr?1:w->left->color))==1 && (w==nullptr?1:(w->right==nullptr?1:w->right->color))==1)//sibling black-even if it wasnt black, we make it black in the above step-children of sibling also black
                {
                    if(w!=nullptr)
                    {
                        w->color=2;
                    }
                    x=parent;
                    parent=x->parent;
                }
                else
                {
                    if((w==nullptr?1:(w->right==nullptr?1:w->right->color))==1)//sibling black and right child is black
                    {
                        if(w!=nullptr && w->left!=nullptr)
                        {
                            w->left->color=1;
                            
                        }
                        if(w!=nullptr)
                        {
                            w->color=2;
                        }
                        rightRotation(w);
                        fixSize(w);
                        if(w!=nullptr)
                        {
                            fixSize(w->parent);
                        }
                        w=parent->right;
                    }
                    if(w!=nullptr)
                    {
                        w->color=parent->color;
                    }
                    parent->color=1;
                    if(w!=nullptr && w->right!=nullptr)
                    {
                        w->right->color=1;
                    }
                    leftRotation(parent);
                    fixSize(parent);
                    if(parent!=nullptr)
                    {
                        fixSize(parent->parent);
                    }
                    x=root;
                }
            }
            else
            {
                Node<T>*w=parent->left;
                if((w==nullptr?1:w->color)==2)
                {
                    if(w!=nullptr)
                    {
                        w->color=1;
                    }
                    parent->color=2;
                    rightRotation(parent);
                    fixSize(parent);
                    if(parent!=nullptr)
                    {
                        fixSize(parent->parent);
                    }
                    w=parent->left;
                }
                if((w==nullptr?1:(w->left==nullptr?1:w->left->color))==1 && (w==nullptr?1:(w->right==nullptr?1:w->right->color))==1)
                {
                    if(w!=nullptr)
                    {
                        w->color=2;
                    }
                    x=parent;
                    parent=x->parent;
                }
                else
                {
                    if((w==nullptr?1:(w->left==nullptr?1:w->left->color))==1)
                    {
                        if(w!=nullptr && w->right!=nullptr)
                        {
                            w->right->color=1;
                            
                        }
                        if(w!=nullptr)
                        {
                            w->color=2;
                        }
                        leftRotation(w);
                        fixSize(w);
                        if(w!=nullptr)
                        {
                            fixSize(w->parent);
                        }
                        w=parent->left;
                    }
                    if(w!=nullptr)
                    {
                        w->color=parent->color;
                    }
                    parent->color=1;
                    if(w!=nullptr && w->left!=nullptr)
                    {
                        w->left->color=1;
                    }
                    rightRotation(parent);
                    fixSize(parent);
                    if(parent!=nullptr)
                    {
                        fixSize(parent->parent);
                    }
                    x=root;
                }
            }
        }
        

        
        if(x!=nullptr)
        {
            x->color=1;
        }

    }

    public:
    RedBlack()
    {
        root=nullptr;
    }
    
    int insert(T x)
    {
        int found=this->search(x);
        if(found==1)
        {
            return 0;
        }

        Node<T>*node=new Node<T>(x);
        Node<T>*curr=root;
        Node<T>*parent=nullptr;
        while(curr!=nullptr)
        {
            parent=curr;
            if(this->compare(curr->getValue(),x))
            {
                curr=curr->right;
            }
            else
            {
                curr=curr->left;
            }
        }

        if(parent==nullptr)
        {
            root=node;
            node->color=1; 
            return 1;
        }

        if(this->compare(parent->getValue(),x))
        {
            parent->right=node;
        }
        else
        {
            parent->left=node;
        }

        node->parent=parent;

        Node<T>*c=node;
        while(c!=nullptr)
        {
            fixSize(c);
            c=c->parent;
        }


        if(parent->color==node->color)
        {
            this->fixNode(node);
        }

        return 1;
    }

    

    int search(T x)
    {
        Node<T>*curr=root;

        while(curr!=nullptr)
        {
            if(curr->getValue()==x)
            {
                return 1;
            }
            if(this->compare(curr->getValue(),x))
            {
                curr=curr->right;
            }
            else
            {
                curr=curr->left;
            }
        }

        return 0;
    }

    int remove(T x)
    {
        Node<T>* curr=root;
        Node<T>*parent=nullptr;
        Node<T>*nodeBroughtToReplace=nullptr;
        int colorOfDeletedNode=-1;
        while(curr!=nullptr)
        {
            if(curr->getValue()==x)
            {
                break;
            }

            parent=curr;
            if(compare(curr->getValue(),x))
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

        colorOfDeletedNode=curr->color;
        

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
                nodeBroughtToReplace=curr->right;
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
                nodeBroughtToReplace=curr->left;
            }
        }
        else
        {
            Node<T>*replacement=curr->right;
            while(replacement->left!=nullptr)
            {
                replacement=replacement->left;
            }
            curr->setValue(replacement->getValue());
            Node<T>*replacementRight=replacement->right;
            Node<T>*replacementParent=replacement->parent;
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
            nodeBroughtToReplace=replacementRight;
            colorOfDeletedNode=replacement->color;
        }

        delete curr;

        Node<T>*c=parent;

        while(c!=nullptr)
        {
            fixSize(c);
            c=c->parent;
        }

        if(colorOfDeletedNode==2 || root==nullptr)//handles when deleted node's color is RED or tree is empty
        {
            return 1;
        }

        if((nodeBroughtToReplace==nullptr?1:nodeBroughtToReplace->color)==2)
        {
            nodeBroughtToReplace->color=1;
            return 1;
        }

        deleteFix(nodeBroughtToReplace,parent);
        root->color=1;
        return 1;
    }

    int find(T x)
    {
        return count(root,x);
    }

    ~RedBlack()
    {
        deleteNodes(root);
    }

};


int main()
{
    RedBlack<int>rb;

    int commands;
    cin>>commands;
    cout<<commands<<endl;

    for(int i=0;i<commands;i++)
    {
        int e,x;
        cin>>e>>x;
        if(e==0)
        {
            int r=rb.remove(x);
            cout<<e<<' '<<x<<' '<<r<<endl;
        }
        else if(e==1)
        {
            int r=rb.insert(x);
            cout<<e<<' '<<x<<' '<<r<<endl;
        }
        else if(e==2)
        {
            int r=rb.search(x);
            cout<<e<<' '<<x<<' '<<r<<endl;
        }
        else if(e==3)
        {
            int r=rb.find(x);//finds count for nodes with value less than x
            cout<<e<<' '<<x<<' '<<r<<endl;
        }
    }


    return 0;
}