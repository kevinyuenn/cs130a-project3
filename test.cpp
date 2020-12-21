#include "avltree.h"
#include <iostream>

using namespace std;

int main(){
    AVLtree test(1);
    test.insert(1,0);
    test.insert(2,0);
    test.insert(3,0);
    // test.insert(3,0);
    // test.insert(5,0);
    // test.insert(10,0);
    // test.insert(9,0);
    cout<<"inorder: "; 
    test.printInOrder();
    cout<<endl;
    cout<<"preorder: ";
    test.printPreOrder();
    cout<<endl;
}