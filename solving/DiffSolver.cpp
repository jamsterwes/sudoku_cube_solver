#include "DiffSolver.h"
#include <iostream>
#include <queue>


using DSNode = TreeNode<DiffNode>;

static int minmm = 100000;

int metric(const Ring& r)
{
    return __builtin_popcount(r ^ RINGSET_SOLVED);
}

int metric(const Cube& a)
{
    int aRings = metric(a.sx0);
    aRings += metric(a.sx1);
    aRings += metric(a.sy0);
    aRings += metric(a.sy1);
    aRings += metric(a.sz0);
    aRings += metric(a.sz1);
    return aRings;
}

// Metric: minimum popcount diff solved
class DSPtrCompare
{
public:
    bool operator()(DSNode* a, DSNode* b) {
        if (metric(a->data.cube) < minmm)
        {
            minmm = metric(a->data.cube);
            std::cout << minmm << std::endl;
        }
        if (metric(b->data.cube) < minmm)
        {
            minmm = metric(b->data.cube);
            std::cout << minmm << std::endl;
        }
        return metric(a->data.cube) < metric(b->data.cube);
    }
};


DiffNode::DiffNode() : cube(), sol(false), diff() {}

DiffNode::DiffNode(const Cube& cube, int diff) : diff(diff)
{
    this->cube = cube;
    sol = solved(cube);
}

DiffSolver::DiffSolver() : Solver(), moves(), root(nullptr) {}

void DiffSolver::initState(const Cube& cube)
{
    // Create new root
    if (root != nullptr) delete root;
    root = new DSNode(DiffNode(cube, 0));
}

const Cube& DiffSolver::getState() const
{
    return root->data.cube;
}

const std::forward_list<RotationType>& DiffSolver::getMoves() const
{
    return moves;
}

// The main routine
RotationType DiffSolver::move()
{
    // Create move tree once:
    if (moves.empty())
    {
        std::cout << "Building move tree..." << std::endl;

        // Breadth-first search
        std::priority_queue<DSNode*, std::vector<DSNode*>, DSPtrCompare> queue{};
        queue.push(root);
        
        while (!queue.empty() && queue.top() && !queue.top()->data.sol)
        {
            // If node outside of [0, min + 10] range metric, pop
            // ALSO IF == minmm, pop
            if (metric(queue.top()->data.cube) > minmm + 10) 
            {
                queue.pop();
                continue;
            }
            // Rollout all 12 children
            if (queue.top()->children == nullptr)
            {
                Cube newCube;
                DiffNode newNode;
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
                    newNode = DiffNode(newCube, metric(newCube) - metric(queue.top()->data.cube));
                    newNode.move = static_cast<RotationType>(i);
                    queue.top()->child(newNode.move) = new DSNode(queue.top(), newNode);

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
        DSNode* ptr = queue.top();
        while (ptr->parent != nullptr)
        {
            moves.push_front(ptr->data.move);
            ptr = ptr->parent;
        }
    }

    // Return first move I guess
    return moves.front();
}