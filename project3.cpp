#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include "avltree.h"


using namespace std;

int main(int argc, char *argv[]){
    cout<<argv[1]<<endl;
    string inputs = argv[1];
    vector<string> in;

    int start = 0;
    for(int i = 0; i < inputs.length(); i++){
        if (inputs[i] == ' '){
            in.push_back(inputs.substr(start, i-start));
            start = i + 1;
            i = start;
        }
        if (inputs[i] == ','){
            in.push_back(inputs.substr(start, i-start));
            start = i + 2;
            i = start;
        }
        if (i == inputs.length()-1){
            in.push_back(inputs.substr(start, i-start+1));
        }
    }

    // int offset = stoi(in[0]);
    // cout<<offset<<endl;
    AVLtree test(stoi(in[0]));
    int i = 1;
    int integer, decimal;
    for(int i = 1;i <in.size();i++){
        if(in[i]=="insert"){
            test.insert(stoi(in[i+1]),stoi(in[i+2]));
            i+=2;

        }
        else if(in[i]=="search"){
            test.search(stoi(in[i+1]),stoi(in[i+2]));
            i+=2;

        }
        else if(in[i]=="approx_search"){
            test.search(stoi(in[i+1]),stoi(in[i+2]));
            i+=2;
        }
        else if(in[i]=="delete"){
            if(test.remove(stoi(in[i+1]),stoi(in[i+2]))){
                cout<<in[i+1]<<"."<<in[i+2]<<" deleted"<<endl;
            }
            i +=2;

        }
        else if(in[i]=="pre_order"){
            test.printPreOrder();
            cout<<endl;

        }
        else if(in[i]=="in_order"){
            test.printInOrder();
            cout<<endl;

        }
        else{
            cout<<in[i]<<" is not recognized"<<endl;
        }
    }
    return 0;
}