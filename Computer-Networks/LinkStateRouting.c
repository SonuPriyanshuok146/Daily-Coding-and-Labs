
#include <stdio.h>

#define MAX 20
#define INF 99999

int main() {
    int n, cost[MAX][MAX];
    int dist[MAX], visited[MAX] = {0};
    int source, u, min;

    printf("Enter number of routers: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of routers.\n");
        return 1;
    }

    printf("Enter cost matrix (0 for no link):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);

            if (i != j && cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    printf("Enter source router (0 to %d): ", n - 1);
    scanf("%d", &source);

    if (source < 0 || source >= n) {
        printf("Invalid source router.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        dist[i] = cost[source][i];

    dist[source] = 0;
    visited[source] = 1;

    for (int count = 1; count < n; count++) {
        min = INF;
        u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] != INF &&
                dist[u] != INF &&
                dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }

    printf("\nShortest distances from Router %d:\n", source);

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF)
            printf("Router %d: Unreachable\n", i);
        else
            printf("Router %d: %d\n", i, dist[i]);
    }

    return 0;
}
