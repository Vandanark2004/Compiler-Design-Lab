#include <stdio.h>
#define N 20

int n, m, trans[N][N], final[N], mark[N][N];

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter transitions (for each state, give next state for each symbol 0..%d):\n", m - 1);
    for (int i = 0; i < n; i++)
        for (int a = 0; a < m; a++)
            scanf("%d", &trans[i][a]);

    int f, x;
    printf("Enter number of final states: ");
    scanf("%d", &f);
    printf("Enter final states: ");
    while (f--) { scanf("%d", &x); final[x] = 1; }

    // Step 1: Mark final vs non-final pairs
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (final[i] != final[j]) mark[i][j] = 1;

    // Step 2: Distinguish states by transitions
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
                if (!mark[i][j]) {
                    for (int a = 0; a < m; a++) {
                        int p = trans[i][a], q = trans[j][a];
                        if (p != q && mark[p > q ? p : q][p < q ? p : q]) {
                            mark[i][j] = 1;
                            changed = 1;
                            break;
                        }
                    }
                }
    } while (changed);

    // Step 3: Print equivalent states
    printf("\nEquivalent States (to be merged):\n");
    int eq_count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (!mark[i][j]) {
                printf("%d = %d\n", i, j);
                eq_count++;
            }
    if (!eq_count) printf("None (No states can be merged)\n");

    // Step 4: Print minimized DFA transitions
    printf("\nMinimized DFA Transitions:\n");
    printf("State\t");
    for (int a = 0; a < m; a++) printf("on %d\t", a);
    printf("Type\n---------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int merged = -1;
        for (int j = 0; j < i; j++)
            if (!mark[i][j]) { merged = j; break; }
        if (merged == -1) {
            printf("%d\t", i);
            for (int a = 0; a < m; a++) printf("%d\t", trans[i][a]);
            printf("%s\n", final[i] ? "Final" : "Normal");
        }
    }
    return 0;
}

