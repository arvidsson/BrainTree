#pragma once

#include "Node.h"
#include <vector>

namespace BrainTree
{

class Composite : public Node
{
public:
    Composite() : it(children.begin()) {}
    virtual ~Composite() {}
    
    void addChild(Node::Ptr child) { children.push_back(child); }
    bool hasChildren() const { return !children.empty(); }
    
protected:
    std::vector<Node::Ptr> children;
    std::vector<Node::Ptr>::iterator it;
};

}