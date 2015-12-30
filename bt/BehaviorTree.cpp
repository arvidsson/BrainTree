#include "BehaviorTree.hpp"

namespace bt
{

BehaviorTree::BehaviorTree()
{
    blackboard = std::make_shared<Blackboard>();
}

Node::Status BehaviorTree::Update()
{
    return root->Tick();
}

}