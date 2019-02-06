
#include "Logging.h"

Log::Level Log::loggingLevel = Log::ERROR;

Log::Log()
{
}

Log::~Log()
{
    stream << std::endl;
    fprintf(stdout, "%s", stream.str().c_str());
    fflush(stdout);
}

void Log::setLevel(Log::Level level)
{
    loggingLevel = level;
}

Log::Level Log::getLevel()
{
    return loggingLevel;
}

std::ostringstream& Log::info()
{
    stream << "INFO: ";
    return stream;
}

std::ostringstream& Log::debug()
{
    stream << "DEBUG: ";
    return stream;
}

std::ostringstream& Log::error()
{
    stream << "ERROR: ";
    return stream;
}

std::ostringstream& Log::report()
{
    return stream;
}
