#pragma once
#include "Solver.h"
#include "../data/Tree.h"


struct BruteNode
{
    RotationType move;  // store what move made this node
    Cube cube;
    bool sol;

    BruteNode();
    BruteNode(const Cube& cube);
};


class BruteSolver : public Solver
{
public:
    BruteSolver();
protected:
    virtual void initState(const Cube& cube);
    virtual const Cube& getState() const;
    virtual const std::forward_list<RotationType>& getMoves() const;
    virtual RotationType move();
private:
    std::forward_list<RotationType> moves;
    TreeNode<BruteNode>* root;
};