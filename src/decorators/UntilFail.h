#pragma once

#include "../Decorator.h"

namespace BrainTree {

// The UntilFail decorator repeats until the child returns fail and then returns success.
class UntilFail : public Decorator
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