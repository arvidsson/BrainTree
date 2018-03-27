#pragma once

#include "../Decorator.h"

namespace BrainTree {

// The UntilFailure decorator repeats until the child returns fail and then returns success.
class UntilFailure : public Decorator
{
public:
    Status update() override
    {
        while (1) {
            auto status = child->tick();

            if (status == Status::Failure) {
                return Status::Success;
            }
        }
    }
};

} // BrainTree