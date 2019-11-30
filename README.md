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

## SJF Scheduler:
To implement the short term scheduler I have used the shortest jobs first algorithm. This algorithm identifies the shortest job by runtime value, and executes/consumes it and reduces the run time by 2 each time. The SJF locks the mutex whenever it attempts to access the Ready Queue to be able to set remvoe and add the job which is being consumed. The idea is that the ready queue should not be accessible by both operations, them being SJF and FCFS. As such mutex lock prevents FCFS thread to access shared memory while SJF is consuming it.

## Final example:
I have put many options from setting the random time to setting the wait before execution of schedulers. Here is a very quick peek of an instance of code where I have executed the scheduler algorithm:

``console
$ ./run -j 5
Jobs to be set 5
Creating 5 jobs and 5 is Ready size

Validating
.....
All Good! 

[LTS] Job Queue: Empty!
......................
[LTS] Ready Queue: Empty!
......................
[LTS] Job Queue: Empty!
......................
[LTS] Ready Queue: Empty!
......................
[LTS] Job Queue: [Process id: 04, Execution Time: 10, Arrival Time: 02]	
......................
[LTS] Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 04, Execution Time: 10, Arrival Time: 02]	
----------------
[STS]: Consuming Process ID: 04	Runtime: 10
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 04	Runtime: 08	Arrival: 02
[STS]: Ready Queue: [Process id: 04, Execution Time: 08, Arrival Time: 02]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 04, Execution Time: 08, Arrival Time: 02]	
----------------
[STS]: Consuming Process ID: 04	Runtime: 08
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 04	Runtime: 06	Arrival: 02
[STS]: Ready Queue: [Process id: 04, Execution Time: 06, Arrival Time: 02]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 04, Execution Time: 06, Arrival Time: 02]	
----------------
[STS]: Consuming Process ID: 04	Runtime: 06
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 04	Runtime: 04	Arrival: 02
[STS]: Ready Queue: [Process id: 04, Execution Time: 04, Arrival Time: 02]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 04, Execution Time: 04, Arrival Time: 02]	
----------------
[STS]: Consuming Process ID: 04	Runtime: 04
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 04	Runtime: 02	Arrival: 02
[STS]: Ready Queue: [Process id: 04, Execution Time: 02, Arrival Time: 02]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 04, Execution Time: 02, Arrival Time: 02]	
----------------
[STS]: Consuming Process ID: 04	Runtime: 02
[STS]: Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: Empty!
----------------
[LTS] Job Queue: [Process id: 03, Execution Time: 17, Arrival Time: 13]	
----------------
[LTS] Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 03, Execution Time: 17, Arrival Time: 13]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 17
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 03	Runtime: 15	Arrival: 13
[STS]: Ready Queue: [Process id: 03, Execution Time: 15, Arrival Time: 13]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 03, Execution Time: 15, Arrival Time: 13]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 15
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 03	Runtime: 13	Arrival: 13
[STS]: Ready Queue: [Process id: 03, Execution Time: 13, Arrival Time: 13]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 03, Execution Time: 13, Arrival Time: 13]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 13
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 03	Runtime: 11	Arrival: 13
[STS]: Ready Queue: [Process id: 03, Execution Time: 11, Arrival Time: 13]	
----------------
[LTS] Job Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	
----------------
[LTS] Ready Queue: [Process id: 03, Execution Time: 11, Arrival Time: 13]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 11
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 03	Runtime: 09	Arrival: 13
[STS]: Ready Queue: [Process id: 03, Execution Time: 09, Arrival Time: 13]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 09
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 03	Runtime: 07	Arrival: 13
[STS]: Ready Queue: [Process id: 03, Execution Time: 07, Arrival Time: 13]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 03, Execution Time: 07, Arrival Time: 13]	[LTS] Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 07
[STS]: Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	
----------------
[STS]: Added Process ID: 03	Runtime: 05	Arrival: 13
[STS]: Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	[STS]: Ready Queue: [Process id: 03, Execution Time: 05, Arrival Time: 13]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	[LTS] Ready Queue: [Process id: 03, Execution Time: 05, Arrival Time: 13]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	[LTS] Ready Queue: [Process id: 03, Execution Time: 05, Arrival Time: 13]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 05
[STS]: Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	
----------------
[STS]: Added Process ID: 03	Runtime: 03	Arrival: 13
[STS]: Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	[STS]: Ready Queue: [Process id: 03, Execution Time: 03, Arrival Time: 13]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 03
[STS]: Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	
----------------
[STS]: Added Process ID: 03	Runtime: 01	Arrival: 13
[STS]: Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	[STS]: Ready Queue: [Process id: 03, Execution Time: 01, Arrival Time: 13]	
----------------
[STS]: Consuming Process ID: 03	Runtime: 01
[STS]: Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 14, Arrival Time: 17]	
----------------
[STS]: Consuming Process ID: 00	Runtime: 14
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 00	Runtime: 12	Arrival: 17
[STS]: Ready Queue: [Process id: 00, Execution Time: 12, Arrival Time: 17]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 12, Arrival Time: 17]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 12, Arrival Time: 17]	
----------------
[STS]: Consuming Process ID: 00	Runtime: 12
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 00	Runtime: 10	Arrival: 17
[STS]: Ready Queue: [Process id: 00, Execution Time: 10, Arrival Time: 17]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 10, Arrival Time: 17]	
----------------
[STS]: Consuming Process ID: 00	Runtime: 10
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 00	Runtime: 08	Arrival: 17
[STS]: Ready Queue: [Process id: 00, Execution Time: 08, Arrival Time: 17]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 08, Arrival Time: 17]	
----------------
[STS]: Consuming Process ID: 00	Runtime: 08
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 00	Runtime: 06	Arrival: 17
[STS]: Ready Queue: [Process id: 00, Execution Time: 06, Arrival Time: 17]	
----------------
[LTS] Job Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Job Queue: [Process id: 02, Execution Time: 24, Arrival Time: 26]	
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 06, Arrival Time: 17]	
----------------
[STS]: Consuming Process ID: 00	Runtime: 06
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 00	Runtime: 04	Arrival: 17
[STS]: Ready Queue: [Process id: 00, Execution Time: 04, Arrival Time: 17]	
----------------
[LTS] Job Queue: [Process id: 02, Execution Time: 24, Arrival Time: 26]	
----------------
[LTS] Ready Queue: [Process id: 00, Execution Time: 04, Arrival Time: 17]	[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 00	Runtime: 04
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 00	Runtime: 02	Arrival: 17
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 00, Execution Time: 02, Arrival Time: 17]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 00, Execution Time: 02, Arrival Time: 17]	
[LTS] Ready Queue: [Process id: 02, Execution Time: 24, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 00	Runtime: 02
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 24, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 24, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 24
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 22	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 22, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 22, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 22
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 20	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 20, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 20
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 18	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 18, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 18, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 18
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 16	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 16, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 16, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 16
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 14	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 14, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 14, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 14
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 12	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 12, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 12, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 12
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 10	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 10, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 10, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 10
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 08	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 08, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 08, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 08
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 06	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 06, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 06, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 06
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 04	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 04, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 04, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 04
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Added Process ID: 02	Runtime: 02	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[STS]: Ready Queue: [Process id: 02, Execution Time: 02, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	[LTS] Ready Queue: [Process id: 02, Execution Time: 02, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 02	Runtime: 02
[STS]: Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 28, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 28
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 26	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 26, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 26, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 26
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 24	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 24, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 24, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 24
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 22	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 22, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 22, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 22
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 20	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 20, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 20, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 20
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 18	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 18, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 18, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 18
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 16	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 16, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 16, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 16
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 14	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 14, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 14, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 14
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 12	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 12, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 12, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 12
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 10	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 10, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 10, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 10
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 08	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 08, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 08
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 06	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 06, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 06, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 06, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 06
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 04	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 04, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 04, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 04
[STS]: Ready Queue: Empty!
----------------
[STS]: Added Process ID: 01	Runtime: 02	Arrival: 26
[STS]: Ready Queue: [Process id: 01, Execution Time: 02, Arrival Time: 26]	
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: [Process id: 01, Execution Time: 02, Arrival Time: 26]	
----------------
[STS]: Consuming Process ID: 01	Runtime: 02
[STS]: Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: Empty!
----------------
JOB LIST:: Empty!
----------------
READY LIST:: Empty!
----------------
Execution of jobs successfull
``

## Problems
When running on terminal I have some overhead issues, as the printf statesments overlaped and after the _Execution of jobs successfull_, I would still recieve a streame of Job and Ready Queue:

``console
----------------
READY LIST:: Empty!
----------------
Execution of jobs success full
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: Empty!
----------------
[LTS] Job Queue: Empty!
----------------
[LTS] Ready Queue: Empty!
----------------
``

I believe this is a printf stream issue, and will try to find a way around it to fix it.

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
+ (--time | -s) [value in int]: Sets random run time for a process to max of a given time. Defult 30
+ (--arrival | -a) [value in int]: Sets random arrival time for a process to max of a given time. Defult 50
+ (--wait | -w) [value in int]: Wait duration before execution of processes. Defult 10



