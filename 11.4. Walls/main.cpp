// 11.4. Стена (6)
// Жил - был жадный Король.Он приказал своему главному Архитектору построить стену вокруг его замка.
// Король был таким жадным, что не послушал предложение Архитектора построить красивую кирпичную стену
// совершенной формы с изящными высокими башнями. Вместо этого он приказал построить стену вокруг всего замка,
// используя минимальное количество камня, но потребовал, чтобы стена не подходила к замку ближе некоторого расстояния.
// Если Король узнает, что Архитектор использовал больше ресурсов для постройки стены, чем было абсолютно необходимо для
// удовлетворения требований, Архитектор лишится головы. Более того, Архитектор должен представить проект стены,
// где указано точное количество ресурсов.
// Ваша задача - помочь Архитектору сохранить голову, написав программу, определяющую минимальную длину стены,
// которую можно построить вокруг замка, удовлетворив требования Короля.
// Задача слегка упрощается тем, что замок Короля представляет собой многоугольник и расположен на плоской поверхности.
// Архитектор уже сопоставил замку прямоугольную декартову систему координат и точно определил координаты каждого угла замка в футах.

// Автор: Нечаев Олег ПС-24
// Среда: MS VisualStudio 2022 cpp 20

#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
    std::string inputName;
    std::string outputName;
};

using Coords = std::pair<int, int>;
using Walls = std::vector<Coords>;

bool IsConvex(const Walls& w) 
{
    if (w.size() < 3) 
    {
        return false;
    }

    int prevCross = 0;
    for (size_t i = 0; i < w.size(); ++i) 
    {
        const Coords& A = w[i];
        const Coords& B = w[(i + 1) % w.size()];
        const Coords& C = w[(i + 2) % w.size()];

        // Проверка на коллинеарность
        int cross = (B.first - A.first) * (C.second - B.second)
            - (B.second - A.second) * (C.first - B.first);
        if (cross == 0)
        {
            continue;
        }

        if (prevCross == 0)
        {
            prevCross = cross;
        }
        else if (cross * prevCross < 0)
        {
            return false; // Если разные знаки - не выпуклый
        }
    }
    return true;
}

double ComputePerimeter(const Walls& w) 
{
    double perimeter = 0.0;
    for (size_t i = 0; i < w.size(); ++i) 
    {
        const Coords& A = w[i];
        const Coords& B = w[(i + 1) % w.size()];
        perimeter += std::hypot(B.first - A.first, B.second - A.second);
    }

    return perimeter;
}

// Построение выпуклой оболочки 
Walls ConvexHull(Walls w) 
{
    if (w.size() <= 2)
    {
        return w;
    }

    Walls hull;
    for (const auto& p : w) 
    {
        while (hull.size() >= 2) 
        {
            const Coords& A = hull[hull.size() - 2];
            const Coords& B = hull.back();

            int cross = (B.first - A.first) * (p.second - B.second)
                - (B.second - A.second) * (p.first - B.first);

            if (cross <= 0)
            {
                break; // Выпуклый поворот 
            }

            hull.pop_back(); // Вогнутость — удаляем точку
        }
        hull.push_back(p);
    }

    return hull;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: Walls.exe <input> <output>\n";
        return std::nullopt;
    }

    return Args{ .inputName = argv[1], .outputName = argv[2] };
}

bool BuildWalls(const Args& args)
{
    std::ifstream input(args.inputName);
    std::ofstream output(args.outputName);

    if (!input)
    {
        std::cout << "Can`t open input file!\n";
        return EXIT_FAILURE;
    }

    int N, L;
    input >> N >> L;

    Walls castle(N);
    for (int i = 0; i < N; ++i)
    {
        input >> castle[i].first >> castle[i].second;
    }

    double wallLength;
    if (IsConvex(castle))
    {
        wallLength = ComputePerimeter(castle) + 2 * M_PI * L;
    }
    else
    {
        Walls hull = ConvexHull(castle);
        wallLength = ComputePerimeter(hull) + 2 * M_PI * L;
    }

    output.precision(0);
    output << std::fixed << wallLength;

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    return BuildWalls(*args);
}