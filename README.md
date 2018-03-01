BrainTree
======

A C++ [behavior tree](http://gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php) header-only library.

Features
--------

* behavior tree
* predefined composites
* predefined decorators
* rudimentary blackboard
* (in progress) behavior tree builders

Install
-------

Include ```BrainTree.h``` in your project.

Example
-------

```c++
#include <BrainTree.h>
namespace bt = BrainTree;

class WaitNode : public bt::Leaf
{
public:
    // note: using a blackboard is optional
    WaitNode(bt::Blackboard::Ptr board, int limit) : Leaf(board), limit(limit) {}

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
    bt::BehaviorTree tree;

    // each tree has one blackboard each, which the leafs can use
    auto &blackboard = tree.getBlackboard();

    // create a sequence
    auto attackEnemySequence = std::make_shared<bt::Sequence>();
    auto targetNearestEnemyNode = std::make_shared<TargetNearestEnemyNode>(blackboard);
    auto moveToEnemyNode = std::make_shared<MoveToEnemyNode>(blackboard);
    auto attackEnemyNode = std::make_shared<AttackEnemyNode>(blackboard);
    attackEnemySequence->addChild(targetNearestEnemyNode);
    attackEnemySequence->addChild(moveToEnemyNode);
    attackEnemySequence->addChild(attackEnemyNode);

    // ...

    // create a selector
    auto selector = std::make_shared<bt::Selector>();
    selector->addChild(attackEnemySequence);
    selector->addChild(idleSequence);

    // set the root of the tree
    tree.setRoot(selector);

    // inside game loop
    tree.update();

    return 0;
}
```

License
-------
MIT (c) arvidsson
