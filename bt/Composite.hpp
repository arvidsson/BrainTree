#pragma once

#include "Node.hpp"

namespace bt
{

class Composite : public Node
{
public:
    virtual ~Composite() {}
    
    void AddChild(Node::Ptr child) { children.push_back(child); }
    bool HasNoChildren() const { return children.empty(); }
    int GetIndex() const { return index; }
    
protected:
    Nodes children;
    int index = 0;
};

}