#pragma once

#include "../Decorator.hpp"

namespace bt
{

/*
    The Inverter decorator inverts the child node's status, i.e. failure becomes success and success becomes failure.
    If the child runs, the Inverter returns the status that it is running too.
*/
class Inverter : public Decorator
{
public:
    Status Update() override
    {
        auto s = child->Tick();

        if (s == Status::Success) {
            return Status::Failure;
        }
        else if (s == Status::Failure) {
            return Status::Success;
        }

        return s;
    }
};

}