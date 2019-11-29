# Project Info

**Class:** EECS 3311

**Year:** 2019-2020

**Description:** Implementation of CPU scheduler.

**Assignment Full Description:** [Link to PDF](captures/assignment-info.pdf)

# Parts:

## Basics

The following project follows the idea of schedulers within operating system, where handeling processes are key to return result to users in fastest manner. Within this project I use a simple handler algorithm **First come First serve** (FCFS) to handle processes, which are time based, at top level, _Long Term Scheduler_.

When processes arrive they are attached/pushed to the _job queue_ where they will await to be scheduled by FCFS in order to finish execution. FCFS takes the latest arrived process and pushes it for CPU consumption/execution. The handling of which is to be executed, put to a pause, and then served again is handled by another scheduler as a _Short Term Scheduler_. I am using the shortest scheduler first on the basis of starvation. If an element reaches starvation level it will be prioritized first.

There are two threads running side by side, first is for _Long Term Scheduler_ and the other for _Short Term Scheduler_. They both are handling **mutext_lock** inorder to synchronize their operation for the access over to the *Ready Queue*.

I have taken the time to give some options while executing the program with different queue sizes and job lengths. Feel free to share for educational pourposes. {With credits :-P}

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



