# CPU-Scheduling-Simulation

This project implements a simulation of three CPU scheduling algorithms in the C programming language. For each algorithm, users can input custom data—such as the number of processes, their arrival times, and burst times—and the program calculates the waiting time, response time, and turnaround time for every process, along with the overall averages of these metrics.

The three algorithms mentioned are FCFS (First-Come, First-Served), SJF (Shortest Job First), and Round Robin, each explained below.
1. FCFS (First-Come, First-Served)

A non-preemptive scheduling algorithm where processes are executed in the order they arrive. The first process to enter the ready queue gets the CPU first.

2. SJF (Shortest Job First)

A scheduling algorithm that prioritizes the process with the shortest burst time. It can be either preemptive (Shortest Remaining Time First - SRTF) or non-preemptive.(in this project it is non-preemptive)

3. Round Robin
   
A preemptive scheduling algorithm where each process gets a fixed time slice (quantum) for execution. If a process doesn't complete within its time slice, it's moved to the end of the queue.

The three times mentioned are waiting time, response time, and turnaround time, each explained below.

1. Turnaround Time

The total time taken from when a process arrives in the ready queue until it completes execution.

2. Response Time

The time taken from when a process arrives until it gets the CPU for the first time (i.e., when it starts producing output).

3. Waiting Time

The total time a process spends waiting in the ready queue (not executing).

Below are some example inputs and their expected outputs, demonstrating the objective of our project.

FCFS :

<img width="583" alt="1" src="https://github.com/user-attachments/assets/8baf0263-0a65-4c14-9715-5506a8a62bf4" />

SJF :

<img width="580" alt="2" src="https://github.com/user-attachments/assets/e72ee68f-cceb-4a54-81c9-326d6b4ca375" />

ROUND ROBIN : 

<img width="575" alt="3" src="https://github.com/user-attachments/assets/66ec1113-a234-46b6-958d-d81a6b469076" />







