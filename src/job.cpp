#include "../includes/job.h"

int Job::get_turnaround_t()
{
    if (start_time == -1 || arrival_time == -1)
        return -1;
    return end_time - arrival_time;
}

int Job::get_response_t()
{
    if (start_time == -1 || arrival_time == -1)
        return -1;
    return start_time - arrival_time;
}

void Job::print_job()
{
    printf("b (arr=%d, dur=%d): Start = %d, Remaining = %d\n", arrival_time, duration, start_time, remaining_time);
}

void Job::next_io()
{
    if (!io_events.empty())
    {
        io_at = io_events.front().first;
        io_duration = io_events.front().second;
        io_events.erase(io_events.begin());
    }
    else
    {
        io_at = -1;
        io_duration = 0;
    }
}
