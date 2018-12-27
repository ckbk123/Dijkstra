#ifndef _ALGORITHM_HPP_
#define _ALGORITHM_HPP_

#include <vector>

using namespace std;
const int infinity = 999999;

// vertex is the element that store the distance to a point in the priority queue and its origin
class VERTEX {
 public:;
  int to;
  int from;
  int distance;

  VERTEX (int to_input, int from_input, int distance_input);
};

// a small sorting algorithm to help organise the vertex stack
void sortPriorityQueue (vector<VERTEX> &input);

// Dijkstra algorithm
void findDijkstraPath(vector < vector<int> > network, int start, int end);

#endif
