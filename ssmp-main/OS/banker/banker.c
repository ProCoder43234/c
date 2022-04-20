#include <stdio.h>

int main()
{
    int n;
    printf("Enter the number of Processes : ");
    scanf("%d", &n);
    printf("Enter the number of resources : ");
    int m;
    scanf("%d", &m);
    printf("\n");
    int alloc[n][m];
    int max[n][m];
    int avail[m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("Enter the Max amount of resources of type R%d required by process P%d : ", j, i);
            scanf("%d", &max[i][j]);
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("Enter the Allocated amount of resources of type R%d for process P%d : ", j, i);
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        printf("Enter the available amount of resources of type R%d : ", i);
        scanf("%d", &avail[i]);
    }
    printf("\n");
    int need[n][m];
    int f[n];
    int index = 0;
    int res[n];
    for (int i = 0; i < n; i++)
    {
        f[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    for (int j = 0; j < m; j++)
                    {
                        avail[j] += alloc[i][j];
                    }
                    f[i] = 1;
                    res[index++] = i;
                }
            }
        }
    }
    printf("Following is the SAFE Sequence\n");
    for (int i = 0; i < index - 1; i++)
        printf("P%d -> ", res[i]);
    printf("P%d\n", res[index - 1]);
    return 0;
}