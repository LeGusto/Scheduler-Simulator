#pragma once

#include "../policy.h"
#include <queue>

class SJF : public Policy
{
private:
    struct cmp
    {
        bool operator()(Job &a, Job &b)
        {
            return a.duration > b.duration;
        }
    };

    std::priority_queue<Job, std::vector<Job>, cmp>
        q;

public:
    void enqueue_job(Job &job) override;
    bool process_job() override;
    int pending_jobs() override;
};