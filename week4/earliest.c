#include <stdio.h>

#define MAX 10

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[MAX], deadline[MAX], period[MAX];
    int remaining[MAX], abs_deadline[MAX];

    printf("Enter Burst Time, Initial Deadline, Period:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &burst[i], &deadline[i], &period[i]);
        remaining[i] = burst[i];
        abs_deadline[i] = deadline[i];
    }

    printf("\nPID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\n", i+1, burst[i], deadline[i], period[i]);
    }

    int time = 0, end_time;

    printf("\nEnter total scheduling time: ");
    scanf("%d", &end_time);

    printf("\nScheduling occurs for %d ms\n\n", end_time);

    while (time < end_time) {

        for (int i = 0; i < n; i++) {
            if (time != 0 && time % period[i] == 0) {
                remaining[i] = burst[i];
                abs_deadline[i] = time + deadline[i];
            }
        }

        int selected = -1;
        int min_deadline = 9999;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                if (abs_deadline[i] < min_deadline) {
                    min_deadline = abs_deadline[i];
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            printf("%dms: CPU is idle.\n", time);
        } else {
            printf("%dms: Task %d is running.\n", time, selected + 1);
            remaining[selected]--; // execute
        }

        time++;
    }

    return 0;
}
