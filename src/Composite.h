#pragma once

#include "Node.h"
#include <vector>

namespace BrainTree
{

class Composite : public Node
{
public:
    virtual ~Composite() {}
    
    void add_child(Node* child) { children.push_back(child); }
    bool has_children() const { return !children.empty(); }
    int get_index() const { return index; }
    
protected:
    std::vector<Node*> children;
    int index = 0;
};

}