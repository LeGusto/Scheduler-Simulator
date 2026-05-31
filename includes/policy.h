#pragma once

#include "job.h"
#include <vector>
#include <queue>

class Policy
{

protected:
    struct cmp_io
    {
        bool operator()(Job &a, Job &b) { return a.io_ready_at > b.io_ready_at; }
    };
    std::priority_queue<Job, std::vector<Job>, cmp_io> waiting;

public:
    int time = 0;
    virtual void enqueue_job(Job &job) = 0;
    virtual bool process_job() = 0;
    virtual int pending_jobs() = 0;
    std::vector<Job> results;

    void enqueue_waiting();
    bool has_waiting() { return !waiting.empty(); }
    void step()
    {
        enqueue_waiting();
        if (pending_jobs())
            process_job();
        else if (has_waiting())
            time++;
    }
    double get_turnaround_t();
    double get_response_t();
    void print_stats();
};