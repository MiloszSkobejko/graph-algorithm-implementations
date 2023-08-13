


#include <iostream>
#include "graph.hpp"

int main(int argc, const char * argv[]) {
    
    std::vector< std::vector<int> > matrix = {{0,1,1,0,0}, {1,0,0,1,0}, {1,0,0,0,1}, {0,1,0,0,0}, {0,0,1,0,0}};
    std::vector< std::vector<int> > matrix2 = {{0,1,1,0}, {0,0,0,0}, {0,0,0,0}, {0,1,0,0}};
    std::vector<std::vector<int>> matrix3 = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 1, 1},
            {0, 1, 1, 0, 0, 1, 1}
        };
    
    std::vector<std::vector<int>> matrix4 = {
            {0, 1, 1, 0, 0, 0, 0},
            {1, 0, 1, 0, 0, 0, 0},
            {1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 1, 1},
            {0, 0, 0, 1, 1, 0, 1},
            {0, 0, 0, 0, 1, 1, 0}
        };
    
    
    std::vector< std::vector<int> > matrix5 = {
        {0, 0, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0}
    };
    
    std::vector< std::vector<int> > matrix6 = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 1, 1, 0, 1, 0}
    };
    
    graph g1(matrix);
    graph g2(matrix2);
    graph g3(matrix3);
    std::vector<int> result;
    
    result = g1.bfs(0);
    for (const auto & v : result) std::cout << v << " ";
    std::cout << "\n";
    
    result = g1.bfs(1);
    for (const auto & v : result) std::cout << v << " ";
    std::cout << "\n";
    
    result = g1.bfs(2);
    for (const auto & v : result) std::cout << v << " ";
    std::cout << "\n";
    
    result = g1.bfs(3);
    for (const auto & v : result) std::cout << v << " ";
    std::cout << "\n";

    
    
//    graph<int>g1(matrix5);
    
    
    
//    g1.addEdge(0, 2);
//    g1.print();
//    std::vector<int> bfs = g1.bfs(0);
//
//    for (const auto  & v : bfs) std::cout << v << " ";
//
//
//    std::unordered_set<int> visited;
    //std::cout << g1.hasPath(1, 5, visited) << "\n";
    
    
    
    
    
//    graph g5(matrix5);
//    std::cout << g5.shortest_path(0, 3) << std::endl;
    
//    graph g1(matrix);
//    graph g2(matrix2);
//    graph g3(matrix6);
//    graph g4(matrix4);
//    std::cout << g3.inslandCount() << " islands" << std::endl;
//
//    //std::cout << g3.countConnectedComponents() << std::endl;
//    std::cout << g4.largestComponent() << std::endl;
    
//    g2.print();
//    std::vector<bool> visited(g2.size(), false);
//    std::cout << g2.hasPath(0, 1, visited);
    
//    g1.print();
//    g1.bfs(2);
//
//    std::vector<bool> visited(g1.size(), false);
//    std::cout << "DFS traversal starting from vertex 0: ";
//    g1.dfs(0, visited);
//    std::cout << std::endl;
    
    
    return 0;
}
