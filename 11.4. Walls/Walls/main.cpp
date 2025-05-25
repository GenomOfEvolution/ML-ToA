// 11.4. ����� (6)
// ��� - ��� ������ ������.�� �������� ������ �������� ����������� ��������� ����� ������ ��� �����.
// ������ ��� ����� ������, ��� �� �������� ����������� ����������� ��������� �������� ��������� �����
// ����������� ����� � �������� �������� �������. ������ ����� �� �������� ��������� ����� ������ ����� �����,
// ��������� ����������� ���������� �����, �� ����������, ����� ����� �� ��������� � ����� ����� ���������� ����������.
// ���� ������ ������, ��� ���������� ����������� ������ �������� ��� ��������� �����, ��� ���� ��������� ���������� ���
// �������������� ����������, ���������� ������� ������. ����� ����, ���������� ������ ����������� ������ �����,
// ��� ������� ������ ���������� ��������.
// ���� ������ - ������ ����������� ��������� ������, ������� ���������, ������������ ����������� ����� �����,
// ������� ����� ��������� ������ �����, ������������ ���������� ������.
// ������ ������ ���������� ���, ��� ����� ������ ������������ ����� ������������� � ���������� �� ������� �����������.
// ���������� ��� ���������� ����� ������������� ��������� ������� ��������� � ����� ��������� ���������� ������� ���� ����� � �����.

// �����: ������ ���� ��-24
// �����: MS VisualStudio 2022 cpp 20

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