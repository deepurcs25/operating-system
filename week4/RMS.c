#include <stdio.h>
#include <math.h>

#define MAX 10

int find_lcm(int a, int b) {
    int max = (a > b) ? a : b;
    while (1) {
        if (max % a == 0 && max % b == 0)
            return max;
        max++;
    }
}

int main() {
    int n;
    printf("Enter the number of processes:");
    scanf("%d", &n);

    int C[MAX], P[MAX];

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &C[i]);

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &P[i]);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (P[i] > P[j]) {
                int temp;

                temp = P[i]; P[i] = P[j]; P[j] = temp;
                temp = C[i]; C[i] = C[j]; C[j] = temp;
            }
        }
    }

    int lcm = P[0];
    for (int i = 1; i < n; i++) {
        lcm = find_lcm(lcm, P[i]);
    }

    printf("LCM=%d\n\n", lcm);

    printf("Rate Monotone Scheduling:\n");
    printf("PID    Burst    Period\n");
    for (int i = 0; i < n; i++) {
        printf("%d      %d        %d\n", i + 1, C[i], P[i]);
    }

    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)C[i] / P[i];
    }

    float bound = n * (pow(2, (float)1 / n) - 1);

    printf("\n%f <= %f => %s\n", U, bound, (U <= bound) ? "true" : "false");

    printf("Scheduling occurs for %d ms\n\n", lcm);

    int remaining[MAX] = {0};
    int current = -1;

    for (int t = 0; t < lcm; t++) {

        for (int i = 0; i < n; i++) {
            if (t % P[i] == 0) {
                remaining[i] = C[i];
            }
        }

        int next = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                next = i;
                break;
            }
        }

        if (next != current) {
            if (next == -1)
                printf("%dms onwards: CPU is idle\n", t);
            else
                printf("%dms onwards: Process %d running\n", t, next + 1);
            current = next;
        }

        if (next != -1) {
            remaining[next]--;
        }
    }

    return 0;
}
