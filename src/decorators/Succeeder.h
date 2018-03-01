#pragma once

#include "../Decorator.h"

namespace BrainTree {

// The Succeeder decorator returns success, regardless of what happens to the child.
class Succeeder : public Decorator
{
public:
    Status update() override
    {
        child->tick();
        return Status::Success;
    }
};

} // BrainTree