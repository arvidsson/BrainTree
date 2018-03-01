#pragma once

#include "../Decorator.h"

namespace BrainTree {

// The Failer decorator returns failure, regardless of what happens to the child.
class Failer : public Decorator
{
public:
    Status update() override
    {
        child->tick();
        return Status::Failure;
    }
};

} // BrainTree