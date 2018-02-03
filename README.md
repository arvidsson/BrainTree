BrainTree
======

A C++ [behavior tree](http://gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php) header-only library.

Features
--------

* behavior tree
* predefined composites
* predefined decorators
* rudimentary blackboard

Install
-------

Include all files in src folder in your project.

Example
-------

```c++
#include <BrainTree.h>

class WaitNode : public BrainTree::Leaf
{
public:
    // note: using a blackboard is optional
    WaitNode(BrainTree::Blackboard::Ptr board, int limit) : Leaf(board), limit(limit) {}

    void initialize() override
    {
        counter = 0;
    }

    Status update() override
    {
        counter++;
        if (counter >= limit) {
            return Node::Status::Success;
        }

        return Node::Status::Running;
    }

private:
    int limit;
    int counter;
};

int main()
{
    BrainTree::BehaviorTree tree;

    // each tree has one blackboard each, which the leafs can use
    auto &blackboard = tree.GetBlackboard();

    // create a sequence
    auto attackEnemySequence = std::make_shared<BrainTree::Sequence>();
    auto targetNearestEnemyNode = std::make_shared<TargetNearestEnemyNode>(blackboard);
    auto moveToEnemyNode = std::make_shared<MoveToEnemyNode>(blackboard);
    auto attackEnemyNode = std::make_shared<AttackEnemyNode>(blackboard);
    attackEnemySequence->AddChild(targetNearestEnemyNode);
    attackEnemySequence->AddChild(moveToEnemyNode);
    attackEnemySequence->AddChild(attackEnemyNode);

    // ...

    // create a selector
    auto selector = std::make_shared<BrainTree::Selector>();
    selector->AddChild(attackEnemySequence);
    selector->AddChild(idleSequence);

    // set the root of the tree
    tree.SetRoot(selector);

    // inside game loop
    tree.update();

    return 0;
}
```

License
-------
MIT (c) arvidsson
