#pragma once
#include <iostream>
#include <vector>
#include <utility>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

Graph ReadGraph(std::istream& input, int& A, int& B, std::vector<int>& inDegree);
std::vector<int> TopoSort(const Graph& adj, std::vector<int>& inDegree);
std::pair<long long, std::vector<int>> FindLongestPath(
    const Graph& adjList,
    const std::vector<int>& topoOrder,
    int startVertex,
    int endVertex
);