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
using Pos = std::pair<int, int>;

Field ReadField(std::istream& input, Pos& queenPosition)
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

bool IsInBorder(Pos pos)
{
    return (pos.first >= 0 && pos.first < FIELD_SIZE) &&
        (pos.second >= 0 && pos.second < FIELD_SIZE);
}

int CountCheckersOnDiagonal(const Field& f, Pos start, Pos end, Pos& firstBlackPos, int dx, int dy) 
{
    int result = 0;
    int x = start.first;
    int y = start.second;

    while ((x != end.first || y != end.second)) 
    {
        if (f[x][y] == FieldCell::Black) 
        {
            result++;


            if (result == 1)
            {
                firstBlackPos = { x, y };
            }
        }

        x += dx;
        y += dy;
    }

    return result;
}

bool IsOppositeDirection(int dx1, int dy1, int dx2, int dy2)
{
    if (dx1 == 0 || dx2 == 0 || dy1 == 0 || dy2 == 0)
        return false;

    return (dx1 == -dx2) && (dy1 == -dy2);
}


void DFS(Field f, Pos queenPos, Path curPath, Path& bestPath, int lastDx, int lastDy)
{
    const int dx[] = { -1, -1, 1, 1 };
    const int dy[] = { -1, 1, -1, 1 };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            Pos firstPos = queenPos;
            int dPosX = dx[i] * j;
            int dPosY = dy[i] * j;
            Pos secondPos = { queenPos.first + dPosX, queenPos.second + dPosY };

            if (!IsInBorder(secondPos))
            {
                break;
            }

            if (f[secondPos.first][secondPos.second] == Black)
            {
                continue;
            }
            
            Pos firstBlackPos;
            int blacksOnDiagonal = CountCheckersOnDiagonal(f, firstPos, secondPos, firstBlackPos, dx[i], dy[i]);
            if (blacksOnDiagonal == 1 && !IsOppositeDirection(dx[i], dy[i], lastDx, lastDy))
            {
                Field newField = f;
                newField[secondPos.first][secondPos.second] = Queen;
                newField[firstPos.first][firstPos.second] = Empty;
                newField[firstBlackPos.first][firstBlackPos.second] = Empty;

                curPath.push_back(secondPos);
                DFS(newField, secondPos, curPath, bestPath, dx[i], dy[i]);

                curPath.pop_back();
            }
        }
    }

    if (curPath.size() > bestPath.size())
    {
        bestPath = curPath;
    }
}

int MaxEatenCheckers(const Field& f, const std::pair<int, int>& queenPosition, std::vector<std::pair<int, int>>& eatHistory)
{
    int maxEaten = 0;
    std::vector<std::pair<int, int>> currentPath = { queenPosition };
    std::vector<std::pair<int, int>> bestPath = { queenPosition };

    DFS(f, queenPosition, currentPath, bestPath, 0, 0);

    eatHistory = bestPath;
    return (bestPath.size() > 0) ? (int)bestPath.size() - 1 : 0;
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