
#include <ctime>
#include <stdexcept>
#include "EOLine.h"
#include "IterativeDeepening.h"
#include "Logging.h"
#include "Options.h"
#include "Report.h"
#include "Scrambler.h"
#include "Sequence.h"
#include "SequenceString.h"

int countBad(const Cube &cube)
{
    int bad = 0;
    for (int i = 0; i < 12; i++)
      if (!cube.edgeSlot(EdgeSlot(i)).isOriented(Z))
        bad++;
    return bad;
}

int main(int argc, const char* argv[0])
{
    Log::setLevel(Log::INFO);
    std::string help = R"([options] scramble-string

  Options:
    -h or --help    : print this help text.
    -b or --bad     : use a random scramble with this number of bad edges.

  scramble-string:
    A cube scramble in standard notation, e.g. " R U' F2 L D B' "
)";

    Options args(argc, argv);

    if (args.has("-h") || args.has("--help"))
    {
        LOG_REPORT << args.usage(help);
        return 1;
    }

    bool random = args.has("-b") || args.has("--bad");

    if (args.positionals() != 1)
    {
        LOG_ERROR << args.usage(help);
        return 1;
    }

    Cube cube;

    if (random)
    {
        int wanted = std::stoi(args.position(0));
        int bad = -1;
        while (bad != wanted)
        {
            cube = cube.randomise();
            bad = countBad(cube);
        }
    }
    else
    {
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
    }

    clock_t start = clock();

    IterativeDeepening solver;
    EOLine pattern;

    std::vector<Sequence> solutions = solver.allSolutions(cube, pattern);
    clock_t solved = clock();

    if (random && !solutions.empty())
    {
        LOG_REPORT << "Scramble:\n    "
                   << SequenceString(solutions[0].inverse());
    }
    report(solutions, false, solved - start);
}
