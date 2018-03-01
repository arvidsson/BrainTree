#pragma once

#include "Node.h"

namespace BrainTree {

class Decorator : public Node
{
public:
    virtual ~Decorator() {}

    void setChild(Node::Ptr node) { child = node; }
    bool hasChild() const { return child != nullptr; }
    
protected:
    Node::Ptr child = nullptr;
};

} // BrainTree