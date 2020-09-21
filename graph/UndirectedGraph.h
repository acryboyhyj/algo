#ifndef __UNDIRECTEDGRAPH_H__
#define __UNDIRECTEDGRAPH_H__

#include <vector>
#include <list>
#include <queue>
#include <string>
#define Invalid -1
class UndirectedGraph
{
public:
    // enum class index
    // {
    //     Invalid = 0;
    // };

public:
    UndirectedGraph(int nums) : vertexNum(nums)
    {
        for (int i = 0; i < vertexNum; i++)
        {
            edges.push_back(std::vector<int>());
        }
    }
    ~UndirectedGraph() {}
    void addEdge(int s, int t)
    {
        edges[s].push_back(t);
        edges[t].push_back(s);
    }

    std::string BFS(int s, int t);
    std::string print(std::vector<int> &prev, int s, int t)
    {
        if (s != t && !prev[t] != Invalid)
        {
            std::string result = std::to_string(t) + "<-";
            return result + print(prev, s, prev[t]);
        }
        return std::to_string(t);
    }

    std::string DFS(int s, int t)
    {
        if (s == t)
            return std::to_string(s);
        found = false;
        std::vector<bool> visited(vertexNum, false);
        std::vector<int> prev(vertexNum, Invalid);

        DFSInternal(s, t, prev, visited);
        return print(prev, s, t);
    }

private:
    void DFSInternal(int s, int t, std::vector<int> &prev, std::vector<bool> &visited)
    {
        if (found)
            return;
        if (s == t)
        {
            found = true;
            return;
        }

        for (size_t i = 0; i < edges[s].size(); i++)
        {
            int v = *(edges[s].begin() + i);
            if (!visited[v])
            {
                visited[v] = true;
                prev[v] = s;
                DFSInternal(v, t, prev, visited);
            }
        }
    }
    bool found;

private:
    int vertexNum;
    std::vector<std::vector<int>> edges; //邻接表
};

std::string UndirectedGraph::BFS(int s, int t)
{
    std::queue<int> q;
    std::vector<bool> visited(vertexNum, false);
    std::vector<int> prev(vertexNum, -1);

    visited[s] = true;
    q.push(s);

    while (!q.empty())
    {
        int curVertex = q.front();
        q.pop();

        for (size_t i = 0; i < edges[curVertex].size(); i++)
        {
            int v = *(edges[curVertex].begin() + i);
            if (!visited[v])
            {
                prev[v] = curVertex;
                if (v == t)
                {
                    return print(prev, s, t);
                }
            }
            visited[v] = true;
            q.push(v);
        }
    }
    return nullptr;
}

#endif // __UNDIRECTEDGRAPH_H__