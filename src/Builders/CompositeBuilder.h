#pragma once

#include "../Composite.h"
#include "DecoratorBuilder.h"

namespace BrainTree
{

template <class Parent>
class DecoratorBuilder;

template <class Parent>
class CompositeBuilder
{
public:
    CompositeBuilder(Parent* parent, Composite* node) : parent(parent), node(node) {}

    template <class NodeType, typename... Args>
    CompositeBuilder<Parent> leaf(Args... args)
    {
        auto child = std::make_shared<NodeType>((args)...);
        node->addChild(child);
        return *this;
    }

    template <class CompositeType, typename... Args>
    CompositeBuilder<CompositeBuilder<Parent>> composite(Args... args)
    {
        auto child = std::make_shared<CompositeType>((args)...);
        node->addChild(child);
        return CompositeBuilder<CompositeBuilder<Parent>>(this, (CompositeType*)child.get());
    }

    template <class DecoratorType, typename... Args>
    DecoratorBuilder<CompositeBuilder<Parent>> decorator(Args... args)
    {
        auto child = std::make_shared<DecoratorType>((args)...);
        node->addChild(child);
        return DecoratorBuilder<CompositeBuilder<Parent>>(this, (DecoratorType*)child.get());
    }

    Parent& end()
    {
        return *parent;
    }

private:
    Parent* parent;
    Composite* node;
};

}