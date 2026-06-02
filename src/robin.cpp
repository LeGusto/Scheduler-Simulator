#include "../includes/policies/robin.h"
#include <iostream>
#include <climits>
#include <algorithm>

void ROBIN::enqueue_job(Job &job)
{
    this->q.push_back(std::move(job));
}

bool ROBIN::process_job()
{
    if (q.empty())
        return false;

    if (last_job != q.end())
        last_job++;

    if (last_job == q.end())
        last_job = q.begin();

    if (last_job->start_time == -1)
        last_job->start_time = time;

    int io_limit = last_job->io_at != -1 ? last_job->io_at : INT_MAX;
    int t = std::min(QUANTUM, std::min(last_job->remaining_time, io_limit));
    printf("[t=%d] running job(arr=%d, rem=%d) for %d ticks\n", time, last_job->arrival_time, last_job->remaining_time, t);
    time += t;
    last_job->remaining_time -= t;
    if (last_job->io_at != -1)
        last_job->io_at -= t;

    if (last_job->io_at == 0)
    {
        last_job->io_ready_at = time + last_job->io_duration;
        last_job->io_at = -1;
        printf("[t=%d] job(arr=%d) blocked for I/O until t=%d\n", time, last_job->arrival_time, last_job->io_ready_at);
        waiting.push(std::move(*last_job));
        last_job = q.erase(last_job);
        last_job--;
    }
    else if (last_job->remaining_time == 0)
    {
        last_job->end_time = time;
        printf("[t=%d] job(arr=%d) done\n", time, last_job->arrival_time);
        results.push_back(std::move(*last_job));

        last_job = q.erase(last_job);
        last_job--;
    }

    return true;
}

int ROBIN::pending_jobs()
{
    return q.size();
}