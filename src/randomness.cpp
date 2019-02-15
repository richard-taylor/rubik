
#include <string.h>
#include <sstream>
#include "Cube.h"
#include "Logging.h"

// To have any hope of estimating the distribution of optimal solutions to
// various problems, we need to ensure that we start with a good distribution
// of cube states.
//
// Applying long random sequences of twists is known to not be very good
// at this. Instead we generate actual cube states that we hope are
// randomly distributed.
//
// This program tests that distribution.

void report(std::string title, int *table, int rows, int columns)
{
    LOG_REPORT << title;
    for (int i = 0; i < rows; i++)
    {
        std::ostringstream row;
        for (int j = 0; j < columns; j++)
        {
            row << " " << *(table++);
        }
        LOG_REPORT << "   " << row.str();
    }
}

int main()
{
    Log::setLevel(Log::ERROR);

    int corner_position[8][8];
    int corner_orientation[8][6];

    int edge_position[12][12];
    int edge_orientation[12][8];

    memset(corner_position, 0, sizeof(corner_position));
    memset(corner_orientation, 0, sizeof(corner_orientation));

    memset(edge_position, 0, sizeof(edge_position));
    memset(edge_orientation, 0, sizeof(edge_orientation));

    Cube solved;
    int N = 1000000;

    for (int i = 1; i <= N; i++)
    {
        Cube cube = solved.randomise();

        for (int c = 0; c < 8; c++)
        {
            Corner corner = cube.cornerSlot(CornerSlot(c));
            corner_position[c][corner.getIndex()]++;
            corner_orientation[c][corner.getOrientation()]++;
        }

        for (int e = 0; e < 12; e++)
        {
            Edge edge = cube.edgeSlot(EdgeSlot(e));
            edge_position[e][edge.getIndex()]++;
            edge_orientation[e][edge.getOrientation()]++;
        }
    }
    report("Corner position", &corner_position[0][0], 8, 8);
    report("Corner orientation", &corner_orientation[0][0], 8, 6);

    report("Edge position", &edge_position[0][0], 12, 12);
    report("Edge orientation", &edge_orientation[0][0], 12, 8);
}
