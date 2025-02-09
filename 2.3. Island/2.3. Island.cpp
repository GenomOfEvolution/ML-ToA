// 2.3. Остров (10)
// Прямоугольный остров имеет кратеры, заполненные водой. Кратером называется совокупность квадратов, удовлетворяющая таким условиям:
// •	из любого квадрата этого кратера можно  попасть  в  любой другой квадрат этого же кратера, последовательно переходя по кратеру из квадрата в квадрат через их общую сторону;
// •	никакие два кратера не пересекаются и не касаются друг друга ни по вертикальной, ни по горизонтальной сторонам квадратов (касание кратеров углами допускается);
// •	нет кратеров на границе прямоугольника.
// Требуется соединить каналами не менее двух  кратеров с океаном так, чтобы общая длина каналов была минимальной. Каналом называется путь из клеток суши, в котором две соседние клетки имеют общую сторону.
// Ввод. В первой строке находятся числа N и M  через пробел, далее  идут  N строк по M символов (3 ≤ N, M ≤ 50). Символ X обозначает территорию кратера, точка соответствует  незанятой территории. Других символов в исходном файле нет.
// Вывод. Вывести N строк по M знаков. Каналы  показать символами '*'. Гарантируется наличие решения.
//
// Среда: MS VisualStudio 2022 cpp standart 20
// Автор: Нечаев Олег ПС-24


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

const char ISLAND_CELL = '.';
const char CRATER_CELL = 'X';
const char CHANNEL_CELL = '*';

const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

using Field = std::vector<std::vector<char>>;
using Craters = std::vector<std::vector<int>>;
using Path = std::pair<int, std::vector<std::pair<int, int>>>;

Field ReadField(std::ifstream& input)
{
    int width, height;
    input >> height >> width;

    Field field(height, std::vector<char>(width));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            input >> field[i][j];
        }
    }

    return field;
}

void FillCraters(int x, int y, int num, const Field& field, Craters& craters)
{
    if (x < 0 || x >= field.size() || y < 0 || y >= field[0].size() || field[x][y] != CRATER_CELL || craters[x][y] != 0) 
    {
        return;
    }

    craters[x][y] = num;

    FillCraters(x - 1, y, num, field, craters);  
    FillCraters(x + 1, y, num, field, craters);  
    FillCraters(x, y - 1, num, field, craters);  
    FillCraters(x, y + 1, num, field, craters);  
}

void SetCraters(const Field& field, Craters& craters) 
{
    int counter = 1;
    for (size_t i = 0; i < field.size(); ++i) 
    {
        for (size_t j = 0; j < field[i].size(); ++j) 
        {
            if (field[i][j] == CRATER_CELL && craters[i][j] == 0) 
            {
                FillCraters(int(i), int(j), counter++, field, craters);
            }
        }
    }
}

int MaxCraters(const Craters& craters)
{
    int maxValue = 0;

    for (const auto& row : craters) 
    {
        for (int value : row) 
        {
            maxValue = std::max(maxValue, value); 
        }
    }

    return maxValue;
}

// Подготовить поле, сделав нужный кратер в 1, другие INT_MAX
Craters SetWorkField(const Craters& craters, int curCrater)
{
    Craters result = craters;

    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
        {
            if (result[i][j] > 0)
            {
                result[i][j] = (result[i][j] != curCrater) ? INT_MAX : 1;
            }
        }
    }

    return result;
}

