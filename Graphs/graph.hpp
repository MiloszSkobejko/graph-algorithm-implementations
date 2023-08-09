//
//  graph.hpp
//  Graphs
//
//  Created by Miłosz Skobejko on 17/07/2023.
//

#ifndef graph_hpp
#define graph_hpp

#include <iostream>
#include <vector>
#include <map>


class graph
{
private:
    int v;
    std::vector< std::vector<int> > adj;
    //std::map<int, std::vector<int> > adj2;
    // 1 : 1 ,2 , 3, 4
    
    int explore(int v_start, std::vector<bool>& visited);
    bool island_exp(int i, int j, std::vector< std::vector<bool> > & visited);

public:
    explicit graph(int v_)
    {
        v = v_;
        
        adj.resize(v_);
        for (auto & row : adj) row.resize(v_);
    }
    
    
    graph(std::vector< std::vector<int> > & g)
    {
        if (g.size() != g[0].size()) { throw std::invalid_argument("Macierz nie jest kwadratowa"); }
        
        adj = g;
        v = static_cast<int>(g.size());
    }
    
    
    graph(int v_, std::vector< std::vector<int> > & g)
    {
        if (g.size() != g[0].size()) { throw std::invalid_argument("Macierz nie jest kwadratowa"); }
        
        v = v_;
        adj = g;
    }
    
    
    ~graph() { }
    
    
    void print()
    {
        // Wyswietlanie grafu w postaci listy sasiedztwa
        for (int i = 0; i < v; i++)
        {
            std::cout << i << ":";
            for (int j = 0; j < v; j++)
            {
                if (adj[i].at(j)) std::cout << "->" << j;
            }
            std::cout << std::endl;
        }
    }
    
    
    int & get(int i, int j) { return adj[i][j]; }
    
    
    bool put(int i, int j)
    {
        if (i >= 0 && i < v && j >= 0 && j < v)
        {
            adj[i][j] = 1;
            return true;
        }
        
        return false;
    }
    
    
    int size() {return v;}
    
    void bfs(int v_start);
    int shortest_path(int v_start, int v_end); //bfs
    void dfs(int v_start, std::vector<bool>& visited);
    bool hasPath(int start_v, int end_v, std::vector<bool>& visited); //dfs
    int countConnectedComponents(); // dfs
    int largestComponent(); //dfs
    int inslandCount();
    
};

#endif /* graph_hpp */
