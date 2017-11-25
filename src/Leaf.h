#pragma once

#include "Node.h"
#include "Blackboard.h"

namespace BrainTree
{

class Leaf : public Node
{
public:
    Leaf() {}
    virtual ~Leaf() {}
    Leaf(Blackboard* blackboard) : blackboard(blackboard) {}
    
    virtual Status update() = 0;

protected:
    Blackboard* blackboard;
};

}
