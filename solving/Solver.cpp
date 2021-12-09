#include "Solver.h"


Solver::Solver() {}

std::forward_list<RotationType> Solver::solve(Cube cube)
{
    // Init state
    initState(cube);

    // Move until solved
    while (!solved(getState()))
    {
        this->move();
    }

    // Return ordered moves list
    return getMoves();
}

bool Solver::hasVisited(const Cube& cube) const
{
    // Search positions set to detect cyclic traversal of move tree/graph/...
    return _visited.find(cube) != _visited.end();
}

void Solver::addVisited(const Cube& cube)
{
    // Try to insert position into position set
    if (!hasVisited(cube)) _visited.insert(cube);
}
