#include "../includes/policies/sjf.h"
#include <iostream>

void SJF::enqueue_job(Job &job)
{
    q.push(std::move(job));
}

bool SJF::process_job()
{
    if (!q.empty())
    {
        Job j = std::move(const_cast<Job &>(q.top()));
        q.pop();

        if (j.start_time == -1)
            j.start_time = time;

        if (j.io_at != -1 && j.io_at < j.remaining_time)
        {
            time += j.io_at;
            j.remaining_time -= j.io_at;
            j.io_ready_at = time + j.io_duration;
            j.io_at = -1;
            waiting.push(std::move(j));
        }
        else
        {
            time += j.remaining_time;
            j.end_time = time;
            results.push_back(std::move(j));
        }
        return true;
    }
    else
        return false;
}

int SJF::pending_jobs()
{
    return q.size();
}