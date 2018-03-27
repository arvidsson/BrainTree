#pragma once

#include "../BehaviorTree.h"
#include "CompositeBuilder.h"
#include "DecoratorBuilder.h"

namespace BrainTree
{

class TreeBuilder
{
public:
    template <class NodeType, typename... Args>
    TreeBuilder leaf(Args... args)
    {
        root = std::make_shared<NodeType>((args)...);
        return *this;
    }

    template <class CompositeType, typename... Args>
    CompositeBuilder<TreeBuilder> composite(Args... args)
    {
        root = std::make_shared<CompositeType>((args)...);
        return CompositeBuilder<TreeBuilder>(this, (CompositeType*)root.get());
    }

    template <class DecoratorType, typename... Args>
    DecoratorBuilder<TreeBuilder> decorator(Args... args)
    {
        root = std::make_shared<DecoratorType>((args)...);
        return DecoratorBuilder<TreeBuilder>(this, (DecoratorType*)root.get());
    }

    Node::Ptr build()
    {
        auto tree = std::make_shared<BehaviorTree>();
        tree->setRoot(root);
        return tree;
    }

private:
    Node::Ptr root;
};

}