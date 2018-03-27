#pragma once

#include "../Composite.h"
#include <cassert>

namespace BrainTree
{

// The StatefulSequence composite ticks each child node in order, and remembers what child it prevously tried to tick.
// If a child fails or runs, the stateful sequence returns the same status.
// In the next tick, it will try to run the next child or start from the beginning again.
// If all children succeeds, only then does the stateful sequence succeed.
class MemSequence : public Composite
{
public:
    Status update() override
    {
        assert(hasChildren() && "Composite has no children");

        while (it != children.end()) {
            auto status = (*it)->tick();

            if (status != Status::Success) {
                return status;
            }

            it++;
        }

        it = children.begin();
        return Status::Success;
    }
};

}