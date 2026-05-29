#pragma once

struct Job
{
    int get_turnaround()
    {
        if (start_time == -1 || arrival_time == -1)
            return -1;

        return end_time - arrival_time;
    }

    int get_response()
    {
        if (start_time == -1 || arrival_time == -1)
            return -1;
        return start_time - arrival_time;
    }

    int start_time = -1;
    int end_time = -1;
    int queue_no = -1;
    int burst_time = -1;
    int arrival_time = -1;
};