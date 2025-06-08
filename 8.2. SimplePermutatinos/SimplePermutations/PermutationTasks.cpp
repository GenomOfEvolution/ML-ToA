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


Permutation InversePermutation(const Permutation& perm) 
{
    int n = perm.size();
    Permutation inverse(n);

    for (int i = 0; i < n; ++i) 
    {
        inverse[perm[i] - 1] = i + 1;
    }

    return inverse;
}

Permutation MultiplyPermutations(const Permutation& A, const Permutation& B) 
{
    int n = A.size();
    Permutation result(n);

    for (int i = 0; i < n; ++i) 
    {
        result[i] = A[B[i] - 1];
    }

    return result;
}

Permutation SolvePermutationEquation(const Permutation& A, const Permutation& B) 
{
    Permutation invA = InversePermutation(A);
    Permutation X = MultiplyPermutations(B, invA);

    return X;
}

bool NextPermutation(Permutation& p)
{
    int n = (int)p.size();
    int i = n - 2;

    while (i >= 0 && p[i] >= p[i + 1])
    {
        i--;
    }

    if (i < 0)
    {
        return false; 
    }

    int j = n - 1;
    while (p[j] <= p[i])
    {
        j--;
    }

    std::swap(p[i], p[j]);
    std::reverse(p.begin() + i + 1, p.end());

    return true;
}

void NextKPermutations(std::ostream& output, Permutation p, int K)
{
    for (int i = 0; i < K; ++i) 
    {
        if (!NextPermutation(p))
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
    size_t n = inv.size();
    std::vector<int> availableNumbers(n);
    for (int i = 0; i < n; ++i)
    {
        availableNumbers[i] = i + 1; 
    }

    Permutation p(n);
    for (int i = (int)(n - 1); i >= 0; --i)
    {
        int pos = (int)availableNumbers.size() - 1 - inv[i];
        p[i] = availableNumbers[pos];
        availableNumbers.erase(availableNumbers.begin() + pos);
    }

    return p;
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

void GeneratePermutationRecursive(std::ostream& output, Permutation& perm, int n, bool moveRight) {
    if (n == 1) {
        output << perm << "\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        GeneratePermutationRecursive(output, perm, n - 1, !moveRight);

        if (i < n - 1) {  // Не делаем лишний своп на последнем шаге
            if (moveRight) {
                std::swap(perm[n - 1], perm[n - 2 - i]);
            }
            else {
                std::swap(perm[0], perm[n - 1 - i]);
            }
            output << perm << "\n";  // Печатаем только после реального изменения
        }
    }
}

void GenerateAllRecursive(std::ostream& output, int N) 
{
    Permutation p(N);

    for (int i = 0; i < N; ++i)
    {
        p[i] = i + 1; 
    }

    GeneratePermutationRecursive(output, p, N, true);
}