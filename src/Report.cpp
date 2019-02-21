
#include <string>
#include "Logging.h"
#include "Report.h"
#include "SequenceString.h"

void report(const std::vector<Sequence> &solutions, bool inverse, clock_t solving)
{
    LOG_INFO << "Solving time: " << (((float)solving)/CLOCKS_PER_SEC) << " seconds.";
    LOG_REPORT << "Solutions:";

    unsigned int longest = 0;

    for (auto s = solutions.begin(); s != solutions.end(); ++s)
    {
        if (inverse)
        {
            std::string normal = std::string(SequenceString(*s));

            if (normal.length() > longest)
                longest = normal.length();
        }
        else
        {
            LOG_REPORT << "    " << SequenceString(*s);
        }
    }

    if (inverse)
    {
        for (auto s = solutions.begin(); s != solutions.end(); ++s)
        {
            std::string normal = std::string(SequenceString(*s));
            std::string inverse = std::string(SequenceString(s->inverse()));

            std::string padding = std::string(longest + 4 - normal.length(), ' ');

            LOG_REPORT << "    (" << normal << ")" << padding << inverse;
        }
    }
}
