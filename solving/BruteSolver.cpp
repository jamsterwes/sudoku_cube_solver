#include "BruteSolver.h"
#include <iostream>
#include <queue>


using BSNode = TreeNode<BruteNode>;

// Metric: higher # of solved rings
class BSPtrCompare
{
public:
    bool operator()(BSNode* a, BSNode* b) {
        // Get # of solved rings for a
        int aRings = (solved(a->data.cube.sx0) ? 1 : 0);
        aRings += (solved(a->data.cube.sx1) ? 1 : 0);
        aRings += (solved(a->data.cube.sy0) ? 1 : 0);
        aRings += (solved(a->data.cube.sy1) ? 1 : 0);
        aRings += (solved(a->data.cube.sz0) ? 1 : 0);
        aRings += (solved(a->data.cube.sz1) ? 1 : 0);
        // Get # of solved rings for b
        int bRings = (solved(b->data.cube.sx0) ? 1 : 0);
        bRings += (solved(b->data.cube.sx1) ? 1 : 0);
        bRings += (solved(b->data.cube.sy0) ? 1 : 0);
        bRings += (solved(b->data.cube.sy1) ? 1 : 0);
        bRings += (solved(b->data.cube.sz0) ? 1 : 0);
        bRings += (solved(b->data.cube.sz1) ? 1 : 0);
        // If either greater than 0, print
        if (aRings > 2) std::cout << aRings << " ";
        if (bRings > 2) std::cout << bRings << " ";
        // Max queue
        return aRings > bRings;
    }
};


BruteNode::BruteNode() : cube(), sol(false) {}

BruteNode::BruteNode(const Cube& cube)
{
    this->cube = cube;
    sol = solved(cube);
}

BruteSolver::BruteSolver() : Solver(), moves(), root(nullptr) {}

void BruteSolver::initState(const Cube& cube)
{
    // Create new root
    if (root != nullptr) delete root;
    root = new BSNode(BruteNode(cube));
}

const Cube& BruteSolver::getState() const
{
    return root->data.cube;
}

const std::forward_list<RotationType>& BruteSolver::getMoves() const
{
    return moves;
}

// The main routine
RotationType BruteSolver::move()
{
    // Create move tree once:
    if (moves.empty())
    {
        std::cout << "Building move tree..." << std::endl;

        // Breadth-first search
        std::priority_queue<BSNode*, std::vector<BSNode*>, BSPtrCompare> queue{};
        queue.push(root);
        
        while (!queue.empty() && queue.top() && !queue.top()->data.sol)
        {
            // Rollout all 12 children
            if (queue.top()->children == nullptr)
            {
                Cube newCube;
                BruteNode newNode;
                for (int i = 0; i < 12; ++i)
                {
                    // Copy cube and make move
                    newCube = queue.top()->data.cube;
                    newCube = ::move(newCube, static_cast<RotationType>(i));

                    // Check for visitation
                    if (hasVisited(newCube)) continue;

                    // Add to visitation set
                    addVisited(newCube);

                    // Create node and attach to parent
                    newNode = BruteNode(newCube);
                    newNode.move = static_cast<RotationType>(i);
                    queue.top()->child(newNode.move) = new BSNode(queue.top(), newNode);

                    // Enqueue child
                    queue.push(queue.top()->child(newNode.move));
                }
            }

            // Pop front node
            queue.pop();
        }

        // Check for nothing found
        if (queue.empty()) 
        {
            std::cerr << "Found nothing ?" << std::endl;
            return RotationType::BACK_CCW;
        }

        // Set root (TODO: DONT LEAK MEMORY)
        root = queue.top();

        // Add solution to moveset
        BSNode* ptr = queue.top();
        while (ptr->parent != nullptr)
        {
            moves.push_front(ptr->data.move);
            ptr = ptr->parent;
        }
    }

    // Return first move I guess
    return moves.front();
}