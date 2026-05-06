#include <stdio.h>

int main() {
    int n = 5; // number of processes
    int at[5], bt[5], pr[5];
    int ct[5], tat[5], wt[5];
    int completed[5] = {0};

    int time = 0, done = 0;

    printf("Enter Arrival Time:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter Burst Time:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    printf("Enter Priority (lower value = higher priority):\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &pr[i]);
    }

    while(done < n) {
        int idx = -1;
        int highest = 9999;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0) {
                if(pr[i] < highest) {
                    highest = pr[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            time += bt[idx];
            ct[idx] = time;
            completed[idx] = 1;
            done++;
        } else {
            time++; // CPU idle
        }
    }

    // Calculate TAT and WT
    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Display results
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    // Average
    float avg_tat = 0, avg_wt = 0;
    for(int i = 0; i < n; i++) {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt/n);

    return 0;
}
