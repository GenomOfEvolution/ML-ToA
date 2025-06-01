#include "PermutationTasks.h"
#include <sstream>
#include <string>
#include <algorithm>

void PrintPermutation(std::ostream& output, const Permutation& p)
{
    output << "[";
    for (size_t i = 0; i < p.size(); ++i)
    {
        if (i != 0)
        {
            output << ", ";
        }
        output << p[i];
    }
    output << "]";
}

Permutation ReadPermutation(std::istream& input)
{
    Permutation p;
    int value;

    std::string line;
    std::getline(input, line);

    std::istringstream iss(line);
    while (iss >> value) 
    {
        p.push_back(value);
    }

    return p;
}

std::ostream& operator<<(std::ostream& os, const Permutation& p)
{
    PrintPermutation(os, p);
    return os;
}

Permutation SolvePermutationEquation(const Permutation& A, const Permutation& B)
{
    size_t n = A.size();
    Permutation inverseA(n);
    Permutation X(n);

    for (int i = 0; i < n; ++i) 
    {
        inverseA[A[i] - 1] = i + 1;
    }

    for (int i = 0; i < n; ++i) 
    {
        X[i] = inverseA[B[i] - 1];
    }

    return X;
}

void NextKPermutations(std::ostream& output, Permutation p, int K)
{
    for (int i = 0; i < K; ++i) 
    {
        if (!std::next_permutation(p.begin(), p.end())) 
        {
            break;
        }
        output << i + 1 << ") " << p << "\n";
    }
}

std::vector<int> PermToInversionVector(const Permutation& p)
{
    size_t n = p.size();
    std::vector<int> inv(n, 0);

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < i; ++j) 
        {
            if (p[j] > p[i]) 
            {
                inv[i]++;
            }
        }
    }

    return inv;
}

Permutation InversionVectorToPerm(const std::vector<int>& inv)
{
    int n = (int)inv.size();
    Permutation perm;
    Permutation numbers;

    for (int i = 1; i <= n; ++i) 
    {
        numbers.push_back(i);
    }

    for (int i = n - 1; i >= 0; --i) 
    {
        perm.insert(perm.begin(), numbers[inv[i]]);
        numbers.erase(numbers.begin() + inv[i]);
    }

    return perm;
}

void JohnsonTrotter(std::ostream& output, int N)
{
    Permutation perm(N);
    std::vector<int> dir(N, -1);

    for (int i = 0; i < N; ++i)
    {
        perm[i] = i + 1;
    }

    output << perm << "\n";

    while(true)
    {
        int mobile = -1, pos = -1;
        // наибольший мобильный элемент
        for (int i = 0; i < N; ++i) 
        {
            int next = i + dir[i];
            if (next >= 0 && next < N && perm[i] > perm[next])
            {
                if (mobile < perm[i]) 
                {
                    mobile = perm[i];
                    pos = i;
                }
            }
        }

        if (mobile == -1)
        {
            break;
        }

        int swapPos = pos + dir[pos];
        std::swap(perm[pos], perm[swapPos]);
        std::swap(dir[pos], dir[swapPos]);

        for (int i = 0; i < N; ++i) 
        {
            if (perm[i] > mobile) 
            {
                dir[i] = -dir[i];
            }
        }

        output << perm << "\n";
    }
}

void GeneratePermutationsRecursive(std::ostream& output, Permutation& perm, int n, int level) 
{
    if (level == n) 
    {
        output << perm << "\n";
        return;
    }

    GeneratePermutationsRecursive(output, perm, n, level + 1);

    for (int i = level + 1; i < n; ++i) 
    {
        std::swap(perm[level], perm[i]);
        GeneratePermutationsRecursive(output, perm, n, level + 1);
        std::swap(perm[level], perm[i]);
    }
}

void GenerateAllRecursive(std::ostream& output, int N)
{
    Permutation p(N);

    for (int i = 0; i < N; i++)
    {
        p[i] = i + 1;
    }

    GeneratePermutationsRecursive(output, p, N, 0);
}