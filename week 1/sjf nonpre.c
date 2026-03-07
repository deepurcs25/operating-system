#include<stdio.h>

int main() {
    int n, bt[20], at[20], ct[20], tat[20], wt[20], completed[20];
    float sumwt=0, sumtat=0, avgwt, avgtat;

    printf("Number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival times:\n");
    for(int i=0; i<n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter burst times:\n");
    for(int i=0; i<n; i++) {
        scanf("%d", &bt[i]);
        completed[i] = 0;
    }

    int time = 0, done = 0;
    while(done < n) {
        int idx = -1;
        int min_bt = 9999;


        for(int i=0; i<n; i++) {
            if(at[i] <= time && completed[i] == 0) {
                if(bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if(idx == -1) {

            time++;
        } else {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            sumwt += wt[idx];
            sumtat += tat[idx];
            completed[idx] = 1;
            done++;
        }
    }

    avgwt = sumwt / n;
    avgtat = sumtat / n;

    printf("\nAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f\n", avgtat);
    printf("Average Waiting Time = %.2f\n", avgwt);

    return 0;
}
