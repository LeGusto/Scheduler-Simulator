# Custom Scheduler

A CPU scheduler simulator built in C++.

## Policies

| Policy | Description |
|--------|-------------|
| `fifo` | First In First Out — jobs run in arrival order |
| `sjf` | Shortest Job First — non-preemptive, picks shortest burst |
| `stcf` | Shortest Time to Completion First — preemptive SJF |
| `robin` | Round Robin — each job gets a fixed time quantum |

## Build

```bash
make all
```

## Usage

```bash
./bin/main <policy> [workload_file]
```

Defaults to `workloads/example_jobs.in` if no file is given.

```bash
./bin/main stcf
./bin/main robin workloads/my_jobs.in
```

## Input Format

Workload files are plain text. Each line is one job:

```
arrival  burst  [io_at  io_duration] ...
```

- Lines starting with `#` are ignored
- `arrival` — tick at which the job enters the system
- `burst` — total CPU time needed
- `io_at io_duration` — optional pairs: block for I/O after `io_at` time, resume after `io_duration` ticks. Multiple pairs supported.

Example:
```
# arrival  burst  io_at  io_dur  io_at  io_dur
0          10     3      5       4      2
1          5
6          4
```

## Configuration

Edit `CONFIG.h` to change scheduler parameters:

| Parameter | Default | Description |
|-----------|---------|-------------|
| `RR_QUANTUM` | `2` | Time slice for Round Robin |

## Metrics

- **Turnaround time** — finish time − arrival time
- **Response time** — first run time − arrival time