Path WaveAlgorithm(Craters& grid) 
{
    int rows = (int)grid.size();
    if (rows == 0)
    {
        return { -1, {} };
    }
        
    int cols = (int)grid[0].size();
    std::queue<std::pair<int, int>> q;

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            if (grid[i][j] == 1)
            {
                q.push({ i, j });
            }
        }
    }

    while (!q.empty()) 
    {
        auto current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;

        // Если достигли границы, вернуть весь путь
        if (x == 0 || x == rows - 1 || y == 0 || y == cols - 1) 
        {
            std::vector<std::pair<int, int>> path;
            int dist = grid[x][y];
            path.push_back({ x, y });

            while (grid[x][y] != 1) 
            {
                for (int i = 0; i < 4; ++i) 
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) 
                    {
                        if (grid[nx][ny] == grid[x][y] - 1) 
                        {
                            x = nx;
                            y = ny;
                            path.push_back({ x, y });
                            break;
                        }
                    }
                }
            }

            path.pop_back();
            reverse(path.begin(), path.end());
            
            return { dist - 1, path };
        }

        for (int i = 0; i < 4; ++i) 
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) 
            {
                if (grid[nx][ny] == 0) 
                {
                    grid[nx][ny] = grid[x][y] + 1;  
                    q.push({ nx, ny });  
                }
            }
        }
    }

    return { -1, {} };
}

std::vector<Path> ShortestPathsToBorder(const Craters& craters)
{
    std::vector<Path> paths;
    int cratersAmount = MaxCraters(craters);

    for (int i = 1; i <= cratersAmount; i++)
    {
        Craters workField = SetWorkField(craters, i);
        Path p = WaveAlgorithm(workField);

        if (p.first != -1)
        {
            paths.push_back(p);
        }
        else
        {
            continue;
        }
    }

    std::sort(paths.begin(), paths.end(), [](const Path& a, const Path& b) {
        return a.first < b.first;
        });

    return paths;
}

std::vector<std::pair<int, int>> GetPath(std::pair<int, int> from, std::pair<int, int> to, const Craters& distances)
{
    std::vector<std::pair<int, int>> path;
    int y = to.first, x = to.second;

    path.push_back({ y, x });

    while (y != from.first || x != from.second) 
    {
        int minDist = distances[y][x];
        int nextY = y, nextX = x;

        for (int i = 0; i < 4; i++) 
        {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny >= 0 && nx >= 0 && ny < distances.size() && nx < distances[0].size()) 
            {
                if (distances[ny][nx] < minDist) 
                {
                    minDist = distances[ny][nx];
                    nextY = ny;
                    nextX = nx;
                }
            }
        }

        y = nextY;
        x = nextX;

        path.push_back({ y, x });
    }

    return path;
}


bool IsBoundary(int y, int x, const Craters& craters) 
{
    return y == 0 || x == 0 || y == craters.size() - 1 || x == craters[0].size() - 1;
}

Path WaveAlgorithmToBoth(Craters& craters, std::pair<int, int> startCell) 
{
    std::pair<int, int> boundary = { -1, -1 }; 
    std::pair<int, int> firstIsland = { -1, -1 }; 
    std::pair<int, int> secondIsland = { -1, -1 };  

    int rows = (int)craters.size();
    int cols = (int)craters[0].size();

    Craters distances(rows, std::vector<int>(cols, INT_MAX));

    std::queue<std::pair<int, int>> q;
    q.push(startCell);

    distances[startCell.first][startCell.second] = 0;

    while (!q.empty() && (boundary.first == -1 || (firstIsland.first == -1 || secondIsland.first == -1))) 
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) 
        {
            int ny = y + dy[i], nx = x + dx[i];

            if (ny >= 0 && nx >= 0 && ny < rows && nx < cols && distances[ny][nx] == INT_MAX) 
            {
                if (craters[ny][nx] > 0) 
                {
                    if (firstIsland.first == -1) 
                    {
                        firstIsland = { ny, nx };
                        distances[ny][nx] = distances[y][x] + 1;
                    }
                    else if (secondIsland.first == -1 && craters[ny][nx] != craters[firstIsland.first][firstIsland.second]) 
                    {
                        secondIsland = { ny, nx };
                        distances[ny][nx] = distances[y][x] + 1;
                    }
                }
                else 
                {
                    distances[ny][nx] = distances[y][x] + 1;
                    q.push({ ny, nx });
                }

                if (IsBoundary(ny, nx, craters) && boundary.first == -1) 
                {
                    boundary = { ny, nx };
                }
            }
        }
    }

    if (boundary.first == -1 || firstIsland.first == -1 || secondIsland.first == -1)
    {
        return { -1, {} };
    }

    int total = distances[boundary.first][boundary.second] + distances[secondIsland.first][secondIsland.second] + distances[firstIsland.first][firstIsland.second] - 1;
    
    auto p1 = GetPath(startCell, firstIsland, distances);
    auto p2 = GetPath(startCell, secondIsland, distances);
    auto p3 = GetPath(startCell, boundary,  distances);

    std::vector<std::pair<int, int>> combinedPath;

    combinedPath.insert(combinedPath.end(), p1.begin(), p1.end());
 
    for (const auto& cell : p2) 
    {
        if (combinedPath.back() != cell) 
        {  
            combinedPath.push_back(cell);
        }
    }

   
    for (const auto& cell : p3) 
    {
        if (combinedPath.back() != cell) 
        {  
            combinedPath.push_back(cell);
        }
    }

    return { total, combinedPath };
}

