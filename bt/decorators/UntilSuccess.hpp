#pragma once

#include "../Decorator.hpp"

namespace bt
{

/*
    The UntilSuccess decorator repeats until the child returns success and then returns success.
*/
class UntilSuccess : public Decorator
{
public:
    Status Update() override
    {
        while (1) {
            auto status = child->Tick();

            if (status == Status::Success) {
                return Status::Success;
            }
        }
    }
};

}