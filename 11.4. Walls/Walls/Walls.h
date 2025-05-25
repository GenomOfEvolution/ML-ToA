#pragma once
#include <fstream>
#include <utility>
#include <vector>

using Coords = std::pair<int, int>;
using Walls = std::vector<Coords>;

Walls ReadWalls(std::ifstream& input, unsigned int& L);
double ComputePerimeter(const Walls& w, unsigned int L);