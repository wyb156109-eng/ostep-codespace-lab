Chapter 8 (MLFQ) Homework

Q1: Ran `./mlfq.py -j 2 -n 2 -m 20 -M 0 -c`. MLFQ successfully demotes jobs that use up their time slices.
Q2: 
  - Fig 8.2: `./mlfq.py -n 3 -q 10 -l 0,200,0 -c` (Long job drops to Q0)
  - Fig 8.3: `./mlfq.py -n 3 -q 10 -l 0,180,0:100,20,0 -c` (Short job preempts)
  - Fig 8.7: `./mlfq.py -n 3 -Q 10,20,40 -l 0,110,0:0,110,0 -c` (Longer quanta at lower priorities)
Q3: To make it behave like Round Robin, just use one queue: `./mlfq.py -n 1 -q 10 -c`.
Q4: `./mlfq.py -n 3 -q 10 -S -l 0,100,0:0,100,9 -c` 
    Using the old rule (-S), the job does I/O right before the 10ms slice ends (at 9ms), retaining its priority and gaming the scheduler to get 99% of CPU.
Q5: `10ms / S >= 0.05` => `S <= 200ms`. We need to boost (-B 200) at least every 200ms to guarantee 5% CPU for the starving long job.
Q6: The `-I` flag moves a job that just finished I/O to the front of the queue instead of the back, reducing response time for I/O bound jobs.