# Project Info

**Class:** EECS 3311

**Year:** 2019-2020

**Description:** Implementation of CPU scheduler.

**Assignment Full Description:** [Link to PDF](captures/assignment-info.pdf)

# Parts:
## FCFS Scheduler:
Handles the execution of _n_ processes according to their arival time. It executes 5 process at a time. The following gif shows a FCFS implementation in action with 100 processes:

![](captures/FCFS-Implementation.gif)

# Deployment

## Todeploy

To execute (On Linux Only) download the **main.c** file and use the following command within folder when that file is placed:

```console
$ gcc -pthread main.c -o run
$ ./run
```

## Arguments

+ (--help | -h): Opens help
+ (--jobs | -j) [value in int]: Change the number of jobs to be processed. Default 100
+ (--ready | -r) [value in int]: Change the # of processes to execute at a time. Default 5
+ (--test | -t):	Runs with test messages



