
#include <stdio.h>

#define MAX 10
#define INF 999

int main()
{
    int n;
    int cost[MAX][MAX];
    int dist[MAX][MAX];
    int nextHop[MAX][MAX];

    int i, j, k;
    int updated;

    // Input number of routers
    printf("Enter number of routers: ");
    scanf("%d", &n);

    // Input cost matrix
    printf("\nEnter the cost matrix:\n");
    printf("Enter 999 if there is no direct connection.\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);

            // distance = direct link cost
            dist[i][j] = cost[i][j];

            // Initially, next hop is the destination itself
            if (i != j && cost[i][j] != INF)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
        }
    }

    // Step 3: Distance Vector Algorithm
    do
    {
        updated = 0;

        // Make a copy of the previous distance vectors
        int oldDist[MAX][MAX];

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                oldDist[i][j] = dist[i][j];
            }
        }

        // Each router updates its routing table
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (i == j)
                    continue;

                // Check all neighbouring routers
                for (k = 0; k < n; k++)
                {
                    // Only consider directly connected neighbours
                    if (cost[i][k] != INF && i != k)
                    {
                        int newDistance =
                            cost[i][k] + oldDist[k][j];

                        if (newDistance < dist[i][j])
                        {
                            dist[i][j] = newDistance;
                            nextHop[i][j] = k;
                            updated = 1;
                        }
                    }
                }
            }
        }

    } while (updated);

    // Step 4: Display final routing tables
    printf("\n\nFINAL ROUTING TABLES\n");

    for (i = 0; i < n; i++)
    {
        printf("\nRouter %c:\n", 'A' + i);

        printf("Destination\tDistance\tNext Hop\n");

        for (j = 0; j < n; j++)
        {
            printf("%c\t\t", 'A' + j);

            if (dist[i][j] == INF)
            {
                printf("INF\t\t-");
            }
            else
            {
                printf("%d\t\t", dist[i][j]);

                if (i == j)
                    printf("-");
                else
                    printf("%c", 'A' + nextHop[i][j]);
            }

            printf("\n");
        }
    }

    return 0;
}
