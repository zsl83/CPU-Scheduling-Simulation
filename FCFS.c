#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], arrival[n], burst[n], turnaround[n], waiting[n], response[n];

    printf("Enter burst time for each process sequentially: ");

    for(int i = 0; i < n; i++){
        scanf("%d", &burst[i]);
    }

    printf("Enter arrival time for each process sequentially: ");

    for(int i = 0; i < n; i++){
        scanf("%d", &arrival[i]);
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
    }

    int order[n];
    for (int i = 0; i < n; i++){
        order[i] = i;
    }

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arrival[order[j]] > arrival[order[j+1]]) {
                int temp = order[j];
                order[j] = order[j+1];
                order[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        int idx = order[i];
        if (current_time < arrival[idx]) {
            current_time = arrival[idx];
        }
        waiting[idx] = current_time - arrival[idx];
        response[idx] = waiting[idx];
        current_time += burst[idx];
        turnaround[idx] = current_time - arrival[idx];
    }

    float avg_wait = 0, avg_turn = 0, avg_resp = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += waiting[i];
        avg_turn += turnaround[i];
        avg_resp += response[i];
    }
    avg_wait = avg_wait / n;
    avg_turn = avg_turn / n;
    avg_resp = avg_resp / n;

    printf("%-5s %-15s %-12s %-15s %-15s %-15s\n", "PID", "Arrival Time", "Burst Time", "Waiting Time", "Turnaround Time", "Response Time");
    for (int i = 0; i < n; ++i) {
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

    return 0;
}
