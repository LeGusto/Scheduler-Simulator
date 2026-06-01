#include "../includes/policies/mlfq.h"
#include <iostream>
#include <climits>
#include <algorithm>
#include "../CONFIG.h"
#include <numeric>
#include <cmath>

void MLFQ::enqueue_job(Job &job)
{
    qs[0].push_back(std::move(job));
}

bool MLFQ::process_job()
{
    for (int q_idx = 0; q_idx < qs.size(); q_idx++) {
    
    std::list<Job>& q = qs[q_idx];
    
    if (q.empty())
        continue;
    
    Job& j = q.front();

    if (j.remaining_quantum == 0) {
        int nx = std::min(j.queue_no+1, MLFQ_QUEUES-1);
        j.remaining_quantum = (int)std::pow(MLFQ_QUANTUM, nx);
        if (j.queue_no != nx) {
            j.queue_no = nx;
            qs[nx].push_back(std::move(j));
            q.erase(q.begin());
            q_idx--;
            continue;
        }
    }
    

    int t = std::min(MLFQ_QUANTUM, std::min(j.remaining_time, std::min(j.remaining_quantum, j.io_at != -1 ? j.io_at : INT_MAX)));
    time += t;
    j.remaining_time -= t;
    j.remaining_quantum -= t;
    if (j.io_at != -1)
        j.io_at -= t;
    
    if (j.io_at == 0)
    {
        j.io_ready_at = time + j.io_duration;
        j.io_at = -1;
        waiting.push(std::move(j));
        q.erase(q.begin());
    }
    else if (j.remaining_time == 0)
    {
        j.end_time = time;
        results.push_back(std::move(j));

        q.erase(q.begin());
    } else {
        q.splice(q.end(), q, q.begin());
    }

    return true;
    }

    return false;
}

int MLFQ::pending_jobs()
{
    return std::accumulate(qs.begin(), qs.end(), 0, [](int sum, std::list<Job>& l) {return sum + l.size();});
}