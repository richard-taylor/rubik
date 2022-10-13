
#include <ctime>
#include <stdexcept>
#include "Cube.h"
#include "Logging.h"
#include "Report.h"

const long N = 1000000000;

/**
Do lots of random scrambles and count the number of "bad" edges with respect to
the Z axis and also the X axis. From this we can work out the probability of
the X axis having fewer "bad" edges than the Z axis for each of the possible
cases.
*/

int countBad(const Cube &cube, Axis axis)
{
    int bad = 0;
    for (int i = 0; i < 12; i++)
      if (!cube.edgeSlot(EdgeSlot(i)).isOriented(axis))
        bad++;
    return bad;
}

int main(int argc, const char* argv[0])
{
    Log::setLevel(Log::INFO);
    Cube cube;
    long samples = 0;
    long sums[7][7] = {};    // 0 <= bad edges / 2 <= 6
    long totals[7] = {};

    while (samples++ < N)
    {
        cube = cube.randomise();

        int badZ = countBad(cube, Z);
        int badX = countBad(cube, X);

        sums[badZ/2][badX/2]++;
        totals[badZ/2]++;
    }

    for (int z = 0; z <= 6; z++)
    {
        LOG_REPORT << z*2 << " bad Z, " << totals[z] / (double)N;
        for (int x = 0; x <= 6; x++)
        {
            LOG_REPORT << " , " << sums[z][x] / (double)totals[z];
        }
    }
    LOG_REPORT << "Better or same given Z";
    for (int z = 0; z <= 6; z++)
    {
        long sum = 0;
        for (int x = 0; x <= z; x++)
        {
            sum += sums[z][x];
        }
        LOG_REPORT << z*2 << " " << sum / (double)totals[z];
    }
    LOG_REPORT << "Better given Z";
    for (int z = 1; z <= 6; z++)
    {
        long sum = 0;
        for (int x = 0; x < z; x++)
        {
            sum += sums[z][x];
        }
        LOG_REPORT << z*2 << " " << sum / (double)totals[z];
    }
    LOG_REPORT << "Better by 4 given Z";
    for (int z = 2; z <= 6; z++)
    {
        long sum = 0;
        for (int x = 0; x < z - 1; x++)
        {
            sum += sums[z][x];
        }
        LOG_REPORT << z*2 << " " << sum / (double)totals[z];
    }
    LOG_REPORT << "Better by 6 given Z";
    for (int z = 3; z <= 6; z++)
    {
        long sum = 0;
        for (int x = 0; x < z - 2; x++)
        {
            sum += sums[z][x];
        }
        LOG_REPORT << z*2 << " " << sum / (double)totals[z];
    }

    long all_bos = 0;
    for (int z = 0; z <= 6; z++)
    {
        for (int x = 0; x <= z; x++)
        {
            all_bos += sums[z][x];
        }
    }
    LOG_REPORT << "Better or same not given Z " << all_bos / (double)N;

    long all_better = 0;
    for (int z = 1; z <= 6; z++)
    {
        for (int x = 0; x < z; x++)
        {
            all_better += sums[z][x];
        }
    }
    LOG_REPORT << "Better not given Z " << all_better / (double)N;
}
