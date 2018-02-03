#pragma once

#include "Node.h"

namespace BrainTree
{

class Decorator : public Node
{
public:
    virtual ~Decorator() {}

    void set_child(Node::Ptr node) { child = node; }
    bool has_child() const { return child != nullptr; }
    
protected:
    Node::Ptr child = nullptr;
};

}