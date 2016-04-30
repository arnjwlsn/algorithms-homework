#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>

int size;

// signatures
struct Node;
struct Edge;

struct Node {
  int id;
  int distance;
  bool visited;
  Node *parent;
  std::vector<Edge *> edges;

  Node() {}

  Node(Node *&node) : id(node->id), distance(node->distance), visited(node->visited) {
    parent = node->parent;
    edges = node->edges;
  }
};

struct Compare {
  bool operator()(Node *first, Node *second) {
    return first->distance > second->distance;
  }
};

struct Edge {
  int distance;
  Node *source;
  Node *destination;
};

void print_pqueue(const std::priority_queue<Node *, std::vector<Node *>, Compare> &pqueue) {
  std::priority_queue<Node *, std::vector<Node *>, Compare> copy(pqueue);
  while (copy.size() > 0) {
    std::cout << "(" << copy.top() << ": " << copy.top()->id << " - " << copy.top()->distance << ") ";
    copy.pop();
  }
  std::cout << std::endl;
}

bool dijkstra_search(Node *source, Node *destination) {
  // Creating a priority queue is O(nlogn) because each insert is O(logn) and
  // you are inserting n things.
  // Taking something from the top of the pqueue is O(1)
  std::priority_queue<Node *, std::vector<Node *>, Compare> to_visit;
  to_visit.push(source);

  int step = 0;

  while (step < size*size && to_visit.size() > 0) {
    //print_pqueue(to_visit);
    ++step;
    // std::cout << "Current step: " << step++ << std::endl;

    // Take current from the top of the pqueue
    Node *current = to_visit.top();
    // Remove the top from the pqueue
    to_visit.pop();
    current->visited = true;

    //std::cout << "At node " << current->id << std::endl;

    if (current->id == destination->id) {
      std::cout << "From Node (" << source->id << ") to Node (" <<  destination->id << ")" << std::endl;
      std::cout << "  Cost: " << current->distance << std::endl;

      std::vector<int> print;
      Node *backtrace = current;
      while (backtrace->id != source->id) {
        //std::cout << backtrace->id << std::endl;
        print.push_back(backtrace->id);
        backtrace = backtrace->parent;
      }
      //std::cout << source->id << std::endl;
      print.push_back(source->id);

      // Reverse path to show start -> finish
      std::reverse(print.begin(), print.end());

      std::cout << "  Path: ";
      for(int i = 0; i < print.size()-1; ++i) {
        std::cout << "(" << print[i] << ")->"; 
      }
      std::cout << "(" << print[print.size()-1] << ")" << std::endl;

      return true;
    }

    // Pre-increment does NOT make a copy of the variable
    // Post-increment needs to first copy i, then read it from memory,
    // THen add 1 to the copy, and place the copy back into i
    // Pre-increment just increments i
    // Note: most compilers fix this anyways and don't give a shit

    // Grab all edges that current is connected to
    //std::cout << "There are " << current->edges.size() << " current->edges.size()" << std::endl;
    for (size_t i = 0; i < current->edges.size(); ++i) {
      Edge *current_edge = current->edges[i];
      Node *next = new Node(current_edge->destination);
      if (!next->visited) {
        next->parent = current;
        next->distance = current->distance + current_edge->distance;//+= current_edge->distance; next->parent = current;
        //std::cout << "We need to travel " << current_edge->distance << " to get to " << next->id << std::endl;
        //std::cout << "We've traveled " << current->distance << " so far" << std::endl;
        //std::cout << "Adding node " << next->id << " is " << next->distance << " total" << std::endl;
        to_visit.push(next);
      }
    }
  }
  // No path was found
  return false;
}

int main() {
  std::ifstream myfile;
  myfile.open("input.inp");
  
  myfile >> size;
  
  std::vector<Node *> nodes;
  nodes.reserve(size);

  // created all nodes
  for (size_t i = 0; i < size; ++i) {
    Node *new_node = new Node();
    new_node->id = i;
    new_node->distance = 0;
    new_node->visited = false;
    new_node->parent = NULL;
    nodes.push_back(new_node);
  }

  // connect the nodes together
  for (size_t i = 0; i < size; ++i) {
    // Start connecting to all the nodes its connected to
    for (size_t j = 0; j < size; ++j) {
      int cost;
      myfile >> cost;
      if (cost > 0) {
        Node *source_copy(nodes[i]);
        Node *destination_copy(nodes[j]);
        Edge *new_edge = new Edge();

        // edges get added here
        nodes[i]->edges.push_back(new_edge);

        new_edge->distance = cost;

        // This doesn't have edges yet
        new_edge->source = source_copy;
        new_edge->destination = destination_copy;
      }
    }
  }

  /*
  for (size_t i = 0; i < nodes.size(); ++i) {
    Node *node = nodes[i];
    std::cout << "Node " << node->id << " is connected to:" << std::endl;
    for (size_t j = 0; j < node->edges.size(); ++j) {
      Edge *edge = node->edges[j];
      std::cout << "  Node " << edge->destination->id << " with cost of " << edge->distance << std::endl;
    }
    std::cout << std::endl;
  }
  */

  int start = 0, finish = 0;
  std::cout << "This country contains " << size << " cities labeled 0-" << (size-1) << std::endl;
  do {
    std::cout << "Starting Node: ";
    std::cin >> start;
    std::cout << "Finishing Node: ";
    std::cin >> finish;
  } while(start < 0 || start >= size || finish < 0 || finish >= size); 
  std::cout << "-------------------" << std::endl;

  bool found = dijkstra_search(nodes[start], nodes[finish]);
  if(!found) std::cout << "No path found from Node (" << start << ") to Node (" << finish << ")" << std::endl;

  return 0;
}
