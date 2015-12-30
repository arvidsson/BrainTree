#pragma once

#include "Node.hpp"
#include "Blackboard.hpp"

namespace bt
{

class BehaviorTree : public Node
{
public:
    BehaviorTree();
    Status Update();
    void SetRoot(Node::Ptr node) { root = node; }
    Blackboard::Ptr GetBlackboard() { return blackboard; }
    
private:
    Node::Ptr root = nullptr;
    Blackboard::Ptr blackboard = nullptr;
};

}