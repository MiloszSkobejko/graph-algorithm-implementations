//
//  graph.hpp
//  Graphs
//
//  Created by Miłosz Skobejko on 12/08/2023.

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>


template <typename Type>
class graph
{
private:
    int v;
    std::unordered_map<Type, std::vector<Type>> adj;

public:
    explicit graph(int v_) : v(v_) { }

    graph(std::vector<std::vector<Type> > & g)
    {
        if (g.size() != g[0].size()) { throw std::invalid_argument("Macierz nie jest kwadratowa"); }
        
        v = static_cast<int>(g.size());
        
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (g[i][j]) adj[i].push_back(j);
    }

    graph(int v_, std::vector<std::vector<Type>>& g) : v(v_)
    {
        if (g.size() != g[0].size() || v_ != g.size()) { throw std::invalid_argument("Macierz nie jest kwadratowa"); }

        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (g[i][j]) adj[i].push_back(j);
    }

    ~graph() {}

    void print()
    {
        // Wyswietlanie grafu w postaci listy sasiedztwa
        for (const auto & pair : adj)
        {
            Type vertex = pair.first;
            std::cout << vertex << ":";
            for (const Type & neighbor : pair.second)
            {
                std::cout << "->" << neighbor;
            }
            std::cout << std::endl;
        }
    }

    int size() { return v; }
    
    
    // Algorytmy
    void bfs(Type v_start)
    {
        std::unordered_set<Type> visited;  // Wektor odwiedzin o rozmiarze v zainicjalizowany false dla kazd elem
        std::queue<Type> queue;                 // Kolejka do przechodzenia po wierzchołkach

        visited.insert(v_start);        // Oznacz startowy wierzchołek jako odwiedzony
        queue.push(v_start);                   // Dodaj startowy wierzchołek do kolejki

        while (!queue.empty())
        {
            Type current = queue.front();        // Pobierz pierwszy wierzchołek z kolejki
            queue.pop();

            std::cout << current << " ";        // Wyświetl wierzchołek

            // Przejdź przez sąsiadów wierzchołka
            for (auto & neighbor : adj[current])
            {
                if (visited.find(neighbor) == visited.end())
                 {
                     visited.insert(neighbor);
                     queue.push(neighbor);
                 }
            }
        }
    }
    
    
    
    void dfsRecursive(Type current, std::unordered_set<Type>& visited)
    {
        if (visited.find(current) != visited.end()) return;

        std::cout << current << " ";
        visited.insert(current);

        for (const Type& neighbor : adj[current])
        {
            if (visited.find(neighbor) == visited.end()) dfsRecursive(neighbor, visited);
        }
    }
    
    

    void dfs(Type start)
    {
        std::unordered_set<Type> visited;
        dfsRecursive(start, visited);
    }
    
    
    
    
    // Wyszukiwanie, czy można przejść z wierzchołka start do end
    bool hasPath(Type start_v, Type end_v, std::unordered_set<Type>& visited)
    {
        if (start_v == end_v) return true;
        visited.insert(start_v);
        
        for (const Type & neighbor : adj[start_v])
        {
            if (visited.find(neighbor) == visited.end())
                if (hasPath(neighbor, end_v, visited)) return true;
        }
        
        return false;
    }
    
    
    
    
    
    int countConnectedComponents()
    {
        std::unordered_set<Type> visited;
        unsigned count = 0;
        
        // Jeśli explore zwraca true, to znaczy, że przeszła przez całą wyspę i nie może się bardziej ruszyć.
        // Nie działa dla grafów skierowanych.
        for (const Type & neighbor : adj[0])
        {
            if (explore(neighbor, visited)) count++;
        }
        
        return count;
    }
    
    
    
    
    
    // PODFUNKCJA EXPLORE'
    // v_start to aktualny wierzchołek, poprawna nazwa powinna być node, aby się myliło
    // n to liczba wierzchołków danego podgrafu, wzrasta z każdą rekurencją.
    int explore(Type v_start, std::unordered_set<Type>& visited)
    {
        if (visited.find(v_start) != visited.end()) return false;
        
        visited.insert(v_start);
        
        int size = 1;
        for (const Type & neighbor : adj[v_start])
        {
            if (visited.find(neighbor) == visited.end()) size += explore(neighbor, visited);
        }
        
        return size;
    }
    

};

#endif /* graph_hpp */
