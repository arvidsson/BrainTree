#pragma once

#include "BehaviorTree.h"
#include <cassert>

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
    Parent * parent;
    Composite* node;
};

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
    Parent * parent;
    Decorator* node;
};

class Builder
{
public:
    template <class NodeType, typename... Args>
    Builder leaf(Args... args)
    {
        root = std::make_shared<NodeType>((args)...);
        return *this;
    }

    template <class CompositeType, typename... Args>
    CompositeBuilder<Builder> composite(Args... args)
    {
        root = std::make_shared<CompositeType>((args)...);
        return CompositeBuilder<Builder>(this, (CompositeType*)root.get());
    }

    template <class DecoratorType, typename... Args>
    DecoratorBuilder<Builder> decorator(Args... args)
    {
        root = std::make_shared<DecoratorType>((args)...);
        return DecoratorBuilder<Builder>(this, (DecoratorType*)root.get());
    }

    Node::Ptr build()
    {
        assert(root != nullptr && "The Behavior Tree is empty!");
        auto tree = std::make_shared<BehaviorTree>();
        tree->setRoot(root);
        return tree;
    }

private:
    Node::Ptr root;
};

}