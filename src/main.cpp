#include "../includes/policies/fifo.h"
#include "../includes/policies/sjf.h"
#include "../includes/policies/stcf.h"
#include "../includes/policies/robin.h"

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
        else if (strcmp(argv[1], "stcf") == 0)
        {
            pol = new STCF;
            std::cout << "hi\n";
        }
        else if (strcmp(argv[1], "robin") == 0)
            pol = new ROBIN;
        else
        {
            pol = new FIFO;
        }
    }

    for (auto &job : jobs)
    {
        while (pol->pending_jobs() && pol->time < job.arrival_time)
        {
            if (!pol->process_job())
                throw std::runtime_error("Processing failed");
        }
        pol->enqueue_job(job);
    }
    while (pol->pending_jobs())
    {
        if (!pol->process_job())
            throw std::runtime_error("Processing failed");
    }

    pol->print_stats();
}