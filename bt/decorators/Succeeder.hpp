#pragma once

#include "../Decorator.hpp"

namespace bt
{

/*
    The Succeeder decorator returns success, regardless of what happens to the child.
*/
class Succeeder : public Decorator
{
public:
    Status Update() override
    {
        child->Tick();
        return Status::Success;
    }
};

}