#pragma once

#include "../policy.h"
#include "../../CONFIG.h"
#include <list>

class ROBIN : public Policy
{
private:
    std::list<Job> q;
    static constexpr int QUANTUM = RR_QUANTUM;
    std::list<Job>::iterator last_job = q.end();

public:
    void enqueue_job(Job &job) override;
    bool process_job() override;
    int pending_jobs() override;
};