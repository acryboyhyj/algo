#include "UndirectedGraph.h"
#include "TestToggle.h"
#include <iostream>
int main()
{
    UndirectedGraph g(8);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 7);

    std::cout << g.BFS(0, 7) << std::endl;
    std::cout << g.DFS(0, 7) << std::endl;
}