
#include <ctime>
#include <stdexcept>
#include "DR.h"
#include "IterativeDeepening.h"
#include "Logging.h"
#include "Options.h"
#include "Report.h"
#include "Scrambler.h"
#include "Sequence.h"
#include "SequenceString.h"

void solve_axis(Cube cube, Axis axis)
{
    LOG_INFO << "Solving on axis " << axis;
    clock_t start = clock();

    IterativeDeepening solver;
    DR pattern(axis);

    std::vector<Sequence> solutions = solver.allSolutions(cube, pattern);
    clock_t solved = clock();

    report(solutions, false, solved - start);
}

int main(int argc, const char* argv[0])
{
    Log::setLevel(Log::INFO);
    std::string help = R"([options] axis scramble-string

  Options:
    -h or --help    : print this help text.

  axis:
    One of X, Y, Z. The desired DR orientation axis.

  scramble-string:
    A cube scramble in standard notation, e.g. " R U' F2 L D B' "
)";

    Options args(argc, argv);

    if (args.has("-h") || args.has("--help"))
    {
        LOG_REPORT << args.usage(help);
        return 1;
    }

    if (args.positionals() != 2)
    {
        LOG_ERROR << args.usage(help);
        return 1;
    }

    Cube cube;

    Scrambler scrambler;
    std::string scramble = args.position(1);
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

    std::string axis = args.position(0);
    if (axis == "X")
        solve_axis(cube, Axis::X);
    else
    if (axis == "Y")
        solve_axis(cube, Axis::Y);
    else
    if (axis == "Z")
        solve_axis(cube, Axis::Z);
    else
        LOG_ERROR << "The axis must be X, Y or Z.";
}
