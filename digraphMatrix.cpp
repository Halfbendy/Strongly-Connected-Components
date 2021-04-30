#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#include "digraphMatrix.h"

//Driver Justina Le
// Navigator Louis-Marie Mondesir
DigraphMatrix::DigraphMatrix(const string& file) {
    ifstream f(file);
    string str;
    
    int i = 0;
    int m;
    int u;
    int v;

    if (f.is_open()) {
        
        while (!f.eof()) {
            getline(f, str);
            
            if(i == 0) {
                istringstream is(str);
                
                is >> n >> m;
                A.resize(n, vector<bool>(n));
            }
            else {
                istringstream is(str);
                
                is >> u >> v;
                A[u][v] = 1;
            }
            i++;
        }
        
        for (int i = 0; i < n; i++)
         {
         
            marks.emplace(i,UNDISCOVERED); 
         
         }  
        
        for (int i = 0; i < n; i++)
         {
            if (marks.at(i) == UNDISCOVERED)
               DFS(i);
         }
         
    }

    //displayMatrix(n); // uncomment to check the matrix entered //checking if matrix works
}

//Driver Justina Le
//Navigator Louis-Marie Mondesir
vector<int> DigraphMatrix::getInNeighbors(int u) {
   
    vector<int> vec;
    for(int i = 0; i < n;  i++) {
        if (A[i][u] == true) {
            vec.push_back(i);
        }
    }
    return vec;
}

//Driver Justina Le
//Navigator Louis-Marie Mondesir
vector<int> DigraphMatrix::getOutNeighbors(int u) {

    vector<int> vec;
    for(int i = 0; i < n;  i++) {
        if (A[u][i] == true) {
            vec.push_back(i);
        }
    }
    return vec;
}

//Driver Louis-Marie Mondesir
//Navigator Justina Le
bool DigraphMatrix::path(vector<vector<bool>> A, int u, int v)
   {
      vector<vector<bool>> copy = A;
        
      if (copy[v][u] == 1)
         return true;
      else 
         {
            if (copy[v][v] != 1)
               {
                  copy[v][v] = 1; 
                  for (int i = 0; i < copy[v].size(); i++)
                     {
                        //cout << "[v][v]: " << A[v][v] << endl;
                           
                        //cout << "I: " << i << endl;
                        
                        if (i == v)
                           continue;
                        
                        if (copy[v][i] == 1)
                           {
                              //cout << "Checking i: " << i << endl;
                              
                              bool temp = path(copy, u, i);
                              
                              if (temp)
                                 return true;
                                  
                           }        
                     }
               }  
 
         }    
      
      return false; 
   }

//Driver Louis-Marie Mondesir
//Navigator Justina Le
vector<int> DigraphMatrix::component(int k)
   {
      vector<int> temp;
      
      temp.push_back(k);
      
      for (int i = 0; i < n; i++)
         {
            if (i != k)
               {
                  if(path(A, i, k) && path(A, k, i))
                     {
                        temp.push_back(i);
                     }
               }  
         }
      
      return temp;
   }

//Driver Louis-Marie Mondesir
//Navigator Justina Le
vector<int> DigraphMatrix::stronglyConnectedComponents()
   {
   
      vector<int> components;
      
      vector<int> temp;
      
      int ID = 0;
   
      for (int i = 0; i < n; i++)
         {
            components.push_back(-1);
         }
         
      //cout << "Explored Size: " << explored.size() << endl;
      
      while (!explored.empty())
         {   
            //cout << explored.top() << endl;
         
            if (components.at(explored.top()) == -1)
               {
                  temp = component(explored.top());
                  
                  for (int j = 0; j < temp.size(); j++)
                     {
                     
                        //cout << temp.at(j) << ' ';
                     
                        components.at(temp.at(j)) = ID;
                     }       
                     
                  ID++;   
               }
               
            explored.pop();   
         }
         
      return components;
   }  
 
//Modification of DFS from Lecture 23 graph-traversals.cpp
void DigraphMatrix::DFS(const int& v)
   {  
      //Mark v discovered
      
      marks.at(v) = DISCOVERED;  
      //cout << v << ", "; 
      
      //Iterate through neighbors of v  
      
      for (int c : getOutNeighbors(v))    
         {if (marks.at(c) == UNDISCOVERED)      
           { DFS(c);}}
              
      //Mark v explored 
      
      //cout << "Before explored: " << v << endl;
      
      explored.push(v); 
      
      marks[v] = EXPLORED;
      
      
      
   }