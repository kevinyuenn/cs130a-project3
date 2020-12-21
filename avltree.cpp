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
    cout<<"left height: "<<getLHeight(n)<<" right height: "<<getRHeight(n)<<endl;
    if(getLHeight(n) - getRHeight(n) < -k){ //rotateL
        if(n->right->right){
            if(n->right->left){
                rotateL(n);
            }
            else{
                rotateL(n);
            }
            cout<<"Finished rotation\n";
        }
        else if(n->right->left){
            rotateRL(n);
        }
    }
    else if(getLHeight(n) - getRHeight(n) > k){ //rotateR
        if(n->left->left){
            if(n->left->right){
                rotateR(n);
            }
            else rotateR(n);
        }
        else if(n->left->right){
            rotateLR(n);
        }
    }
    if(n->parent) findRotation(n->parent);
}

void AVLtree::remove(int integer, int decimal) 
{
    
}

bool AVLtree::search(int integer, int decimal) 
{
    if (getNodeFor(integer, decimal, root)) return true;
    return false;
}

tuple<int,int> AVLtree::approxSearch(int integer, int decimal) 
{
    
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
        if(get<0>(n->value)==integer || get<1>(n->value)==decimal)
            return n;
        else{
            Node *p = getNodeFor(integer, decimal, n->left);
            if(p) return p;
            else return getNodeFor(integer, decimal, n->right);
        }
    }
    return NULL;
}

void AVLtree::rotate(Node *n) 
{
    if(!n) return;
    if(!n->parent) return;
    if(!n->parent->parent) return;
    if ((n == n->parent->right) && (n->parent->left)
        && (n->parent == n->parent->parent->right) 
        && (n->parent->parent->left)) //rotateL case
        rotateL(n);
    else if ((n == n->parent->left) && (n->parent->right == NULL)
        && (n->parent == n->parent->parent->left)
        && (n->parent->parent->right == NULL)) //rotateR case
        rotateR(n);
    else if ((n == n->parent->right) && (n->parent->left == NULL)
        && (n->parent == n->parent->parent->left)
        && (n->parent->parent->right == NULL)) //rotateLR
        rotateLR(n);
    else if ((n == n->parent->left) && (n->parent->right == NULL)
        && (n->parent == n->parent->parent->right)
        && (n->parent->parent->left == NULL)) //rotateRL
        rotateRL(n);

}

// void AVLtree::rotateL(Node *c) 
// {
//     Node* b = c->parent;
//     Node* a = b->parent;
//     if (a->parent)
//         a->parent->right = b;
//     if(b->left)
//         a->right = b->left;
//     else a->right = NULL;
//     b->parent = a->parent;
//     a->parent = b;
//     b->left = a;

//     if (a == root){
//         root = b;
//     }
//     // a->depth += 1;
//     // b->depth -= 1;
//     // c->depth -= 1;
// }

// void AVLtree::rotateR(Node *a) 
// {
//     cout<<"rotateR\n";
//     Node* b = a->parent;
//     // cout<<"here";
//     Node* c = b->parent;
//     // cout<<"here";
//     if( c->parent)
//         c->parent->left = b;
//     if(b->right)
//         c->left = b->right;
//     b->parent = c->parent;
//     c->parent = b;
//     b->right = c;
//     c->left = NULL;
//     if (c == root){
//         root = b;
//     }
//     // c->depth++;
//     // b->depth--;
//     // a->depth--;
// }

// void AVLtree::rotateLR(Node *b) 
// {
//     cout<<"rotateLR\n";
//     Node* a = b->parent;
//     Node* c = a->parent;
//     // c->left = b;
//     // b->left = a;
//     // b->parent = c;
//     // a->parent = b;
//     // a->right = NULL;
//     b->parent = c;
//     c->left = b;
//     a->parent = b;
//     a->right = NULL;
//     b->left = a;
//     rotateR(a);
//     // cout<<"finish\n";
//     // b->depth--;
//     // a->depth++;
//     // rotateR(a);
// }

// void AVLtree::rotateRL(Node *b) 
// {
//     cout<<"rotateRL\n";
//     Node* c = b->parent;
//     Node* a = c->parent;
//     b->parent = a;
//     a->right = b;
//     c->parent = b;
//     b->right = c;
//     c->left = NULL;
//     // a->left = b->left = b->right =c->right = NULL;
//     // b->left = a;
//     // b->right = c;
//     // a->parent = b;
//     // c->parent = b;
//     // if(c==root)
//     //     root = b;
//     rotateL(c);
// }

void AVLtree::rotateL(Node *n){
    cout<<"rotateL\n";
    Node *p = n->right;
    Node *q = p->right;
    
    p->left = n->right;
    p->parent = n->parent;
    n->parent = p;
    p->left = n;
    p->right = q;
    q->parent = p;


    if(n == root){
        root = p;
    }
    cout<<"p: "<<get<0>(p->value)<<endl;
    cout<<"n: "<<get<0>(n->value)<<endl;
    cout<<"q: "<<get<0>(q->value)<<endl;
    cout<<"root: "<<get<0>(root->value)<<endl;
    cout<<"root right: "<<get<0>(root->right->value)<<endl;
    cout<<"root left: "<<get<0>(root->left->value)<<endl;
    cout<<"finished rotation\n";
}

void AVLtree::rotateRL(Node *n){
    cout<<"rotateRL\n";
    Node *p = n->right;
    Node *q = p->left;

    n->right = q;
    q->parent = n;
    q->right = p;
    p->parent = q;
    p->left = NULL;
    rotateL(n);
}

void AVLtree::rotateR(Node *n){
    cout<<"rotateR\n";
    Node *p = n->left;
    Node *q = p->left;

    n->left = p->right;
    p->right = n;
    p->parent = n->parent;
    n->parent = p;
    q->parent = n;

    if(n == root && n->parent == p){
        root = p;
    }
}

void AVLtree::rotateLR(Node *n){
    cout<<"rotateLR\n";
    Node* p = n->left;
    Node* q = p->right;
    n->left = q;
    q->parent = n;
    q->left = p;
    p->parent = q;
    p->right = NULL;
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

AVLtree::Node* AVLtree::deepestNode(Node *root, int k) 
{
    Node* deepest = root;
    int maxLevel = -1;
    dNHelper(root, 0, maxLevel, deepest);
    // cout<<"deepest value: "<<get<0>(deepest->value);
    return deepest;
}



