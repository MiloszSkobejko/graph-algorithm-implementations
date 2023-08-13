//
//  tests.cpp
//  Graphs
//
//  Created by Miłosz Skobejko on 13/08/2023.
//

#include "tests.hpp"


void test_bfs()
{
    
    std::cout << "Running bfs algorithm tests...\n";
    
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
    
    graph g1(matrix);
    graph g2(matrix2);
    graph g3(matrix3);
    
    std::vector<int> result;
    result = g1.bfs(0);
}


void test_dfs();
void test_hasPath();
void test_count_connected_components();
void test_largest_component();
void test_island_count();
void test_shortest_path();
