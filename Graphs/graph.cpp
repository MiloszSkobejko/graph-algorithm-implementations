//
//  graph.cpp
//  Graphs
//
//  Created by Miłosz Skobejko on 17/07/2023.


#include "graph.hpp"
#include <queue>


// Tylko algorytmy grafów, reszta jest zdefiniowana w graph.hpp

// BFS
// Metoda bfs wykonuje przeszukiwanie wszerz (BFS) w grafie, zaczynając od podanego wierzchołka start.
// Algorytm BFS polega na odwiedzeniu wszystkich sąsiadów danego wierzchołka, a następnie powtórzeniu
// tego procesu dla sąsiadów, którzy jeszcze nie zostali odwiedzeni.

// Wszystkie krawędzie traktuje bezwagowo, nie lubi cykli bo może utknąć, nie uwzględnia kierunku i zabiera pamięć

void graph::bfs(int v_start)
{
        std::vector<bool> visited(v, false);   // Wektor odwiedzin o rozmiarze v zainicjalizowany false dla kazd elem
        std::queue<int> queue;                 // Kolejka do przechodzenia po wierzchołkach

        visited[v_start] = true;               // Oznacz startowy wierzchołek jako odwiedzony
        queue.push(v_start);                   // Dodaj startowy wierzchołek do kolejki

        while (!queue.empty())
        {
            int current = queue.front();        // Pobierz pierwszy wierzchołek z kolejki
            queue.pop();

            std::cout << current << " ";        // Wyświetl wierzchołek

            // Przejdź przez sąsiadów wierzchołka
            for (int i = 0; i < v; i++)
            {
                if (adj[current][i] && !visited[i]) // Jeśli istnieje krawędź i sąsiad nie był jeszcze odwiedzony
                {
                    visited[i] = true;          // Oznacz sąsiada jako odwiedzonego
                    queue.push(i);              // Dodaj sąsiada do kolejki
                }
            }
        }
}



// Zaczyna od jakiegos wierzcholka i podrozuje najglebiej jak sie da bez cofania
void graph::dfs(int v_start, std::vector<bool>& visited)
{
    visited[v_start] = true;            // Oznacz startowy wierzchołek jako odwiedzony
    std::cout << v_start << " ";        // Wyświetl wierzchołek

    // Przejdź przez sąsiadów startowego wierzchołka
    for (int i = 0; i < v; i++)
    {
        // Jeśli istnieje krawędź i sąsiad nie był jeszcze odwiedzony
        // Wywołaj rekurencyjnie DFS dla nieodwiedzonego sąsiada
        if (adj[v_start][i] != 0 && !visited[i]) dfs(i, visited);
    }
}




// Wyszukiwanie, czy można przejść z wierzchołka start do end
bool graph::hasPath(int start_v, int end_v, std::vector<bool>& visited)
{
    if (start_v == end_v) return true;
    visited[start_v] = true;
    
    for (int i = 0; i < v; i++)
    {
        if (adj[start_v][i] != 0 && !visited[i]) // upewnienie ze nie wpadnie w nieskonczona petle
            if (hasPath(i, end_v, visited)) return true;
    }
    
    return false;
}




int graph::countConnectedComponents()
{
    std::vector<bool> visited(v, false);
    unsigned count = 0;
    
    // Jeśli explore zwraca true, to znaczy, że przeszła przez całą wyspę i nie może się bardziej ruszyć.
    // Nie działa dla grafów skierowanych.
    for (int i = 0; i < v; i++)
    {
        if (explore(i, visited)) count++;
    }
    
    return count;
}


// Znajduje ilość PODGRAFÓW w grafie. Nie ilość "wysp"
int graph::largestComponent()
{
    std::vector<bool> visited(v, false);
    unsigned max = 0;
    
    
    for (int i = 0; i < v; i++)
    {
        int current = explore(i, visited);
        if (current > max) max = current;
    }
    
    
    return max;
}


int graph::inslandCount()
{
    // Taki sam jak macierz, która przechowuje
    std::vector< std::vector<bool> > visited(v, std::vector<bool>(v, false));
    int count = 0;
    
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            if (island_exp(i, j, visited)) count++;

    return count;
}


bool graph::island_exp(int i, int j, std::vector< std::vector<bool> > & visited)
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


// v_start to aktualny wierzchołek, poprawna nazwa powinna być node, aby się myliło
// n to liczba wierzchołków danego podgrafu, wzrasta z każdą rekurencją.
int graph::explore(int v_start, std::vector<bool>& visited)
{
    if (visited[v_start]) return false;
    
    visited[v_start] = true;
    
    int size = 1;
    for (int i = 0; i < v; i++)
    {
        if (adj[v_start][i] != 0 && !visited[i]) size += explore(i, visited);
    }
    
    return size;
}



int graph::shortest_path(int v_start, int v_end)
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
