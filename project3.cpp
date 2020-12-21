#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include "kavl.h"


using namespace std;

int main(int argc, char *argv[]){
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


    Kavl test(stoi(in[0]));
    int i = 1;
    //while(i<in.size()){

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

        }
        else if(in[i]=="in_order"){
            test.printInOrder();

        }
        else{
            cout<<in[i]<<" is not recognized"<<endl;
        }
    }
    return 0;
}