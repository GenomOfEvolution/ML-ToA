#include "TaskController.h"
#include "PermutationTasks.h"

TaskController::TaskController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
        { "Info", [this]() { Info(); } },
        { "1", [this]() { TaskOne(); } },
        { "2", [this]() { TaskTwo(); } },
        { "3", [this]() { TaskThree(); } },
        { "4", [this]() { TaskFour(); } }
    })
{
    Info();
}

bool TaskController::HandleUserInput()
{
    std::string command;
    m_output << "Введите команду: ";
    while (!std::getline(m_input, command) || command.empty())
    {
        if (m_input.eof())
        {
            return false;
        }
    }

    if (command == "exit")
    {
        return false;
    }

    auto it = m_actionMap.find(command);
    if (it != m_actionMap.end())
    {
        it->second();
    }
    else
    {
        m_output << "Unknown command!\n";
        Info();
    }

    return true;
}

void TaskController::Info() const
{
    m_output << "\"Info\": Показать эту табличку\n"
        << "\"1\": Решить уравнение на перестановках вида A * X = B\n"
        << "\"2\": По заданной перестановке из N элементов выдать K следующих перестановок в лексикографическом порядке\n"
        << "\"3\": По заданной перестановке построить вектор  инверсий, а по вектору инверсий восстановить перестановку\n"
        << "\"4\": Перечислить перестановки из N элементов путем транспозиции смежных элементов с рекурсией и без нее\n"
        << "\"exit\": Завершить работу\n\n";
}

void TaskController::TaskOne() const
{
    m_output << "Введите перестановку A: ";
    Permutation A = ReadPermutation(m_input);

    m_output << "Введите перестановку B: ";
    Permutation B = ReadPermutation(m_input);

    m_output << "A: " << A << "\n";
    m_output << "B: " << B << "\n";
    m_output << "X: " << SolvePermutationEquation(A, B) << "\n";
}

void TaskController::TaskTwo() const
{
    m_output << "Введите перестановку: ";
    Permutation p = ReadPermutation(m_input);

    m_output << "Введите K: ";
    int K;
    m_input >> K;

    NextKPermutations(m_output, p, K);
}

void TaskController::TaskThree() const
{
    m_output << "Введите перестановку: ";
    Permutation p = ReadPermutation(m_input);

    std::vector<int> inv = PermToInversionVector(p);
    m_output << "Вектор инверсий: " << inv << "\n";
    m_output << "Восстановленная перестановка: " << InversionVectorToPerm(inv) << "\n";
}

void TaskController::TaskFour() const
{
    m_output << "Введите N: ";
    int N;
    m_input >> N;

    m_output << "Перестановки без рекурсии (алгоритм Джонсона-Троттера): \n\n";
    JohnsonTrotter(m_output, N);

    m_output << "\nРекурсивный метод: \n\n";
    GenerateAllRecursive(m_output, N);
    m_output << "\n";
}
