#include "avltree.h"
#include <iostream>

using namespace std;

int main(){
    AVLtree test(1);
    // test.insert(5,0);
    // test.insert(1,0);
    // test.insert(2,0);
    // test.insert(7,0);
    // test.insert(8,0);
    // test.insert(10,0);
    // test.printPreOrder();
    // // test.remove(10,0);
    // test.remove(2,0);
    // test.printPreOrder();
    // test.remove(8,0);
    // test.remove(7,0);
    // test.remove(1,0);
    // test.remove(10,0);

    // test.remove(5,0);
    // test.remove(10,0);
    // test.remove(1,0);
    // test.remove(10,0);

    // test.insert(10,0);
    // test.insert(8,0);
    // test.insert(7,0);
    // test.insert(2,0);
    // test.insert(1,0);
    // test.insert(5,0);


    // test.insert(3,0);
    // test.insert(5,0);
    // test.insert(4,0); //testing rL
    // test.remove(5,0);

    // test.insert(3,0);
    // test.insert(5,0);
    // test.insert(4,0); //testing rRL

    // test.insert(4,0);
    // test.insert(3,0);
    // test.insert(2,0); //testing rR

    // test.insert(4,0);
    // test.insert(2,0);
    // test.insert(3,0); //testing rLR

    test.insert(4,5);
    test.insert(3,9);
    test.insert(3,5);
    test.insert(2,7);
    test.insert(2,6);
    test.insert(5,6);
    test.insert(4,2);
    test.insert(5,1);
    test.insert(5,4);
    test.insert(5,2);
    test.insert(4,1);

    test.remove(3,9);
    test.remove(2,7);
    test.remove(5,4);
    test.remove(5,2);
    test.remove(3,5);
    test.remove(2,6);
    test.remove(4,1);
    test.remove(5,6);
    test.remove(5,1);
    test.printInOrder();
    test.printPreOrder();
    cout<<"test.remove(4,5)\n";
    test.remove(4,5);
    test.printInOrder();
    test.printPreOrder();
    test.remove(4,2);


    cout<<"inorder: \n"; 
    test.printInOrder();
    cout<<endl;
    cout<<"preorder: \n";
    test.printPreOrder();
    cout<<endl;
}