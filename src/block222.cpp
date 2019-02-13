
#include <ctime>
#include <stdexcept>
#include "Block2x2x2.h"
#include "IterativeDeepening.h"
#include "Logging.h"
#include "Options.h"
#include "Scrambler.h"
#include "Sequence.h"
#include "SequenceString.h"

void report(const std::vector<Sequence> &solutions, clock_t solving)
{
    LOG_INFO << "solving time: " << (((float)solving)/CLOCKS_PER_SEC) << " seconds.";
    LOG_REPORT << "solutions:";
    for (auto s = solutions.begin(); s != solutions.end(); ++s)
    {
        LOG_REPORT << "    " << SequenceString(*s);
    }
}

int main(int argc, const char* argv[0])
{
    Log::setLevel(Log::INFO);
    std::string help = "[--help] [-i] scramble-string";

    Options args(argc, argv);

    if (args.has("-h") || args.has("--help"))
    {
        LOG_REPORT << args.usage(help);
        return 1;
    }
    if (args.positionals() != 1)
    {
        LOG_ERROR << args.usage(help);
        return 1;
    }

    Cube cube;
    Scrambler scrambler;
    std::string scramble = args.position(0);
    try
    {
        Sequence twists = SequenceString(scramble);
        scrambler.scramble(cube, twists);
    }
    catch (const std::invalid_argument &e)
    {
        LOG_ERROR << "Could not parse the scramble \"" << scramble << "\".";
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
