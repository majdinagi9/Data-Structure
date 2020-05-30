
/*
CSC 331 - 170L
Majdi Nagi
csc331_170_prog5_Nagi.cpp
Assignment 5 due 11:59pm Sunday 5-10-2020.
Purpose: The purpose of this code is to show if the graph is connected ot not. 
*/
#include <bits/stdc++.h> 
#include<cmath>
using namespace std; 

#define N 100000 

vector<int> gr1[N], gr2[N]; 
bool vis1[N], vis2[N]; 
void Add_edge(int u, int v) { 
    gr1[u].push_back(v); 
    gr2[v].push_back(u); 
} 
  
void graph1(int x){ 
    vis1[x] = true; 
    for (auto i : gr1[x]) 
        if (!vis1[i]) 
            graph1(i); 
} 
  
void graph2(int x){ 
    vis2[x] = true; 
  
    for (auto i : gr2[x]) 
        if (!vis2[i]) 
            graph2(i); 
} 
  
bool Is_Connected(int n){ 

    memset(vis1, false, sizeof vis1); 
    graph1(1); 

    memset(vis2, false, sizeof vis2); 
    graph2(1); 
  
    for (int i = 1; i <= n ; i++) { 

        if (!vis1[i] && !vis2[i]) 
            return false; 
    } 

    return true; 
} 

int main() { 
  string E; 
  int  edge = 0;
  cout<<"Enter number of edge from vertex x to vertex y and end-of-file to end the program: \n"; 
    getline (cin, E);
   
while(E.compare("end-of-file") != 0){
      int pos2=2;
      int num2;
      int num1 = stoi(E);
        istringstream(E.substr(pos2))>>num2;
        Add_edge(num1,num2);
        edge++;
        
     getline (cin, E);
    }
     if (Is_Connected(edge)) 

        cout << "Graph is connected"; 
      else
        cout << "Graph is not connected";

    return 0; 
} 
