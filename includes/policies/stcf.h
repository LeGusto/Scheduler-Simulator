#pragma once

#include "../policy.h"
#include <queue>

class STCF : public Policy
{
private:
    Job curr_job = Job(-1, -1);

    struct cmp
    {
        bool operator()(Job &a, Job &b)
        {
            return a.remaining_time > b.remaining_time;
        }
    };

    std::priority_queue<Job, std::vector<Job>, cmp>
        q;

public:
    void enqueue_job(Job &job) override;
    bool process_job() override;
    int pending_jobs() override;
};