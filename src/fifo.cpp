#include "../includes/policies/fifo.h"
#include <iostream>

void FIFO::enqueue_job(Job &job)
{
    this->q.push(std::move(job));
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
        // std::cout << time << "\n";
        return true;
    }
    else
        return false;
}

int FIFO::pending_jobs()
{
    return q.size();
}