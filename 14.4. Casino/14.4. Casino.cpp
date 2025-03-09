#include <iostream>
#include <fstream>
#include <vector>
#include <stack>  
#include <climits>
#include <optional>
#include <string>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: \"14.4. Casino.exe\" <inputFile> <outputFile>";
        return std::nullopt;
    }

    Args result;
    result.inputFileName = argv[1];
    result.outputFileName = argv[2];

    return result;
}

int MaxFinalValue(const std::vector<int>& arr, std::stack<int>& operations)
{
    int n = (int)arr.size();

    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    std::vector<std::vector<int>> split(n, std::vector<int>(n, -1));

    for (int i = 0; i < n; ++i)
    {
        dp[i][i] = arr[i];
    }

    for (int length = 2; length <= n; ++length)
    {
        for (int i = 0; i <= n - length; ++i)
        {
            int j = i + length - 1;
            dp[i][j] = INT_MIN;

            for (int k = i; k < j; ++k)
            {
                int current_value = dp[i][k] - dp[k + 1][j];
                if (current_value > dp[i][j])
                {
                    dp[i][j] = current_value;
                    split[i][j] = k;
                }
            }
        }
    }

    std::stack<std::pair<int, int>> stack;
    stack.push({ 0, n - 1 });   // Восстанавливаем разбиения с конца

    while (!stack.empty())
    {
        auto [l, r] = stack.top();
        stack.pop();

        if (l >= r)
            continue;

        int k = split[l][r];
        operations.push(k + 1);
        stack.push({ k + 1, r });
        stack.push({ l, k });
    }

    return dp[0][n - 1];
}

void Casino(const Args& args)
{
    std::ifstream input(args.inputFileName);
    std::ofstream output(args.outputFileName);

    if (!input)
    {
        std::cout << "Cant open " << args.inputFileName << "\n";
        return;
    }

    int n = 0;
    input >> n;

    std::vector<int> arr;
    arr.resize(n);

    for (int i = 0; i < n; ++i)
    {
        input >> arr[i];
    }

    std::stack<int> operations;
    int result = MaxFinalValue(arr, operations);

    output << result << "\n";
    while (!operations.empty()) 
    {
        output << operations.top() << " ";
        operations.pop();
    }
}

int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);
    if (!args)
    {
        return EXIT_FAILURE;
    }

    Casino(*args);

    return EXIT_SUCCESS;
}