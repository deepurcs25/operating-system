#include <stdio.h>

#define MAX 20

struct Process {
    int pid, at, bt, rt;
    int ct, tat, wt;
    int qno;
};

int main() {

    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter AT BT QueueNo(1-RR,2-FCFS):\n");

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].qno);
        p[i].rt = p[i].bt;
    }

    int time = 0, completed = 0;
    int tq = 2;

    while (completed < n) {

        int executed = 0;

        for (int i = 0; i < n; i++) {

            if (p[i].qno == 1 &&
                p[i].rt > 0 &&
                p[i].at <= time) {

                executed = 1;

                int run = (p[i].rt > tq) ? tq : p[i].rt;

                time += run;
                p[i].rt -= run;

                if (p[i].rt == 0) {
                    p[i].ct = time;
                    completed++;
                }
            }
        }

        if (executed) continue;

        int idx = -1;
        int earliest = 99999;

        for (int i = 0; i < n; i++) {
            if (p[i].qno == 2 &&
                p[i].rt > 0 &&
                p[i].at <= time) {

                if (p[i].at < earliest) {
                    earliest = p[i].at;
                    idx = i;
                }
            }
        }

        if (idx != -1) {

            executed = 1;

            while (p[idx].rt > 0) {
                int q1_ready = 0;

                for (int j = 0; j < n; j++) {
                    if (p[j].qno == 1 &&
                        p[j].rt > 0 &&
                        p[j].at <= time) {
                        q1_ready = 1;
                        break;
                    }
                }

                if (q1_ready)
                    break;

                time++;
                p[idx].rt--;
            }

            if (p[idx].rt == 0) {
                p[idx].ct = time;
                completed++;
            }
        }

        if (!executed)
            time++;
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nAvg WT = %.2f", avg_wt / n);
    printf("\nAvg TAT = %.2f\n", avg_tat / n);

    return 0;
}
