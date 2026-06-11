#include "../includes/policies/mlfq.h"
#include <iostream>
#include <climits>
#include <algorithm>
#include "../CONFIG.h"
#include <numeric>
#include <cmath>

void MLFQ::enqueue_job(Job &job)
{
    if (job.remaining_quantum == -1) job.remaining_quantum = MLFQ_QUANTUM;
    qs[job.queue_no].push_back(std::move(job));
}

void MLFQ::boost()
{
    for (auto &q : qs)
    {
        for (auto &j : q)
        {
            j.queue_no = 0;
            j.remaining_quantum = MLFQ_QUANTUM;
        }
        if (&q != &qs[0])
            qs[0].splice(qs[0].end(), q);
    }

    std::vector<Job> tmp;
    tmp.reserve(waiting.size());

    while (!waiting.empty())
    {
        tmp.push_back(std::move(waiting.top()));
        waiting.pop();
        tmp.back().remaining_quantum = MLFQ_QUANTUM;
        tmp.back().queue_no = 0;
    }
    while (!tmp.empty())
    {
        waiting.push(tmp.back());
        tmp.pop_back();
    }

    last_boost = time;
}

bool MLFQ::process_job()
{
    if (time - last_boost >= MLFQ_BOOST_INTERVAL)
        boost();

    for (int q_idx = 0; q_idx < qs.size(); q_idx++)
    {

        std::list<Job> &q = qs[q_idx];

        if (q.empty())
            continue;

        Job &j = q.front();

        if (j.remaining_quantum == 0)
        {
            int nx = std::min(j.queue_no + 1, MLFQ_QUEUES - 1);
            j.remaining_quantum = (int)std::pow(MLFQ_QUANTUM, nx);
            j.queue_no = nx;
            printf("[t=%d] job(arr=%d) demoted to q%d\n", time, j.arrival_time, nx);
            qs[nx].push_back(std::move(j));
            q.erase(q.begin());
            q_idx--;
            continue;
        }

        if (j.start_time == -1)
            j.start_time = time;
        int t = std::min(j.remaining_time, std::min(j.remaining_quantum, j.io_at != -1 ? j.io_at : INT_MAX));
        printf("[t=%d] running job(arr=%d, rem=%d) on q%d for %d ticks\n", time, j.arrival_time, j.remaining_time, q_idx, t);
        time += t;
        j.remaining_time -= t;
        j.remaining_quantum -= t;
        if (j.io_at != -1)
            j.io_at -= t;

        if (j.io_at == 0)
        {
            j.io_ready_at = time + j.io_duration;
            j.io_at = -1;
            printf("[t=%d] job(arr=%d) blocked for I/O until t=%d\n", time, j.arrival_time, j.io_ready_at);
            waiting.push(std::move(j));
            q.erase(q.begin());
        }
        else if (j.remaining_time == 0)
        {
            j.end_time = time;
            printf("[t=%d] job(arr=%d) done\n", time, j.arrival_time);
            results.push_back(std::move(j));
            q.erase(q.begin());
        }
        else
        {
            q.splice(q.end(), q, q.begin());
        }

        return true;
    }

    return false;
}

int MLFQ::pending_jobs()
{
    return std::accumulate(qs.begin(), qs.end(), 0, [](int sum, std::list<Job> &l)
                           { return sum + l.size(); });
}