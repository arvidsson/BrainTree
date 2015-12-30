bt
======

A C++ behavior tree implementation.

example
--------------
```c++
#include "bt/bt.hpp"
using namespace bt;

class WaitNode : public Leaf
{
public:
    WaitNode(Blackboard::Ptr board, int limit) : Leaf(board), limit(limit) {}

    void Initialize() override
    {
        counter = 0;
    }

    Status Update() override
    {
        counter++;
        if (counter >= limit) {
            return Node::Status::Success;
        }

        return Node::Status::Running;
    }

private:
    int counter = 0;
    int limit;
};

// define the rest of the nodes here...

int main()
{
    BehaviorTree tree;
    auto &blackboard = tree.GetBlackboard();

    // attack enemy sequence
    auto attackEnemySequence = std::make_shared<bt::Sequence>();
    auto targetNearestEnemyNode = std::make_shared<TargetNearestEnemyNode>(blackboard);
    auto moveToEnemyNode = std::make_shared<MoveToEnemyNode>(blackboard);
    auto attackEnemyNode = std::make_shared<AttackEnemyNode>(blackboard);
    attackEnemySequence->AddChild(targetNearestEnemyNode);
    attackEnemySequence->AddChild(moveToEnemyNode);
    attackEnemySequence->AddChild(attackEnemyNode);

    // idle sequence
    auto idleSequence = std::make_shared<bt::Sequence>();
    auto setRandomTargetNode = std::make_shared<SetRandomTargetNode>(blackboard);
    auto moveNode = std::make_shared<MoveNode>(blackboard);
    auto waitNode = std::make_shared<WaitNode>(blackboard, 500);
    idleSequence->AddChild(setRandomTargetNode);
    idleSequence->AddChild(moveNode);
    idleSequence->AddChild(waitNode);

    auto selector = std::make_shared<bt::Selector>();
    selector->AddChild(attackEnemySequence);
    selector->AddChild(idleSequence);
    tree.SetRoot(selector);

    tree.Update();

    return 0;
}
```
