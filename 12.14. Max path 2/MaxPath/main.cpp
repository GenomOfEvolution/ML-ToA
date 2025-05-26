// 12.14.Максимальный путь 2 (7)
// Имеется взвешенный ориентированный ациклический граф.Найти максимальный путь, используя топологическую сортировку.
// Ввод из файла INPUT.TXT.Первая строка входного файла INPUT.TXT содержит 4 числа:
// N - количество вершин графа(3 ≤ N ≤ 2000), M – дуг(3 ≤ M ≤ 2000000), A – номер начальной вершины и B – номер конечной вершины.
// В следующих M строках по 3 числа, задающих дуги : начало дуги, конец дуги, длина(вес).
// Вывод в файл OUTPUT.TXT.В первую строку вывести максимальную длину пути, во вторую строку через пробел – вершины максимального пути.
// Если решений несколько, вывести любое из них.Если пути нет, выдать No.
// Автор: Нечаев Олег ПС-24
// Среда: MSVisualStudio 2022 cpp20

#include "MaxPath.h"
#include <fstream>
#include <optional>
#include <string>

struct Args
{
    std::string inputName;
    std::string outputName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: MaxPath.exe <input> <output>\n";
        return std::nullopt;
    }

    return Args{ .inputName = argv[1], .outputName = argv[2] };
}

bool ExecuteTask(const Args& args)
{
    std::ifstream input(args.inputName);
    std::ofstream output(args.outputName);

    if (!input)
    {
        std::cout << "Can`t open input file!\n";
        return EXIT_FAILURE;
    }

    if (!output)
    {
        std::cout << "Can`t open output file!\n";
        return EXIT_FAILURE;
    }

    int A, B;
    std::vector<int> inDegree;
    Graph adj = ReadGraph(input, A, B, inDegree);

    std::vector<int> topoOrder = TopoSort(adj, inDegree);
    auto [maxDist, path] = FindLongestPath(adj, topoOrder, A, B);

    if (path.empty()) 
    {
        output << "No\n";
    }
    else 
    {
        output << maxDist << '\n';
        for (size_t i = 0; i < path.size(); ++i) 
        {
            if (i > 0)
            {
                output << ' ';
            }
            output << path[i];
        }
        output << '\n';
    }

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    return ExecuteTask(*args);
}