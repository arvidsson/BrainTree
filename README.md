bt
======

A C++ [behavior tree](http://gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php) implementation.

the basics
----------

##### 0. include bt

```c++
#include <bt.hpp>
```

##### 1. define leafs

```c++
class WaitNode : public bt::Leaf
{
public:
    // note: using a blackboard is optional
    WaitNode(bt::Blackboard::Ptr board, int limit) : Leaf(board), limit(limit) {}

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
    int limit;
    int counter;
};
```

##### 2. construct the behavior tree

```c++
bt::BehaviorTree tree;

// each tree has one blackboard each, which the leafs can use
auto &blackboard = tree.GetBlackBoard();

// create a sequence
auto attackEnemySequence = std::make_shared<bt::Sequence>();
auto targetNearestEnemyNode = std::make_shared<TargetNearestEnemyNode>(blackboard);
auto moveToEnemyNode = std::make_shared<MoveToEnemyNode>(blackboard);
auto attackEnemyNode = std::make_shared<AttackEnemyNode>(blackboard);
attackEnemySequence->AddChild(targetNearestEnemyNode);
attackEnemySequence->AddChild(moveToEnemyNode);
attackEnemySequence->AddChild(attackEnemyNode);

...

// create a selector
auto selector = std::make_shared<bt::Selector>();
selector->AddChild(attackEnemySequence);
selector->AddChild(idleSequence);

// set the root of the tree
tree.SetRoot(selector);
```

##### 3. update the tree

```c++
// inside game loop
tree.Update();
}
```

##### 4. what else?

* Code is fairly well documented. Read up on what the different composites and decorators do!
* Access a global, singleton blackboard using Blackboard::GetInstance()
