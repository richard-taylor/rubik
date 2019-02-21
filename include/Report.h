
#ifndef REPORT_H
#define REPORT_H

#include <ctime>
#include <vector>
#include "Sequence.h"

void report(const std::vector<Sequence> &solutions, bool inverse, clock_t solving);

#endif
