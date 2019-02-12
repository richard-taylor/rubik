
#include <cassert>
#include "Options.h"

int main()
{
    const char *command_only_args[] = { "command" };

    Options command_only(1, command_only_args);
    assert(command_only.switches() == 0);
    assert(command_only.positionals() == 0);

    const char *help_args[] = { "command", "-h" };

    Options help(2, help_args);
    assert(help.switches() == 1);
    assert(help.has("-h") == true);
    assert(help.has("-i") == false);
    assert(help.positionals() == 0);

    const char *position_args[] = { "command", "first" };

    Options position(2, position_args);
    assert(position.switches() == 0);
    assert(position.positionals() == 1);
    assert(position.position(0) == "first");

    const char *mixed_args[] = { "command", "first", "-flag", "second", "-z" };

    Options mixed(5, mixed_args);
    assert(mixed.switches() == 2);
    assert(mixed.has("-z"));
    assert(mixed.has("-flag"));
    assert(mixed.positionals() == 2);
    assert(mixed.position(0) == "first");
    assert(mixed.position(1) == "second");
}
