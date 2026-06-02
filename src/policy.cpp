#include "includes/policy.h"
#include <numeric>
#include <iostream>

void Policy::enqueue_waiting()
{
    while (!waiting.empty() && waiting.top().io_ready_at <= time)
    {
        Job j = std::move(const_cast<Job &>(waiting.top()));
        waiting.pop();
        j.next_io();
        enqueue_job(j);
    }
}

double Policy::get_response_t()
{
    int n = results.size();
    double tot = std::accumulate(results.begin(), results.end(), 0, [](int sum, Job &j)
                                 { return sum += j.get_response_t(); });
    return tot / n;
}

double Policy::get_turnaround_t()
{
    int n = results.size();
    double tot = std::accumulate(results.begin(), results.end(), 0, [](int sum, Job &j)
                                 { return sum += j.get_turnaround_t(); });

    return tot / n;
}

void Policy::print_stats()
{
    printf("\n=== Results ===\n");
    printf("Turnaround: %f\nResponse: %f\n", get_turnaround_t(), get_response_t());

    for (auto &j : results)
    {
        printf("Job (arr=%d, dur=%d): Start = %d, End = %d\n", j.arrival_time, j.burst_time, j.start_time, j.end_time);
    }
}