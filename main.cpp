#include <iostream>
#include <vector>
#include "algorithm.hpp"

using namespace std; 

int main () {
  int start, end, size;

  cout << "Shortest path finder using Dijkstra algorithm." << endl;
  cout << "Nodes must be numbered from 1 to n for a network with n nodes." << endl;
  
  cout << "Please input total nodes in the network: " << endl;
  cin >> size;
  cout << size << endl;
  vector< vector<int> > network(size, vector<int> (size,0));
  
  cout << "Next, please input the distance between each node. Note for unconnected nodes, put 0." << endl;
  for (int i = 0; i < size-1; i++) {
    for (int j = i+1; j < size; j++) {
      cout << "Node " << i+1 << " to " << j+1 << ": ";
      cin >> network[i][j];
      network[j][i] = network[i][j];
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << network[i][j] << ", ";
    }
    cout << endl;
  }
  
  cout << "Starting node: ";
  cin >> start;
  cout << "End node: ";
  cin >> end;
  
  findDijkstraPath(network,start,end);
}
