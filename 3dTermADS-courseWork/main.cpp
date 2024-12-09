#include "Graph.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

const string FILE_PATH = "/home/theo/projects/allgorithms2024/3dTermADS-courseWork/3dTermADS-courseWork/file.txt";


int main()
{
    Graph g(FILE_PATH);

    cout << "Adjacency Matrix:" << endl;
    g.displayMatrix(); // Display the adjacency matrix

    g.kruskalMST();

    return 0;
}
