/*
CSC 331 - 170L
Majdi Nagi
csc331_170_prog3_Nagi.cpp
Assignment 3 due 11:59pm Saturday 4-4-2020.
Purpose: The purpose of this program is to calculate a postFix experssion, evaluate and printing the answer using stack pushing and popping functions from the STL. Also,this program will not accept any division by zero. And it will show an error message if there is.
*/

#include<iostream>
#include<cmath>
#include<stack>
using namespace std;

int operations(int, int, char);

int main(){
    int num1, num2;
    int result;
    stack<int> s1;
    string E;
    
    cout << "Please enter an expression in post-fix notation: (enter 'end-of-file' when done)..."<<endl;
    cin >> E;
    while(E.compare("end-of-file") != 0){
        for(int i = 0; i< E.length(); i++){
            char x = E[i];
            if((x >= '0')&&(x <='9')){
                int I;
                I = x - 48;
                s1.push(I);
            }
            else if (E[i]=='+' || E[i]=='-' || E[i]=='*' || E[i]=='/'){
                num1 = s1.top();
                s1.pop();
                num2 = s1.top();
                s1.pop();
                s1.push(operations(num1, num2, E[i]));
            }
        }
        result = s1.top();
        if(result != -1){
            cout<<"result= "<< result;
        }
        cout << "\nPlease enter an expression in post-fix notation: (enter 'end-of-file' when done) ";
        cin >> E;
    }
    cout << "good-bye." << endl;
    
    return 0;
}

int operations(int num1, int num2, char op) {
    int num = 0;
    if(op == '+'){
        num = num2 + num1;
        return num;
    }
    else if(op == '-'){
        num = num2 - num1;
        return num;
    }
    else if(op == '*'){
        num = num2 * num1;
        return num;
    }
    else if(op == '/'){
        if(num1 == 0)
            cout<<"error:division by zero";
        else
            return num2 / num1;
    }
    return -1;
}
