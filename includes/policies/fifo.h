#pragma once

#include "../policy.h"
#include <queue>

class FIFO : public Policy
{
private:
    std::queue<Job> q;

public:
    void enqueue_job(Job job) override;
    bool process_job() override;
    int pending_jobs() override;
};