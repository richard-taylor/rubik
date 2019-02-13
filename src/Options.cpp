
#include "Options.h"

Options::Options(int argc, const char *argv[])
{
    command = argv[0];

    for (int i = 1; i < argc; i++)
    {
        const char *arg = argv[i];

        if (*arg == '-')
        {
            switchSet.insert(arg);
        }
        else
        {
            positionalList.push_back(arg);
        }
    }
}

int Options::switches() const
{
    return switchSet.size();
}

bool Options::has(const std::string &name) const
{
    return (switchSet.find(name) != switchSet.end());
}

int Options::positionals() const
{
    return positionalList.size();
}

std::string Options::position(int index) const
{
    return positionalList[index];
}

std::string Options::usage(const std::string &help) const
{
    return "usage: " + command + " " + help;
}
