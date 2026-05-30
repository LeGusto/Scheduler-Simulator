#include "../includes/policies/sjf.h"
#include <iostream>

void SJF::enqueue_job(Job job)
{
    this->q.push(std::move(job));
}

bool SJF::process_job()
{
    if (!q.empty())
    {
        Job j = std::move(q.top());
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

int SJF::pending_jobs()
{
    return q.size();
}