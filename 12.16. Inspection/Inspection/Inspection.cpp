// 12.16.Осмотр(4)
// Для того, чтобы быть допущенным к занятиям в бассейне, необходимо предъявить справку,
// на которой должны поставить свои подписи K врачей.Некоторые врачи отказываются ставить подписи
// на справке до тех пор, пока на ней не распишется другой врач. Например, стоматолог отказывается ставить подпись,
// пока не будет принесена справка от психиатра, потому что однажды его укусил психически неуравновешенный студент.
// Составлен список, какому врачу нужны какие справки.Нужно определить, можно ли получить все справки, 
// а также в какой последовательности необходимо обходить врачей.
// Автор: Нечаев Олег ПС-24
// Среда: MS Visual Studio 2022 cpp 20


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

void Solve(std::istream& input, std::ostream& output)
{
    int k;
    input >> k;

    std::vector<std::vector<int>> adj(k + 1);
    std::vector<int> inDegree(k + 1, 0);

    for (int i = 1; i <= k; ++i)
    {
        int j;
        input >> j;

        for (int dep = 0; dep < j; ++dep)
        {
            int doctor;
            input >> doctor;
            adj[doctor].push_back(i);
            inDegree[i]++;
        }
    }

    std::queue<int> q;
    for (int i = 1; i <= k; ++i)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    std::vector<int> topoOrder;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (int v : adj[u])
        {
            inDegree[v]--;
            if (inDegree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (topoOrder.size() != k)
    {
        output << "NO" << std::endl;
    }
    else
    {
        output << "YES" << std::endl;
        for (int node : topoOrder)
        {
            output << node << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: Inspection.exe <input> <output>";
        return EXIT_FAILURE;
    }

    std::ifstream input;
    input.open(argv[1]);

    if (!input)
    {
        return EXIT_FAILURE;
    }

    std::ofstream output;
    output.open(argv[2]);

    Solve(input, output);

    return EXIT_SUCCESS;
}