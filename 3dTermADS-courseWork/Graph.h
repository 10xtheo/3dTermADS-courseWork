#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    vector<vector<int>> adjMatrix; // Adjacency matrix to store graph edges

public:
    Graph();
    ~Graph();

    void printGraph();
};

#endif // GRAPH_H
