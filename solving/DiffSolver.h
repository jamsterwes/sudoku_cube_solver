#pragma once
#include "Solver.h"
#include "../data/Tree.h"


struct DiffNode
{
    RotationType move;  // store what move made this node
    Cube cube;
    bool sol;
    int diff;

    DiffNode();
    DiffNode(const Cube& cube, int diff);
};


class DiffSolver : public Solver
{
public:
    DiffSolver();
protected:
    virtual void initState(const Cube& cube);
    virtual const Cube& getState() const;
    virtual const std::forward_list<RotationType>& getMoves() const;
    virtual RotationType move();
private:
    std::forward_list<RotationType> moves;
    TreeNode<DiffNode>* root;
};