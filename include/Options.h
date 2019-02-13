
#ifndef OPTIONS_H
#define OPTIONS_H

#include <set>
#include <string>
#include <vector>

/**
Command-line options for shell-based tools.

Anything starting with '-' is a switch and the order is not significant;
everything else is a positional argument, where the order does matter.

For example,

    command -apple something -carrot -banana other

is the same as:

    command -apple -banana -carrot something other

but different from:

    command -apple -banana -carrot other something
*/
class Options
{
public:

    Options(int argc, const char *argv[]);

    int switches() const;
    bool has(const std::string &name) const;

    int positionals() const;
    std::string position(int index) const;

    std::string usage(const std::string &help) const;

private:
    std::string command;
    std::set<std::string> switchSet;
    std::vector<std::string> positionalList;
};

#endif
