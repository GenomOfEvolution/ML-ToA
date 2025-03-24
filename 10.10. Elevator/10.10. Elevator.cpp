#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

long long FindMaxPeople(int N, long long C, long long P, long long T, std::vector<long long>& A) 
{
    std::vector<long long> dp(T + 1, 0); // dp[t] - максимум людей за время t

    for (int k = 1; k <= N; k++) 
    {
        long long time = 2 * k * P; // Время для поездки до k и обратно
        if (time > T)
        {
            continue;
        }

        std::vector<long long> people(k, 0); // Текущие доступные люди на этажах 1 до k
        for (int i = 0; i < k; i++) people[i] = A[i];

        // Сначала идем вверх, забираем людей по порядку, пока можем
        long long currentLoad = 0;
        long long totalPeople = 0;
        std::vector<long long> pickedUp(k, 0); // Сколько забрали с каждого этажа

        // На пути вверх
        for (int i = 0; i < k; i++) 
        {
            long long canPick = std::min(C - currentLoad, people[i]);
            if (canPick > 0)
            {
                currentLoad += canPick;
                pickedUp[i] = canPick;
                people[i] -= canPick;
                totalPeople += canPick;
            }
        }

        // На пути вниз
        for (int i = k - 1; i >= 0; i--) 
        {
            if (people[i] > 0 && currentLoad < C)
            {
                long long canPick = std::min(C - currentLoad, people[i]);
                currentLoad += canPick;
                totalPeople += canPick;
                pickedUp[i] += canPick; 
            }
        }


        for (long long t = T; t >= time; t--) 
        {
            dp[t] = std::max(dp[t], dp[t - time] + totalPeople);
        }
    }

    return dp[T];
}

void Elevator(const Args& args)
{
    std::ifstream input(args.inputFileName);
    if (!input)
    {
        std::cout << "Can't open " << args.inputFileName;
        return;
    }

    std::ofstream output(args.outputFileName);

    int N;
    long long C, P, T;

    input >> N >> C >> P >> T;
    std::vector<long long> A(N);
    for (int i = 0; i < N; i++)
    {
        input >> A[i];
    }

    long long result = FindMaxPeople(N, C, P, T, A);
    output << result;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    Args result;
    if (argc != 3)
    {
        std::cout << "Usage: \"10.10. Elevator.exe\" <input file> <output file>\n";
        return std::nullopt;
    }

    result.inputFileName = argv[1];
    result.outputFileName = argv[2];

    return result;
}


int main(int argc, char* argv[])
{
    std::optional<Args> args = ParseArgs(argc, argv);

    if (!args)
    {
        return EXIT_FAILURE;
    }

    Elevator(*args);

    return EXIT_SUCCESS;
}