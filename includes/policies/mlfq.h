#pragma once

#include "../policy.h"
#include "../../CONFIG.h"
#include "robin.h"
#include <list>

class MLFQ : public Policy
{
private:
    std::vector<std::list<Job>> qs{MLFQ_QUEUES};

public:
    void enqueue_job(Job &job) override;
    bool process_job() override;
    int pending_jobs() override;
};