#pragma once

#include "../Composite.h"
#include <cassert>

namespace BrainTree
{

// The StatefulSelector composite ticks each child node in order, and remembers what child it prevously tried to tick.
// If a child succeeds or runs, the stateful selector returns the same status.
// In the next tick, it will try to run the next child or start from the beginning again.
// If all children fails, only then does the stateful selector fail.
class StatefulSelector : public Composite
{
public:
    Status update() override
    {
        assert(hasChildren() && "Composite has no children");

        while (it != children.end()) {
            auto status = (*it)->tick();

            if (status != Status::Failure) {
                return status;
            }

            it++;
        }

        it = children.begin();
        return Status::Failure;
    }
};

}