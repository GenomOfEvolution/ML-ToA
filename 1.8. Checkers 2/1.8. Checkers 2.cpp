/*
На шахматном поле расположены N черных шашек и одна белая дамка.
Требуется написать программу, которая по заданному расположению шашек определяет,
какое максимальное количество шашек может взять белая дамка за один ход.

Автор: Нечаев Олег ПС-24
Среда: MS VisualStudio 2022, cpp 20
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <optional>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

enum FieldCell
{
    Empty = 0,
    Black = 1,
    Queen = 2,
    Visited = 3,
};

const int FIELD_SIZE = 8;
using Field = std::vector<std::vector<FieldCell>>;
using Path = std::vector<std::pair<int, int>>;

Field ReadField(std::istream& input, std::pair<int, int>& queenPosition)
{
    Field result(FIELD_SIZE, std::vector<FieldCell>(FIELD_SIZE, FieldCell::Empty));

    for (int i = 0; i < FIELD_SIZE; i++)
    {
        std::string line;
        std::getline(input, line);

        for (int j = 0; j < FIELD_SIZE; j++)
        {
            switch (line[j])
            {
            case '1':
                result[i][j] = FieldCell::Black;
                break;
            case '2':
                result[i][j] = FieldCell::Queen;
                queenPosition = { i, j };
                break;
            default:
                break;
            }
        }
    }

    return result;
}

bool IsInBorder(std::pair<int, int> pos)
{
    return (pos.first >= 0 && pos.first < FIELD_SIZE) &&
        (pos.second >= 0 && pos.second < FIELD_SIZE);
}



void DFS(Field f, std::pair<int, int> queenPos, Path curPath, Path& bestPath)
{
    const int dx[] = { -1, -1, 1, 1 };
    const int dy[] = { -1, 1, -1, 1 };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 2; j < 6; j++)
        {
            std::pair<int, int> firstPos = queenPos;
            int dPosX = dx[i] * j;
            int dPosY = dy[i] * j;
            std::pair<int, int> secondPos = { queenPos.first + dPosX, queenPos.second + dPosY };

            
        }
    }
}

int MaxEatenCheckers(const Field& f, const std::pair<int, int>& queenPosition, std::vector<std::pair<int, int>>& eatHistory)
{
    int maxEaten = 0;
    std::vector<std::pair<int, int>> currentPath = { queenPosition };
    std::vector<std::pair<int, int>> bestPath = { queenPosition };

    DFS(f, queenPosition, currentPath, bestPath);

    eatHistory = bestPath;
    return (int)bestPath.size() - 1;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    Args result;
    if (argc != 3)
    {
        std::cout << "Usage: \"1.8. Checkers 2.exe\" <input file> <output file>\n";
        return std::nullopt;
    }

    result.inputFileName = argv[1];
    result.outputFileName = argv[2];

    return result;
}

void Checkers(const Args& args)
{
    std::ifstream input(args.inputFileName);

    if (!input)
    {
        std::cout << "Can't open " << args.inputFileName;
        return;
    }

    std::pair<int, int> queenPosition = { -1, -1 };
    Field f = ReadField(input, queenPosition);

    if (queenPosition.first == -1 || queenPosition.second == -1)
    {
        std::cout << "No queen!" << std::endl;
        return;
    }

    std::vector<std::pair<int, int>> eatHistory;
    int maxEaten = MaxEatenCheckers(f, queenPosition, eatHistory);

    std::ofstream output(args.outputFileName);
    output << eatHistory.size() - 1 << "\n";
    for (const auto& move : eatHistory)
    {
        output << move.first + 1 << " " << move.second + 1<< "\n";
    }
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);

    if (!args)
    {
        return EXIT_FAILURE;
    }

    Checkers(*args);

    return EXIT_SUCCESS;
}