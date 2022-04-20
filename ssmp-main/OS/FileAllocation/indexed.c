#include <stdio.h>

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

        int index;
        printf("Enter the index block number: ");
        scanf("%d", &index);

        if (blocks[index] == 1)
        {

            printf("Index block is already allocated\n");
            ;
        }
        else
        {

            blocks[index] = 1;
            int length;
            printf("Enter the length of file: ");
            scanf("%d", &length);

            int index_block[100];
            int count = 0;

            for (int i = 0; (i < nob) && (count < length); i++)
            {

                if (blocks[i] == 0)
                {

                    blocks[i] = 1;
                    index_block[count] = i;
                    count++;
                }
            }

            if (count < length)
            {

                printf("No space for allocation\n");

                for (int i = 0; i < count; i++)
                {

                    blocks[index_block[i]] = 0;
                }
                blocks[index] = 0;
            }
            else
            {

                for (int i = 0; i < count; i++)
                {

                    printf("%d -> %d\n", index, index_block[i]);
                }
            }
        }

        printf("1-Continue\n0-Exit:\n");
        scanf("%d", &flag);
    } while (flag != 0);
}