#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int *items;
    int front;
    int rear;
    int size;
    int capacity;
} ReadyQueue;

void initQueue(ReadyQueue *q, int capacity) {
    q->items = (int *)malloc(capacity * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
}

bool isEmpty(ReadyQueue *q) {
    return q->size == 0;
}

void enqueue(ReadyQueue *q, int item) {
    if (q->size < q->capacity) {
        q->rear = (q->rear + 1) % q->capacity;
        q->items[q->rear] = item;
        q->size++;
    }
}

int dequeue(ReadyQueue *q) {
    if (isEmpty(q)) {
        return -1;
    }
    int item = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int pid[n], arrival[n], burst[n], turnaround[n], waiting[n], response[n];
    int remaining[n], completed[n];
    bool started[n];

    printf("Enter burst time for each process sequentially: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
        started[i] = false;
        completed[i] = 0;
    }

    printf("Enter arrival time for each process sequentially: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arrival[i]);
    }

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
    }

    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arrival[j] > arrival[j+1]) {
                int temp = arrival[j];
                arrival[j] = arrival[j+1];
                arrival[j+1] = temp;

                temp = burst[j];
                burst[j] = burst[j+1];
                burst[j+1] = temp;

                temp = remaining[j];
                remaining[j] = remaining[j+1];
                remaining[j+1] = temp;

                temp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp;
            }
        }
    }

    ReadyQueue ready_queue;
    initQueue(&ready_queue, n * 2);

    int current_time = 0, counter = 0, idx = 0;

    while(idx < n && arrival[idx] <= current_time) {
        enqueue(&ready_queue, idx);
        idx++;
    }

    while(counter != n) {
        if (isEmpty(&ready_queue)) {
            current_time = arrival[idx];
            while(idx < n && arrival[idx] <= current_time) {
                enqueue(&ready_queue, idx);
                idx++;
            }
            continue;
        }

        int current = dequeue(&ready_queue);

        if(!started[current]) {
            started[current] = true;
            response[current] = current_time - arrival[current];
        }

        int exec_time = (quantum < remaining[current]) ? quantum : remaining[current];
        current_time += exec_time;
        remaining[current] -= exec_time;

        while(idx < n && arrival[idx] <= current_time) {
            enqueue(&ready_queue, idx);
            idx++;
        }

        if(remaining[current] > 0) {
            enqueue(&ready_queue, current);
        } else {
            completed[current] = 1;
            counter++;
            turnaround[current] = current_time - arrival[current];
            waiting[current] = turnaround[current] - burst[current];
        }
    }

    float avg_wait = 0, avg_turn = 0, avg_resp = 0;
    for(int i = 0; i < n; i++) {
        avg_wait += waiting[i];
        avg_turn += turnaround[i];
        avg_resp += response[i];
    }
    avg_wait = avg_wait / n;
    avg_turn = avg_turn / n;
    avg_resp = avg_resp / n;

    printf("%-5s %-15s %-12s %-15s %-15s %-15s\n",
           "PID", "Arrival Time", "Burst Time", "Waiting Time", "Turnaround Time", "Response Time");
    for(int i = 0; i < n; i++) {
        printf("%-5d %-15d %-12d %-15d %-15d %-15d\n",
               pid[i],
               arrival[i],
               burst[i],
               waiting[i],
               turnaround[i],
               response[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wait);
    printf("Average Turnaround Time = %.2f\n", avg_turn);
    printf("Average Response Time = %.2f\n", avg_resp);

    free(ready_queue.items);
    return 0;
}
