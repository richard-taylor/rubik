
#include <ctime>
#include <stdexcept>
#include "Finished.h"
#include "IterativeDeepening.h"
#include "Logging.h"
#include "Options.h"
#include "Report.h"
#include "Scrambler.h"
#include "Sequence.h"
#include "SequenceString.h"

int main(int argc, const char* argv[0])
{
    Log::setLevel(Log::INFO);
    std::string help = R"([options] scramble-string

Finish off a partially solved cube, optimally. This program is not
optimised for arbitrary cube states so it will be slow to process
positions that are more than 12 moves from a solution.

  Options:
    -h or --help    : print this help text.
    -i or --inverse : use the inverse of the scramble.

  scramble-string:
    A cube scramble in standard notation, e.g. " R U' F2 L D B' "
)";

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

    bool inverse = (args.has("-i") || args.has("--inverse"));

    Cube cube;
    Scrambler scrambler;
    std::string scramble = args.position(0);
    try
    {
        Sequence twists = SequenceString(scramble);

        if (inverse)
        {
            scrambler.scramble(cube, twists.inverse());
        }
        else
        {
            scrambler.scramble(cube, twists);
        }
    }
    catch (const std::invalid_argument &e)
    {
        LOG_ERROR << "Could not parse the scramble \"" << scramble << "\".";
        LOG_ERROR << e.what();
        return 1;
    }

    clock_t start = clock();

    IterativeDeepening solver;
    Finished pattern(5);

    std::vector<Sequence> solutions = solver.allSolutions(cube, pattern);

    clock_t solved = clock();
    report(solutions, inverse, solved - start);
}
