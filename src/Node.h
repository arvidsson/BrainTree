#pragma once

namespace BrainTree
{

class Node
{
public:
    enum class Status
    {
        Invalid,
        Success,
        Failure,
        Running,
    };

    virtual ~Node() {}

    virtual Status update() = 0;
    virtual void initialize() {}
    virtual void terminate(Status s) {}

    Status tick()
    {
        if (status != Status::Running) {
            initialize();
        }

        status = update();

        if (status != Status::Running) {
            terminate(status);
        }

        return status;
    }

    bool is_success() const { return status == Status::Success; }
    bool is_failure() const { return status == Status::Failure; }
    bool is_running() const { return status == Status::Running; }
    bool is_terminated() const { return is_success() || is_failure(); }
    void reset() { status = Status::Invalid; }

protected:
    Status status = Status::Invalid;
};

}