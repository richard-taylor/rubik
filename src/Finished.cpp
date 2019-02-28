
#include <stack>
#include "Finished.h"
#include "Logging.h"

Finished::Finished(int cache_depth)
{
    cacheDepth(cache_depth);
}

bool Finished::on(const Cube &cube) const
{
    return cube.solved();
}

bool Finished::search(const Cube &cube,
                      const Sequence &twists,
                      std::vector<Sequence> &results) const
{
    auto found = cache.find(cube);

    if (found == cache.end())
    {
        return false;
    }
    else
    {
        const std::vector<Sequence> &routes = found->second;

        for (auto route = routes.begin(); route != routes.end(); ++route)
        {
            Sequence extended = twists;
            extended.append(route->inverse());

            results.push_back(extended);
        }
        return true;
    }
}

struct Position
{
    Cube cube;
    Sequence twists;
};

void Finished::cacheDepth(int depth)
{
    LOG_INFO << "Building a cache to " << depth << " turns.";

    std::stack<Position> stack;
    Position position;

    position.cube = Cube();
    position.twists = Sequence();

    stack.push(position);

    while (!stack.empty())
    {
        position = stack.top();
        stack.pop();

        int this_length = position.twists.length();
        std::vector<Sequence> &previous_routes = cache[position.cube];

        bool long_way_round = false;

        if (previous_routes.size() == 0)
        {
            previous_routes.push_back(position.twists);
        }
        else
        {
            int previous_length = previous_routes[0].length();

            if (this_length < previous_length)
            {
                previous_routes.clear();
                previous_routes.push_back(position.twists);
            }
            else if (this_length == previous_length)
            {
                previous_routes.push_back(position.twists);
            }
            else
            {
                long_way_round = true;
            }
        }

        if (this_length < depth && !long_way_round)
        {
            for (int f = 0; f < 6; f++)
            {
                if (position.twists.nextFace(Face(f)))
                {
                    for (int t = 1; t <= 3; t++)
                    {
                        Twist twist = Twist(Face(f), t);
                        Position next = position;

                        next.cube.twist(twist);
                        next.twists.add(twist);

                        stack.push(next);
                    }
                }
            }
        }
    }
    LOG_INFO << "Cache has " << cache.size() << " positions.";
}
