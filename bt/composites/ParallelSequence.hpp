#pragma once

#include "../Composite.hpp"

namespace bt
{

class ParallelSequence : public Composite
{
public:
    ParallelSequence(bool successOnAll = true, bool failOnAll = true) : useSuccessFailPolicy(true), successOnAll(successOnAll), failOnAll(failOnAll) {}
    ParallelSequence(int minSuccess, int minFail) : minSuccess(minSuccess), minFail(minFail) {}

    Status Update() override
    {
        int minimumSuccess = minSuccess;
        int minimumFail = minFail;

        if (useSuccessFailPolicy) {
            if (successOnAll) {
                minimumSuccess = children.size();
            }
            else {
                minimumSuccess = 1;
            }

            if (failOnAll) {
                minimumFail = children.size();
            }
            else {
                minimumFail = 1;
            }
        }

        int totalSuccess = 0;
        int totalFail = 0;

        for (auto &child : children) {
            auto status = child->Tick();
            if (status == Status::Success) {
                totalSuccess++;
            }
            if (status == Status::Failure) {
                totalFail++;
            }
        }

        if (totalSuccess >= minimumSuccess) {
            return Status::Success;
        }
        if (totalFail >= minimumFail) {
            return Status::Failure;
        }

        return Status::Running;
    }
    
    using Ptr = std::shared_ptr<ParallelSequence>;

private:
    bool useSuccessFailPolicy = false;
    bool successOnAll = true;
    bool failOnAll = true;
    int minSuccess = 0;
    int minFail = 0;
};

static ParallelSequence::Ptr MakeParallelSequence()
{
    return std::make_shared<ParallelSequence>();
}

}
