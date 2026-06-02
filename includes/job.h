#pragma once

#include <cstdio>
#include <vector>
#include <utility>

struct Job
{
    int get_turnaround_t();
    int get_response_t();
    void print_job();
    void next_io();

    Job(int _arrival_time, int _duration) : arrival_time(_arrival_time), duration(_duration), remaining_time(_duration) {};
    Job(int _arrival_time, int _duration, std::vector<std::pair<int, int>> _io_events)
        : arrival_time(_arrival_time), duration(_duration), remaining_time(_duration), io_events(std::move(_io_events))
    {
        next_io();
    };

    int start_time = -1;
    int end_time = -1;
    int queue_no = 0;
    int duration = -1;
    int arrival_time = -1;
    int remaining_time = -1;
    int io_at = -1;
    int io_duration = 0;
    int io_ready_at = -1;
    std::vector<std::pair<int, int>> io_events;

    int remaining_quantum = 0;
};