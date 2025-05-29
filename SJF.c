#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], arrival[n], burst[n], turnaround[n], waiting[n], response[n];
    int completed[n];

    for(int i = 0; i < n; i++) {
        completed[i] = 0;
    }

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

    int current_time = 0, counter = 0;
    while (counter < n) {
        int idx_shortest = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && arrival[i] <= current_time && burst[i] < min_bt) {
                min_bt = burst[i];
                idx_shortest = i;
            }
        }

        if (idx_shortest == -1) {
            current_time++;
            continue;
        }

        response[idx_shortest] = current_time - arrival[idx_shortest];
        current_time += burst[idx_shortest];
        turnaround[idx_shortest] = current_time - arrival[idx_shortest];
        waiting[idx_shortest] = turnaround[idx_shortest] - burst[idx_shortest];
        completed[idx_shortest] = 1;
        counter++;
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
