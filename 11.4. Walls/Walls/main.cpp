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

#include <iostream>
#include <optional>
#include <string>

#include "Walls.h"

struct Args
{
    std::string inputName;
    std::string outputName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: Walls.exe <input> <output>\n";
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

    unsigned int L;
    Walls w = ReadWalls(input, L);
    output << ComputePerimeter(w, L);

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