std::vector<Path> ShortestPathsFromCells(const Craters& craters)
{
    std::vector<Path> result;
    for (int i = 0; i < craters.size(); i++)
    {
        for (int j = 0; j < craters[i].size(); j++)
        {
            if (craters[i][j] == 0)
            {
                Craters workField = craters;
                Path p = WaveAlgorithmToBoth(workField, { i, j });
                if (p.first != INT_MAX && p.first != -1)
                {
                    result.push_back(p);
                }
            }
        }
    }

    std::sort(result.begin(), result.end(), [](const Path& a, const Path& b) {
        return a.first < b.first;
        });

    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Input format: <input file> <output file>\n";
        return EXIT_FAILURE;
    }

    std::ifstream input;
    input.open(argv[1]);
    if (!input)
    {
        std::cout << "Can't open " << argv[1] << "\n";
        return EXIT_FAILURE;
    }

    Field field = ReadField(input);
    input.close();

    // 1. Пометить клетки кратеров числовыми метками 
    Craters craters(field.size(), std::vector<int>(field[0].size(), 0));
    SetCraters(field, craters);

    // 2. Два кратчайших пути от разных кратеров до края, определить их общую длину
    std::vector<Path> pathsToBorder = ShortestPathsToBorder(craters);
    int pathToBorderTotal = INT_MAX;
    if (pathsToBorder.size() >= 2)
    {
        pathToBorderTotal = pathsToBorder[0].first + pathsToBorder[1].first;
    }
   
    // 3. От каждой свободной клетки поиском  в  ширину найти
    // Кратчайший путь до границы и до 2-х кратеров
    std::vector<Path> pathsFromCells = ShortestPathsFromCells(craters);
    int cellToBothTotal = INT_MAX;
    if (pathsFromCells.size() > 0)
    {
        cellToBothTotal = pathsFromCells[0].first;
    }

    // 4. Сравнить и вывести кротчайшие пути.
    if (pathToBorderTotal < cellToBothTotal)
    {
        for (int i = 0; i < 2; i++)
        {
            for (auto p : pathsToBorder[i].second)
            {
                field[p.first][p.second] = CHANNEL_CELL;
            }
        }
    }
    else
    {
        for (auto p : pathsFromCells[0].second)
        {
            if (field[p.first][p.second] != CRATER_CELL)
            {
                field[p.first][p.second] = CHANNEL_CELL;
            }    
        }
    }

    std::ofstream output;
    output.open(argv[2]);
    if (!output)
    {
        std::cout << "Can't open " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    for (int i = 0; i < craters.size(); i++)
    {
        for (int j = 0; j < craters[i].size(); j++)
        {
            output << field[i][j];
        }
        output << '\n';
    }

    output.close();

    return EXIT_SUCCESS;
}