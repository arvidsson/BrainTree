#pragma once

namespace BrainTree
{

template <class Parent, class Behavior>
class LeafBuilder
{
public:
    LeafBuilder(Parent* parent, Behavior* behavior) : parent(parent), behavior(behavior) {}

    

private:
    Parent* parent;
    Behavior* behavior;
}

}