#pragma once

#include "../Decorator.h"
#include "CompositeBuilder.h"

namespace BrainTree
{

template <class Parent>
class DecoratorBuilder
{
public:
    DecoratorBuilder(Parent* parent, Decorator* node) : parent(parent), node(node) {}

    template <class NodeType, typename... Args>
    DecoratorBuilder<Parent> leaf(Args... args)
    {
        auto child = std::make_shared<NodeType>((args)...);
        node->setChild(child);
        return *this;
    }

    template <class CompositeType, typename... Args>
    CompositeBuilder<DecoratorBuilder<Parent>> composite(Args... args)
    {
        auto child = std::make_shared<CompositeType>((args)...);
        node->setChild(child);
        return CompositeBuilder<DecoratorBuilder<Parent>>(this, (CompositeType*)child.get());
    }

    template <class DecoratorType, typename... Args>
    DecoratorBuilder<DecoratorBuilder<Parent>> decorator(Args... args)
    {
        auto child = std::make_shared<DecoratorType>((args)...);
        node->setChild(child);
        return DecoratorBuilder<DecoratorBuilder<Parent>>(this, (DecoratorType*)child.get());
    }

    Parent& end()
    {
        return *parent;
    }

private:
    Parent* parent;
    Decorator* node;
};

}