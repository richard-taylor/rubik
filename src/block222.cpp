
#include <ctime>
#include <stdexcept>
#include "Block2x2x2.h"
#include "IterativeDeepening.h"
#include "Logging.h"
#include "Scrambler.h"
#include "Sequence.h"
#include "SequenceString.h"

void report(const std::vector<Sequence> &solutions, clock_t solving)
{
    LOG_INFO << "solving time: " << (((float)solving)/CLOCKS_PER_SEC);
    LOG_REPORT << "solutions:";
    for (auto s = solutions.begin(); s != solutions.end(); ++s)
    {
        LOG_REPORT << "    " << SequenceString(*s);
    }
}

int main(int argc, char* argv[0])
{
    Log::setLevel(Log::INFO);

    if (argc != 2)
    {
        LOG_ERROR << "usage: " << argv[0] << " scramble-string";
        return 1;
    }

    Cube cube;
    Scrambler scrambler;

    try
    {
        Sequence twists = SequenceString(argv[1]);
        scrambler.scramble(cube, twists);
    }
    catch (const std::invalid_argument &e)
    {
        LOG_ERROR << "Could not parse the scramble \"" << argv[1] << "\".";
        LOG_ERROR << e.what();
        return 1;
    }

    clock_t start = clock();

    IterativeDeepening solver;
    Block2x2x2 pattern;

    std::vector<Sequence> solutions = solver.allSolutions(cube, pattern);

    clock_t solved = clock();
    report(solutions, solved - start);
}
