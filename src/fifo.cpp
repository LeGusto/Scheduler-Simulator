#include "includes/policies/fifo.h"

bool FIFO::enqueue_job(Job job)
{
    job.arrival_time = time;
    this->q.push(job);
}

bool FIFO::process_job()
{
    if (!q.empty())
    {
        Job j = std::move(q.front());
        q.pop();

        j.start_time = time;
        time += j.burst_time;
        j.end_time = time;
        results.push_back(std::move(j));
        return true;
    }
    else
        return false;
}