#pragma once

#include "../Decorator.h"

namespace BrainTree {

// The Repeater decorator repeats infinitely or to a limit until the child returns success.
class Repeater : public Decorator
{
public:
    Repeater(int limit = 0) : limit(limit) {}

    void initialize() override
    {
        counter = 0;
    }

    Status update() override
    {
        while (1) {
            auto s = child->tick();

            if (s == Status::Running) {
                return Status::Running;
            }

            if (s == Status::Failure) {
                return Status::Failure;
            }

            if (limit > 0 && ++counter == limit) {
                return Status::Success;
            }

            child->reset();
        }
    }

protected:
    int limit;
    int counter = 0;
};

} // BrainTree