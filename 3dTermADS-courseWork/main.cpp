#include "Graph.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;


void readGraphFromFile(const std::string& filename, std::vector<std::vector<int>>& adjacencyMatrix, std::vector<char>& vertices)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;

    // Read the first line for vertex labels
    if (std::getline(file, line))
    {
        for (char vertex : line)
        {
            if (vertex != ' ')
            {
                // Ignore spaces
                vertices.push_back(vertex);
            }
        }
    }

    // Initialize adjacency matrix with zeros
    size_t size = vertices.size();
    adjacencyMatrix.resize(size, std::vector<int>(size, 0));

    // Read the adjacency matrix
    size_t row = 0;
    while (std::getline(file, line) && row < size)
    {
        std::istringstream iss(line);
        std::string value;
        size_t col = 0;

        while (std::getline(iss, value, ' '))
        {
            if (col < size)
            {
                adjacencyMatrix[row][col] = std::stoi(value);
                col++;
            }
        }
        row++;
    }

    file.close();
}


int main()
{

    std::vector<std::vector<int>> adjacencyMatrix;
    std::vector<char> vertices;

    readGraphFromFile("/home/theo/projects/allgorithms2024/3dTermADS-courseWork/3dTermADS-courseWork/file.txt", adjacencyMatrix, vertices);

    // Output the results for verification
    std::cout << "Vertices: ";
    for (char vertex : vertices)
    {
        std::cout << vertex << " ";
    }
    std::cout << "\nAdjacency Matrix:\n";


    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            cout << adjacencyMatrix[row][col] << " ";
        }
        cout << endl;
    }

    return 0;
}
