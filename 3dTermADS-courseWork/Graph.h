#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;



// Edge structure with string vertices
struct Edge
{
    int weight;
    string src, dest; // Use strings for src and dest
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }
};

// Union-Find structure for Kruskal's algorithm
class UnionFind
{
private:
    unordered_map<string, string> parent; // Maps vertex labels to their parents
    unordered_map<string, int> rank; // Maps vertex labels to their ranks

public:
    void makeSet(const string& vertex)
    {
        parent[vertex] = vertex; // Each vertex is its own parent initially
        rank[vertex] = 0; // Initial rank is 0
    }

    string find(const string& vertex)
    {
        if (parent[vertex] != vertex)
        {
            parent[vertex] = find(parent[vertex]); // Path compression
        }
        return parent[vertex];
    }

    void unionSets(const string& u, const string& v)
    {
        string rootU = find(u);
        string rootV = find(v);
        if (rootU != rootV) {
            // Union by rank
            if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};



class Graph
{
private:
    vector<vector<int>> adjMatrix;
    unordered_map<string, int> vertexMap;
    vector<string> vertices;

public:
    // Constructors to initialize the graph
    Graph();
    Graph(const string& filename);

    // Function to add a vertex
    void addVertex(const string& vertex);

    // Function to add a weighted edge between two vertices
    void addEdge(const string& v1, const string& v2, int weight);

    // Function to display the adjacency matrix with vertex labels
    void displayMatrix();

    void readGraphFromFile(const string& filename);

    // Method to perform Kruskal's algorithm
    void kruskalMST();
};

// Method implementations

Graph::Graph()
{

}

Graph::Graph(const string& filename)
{
    readGraphFromFile(filename);
}

void Graph::addVertex(const string& vertex)
{
    if (vertexMap.find(vertex) == vertexMap.end())
    {
        vertexMap[vertex] = vertices.size(); // Map vertex label to index
        vertices.push_back(vertex); // Add vertex label to list

        // Resize the adjacency matrix
        for (auto& row : adjMatrix)
        {
            row.resize(vertices.size(), 0); // Initialize with 0
        }
        adjMatrix.resize(vertices.size(), vector<int>(vertices.size(), 0)); // Initialize with 0
    }
}

void Graph::addEdge(const string& v1, const string& v2, int weight)
{
    if (vertexMap.find(v1) != vertexMap.end() && vertexMap.find(v2) != vertexMap.end())
    {
        int i = vertexMap[v1];
        int j = vertexMap[v2];
        adjMatrix[i][j] = weight; // Set the weight from v1 to v2
        adjMatrix[j][i] = weight; // Since the graph is undirected
    }
}

void Graph::displayMatrix()
{
    for (const auto& vertex : vertices)
    {
        if (!vertexMap[vertex]) {cout << " ";}
        cout << " " << vertex;
    }
    cout << endl;

    for (size_t i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i]; // Print row label
        for (size_t j = 0; j < vertices.size(); j++)
        {
            cout << " " << adjMatrix[i][j]; // Print weight or 0 for no edge
        }
        cout << endl;
    }
}

void Graph::readGraphFromFile(const string& filename)
{
    this->adjMatrix.clear();
    this->vertices.clear();
    this->vertexMap.clear();

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;

    // Read the first line for vertex labels
    if (getline(file, line))
    {
        istringstream iss(line);
        string vertex;

        while (iss >> vertex) // Read each vertex as a string
        {
            addVertex(vertex); // Use addVertex to add each vertex
        }
    }

    // Read the adjacency matrix
    size_t row = 0;
    while (getline(file, line))
    {
        istringstream iss(line);
        string value;
        size_t col = 0;

        while (iss >> value) // Read each value as a string
        {
            if (col < vertices.size() && row < vertices.size())
            {
                int weight = stoi(value);
                if (weight != 0) // Only add edges for non-zero weights
                {
                    addEdge(vertices[row], vertices[col], weight); // Use addEdge to add edges
                }
            }
            col++;
        }
        row++;
    }

    file.close();
}

void Graph::kruskalMST()
{
    vector<Edge> edges;

    // Create a list of edges from the adjacency matrix
    for (size_t i = 0; i < vertices.size(); i++)
    {
        for (size_t j = i + 1; j < vertices.size(); j++)
        {
            // Avoid duplicate edges
            if (adjMatrix[i][j] != 0)
            {
                // There is an edge
                edges.push_back({adjMatrix[i][j], vertices[i], vertices[j]}); // Use strings for src and dest
            }
        }
    }

    // Sort edges based on weight
    sort(edges.begin(), edges.end());

    UnionFind uf;

    // Initialize the union-find structure with all vertices
    for (const auto& vertex : vertices)
    {
        uf.makeSet(vertex);
    }

    cout << "Edges in the Minimum Spanning Tree:" << endl;

    int totalWeight = 0;
    for (const auto& edge : edges)
    {
        string uRoot = uf.find(edge.src);
        string vRoot = uf.find(edge.dest);

        if (uRoot != vRoot)
        {
            // If they are not in the same set
            uf.unionSets(uRoot, vRoot); // Union the sets
            cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl; // Print edge
            totalWeight += edge.weight;
        }
    }
    cout << "Total weight: " << totalWeight << endl;
}


#endif // GRAPH_H
