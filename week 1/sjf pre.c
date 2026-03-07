#include <stdio.h>

int main() {
    int n, at[20], bt[20], rt[20], ct[20], tat[20], wt[20];
    int i, time = 0, completed = 0, shortest, min_rt;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter Burst Time:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  
    }

    while(completed < n) {
        shortest = -1;
        min_rt = 9999;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
        } 
        else {
            rt[shortest]--;   
            time++;

            if(rt[shortest] == 0) {
                completed++;

                ct[shortest] = time;
                tat[shortest] = ct[shortest] - at[shortest];
                wt[shortest] = tat[shortest] - bt[shortest];

                if(wt[shortest] < 0)
                    wt[shortest] = 0;

                avg_tat += tat[shortest];
                avg_wt += wt[shortest];
            }
        }
    }

    printf("\nAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);
    printf("Average Waiting Time = %.2f\n", avg_wt/n);

    return 0;
}