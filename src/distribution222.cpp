
#include <stdexcept>
#include "Block2x2x2.h"
#include "IterativeDeepening.h"
#include "Logging.h"
#include "RandomSequence.h"
#include "Scrambler.h"
#include "Sequence.h"
#include "SequenceString.h"

// Estimate the distribution of optimal solutions to a 2x2x2 block on
// a 3x3x3 cube. Experience suggests that 5 moves is the most common.

int main()
{
    Log::setLevel(Log::ERROR);

    RandomSequence scramble(50);
    int frequency[21] = { 0 };
    int N = 10000;

    for (int i = 1; i <= N; i++)
    {
        Sequence twists = scramble.next();
        Cube cube;
        Scrambler scrambler;

        scrambler.scramble(cube, twists);

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
            LOG_REPORT << "trials: " << i;
        }
    }

    LOG_REPORT << "Frequency distribution";

    for (int n = 0; n <= 20; n++)
    {
        LOG_REPORT << n << " : " << frequency[n] / double(N);
    }
}
