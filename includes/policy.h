#pragma once

#include "job.h"
#include <vector>

class Policy
{

public:
    int time = 0;
    virtual void enqueue_job(Job &job) = 0;
    virtual bool process_job() = 0;
    virtual int pending_jobs() = 0;
    std::vector<Job> results;

    double get_turnaround_t();
    double get_response_t();
    void print_stats();
};