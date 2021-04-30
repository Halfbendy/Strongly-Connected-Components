#ifndef __DIGRAPH_H
#define __DIGRAPH_H

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };

class DigraphMatrix
{
public:
  int n;
  stack<int> explored;
  vector<vector<bool>> A;
  unordered_map<int, mark_t> marks;
//public:
  //Reads in digraph from given file
  //Stores graph as an adjacency matrix
  DigraphMatrix(const string&);

  //Returns number of vertices
  int getOrder() const { return n; }

  void addVertex();

  vector<int> getInNeighbors(int v);

  vector<int> getOutNeighbors(int v);

  void displayMatrix(int v);

  //Returns vector containing component ID for each vertex
  vector<int> stronglyConnectedComponents();
  
  vector<int> component(int);
  
  bool path(vector<vector<bool>>, int, int);
  
  void DFS(const int& v);

};

#endif