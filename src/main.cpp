#include "../includes/policies/fifo.h"
#include "../includes/policies/sjf.h"
#include "../includes/policies/stcf.h"
#include "../includes/policies/robin.h"
#include "../includes/policies/mlfq.h"

#include <cstdio>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
    const char *policy_name = (argc > 1) ? argv[1] : "fifo";
    if (argc <= 1)
        std::cerr << "No policy given, defaulting to 'fifo'. "
                     "Usage: " << argv[0] << " <policy> [workload_file]\n";

    Policy *pol;
    if (strcmp(policy_name, "sjf") == 0)
        pol = new SJF;
    else if (strcmp(policy_name, "fifo") == 0)
        pol = new FIFO;
    else if (strcmp(policy_name, "stcf") == 0)
        pol = new STCF;
    else if (strcmp(policy_name, "robin") == 0)
        pol = new ROBIN;
    else if (strcmp(policy_name, "mlfq") == 0)
        pol = new MLFQ;
    else
    {
        std::cerr << "Unknown policy '" << policy_name << "', defaulting to 'fifo'.\n";
        pol = new FIFO;
    }

    const char *dir = "";
    if (argc > 2)
    {
        dir = argv[2];
    }
    else
    {
        dir = "workloads/example_jobs.in";
    }

    std::vector<Job> jobs;
    std::ifstream in(dir);
    std::string line;

    while (std::getline(in, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream ss(line);
        int arrival, duration;
        ss >> arrival >> duration;

        std::vector<std::pair<int, int>> io_events;
        int io_at, io_dur;
        while (ss >> io_at >> io_dur)
            io_events.push_back({io_at, io_dur});

        if (io_events.empty())
            jobs.push_back(Job(arrival, duration));
        else
            jobs.push_back(Job(arrival, duration, std::move(io_events)));
    }

    for (auto &job : jobs)
    {
        while ((pol->pending_jobs() || pol->has_waiting()) && pol->time < job.arrival_time)
            pol->step();
        pol->time = std::max(pol->time, job.arrival_time);
        pol->enqueue_job(job);
    }
    while (pol->pending_jobs() || pol->has_waiting())
        pol->step();

    pol->print_stats();
}