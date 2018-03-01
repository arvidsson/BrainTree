#pragma once

#include "Node.h"
#include <vector>

namespace BrainTree {

class Composite : public Node
{
public:
    virtual ~Composite() {}
    
    void addChild(Node::Ptr child) { children.push_back(child); }
    bool hasChildren() const { return !children.empty(); }
    int getIndex() const { return index; }
    
protected:
    std::vector<Node::Ptr> children;
    int index = 0;
};

} // BrainTree