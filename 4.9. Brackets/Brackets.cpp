#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <optional>
#include <string>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

// Используем long long для точного хранения больших чисел
long long CountValidBrackets(int N, int k)
{
    // Создаем таблицу dp размером (N+1) x (k+1), инициализированную нулями
    std::vector<std::vector<long long>> dp(N + 1, std::vector<long long>(k + 1, 0));

    // пустая строка
    for (int j = 0; j <= k; j++)
    {
        dp[0][j] = 1;
    }

    // невозможно создать форму с глубиной 0, если есть скобки
    for (int i = 1; i <= N; i++)
    {
        dp[i][0] = 0;
    }

    // Заполнение таблицы dp
    for (int i = 1; i <= N; i++)
    {
        // Считаем формы с максимальной глубиной не более k
        for (int j = 1; j <= k; j++)
        {
            dp[i][j] = 0;
            for (int m = 0; m < i; m++)
            {
                dp[i][j] += dp[m][j - 1] * dp[i - m - 1][j];
            }
        }
    }

    // Возвращаем разницу между dp[N][k] и dp[N][k-1]
    if (k == 0)
    {
        return dp[N][k];
    }

    // вычитаем формы с максимальной глубиной не более (k - 1)
    return dp[N][k] - dp[N][k - 1];
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Program use: \n"
            << " \"4.9. Brackets.exe\" <input> <output>";
        return std::nullopt;
    }

    Args result;

    result.inputFileName = argv[1];
    result.outputFileName = argv[2];

    return result;
}

void CalcBraces(const Args& args)
{
    std::ifstream input(args.inputFileName);
    if (!input)
    {
        throw std::runtime_error("Cant open input file: " + args.inputFileName);
    }

    int N, k;
    input >> N >> k;

    std::ofstream output;
    output.open(args.outputFileName);
    output << std::fixed << std::setprecision(0) << CountValidBrackets(N, k);
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);

    if (!args)
    {
        return EXIT_FAILURE;
    }

    try
    {
        CalcBraces(*args);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}