#include "../includes/policies/stcf.h"
#include <iostream>

void STCF::enqueue_job(Job &job)
{
    q.push(std::move(job));
    if (curr_job.arrival_time != -1)
    {
        q.push(curr_job);
        curr_job.arrival_time = -1;
    }
}

bool STCF::process_job()
{
    if (!q.empty() || curr_job.arrival_time != -1)
    {
        if (curr_job.arrival_time == -1)
        {
            curr_job = q.top();
            q.pop();
            if (curr_job.start_time == -1)
                curr_job.start_time = time;
            printf("[t=%d] running job(arr=%d, rem=%d)\n", time, curr_job.arrival_time, curr_job.remaining_time);
        }
        time++;
        curr_job.remaining_time--;

        if (curr_job.io_at != -1 && --curr_job.io_at == 0)
        {
            curr_job.io_ready_at = time + curr_job.io_duration;
            curr_job.io_at = -1;
            printf("[t=%d] job(arr=%d) blocked for I/O until t=%d\n", time, curr_job.arrival_time, curr_job.io_ready_at);
            waiting.push(std::move(curr_job));
            curr_job.arrival_time = -1;
        }
        else if (curr_job.remaining_time == 0)
        {
            curr_job.end_time = time;
            printf("[t=%d] job(arr=%d) done\n", time, curr_job.arrival_time);
            results.push_back(std::move(curr_job));
            curr_job.arrival_time = -1;
        }
        return true;
    }
    else
        return false;
}

int STCF::pending_jobs()
{
    return q.size() + (curr_job.arrival_time == -1 ? 0 : 1);
}