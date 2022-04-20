#include <stdio.h>
#include <stdlib.h>

void main()
{

    int nob, blocks[100];

    printf("Enter the number of blocks: ");
    scanf("%d", &nob);

    for (int i = 0; i < nob; i++)
    {

        blocks[i] = 0;
    }

    int flag = 0;
    do
    {
        int b;
        printf("Enter the starting block of file: ");
        scanf("%d", &b);

        int len;
        printf("Enter the length of file: ");
        scanf("%d", &len);

        if ((b + len - 1) > (nob - 1))
        {

            printf("No space for allocation\n");
        }
        else
        {

            int flag = 0;

            for (int i = b; i < (b + len); i++)
            {

                if (blocks[i] == 1)
                {

                    flag = 1;
                    break;
                }
            }

            if (flag != 1)
            {

                printf("The blocks allocated to file are:\n");

                for (int i = b; i < (b + len); i++)
                {

                    blocks[i] = 1;
                    printf("%d ", i);
                }
                printf("\n\n");
            }
            else
            {

                printf("No space for allocation\n");
            }
        }

        printf("1-Continue\n0-Exit:\n");
        scanf("%d", &flag);
    } while (flag != 0);
}