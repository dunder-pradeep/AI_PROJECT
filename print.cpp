#include "print.h"
#include<iostream>

void print(vector<int> a){
    cout << "{ ";
    for(int i = 0;i < a.size() - 1;i++)
        cout << a[i] << ",";
    cout << a[a.size() -1];
    cout <<  " }" << endl;

}

void print(set<int> s){
    cout << "{  ";
    for(int i : s)
        cout << i << " ";
    cout << " }" << endl;
}

void printline(int n){
    for(int i = 0;i < n;i++)
        cout << "-";
    cout << endl;
}

