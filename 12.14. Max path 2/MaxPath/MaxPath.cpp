#include "MaxPath.h"
#include <queue>
#include <climits>

std::vector<int> TopoSort(const Graph& adj, std::vector<int>& inDegree) 
{
    std::queue<int> q;
    for (size_t u = 1; u < adj.size(); ++u) 
    {
        if (inDegree[u] == 0)
        {
            q.push(u);
        }
    }

    std::vector<int> topoOrder;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (const auto& [v, _] : adj[u])
        {
            if (--inDegree[v] == 0) 
            {
                q.push(v);
            }
        }
    }

    return topoOrder;
}

Graph ReadGraph(std::istream& input, int& A, int& B, std::vector<int>& inDegree) 
{
    int N, M;
    input >> N >> M >> A >> B;

    Graph adj(N + 1);
    inDegree.resize(N + 1, 0);

    for (int i = 0; i < M; ++i)
    {
        int u, v, w;
        input >> u >> v >> w;
        adj[u].emplace_back(v, w);
        inDegree[v]++;
    }

    return adj;
}

std::pair<long long, std::vector<int>> FindLongestPath(
    const Graph& adjList,
    const std::vector<int>& topoOrder,
    int startVertex,
    int endVertex
) 
{
    std::vector<long long> dist(adjList.size(), LLONG_MIN);
    std::vector<int> pred(adjList.size(), -1);
    dist[startVertex] = 0;

    for (int u : topoOrder) 
    {
        if (dist[u] != LLONG_MIN) 
        {
            for (const auto& [v, w] : adjList[u])
            {
                if (dist[v] < dist[u] + w) 
                {
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                }
            }
        }
    }

    if (dist[endVertex] == LLONG_MIN) 
    {
        return { LLONG_MIN, {} };
    }

    std::vector<int> path;
    for (int u = endVertex; u != -1; u = pred[u]) 
    {
        path.push_back(u);
    }
    std::reverse(path.begin(), path.end());

    return { dist[endVertex], path };
}