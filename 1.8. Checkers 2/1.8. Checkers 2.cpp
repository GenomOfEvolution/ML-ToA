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
};

const int FIELD_SIZE = 8;
using Field = std::vector<std::vector<FieldCell>>;

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

void DFS(const Field& field, int x, int y, int eaten, std::vector<std::pair<int, int>>& currentPath, std::vector<std::pair<int, int>>& bestPath)
{
    int dx[] = { -1, -1, 1, 1 };
    int dy[] = { -1, 1, -1, 1 };

    for (int dir = 0; dir < 4; ++dir)
    {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        while (nx >= 0 && nx < FIELD_SIZE && ny >= 0 && ny < FIELD_SIZE)
        {
            if (field[nx][ny] == FieldCell::Black)
            {
                int nnx = nx + dx[dir];
                int nny = ny + dy[dir];

                if (nnx >= 0 && nnx < FIELD_SIZE && nny >= 0 && nny < FIELD_SIZE && field[nnx][nny] == FieldCell::Empty)
                {
                    Field newField = field;
                    newField[x][y] = FieldCell::Empty;
                    newField[nx][ny] = FieldCell::Empty;
                    newField[nnx][nny] = FieldCell::Queen;

                    currentPath.push_back({ nnx, nny });

                    DFS(newField, nnx, nny, eaten + 1, currentPath, bestPath);

                    currentPath.pop_back();
                }
                break;
            }
            nx += dx[dir];
            ny += dy[dir];
        }
    }

    if (eaten > bestPath.size())
    {
        bestPath = currentPath;
    }
}

int MaxEatenCheckers(const Field& f, const std::pair<int, int>& queenPosition, std::vector<std::pair<int, int>>& eatHistory)
{
    int maxEaten = 0;
    std::vector<std::pair<int, int>> currentPath;
    std::vector<std::pair<int, int>> bestPath;

    DFS(f, queenPosition.first, queenPosition.second, 0, currentPath, bestPath);

    eatHistory = bestPath;
    return (int)bestPath.size();
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
    output << eatHistory.size();
    output << queenPosition.first << " " << queenPosition.second << "\n";
    for (const auto& move : eatHistory)
    {
        std::cout << move.first << " " << move.second << "\n";
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