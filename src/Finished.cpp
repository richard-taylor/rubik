
#include "Finished.h"
#include "Cube.h"

bool Finished::on(const Cube &cube) const
{
    return cube.solved();
}
