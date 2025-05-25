#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <algorithm>
#include "Walls.h"

constexpr double kEps = 1e-10;
constexpr double kInf = std::numeric_limits<double>::infinity();

Walls ReadWalls(std::ifstream& input, unsigned int& L)
{
	int N;
	input >> N >> L;

	Walls result(N);
	for (int i = 0; i < N; ++i)
	{
		input >> result[i].first >> result[i].second;
	}

	return result;
}

int GetLowLeftTowerIndex(const Walls& w) 
{
    if (w.empty())
    {
        return 0;
    }

    int j = 0;
    for (int i = 1; i < w.size(); ++i)
    {
        if ((w[i].second < w[j].second) ||
            (w[i].second == w[j].second && w[i].first < w[j].first)) 
        {
            j = i;
        }
    }
    return j;
}

Walls BuildConvexHull(const Walls& w) 
{
    if (w.size() < 3)
    { 
        return w; 
    }

    Walls H;
    H.reserve(w.size());

    int j = GetLowLeftTowerIndex(w);
    H.push_back(w[j]);

    int jj = j;
    double maxCos = -kInf;
    double maxDist = -1.0;
    int d1 = -1, d2 = 0;

    do 
    {
        maxCos = -kInf;
        maxDist = -1.0;
        int nextPoint = j;

        for (int i = 0; i < w.size(); ++i) 
        {
            int dx = w[i].first - w[j].first;
            int dy = w[i].second - w[j].second;

            if (dx == 0 && dy == 0) 
            { 
                continue;
            }

            double dist = std::hypot(dx, dy);
            double cosAngle = (d1 * dx + d2 * dy) /
                (std::hypot(d1, d2) * dist);

            if (cosAngle > maxCos + kEps ||
                (std::abs(cosAngle - maxCos) < kEps && dist > maxDist + kEps)) 
            {
                maxCos = cosAngle;
                maxDist = dist;
                nextPoint = i;
            }
        }

        if (nextPoint != jj) 
        {
            d1 = w[nextPoint].first - w[j].first;
            d2 = w[nextPoint].second - w[j].second;
            H.push_back(w[nextPoint]);
        }

        j = nextPoint;
    } while (j != jj);

    return H;
}

double ComputePerimeter(const Walls& w, unsigned int L) 
{
    const Walls H = BuildConvexHull(w);

    double perimeter = 0.0;
    for (size_t i = 0; i < H.size(); ++i) 
    {
        const auto& A = H[i];
        const auto& B = H[(i + 1) % H.size()];
        perimeter += std::hypot(B.first - A.first, B.second - A.second);
    }

    return std::round(perimeter + 2 * M_PI * L);
}