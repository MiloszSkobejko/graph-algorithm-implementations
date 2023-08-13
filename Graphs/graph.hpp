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
    std::unordered_map<Type, std::vector<Type> > adj;

public:
    explicit graph(int v_) : v(v_) { }

    
    // Adjency matrix constructor
    graph(std::vector<std::vector<Type> > & g)
    {
        if (g.size() != g[0].size()) { throw std::invalid_argument("Matrix is not square"); }
        
        v = static_cast<int>(g.size());
        
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (g[i][j]) adj[i].push_back(j);
    }
    
    // Adjency list constructor
    graph(std::unordered_map<Type, std::vector<Type> > g) : adj(g)
    {
        v = g.size();
    }
    

    ~graph() {}
    
    
    
    void addVertex(Type vertex)
    {
        if (adj.find(vertex) == adj.end()) adj.insert({ vertex, std::vector<Type> () });
    }
    
    
    
    void addEdge(Type v1, Type v2)
    {
        // Adding verticies if nox exist. If exist then won't be added
        addVertex(v1);
        addVertex(v2);
        // Add edge between v1 and v2
        adj[v1].push_back(v2);
    }
    
    

    void print()
    {
        // Wyswietlanie grafu w postaci listy sasiedztwa
        for (const auto & pair : adj)
        {
            Type vertex = pair.first;
            std::cout << vertex << ": ";
            for (const Type & neighbor : pair.second)
            {
                std::cout << neighbor << ", ";
            }
            std::cout << std::endl;
        }
    }
    

    int size() { return v; }
    
    
    
    std::vector<Type> bfs(Type v_start)
    {
        std::vector<Type> result;
        std::unordered_set<Type> visited;       // Wektor odwiedzin o rozmiarze v zainicjalizowany false dla kazd elem
        std::queue<Type> queue;                 // Kolejka do przechodzenia po wierzchołkach

        visited.insert(v_start);                // Oznacz startowy wierzchołek jako odwiedzony
        queue.push(v_start);                    // Dodaj startowy wierzchołek do kolejki

        while (!queue.empty())
        {
            Type current = queue.front();       // Pobierz pierwszy wierzchołek z kolejki
            queue.pop();

            result.push_back(current);

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
        
        return result;
    }
    
    
    
    void dfsRecursive(Type current, std::unordered_set<Type>& visited, std::vector<Type> & result)
    {
        if (visited.find(current) != visited.end()) return;

        result.push_back(current);
        visited.insert(current);

        for (const Type& neighbor : adj[current])
        {
            if (visited.find(neighbor) == visited.end()) dfsRecursive(neighbor, visited);
        }
    }
    
    

    std::vector<Type> dfs(Type start)
    {
        std::vector<Type> result;
        std::unordered_set<Type> visited;
        dfsRecursive(start, visited, result);
        
        return result;
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
    
    
    
    int largestComponent()
    {
        std::unordered_set<Type> visited;
        unsigned max = 0;
        
        for (int i = 0; i < v; i++)
        {
            int current = explore(i, visited);
            if (current > max) max = current;
        }
        
        return max;
    }
    
    
    
    int inslandCount()
    {
        // Taki sam jak macierz, która przechowuje
        std::vector< std::vector<bool> > visited(v, std::vector<bool>(v, false));
        int count = 0;
        
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (island_exp(i, j, visited)) count++;

        return count;
    }


    bool island_exp(int i, int j, std::vector< std::vector<bool> > & visited)
    {
        if (i < 0 || j < 0 || i >= v || j >= v) return false;
        
        
        if (adj[i][j] == 0 || visited[i][j]) return false;
        visited[i][j] = true;
        
        // Poruszanie sie 1 w kazdym kierunku. Jak nie moze to przestaje
        island_exp(i - 1, j, visited);
        island_exp(i + 1, j, visited);
        island_exp(i, j - 1, visited);
        island_exp(i, j + 1, visited);
        
        return true;
    }
    
    
    
    
    int shortest_path(int v_start, int v_end)
    {
       // Sprawdzanie poprawności argumentów
       if (v_start < 0 || v_start >= v || v_end < 0 || v_end >= v)
       {
           throw std::invalid_argument("Invalid start or end vertex");
       }

       std::queue<int> queue;
       std::vector<bool> visited(v, false);
       std::vector<int> distance(v, -1);

       
       visited[v_start] = true;
       distance[v_start] = 0;
       queue.push(v_start);

       while (!queue.empty())
       {
           int current_vertex = queue.front();
           queue.pop();

           // Sprawdzenie, czy doszliśmy do mety
           if (current_vertex == v_end) return distance[v_end];


           // Przejście przez wszystkie wierzchołki
           for (int i = 0; i < v; i++)
           {
               if (adj[current_vertex][i] && !visited[i])
               {
                   visited[i] = true;
                   distance[i] = distance[current_vertex] + 1;
                   queue.push(i);
               }
           }
       }

       // If the destination vertex is not reachable from the start vertex, return -1
       return -1;
    }
};

#endif /* graph_hpp */
