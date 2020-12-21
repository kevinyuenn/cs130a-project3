#include "avltree.h"
#include <tuple>
#include <iostream>
#include <math.h>

using namespace std;


AVLtree::AVLtree() 
{
    k = -1;
}

AVLtree::~AVLtree() 
{
    clear(root);
}

void AVLtree::clear(AVLtree::Node *n) 
{
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

void AVLtree::insert(int integer, int decimal) 
{   
    if(!root){
        root = new Node(integer, decimal);
        return;
    }
    return insert(root, integer, decimal);
}

void AVLtree::insert(Node *n, int integer, int decimal) 
{
    if(integer == get<0>(n->value) && decimal == get<1>(n->value))
        return;

    if(integer < get<0>(n->value)){
        if(n->left)
            return insert(n->left, integer, decimal);
        else{
            Node *p = new Node(integer, decimal);
            n->left = p;
            p->parent = n;
            findRotation(p);
            return;
        }
    }
    else if(integer > get<0>(n->value)){
        if(n->right)
            return insert(n->right, integer, decimal);
        else {
            Node *p = new Node(integer, decimal);
            n->right = p;
            p->parent = n;
            findRotation(p);
            return;
        }
    }
    else if(integer == get<0>(n->value)){
        if(decimal < get<1>(n->value)){
            if(n->left)
                return insert(n->left, integer, decimal);
            else{
                Node *p = new Node(integer, decimal);
                n->left = p;
                p->parent = n;
                findRotation(p);
                return;
            }
        }
        else if(decimal > get<1>(n->value)){
            if(n->right)
                return insert(n->right, integer, decimal);
            else {
                Node *p = new Node(integer, decimal);
                n->right = p;
                p->parent = n;
                findRotation(p);
                return;
            }
        }
    }
}

void AVLtree::findRotation(Node *n) 
{   
    if(!n) return;
    // cout<<"left height: "<<getLHeight(n)<<" right height: "<<getRHeight(n)<<endl;
    if(fabs(getLHeight(n) - getRHeight(n)) > k){ 
        Node* p;
        kdeepestNode(n,p,2); //returns one of nodes at k+1 level
        if(p->parent){
            p = p->parent;
            if((getLHeight(p)-getRHeight(p))>0) //if left is longer
                p = p->left;
            else if ((getLHeight(p)-getRHeight(p))<0) //if right is longer
                p = p->right;
            
            if(p->parent->parent == n){
                if(p->parent == n->left){
                    if(p == p->parent->left) rotateR(n);
                    else if(p == p->parent->right) rotateLR(n);
                }
                else if (p->parent == n->right){
                    if(p == p->parent->right) rotateL(n);
                    else if(p == p->parent->left) rotateRL(n);
                }
                
                
            }
        }
    }  
    findRotation(n->parent);
}

tuple<int,int> AVLtree::getPredecessor(int integer, int decimal) 
{
    Node *n = getNodeFor(integer, decimal, root);
    if(n == NULL) return make_tuple(-1,-1);
    if(n->left){
        n = n->left;
        while(n->right){
            n = n->right;
        } 
        return n->value;
    }
    else{
        tuple<int,int> current = n->value;
        while(n->parent){
            if(get<0>(n->parent->value) == get<0>(current)){
                if(get<1>(n->parent->value) < get<1>(current)){
                    return n->parent->value;
                }
                else n = n->parent;
            }
            if(get<0>(n->parent->value) < get<0>(current)) 
                return n->parent->value;
            else n = n->parent;
        }
        return make_tuple(-1,-1);
    }
}

AVLtree::Node* AVLtree::getPredecessorNode(int integer, int decimal) 
{
    tuple<int,int> find = getPredecessor(integer, decimal);
    // cout<<get<0>(find)<<"."<<get<1>(find)<<endl;
    // int find0 = get<0>(find);
    // int find1 = get<1>(find);
    return getNodeFor(get<0>(find),get<1>(find),root);
    // cout<<get<0>(n->value)<<"."<<get<1>(n->value);
}

bool AVLtree::remove(int integer, int decimal) 
{
    Node* n = getNodeFor(integer,decimal,root);

    if(!n) return false; 
    
    if(n == root){
        if(!n->right && !n->left){
            delete n;
            root = NULL;
        }
        if(n->right && !n->left){
            root = n->right;
            delete n;
        }
        if(!n->right && n->left){
            root = n->left;
            delete n;
        }
    }

    if(!n->left && !n->right && n->parent){
        if(n->parent->left==n)
            n->parent->left = NULL;
        else
            n->parent->right = NULL;
        findRotation(n->parent);
        delete n;
    }

    else if(!n->right && n->parent){
        if (n->parent->left == n) 
            n->parent->left = n->left;
        else 
            n->parent->right = n->left;
        findRotation(n->parent);
        delete n;

    }

    else if(!n->left && n->parent){
        if (n->parent->left == n) 
            n->parent->left = n->right;
        else 
            n->parent->right = n->right;
        findRotation(n->parent);
        delete n;

    }

    else if(n->left && n->right){
        Node *temp = getPredecessorNode(integer, decimal);
        tuple<int,int> test = getPredecessor(integer,decimal);
        // cout<<"temp: "<<get<0>(temp->value)<<"."<<get<1>(temp->value)<<endl;
        tuple<int,int> tempVal = make_tuple(get<0>(temp->value), get<1>(temp->value));
        temp->value = n->value;
        n->value = tempVal;
        remove(integer,decimal);
    }
    return true;
}

bool AVLtree::search(int integer, int decimal) 
{
    if (getNodeFor(integer, decimal, root)) {
        cout<<integer<<"."<<decimal<<" found\n";
        return true;
    }
    else{
        cout<<integer<<"."<<decimal<<" not found\n";
        return false;
    }
}

tuple<int,int> AVLtree::approxSearch(int integer, int decimal) 
{
    if (getNodeFor(integer,decimal,root)){
        cout<<"closest to "<<integer<<"."<<decimal<<" is"<< integer<<"."<<decimal<<endl;
    }
}

void AVLtree::printInOrder() 
{
    printInOrder(root);
}

void AVLtree::printPreOrder() 
{
    printPreOrder(root);
}

void AVLtree::printInOrder(AVLtree::Node *n) 
{
    if (!n) return;
    printInOrder(n->left);
    cout<<get<0>(n->value)<<"."<<get<1>(n->value)<<" ";
    printInOrder(n->right);
}

void AVLtree::printPreOrder(AVLtree::Node *n) 
{
    if (n) {
        cout<<get<0>(n->value)<<"."<<get<1>(n->value)<<" ";        
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

AVLtree::Node* AVLtree::getNodeFor(int integer, int decimal, Node* n)
{
    if(n){
        if(get<0>(n->value)==integer && get<1>(n->value)==decimal)
            return n;
        else{
            Node *p = getNodeFor(integer, decimal, n->left);
            if(p) return p;
            else return getNodeFor(integer, decimal, n->right);
        }
    }
    return NULL;
}

void AVLtree::rotateL(Node *n){
    // cout<<"rotateL\n";
    Node *p = n->right;

    // cout<<"was:\n n: "<<get<0>(n->value)<<" p: "<<get<0>(p->value)<<endl;
    
    n->right = p->left;
    if(p->left)
        p->left->parent = n;
    
    if(n->parent){
        if(n->parent->left == n){
            n->parent->left = p;
            p->parent = n->parent;
        }
        else if(n->parent->right == n){
            n->parent->right = p;
            p->parent = n->parent;
        }
    }
    else{
        p->parent = NULL;
        root = p;
    }
    n->parent = p;
    p->left = n;

    // cout<<"now:\n n: "<<get<0>(n->value)<<" p: "<<get<0>(p->value)<<endl;
    // // cout<<"p left: "<<get<0>(p->left->value)<<endl;
    // cout<<"root: "<<get<0>(root->value)<<endl;
    // if(root->left)
    // cout<<"root left: "<<get<0>(root->left->value)<<endl;
    // if(root->right)
    // cout<<"root right: "<<get<0>(root->right->value)<<endl;
    // cout<<"finished rotation\n";
}

void AVLtree::rotateRL(Node *n){
    // cout<<"rotateRL\n";
    // Node *p = n->right;
    // Node *q = p->left;

    // if(q->left)
    //     p->left = q->left;
    // else if(q->right)
    //     p->left = q->right;
    // else if(!q->right || !q->left) p->left = NULL;
    // n->right = q;
    // q->parent = n;
    // q->right = p;
    // p->parent = q;
    // p->left = NULL;
    rotateR(n->right);
    rotateL(n);
}

void AVLtree::rotateR(Node *n){
    // cout<<"rotateR\n";
    Node *p = n->left;
    // cout<<"was:\n n: "<<get<0>(n->value)<<" p: "<<get<0>(p->value)<<endl;
    n->left = p->right;
    if(p->right)
        p->right->parent = n;

    if(n->parent){
        if(n->parent->left == n){
            n->parent->left = p;
            p->parent = n->parent;
        }
        else if(n->parent->right == n){
            n->parent->right = p;
            p->parent = n->parent;
        }
    }
    else{
        p->parent = NULL;
        root = p;
    }
    n->parent = p;
    p->right = n;

    // cout<<"now:\n n: "<<get<0>(n->value)<<" p: "<<get<0>(p->value)<<endl;
    // // cout<<"p left: "<<get<0>(p->left->value)<<endl;
    // cout<<"root: "<<get<0>(root->value)<<endl;
    // if(root->left)
    // cout<<"root left: "<<get<0>(root->left->value)<<endl;
    // if(root->right)
    // cout<<"root right: "<<get<0>(root->right->value)<<endl;
    // cout<<"finished rotation\n";
}

void AVLtree::rotateLR(Node *n){ //double rotate right
    // cout<<"rotateRR\n";
    // Node* p = n->left;
    // Node* q = p->right;
    // if(q->left)
    //     p->right = q->left;
    // else if(q->right)
    //     p->right = q->right;
    // else if(!q->right || !q->left) p->right = NULL;
    // n->left = q;
    // q->parent = n;
    // q->left = p;
    // p->parent = q;
    rotateL(n->left);
    rotateR(n);

}

int AVLtree::getHeight(Node *n) 
{
    if (!n) return 0;
    else{
        int heightL = 0;
        int heightR = 0;
        if (n->left)
            heightL = getHeight(n->left);
        else heightL = 0;
        if (n->right)
            heightR = getHeight(n->right);
        else heightR = 0;
        if (heightL > heightR)
            return heightL + 1;
        else return heightR + 1;
    }
}

int AVLtree::getLHeight(Node *n) 
{
    if(n->left);
        return getHeight(n->left);
}

int AVLtree::getRHeight(Node *n) 
{
    if(n->right);
        return getHeight(n->right);
}

void AVLtree::dNHelper(Node* root, int level, int& maxLevel, Node*& deepest) 
{
    if(root != NULL){
        dNHelper(root->left, ++level, maxLevel, deepest);
        if(level>maxLevel)
        {
            deepest = root;
            maxLevel = level;
        }
        dNHelper(root->right, ++level, maxLevel, deepest);
    }
}

void* AVLtree::kdeepestNode(Node *n, Node*& p, int k) 
{
    if(n){
        if(n && !k)
            p = n;
        kdeepestNode(n->left, p, k-1);
        kdeepestNode(n->right, p, k-1);
    }
}



