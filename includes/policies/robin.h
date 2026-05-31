#pragma once

#include "../policy.h"
#include <list>

class ROBIN : public Policy
{
private:
    std::list<Job> q;
    const int QUANTUM = 2;
    std::list<Job>::iterator last_job = q.end();

public:
    void enqueue_job(Job &job) override;
    bool process_job() override;
    int pending_jobs() override;
};