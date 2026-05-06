#include <stdio.h>

struct process {
    int pid;
    int at, bt, rt;
    int ct, tat, wt;
};

int main() {
    int n, tq;
    struct process p[10];
    int time = 0, remain, i;

    float total_tat = 0, total_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    // Input
    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Round Robin Scheduling
    while(remain != 0) {
        int done = 1;

        for(i = 0; i < n; i++) {

            if(p[i].rt > 0 && p[i].at <= time) {
                done = 0;

                if(p[i].rt > tq) {
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    remain--;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    total_tat += p[i].tat;
                    total_wt += p[i].wt;
                }
            }
        }

        // If no process is ready, increment time
        if(done)
            time++;
    }

    // Output
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);

    return 0;
}
