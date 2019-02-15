
#include <stdexcept>
#include "Block2x2x2.h"
#include "IterativeDeepening.h"
#include "Logging.h"
#include "Sequence.h"

// Estimate the distribution of optimal solutions to a 2x2x2 block on
// a 3x3x3 cube. Experience suggests that 5 moves is the most common.

void report(int trials, int *frequency)
{
    LOG_REPORT << "Trials: " << trials;
    LOG_REPORT << "Frequency distribution";

    for (int n = 0; n <= 20; n++)
    {
        LOG_REPORT << n << " : " << frequency[n]
                        << " : " << frequency[n] / double(trials);
    }
}

int main()
{
    Log::setLevel(Log::ERROR);

    Cube solved;
    int frequency[21] = { 0 };
    int N = 100000;

    for (int i = 1; i <= N; i++)
    {
        Cube cube = solved.randomise();

        IterativeDeepening solver;
        Block2x2x2 pattern;
        try
        {
            Sequence solution = solver.solve(cube, pattern);

            frequency[solution.length()]++;
        }
        catch (const std::runtime_error &e)
        {
            LOG_ERROR << "No solution found.";
        }
        if (i % 10 == 0)
        {
            report(i, frequency);
        }
    }
}
