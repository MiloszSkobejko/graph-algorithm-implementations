# graph-algorithm-implementations
My journey with graphs, algorithms and its implementation in c++. 

The `graph` class is a C++ template class that represents an undirected graph and provides various graph-related functionalities. This class allows you to create, manipulate, and traverse graphs using adjacency lists or adjacency matrices. It includes implementations for Breadth-First Search (BFS), Depth-First Search (DFS), counting connected components, finding the largest component, counting islands, and calculating the shortest path between vertices.

## Table of Contents

1. [Introduction](#introduction)
2. [Class Features](#class-features)
   - [Constructor](#constructor)
   - [Adding Vertices and Edges](#adding-vertices-and-edges)
   - [Traversal Algorithms](#traversal-algorithms)
   - [Component and Island Counting](#component-and-island-counting)
   - [Shortest Path](#shortest-path)
3. [Usage](#usage)
4. [Examples](#examples)

## Introduction

The `graph` class provides a flexible and efficient way to work with graphs. It supports two methods of graph representation: adjacency lists and adjacency matrices. You can easily create a graph, add vertices and edges, and perform various graph traversal and analysis operations.

## Class Features

### Constructor

- `graph(int v_)`: Creates an empty graph with the specified number of vertices.
- `graph(std::vector<std::vector<Type> > & g)`: Constructs a graph using an adjacency matrix.
- `graph(std::unordered_map<Type, std::vector<Type> > g)`: Constructs a graph using an adjacency list.

### Adding Vertices and Edges

- `void addVertex(Type vertex)`: Adds a vertex to the graph if it does not already exist.
- `void addEdge(Type v1, Type v2)`: Adds an undirected edge between two vertices.

### Traversal Algorithms

- `std::vector<Type> bfs(Type v_start)`: Performs Breadth-First Search starting from the specified vertex.
- `std::vector<Type> dfs(Type start)`: Performs Depth-First Search starting from the specified vertex.

### Component and Island Counting

- `int countConnectedComponents()`: Counts the number of connected components in the graph.
- `int largestComponent()`: Finds the size of the largest connected component in the graph.
- `int islandCount()`: Counts the number of islands in the graph.

### Shortest Path

- `int shortest_path(int v_start, int v_end)`: Finds the shortest path between two vertices using BFS.

## Usage

1. Include the `graph.hpp` header in your C++ program.
2. Instantiate the `graph` class with the desired number of vertices or using an adjacency matrix/adjacency list.
3. Use the various member functions to perform operations on the graph.

## Examples

Creating a graph and performing BFS:

```cpp
#include "graph.hpp"

int main() {
    graph<int> g(6);
    
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    
    std::cout << "BFS traversal starting from vertex 0:" << std::endl;
    std::vector<int> bfs_result = g.bfs(0);
    
    for (int vertex : bfs_result) {
        std::cout << vertex << " ";
    }
    
    return 0;
}
```

