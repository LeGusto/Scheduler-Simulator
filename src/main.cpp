#include "../includes/policies/fifo.h"
#include "../includes/policies/sjf.h"

#include <cstdio>
#include <iostream>
#include <string.h>

std::vector<Job> jobs =
    {
        Job(0, 10),
        Job(1, 5),
        Job(6, 4)};

int main(int argc, char *argv[])
{
    Policy *pol;

    if (argc > 1)
    {
        if (strcmp(argv[1], "sjf") == 0)
            pol = new SJF;

        else if (strcmp(argv[1], "fifo") == 0)
            pol = new FIFO;
        else
        {
            pol = new FIFO;
        }
    }

    for (auto &job : jobs)
    {
        while (pol->pending_jobs() && pol->time < job.arrival_time)
        {
            pol->process_job();
        }
        pol->enqueue_job(job);
    }
    while (pol->pending_jobs())
    {
        pol->process_job();
    }

    pol->print_stats();
}