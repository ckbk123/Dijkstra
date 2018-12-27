#include <iostream>
#include "algorithm.hpp"

using namespace std;

// class initialiser
VERTEX::VERTEX (int to_input, int from_input, int distance_input) {
  to = to_input;
  from = from_input;
  distance = distance_input;
}

// a small sorting algorithm to help organise the vertex stack
void sortPriorityQueue (vector<VERTEX> &input) {
  for (vector<VERTEX>::iterator it = input.begin(); it != input.end(); it++) {
    for (vector<VERTEX>::iterator at = it; at != input.end(); at++) {
      if ((*at).distance < (*it).distance) {
	VERTEX temp_node((*at).to,(*at).from,(*at).distance);
	*at = *it;
	*it = temp_node; 
      }else;
    }
  }
}

// Dijkstra algorithm and print out the shortest path between the 2 points of the graph
void findDijkstraPath(vector < vector<int> > network, int start, int end) {

  // declare the priority queue.
  vector<VERTEX> priorityQueue;
  
  // assign priority queue with default values: 0 for the starting node and infinite(999999) for all other nodes
  for (int i = 1; i < network.size()+1 ; i++) {
    VERTEX new_vertex(i, start, [i, start]() {return (i==start) ? 0 : infinity;}());
    priorityQueue.push_back(new_vertex);
  }

  // sort the priority queue
  sortPriorityQueue(priorityQueue);
  
  /*
    ALGORITHM NOTE:
    - access priority queue via index
    - then search all points that are connected to the current node, assign the distance to them if they are smaller than current values and that point is not the point where they came from
  */
  for (int i = 0; i < priorityQueue.size(); i++) {
    // first we find the corresponding node to the point that we want
    int currentNode = priorityQueue[i].to-1; // a simple conversion to match vector index
    cout << "Calculating for node " << priorityQueue[i].to << endl;
    // if we reach calculating for node N, it means that the path that reach N is indeed the shortest, so no need to do anything further if this is our endpoint

    if ([=]()->bool{
	bool found_shortest = false;
	for (int k = 0; k < priorityQueue.size(); k++) {
	  if (priorityQueue[k].to == end && priorityQueue[k].distance == priorityQueue[i].distance) {
	    found_shortest = true;
	    break;
	  }
	}
	return found_shortest;
      }()
      )
    {
      // this if would treat the case where there are multiple shortest path. If we calculate the shortest path from a given point, and the distance to this point is equal to the current distance to our end node, we can be sure that the shortest path to the end node has been achieved
      cout << "We have reached the destination via the shortest path" << endl;
      break;
      ///////////////////////////////////////////////////////////////////////////////////////////
    }else if (priorityQueue[i].to != end) {
      // here b is a node is a node that the current node CAN reach
      for (int b = 0; b < network[currentNode].size(); b++) {
	// this condition verify that b is reacheable from the currentNode and that it is not a backtrack
	if (network[currentNode][b]!=0 && (b+1)!=priorityQueue[i].from) {
	  // here a is used as an index to find the node defined by b from the priorityQueue, so that we can assign value to them if possible
	  for (int a = 0; a < priorityQueue.size(); a++) {
	    // verifies that the a is the correct index and the new path to 
	    if (priorityQueue[a].to == b+1 && (network[currentNode][b]+priorityQueue[i].distance) < priorityQueue[a].distance) {
	      priorityQueue[a].distance = network[currentNode][b]+priorityQueue[i].distance;  
	      priorityQueue[a].from = priorityQueue[i].to;
	    }else;
	  }
	}else;
      }
      ///////////////////////////////////////////////////////////////////////////////////////////
    }else {
      cout << "We have reached the destination via the shortest path" << endl;
      break;
    }
    sortPriorityQueue(priorityQueue);

    cout << "Algorithm test update :" << endl;
    for (vector<VERTEX>::iterator it = priorityQueue.begin(); it != priorityQueue.end(); it++) {
      cout << "Coming to "<< (*it).to << " from node " << (*it).from << " at a distance of " << (*it).distance << endl;
    } cout << endl;
  }

  // last, display the shortest path that connects the end point with the starting point
  int backtrack = end;
  vector <int> dijkstra_path = {end};

  cout << "The shortest path from " << start << " to " << end  << " at a distance of " <<
    [=]()->int{
    int distance;
    for (int j = 0; j < priorityQueue.size(); j++) {
      if (priorityQueue[j].to == end) {
        distance = priorityQueue[j].distance;
	break;
      }
    }
    return distance;
  }()
     << " is: " << endl;
  // find the path list that 
  while (backtrack != start) {
    for (int k = 0; k < priorityQueue.size(); k++) {
      if (priorityQueue[k].to == backtrack) {
	dijkstra_path.push_back(priorityQueue[k].from);
	backtrack = priorityQueue[k].from;
	break;
      }else;
    }
  }
  // display the path
  for (int i = dijkstra_path.size()-1; i > 0; i--) {
    if (i != 1) {
      cout << dijkstra_path[i] << " -> ";
    }else {
      cout << dijkstra_path[i] << " -> " << dijkstra_path[i-1] << endl;
    }
  }
}

