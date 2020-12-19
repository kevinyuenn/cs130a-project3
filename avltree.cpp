#include "avltree.h"
#include <tuple>
#include <iostream>

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