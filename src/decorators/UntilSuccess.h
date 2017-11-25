#pragma once

#include "../Decorator.h"

namespace BrainTree
{

// The UntilSuccess decorator repeats until the child returns success and then returns success.
class UntilSuccess : public Decorator
{
public:
    Status update() override
    {
        while (1) {
            auto status = child->tick();

            if (status == Status::Success) {
                return Status::Success;
            }
        }
    }
};

}