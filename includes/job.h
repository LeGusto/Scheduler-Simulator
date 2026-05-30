#pragma once

struct Job
{
    int get_turnaround_t()
    {
        if (start_time == -1 || arrival_time == -1)
            return -1;

        return end_time - arrival_time;
    }

    int get_response_t()
    {
        if (start_time == -1 || arrival_time == -1)
            return -1;
        return start_time - arrival_time;
    }

    Job(int _arrival_time, int _burst_time) : arrival_time(_arrival_time), burst_time(_burst_time) {};

    int start_time = -1;
    int end_time = -1;
    int queue_no = -1;
    int burst_time = -1;
    int arrival_time = -1;
};