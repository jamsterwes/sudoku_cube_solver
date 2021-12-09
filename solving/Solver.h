#pragma once
#include "../data/Cube.h"
#include <forward_list>
#include <unordered_set>


class Solver
{
public:
    Solver();
    std::forward_list<RotationType> solve(Cube cube);
protected:
    virtual void initState(const Cube& cube) = 0;
    virtual const Cube& getState() const = 0;
    virtual const std::forward_list<RotationType>& getMoves() const = 0;
    virtual RotationType move() = 0;
protected:
    bool hasVisited(const Cube& cube) const;
    void addVisited(const Cube& cube);
private:
    std::unordered_set<Cube> _visited;
};
