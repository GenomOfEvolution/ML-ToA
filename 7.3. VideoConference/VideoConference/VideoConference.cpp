#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Event
{
    int time;
    int delta;
};

bool CompareEvents(const Event& a, const Event& b)
{
    if (a.time != b.time)
    {
        return a.time < b.time;
    }
    return a.delta < b.delta;
}

void Solve(std::istream& input, std::ostream& output)
{
    int n, m;
    input >> n >> m;

    std::vector<Event> events;

    for (int i = 0; i < n; i++)
    {
        int ni;
        input >> ni;
        for (int j = 0; j < ni; j++)
        {
            int a, b;
            input >> a >> b;
            events.push_back({ a, 1 });
            events.push_back({ b, -1 });
        }
    }

    sort(events.begin(), events.end(), CompareEvents);

    int maxDuration = 0;
    int bestStart = 0;
    int bestEnd = 0;

    int currentCount = 0;
    int startSegment = -1;

    for (const auto& event : events)
    {
        int prevCount = currentCount;
        currentCount += event.delta;

        if (prevCount >= m && currentCount < m)
        {
            int endSegment = event.time;
            int duration = endSegment - startSegment;
            if (duration > maxDuration)
            {
                maxDuration = duration;
                bestStart = startSegment;
                bestEnd = endSegment;
            }
            else if (duration == maxDuration && startSegment < bestStart)
            {
                bestStart = startSegment;
                bestEnd = endSegment;
            }
        }

        if (currentCount >= m && prevCount < m)
        {
            startSegment = event.time;
        }
    }

    if (maxDuration > 0)
    {
        output << maxDuration << std::endl;
        output << bestStart << " " << bestEnd << std::endl;
    }
    else
    {
        output << 0 << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: VideoConference.exe <input> <output>";
    }

    std::ifstream input;
    input.open(argv[1]);

    if (!input)
    {
        return EXIT_FAILURE;
    }

    std::ofstream output;
    output.open(argv[2]);
    Solve(input, output);

    return EXIT_SUCCESS;
}