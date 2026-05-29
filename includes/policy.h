#include "job.h"
#include <vector>

class Policy
{
protected:
    int time = 0;

public:
    virtual bool enqueue_job(Job job) = 0;
    virtual bool process_job() = 0;
    std::vector<Job> results;
};