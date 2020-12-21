#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include <stdlib.h>
#include <tuple>

using namespace std;

class AVLtree{
    public:
        AVLtree();
        AVLtree(int k): k(k){}
        ~AVLtree();
        void insert(int integer, int decimal);
        void remove(int integer, int decimal);
        bool search(int integer, int decimal);
        tuple<int,int> approxSearch(int integer, int decimal);
        void printInOrder();
        void printPreOrder();
    private:
        struct Node{
            Node(){
                value = make_tuple(0,0);
                // depth, leftHeight, rightHeight = 0;
                left = right = parent = NULL;
            }
            Node(int integer, int decimal){
                value = make_tuple(integer, decimal);
                // depth, leftHeight, rightHeight = 0;
                left = right = parent = NULL;
            }
            tuple<int,int> value;
            // int depth;
            // int leftHeight;
            // int rightHeight;
            Node *left;
            Node *right;
            Node *parent;
        };
        void clear(Node *n);
        int k;
        Node *root;
        void printInOrder(Node *n);
        void printPreOrder(Node *n);
        Node* getNodeFor(int integer, int decimal, Node* n);
        void rotate(Node *n);
        void rotateL(Node *n);
        void rotateR(Node *n);
        void rotateLR(Node *n);
        void rotateRL(Node *n);
        int getHeight(Node *n);
        int getLHeight(Node *n);
        int getRHeight(Node *n);
        void dNHelper(Node *root, int level, int& maxLevel, Node*& deepest);
        Node* deepestNode(Node *root, int k);
        void insert(Node *n, int integer, int decimal);
        void findRotation(Node *n);
};

#endif // __AVLTREE_H__