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
    // test.remove(2,0);

    // test.insert(10,0);
    // test.insert(8,0);
    // test.insert(7,0);
    // test.insert(2,0);
    // test.insert(1,0);
    // test.insert(5,0);


    // test.insert(3,0);
    // test.insert(5,0);
    // test.insert(4,0); //testing rL
    // test.remove(4,0);

    // test.insert(3,0);
    // test.insert(5,0);
    // test.insert(4,0); //testing rRL

    // test.insert(4,0);
    // test.insert(3,0);
    // test.insert(2,0); //testing rR

    // test.insert(4,0);
    // test.insert(2,0);
    // test.insert(3,0); //testing rLR

    cout<<"inorder: "; 
    test.printInOrder();
    cout<<endl;
    cout<<"preorder: ";
    test.printPreOrder();
    cout<<endl;
}