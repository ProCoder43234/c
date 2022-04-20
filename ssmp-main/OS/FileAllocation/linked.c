#include <stdio.h>
#include <stdlib.h>

typedef struct block
{

    int block_no;
    struct block *next;
} block;

typedef struct
{

    int start_block;
    int length;
    block *list;
} file;

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

        file *ptr = (file *)malloc(sizeof(block));
        printf("Enter the starting block: ");
        scanf("%d", &(ptr->start_block));

        printf("Enter the length of file: ");
        scanf("%d", &(ptr->length));

        if (blocks[ptr->start_block] == 1)
        {

            printf("Starting block is already allocated\n");
        }
        else
        {

            block *b = (block *)malloc(sizeof(block));
            b->block_no = ptr->start_block;
            b->next = NULL;
            ptr->list = b;
            blocks[ptr->start_block] = 1;
            int count = 1, i;

            for (i = 0; (i < nob) && (count < (ptr->length)); i++)
            {

                if (blocks[i] == 0)
                {

                    block *new = (block *)malloc(sizeof(block));
                    new->next = NULL;
                    new->block_no = i;
                    block *p = ptr->list;
                    while (p->next != NULL)
                    {

                        p = p->next;
                    }
                    p->next = new;
                    blocks[i] = 1;
                    count++;
                }
            }

            if ((i == nob) && (count < (ptr->length)))
            {

                printf("No space for allocation\n");

                block *p = ptr->list;
                while (p != NULL)
                {

                    blocks[p->block_no] = 0;
                    p = p->next;
                }
            }
            else
            {

                printf("The blocks allocated to file are: ");
                block *p = ptr->list;

                while (p->next != NULL)
                {

                    printf("%d -> ", p->block_no);
                    p = p->next;
                }
                printf("%d", p->block_no);
                printf("\n");
            }
        }

        printf("1-Continue\n0-Exit:\n");
        scanf("%d", &flag);
    } while (flag != 0);
}
