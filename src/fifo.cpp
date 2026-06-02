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

        if (j.start_time == -1)
            j.start_time = time;

        if (j.io_at != -1 && j.io_at < j.remaining_time)
        {
            printf("[t=%d] running job(arr=%d, rem=%d) for %d ticks\n", time, j.arrival_time, j.remaining_time, j.io_at);
            time += j.io_at;
            j.remaining_time -= j.io_at;
            j.io_ready_at = time + j.io_duration;
            j.io_at = -1;
            printf("[t=%d] job(arr=%d) blocked for I/O until t=%d\n", time, j.arrival_time, j.io_ready_at);
            waiting.push(std::move(j));
        }
        else
        {
            printf("[t=%d] running job(arr=%d, rem=%d) for %d ticks\n", time, j.arrival_time, j.remaining_time, j.remaining_time);
            time += j.remaining_time;
            j.end_time = time;
            printf("[t=%d] job(arr=%d) done\n", time, j.arrival_time);
            results.push_back(std::move(j));
        }
        return true;
    }
    else
        return false;
}

int FIFO::pending_jobs()
{
    return q.size();
}