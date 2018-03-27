BrainTree
======

A C++ [behavior tree](http://gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php) header-only library.

Features
--------

* behavior tree
* predefined composites
* predefined decorators
* (optional) rudimentary blackboard
* (optional) behavior tree builders

Install
-------

Include ```BrainTree.h``` in your project.

Example
-------

```c++
// this example should print out "Hello, World!", six times
#include <iostream>
#include <BrainTree.h>

class Action : public BrainTree::Node
{
public:
    Action() {}

    Status update() override
    {
        std::cout << "Hello, World!" << std::endl;

        return Node::Status::Success;
    }
};

void CreatingBehaviorTreeManually()
{
    BrainTree::BehaviorTree tree;
    auto sequence = std::make_shared<BrainTree::Sequence>();
    auto actionOne = std::make_shared<Action>();
    auto actionTwo = std::make_shared<Action>();
    auto actionThree = std::make_shared<Action>();
    sequence.addChild(actionOne);
    sequence.addChild(actionTwo);
    sequence.addChild(actionThree);
    tree.setRoot(sequence);
    tree.update();
}

void CreatingBehaviorTreeUsingBuilders()
{
    auto tree = BrainTree::TreeBuilder()
        .composite<BrainTree::Sequence>()
            .leaf<Action>()
            .leaf<Action>()
            .leaf<Action>()
        .end()
        .build();
    tree->update();
}

int main()
{
    CreatingBehaviorTreeManually();

    CreatingBehaviorTreeUsingBuilders();

    return 0;
}
```

License
-------
MIT (c) arvidsson
