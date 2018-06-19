BrainTree
======

A C++ [behavior tree](http://gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php) header-only library.

Features
--------

* behavior tree implementation
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
// this example should print out "Hello, World!", four times
#include <iostream>
#include "BrainTree.h"

class Action : public BrainTree::Node
{
public:
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
    auto sayHello = std::make_shared<Action>();
    auto sayHelloAgain = std::make_shared<Action>();
    sequence.addChild(sayHello);
    sequence.addChild(sayHelloAgain);
    tree.setRoot(sequence);
    tree.update();
}

void CreatingBehaviorTreeUsingBuilders()
{
    auto tree = BrainTree::Builder()
        .composite<BrainTree::Sequence>()
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

Composites
----------

### Selector

* The Selector composite ticks each child node in order.
* If a child succeeds or runs, the selector returns the same status.
* In the next tick, it will try to run each child in order again.
* If all children fails, only then does the selector fail.

### Sequence

* The Sequence composite ticks each child node in order.
* If a child fails or runs, the sequence returns the same status.
* In the next tick, it will try to run each child in order again.
* If all children succeeds, only then does the sequence succeed.

### StatefulSelector

* The StatefulSelector composite ticks each child node in order, and remembers what child it prevously tried to tick.
* If a child succeeds or runs, the stateful selector returns the same status.
* In the next tick, it will try to run the next child or start from the beginning again.
* If all children fails, only then does the stateful selector fail.

### StatefulSequence

* The StatefulSequence composite ticks each child node in order, and remembers what child it prevously tried to tick.
* If a child fails or runs, the stateful sequence returns the same status.
* In the next tick, it will try to run the next child or start from the beginning again.
* If all children succeeds, only then does the stateful sequence succeed.

Builder
-------

The Builder class simplifies the process of creating a behavior tree. You use three methods to build your tree:

* `leaf<NodeType>()`
* `composite<CompositeType>()`
* `decorator<DecoratorType>()`

Both `composite()` and `decorator()` require a corresponding call to `end()`, this marks where you are done adding children to a composite or a child to a decorator. At the very end you call `build()` which will then give you the finished behavior tree.

```
auto tree = Builder()
    .decorator<Repeater>()
        .composite<Sequence>()
            .leaf<SayHello>("Foo")
            .leaf<SayHello>("Bar")
        .end()
    .end()
    .build();
```

License
-------
MIT (c) arvidsson 2015-2018
