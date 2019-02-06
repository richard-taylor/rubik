
#ifndef LOGGING_H
#define LOGGING_H

#include <sstream>

class Log
{
public:
    enum Level { TRACE, DEBUG, INFO, WARNING, ERROR, REPORT, SILENT };

    Log();
    ~Log();

    static void setLevel(Level level);
    static Level getLevel();

    std::ostringstream& info();
    std::ostringstream& debug();
    std::ostringstream& error();
    std::ostringstream& report();

private:
    static Level loggingLevel;
    std::ostringstream stream;
};

/**
Use these macros to do the logging in code. For example,

LOG_INFO << "Starting up.";
LOG_DEBUG << "Step " << n;
LOG_REPORT << "The result is " << answer;
*/
#define LOG_INFO if (Log::getLevel() > Log::INFO) { /* NOP */ } else Log().info()
#define LOG_DEBUG if (Log::getLevel() > Log::DEBUG) { /* NOP */ } else Log().debug()
#define LOG_ERROR if (Log::getLevel() > Log::ERROR) { /* NOP */ } else Log().error()
#define LOG_REPORT if (Log::getLevel() > Log::REPORT) { /* NOP */ } else Log().report()

#endif
