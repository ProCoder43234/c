#include <stdio.h>

void main()
{
    int memorySize, pageSize, pageCount, processCount, processPageRequirement[100], pageTable[100][100];

    printf("Enter the memory size: ");
    scanf("%d", &memorySize);
    printf("Enter the page size: ");
    scanf("%d", &pageSize);

    pageCount = memorySize / pageSize;
    printf("No:of pages = %d\n", pageCount);

    printf("\nEnter the number of processes: ");
    scanf("%d", &processCount);

    int temp = pageCount;
    for (int i = 0; i < processCount; i++)
    {
        printf("\nProcess %d:", i + 1);
        printf("\nEnter the no:of pages required: ");
        scanf("%d", &processPageRequirement[i]);

        if (processPageRequirement[i] > temp)
        {
            printf("Memory Full\n");
            break;
        }

        temp -= processPageRequirement[i];
        printf("Associated page table: ");
        for (int j = 0; j < processPageRequirement[i]; j++)
            scanf("%d", &pageTable[i][j]);
    }

    int pageNumber, pageOffset, n;
    char choice;

    printf("\nCalculate physical address:\n");
    do
    {
        printf("\nEnter the process number:");
        scanf("%d", &n);
        printf("Enter the logical address using page number and page offset: ");
        scanf("%d%d", &pageNumber, &pageOffset);

        if (n > processCount)
            printf("Invalid process\n");
        else if (pageNumber > processPageRequirement[n])
            printf("Invalid page number\n");
        else if (pageOffset > pageSize)
            printf("Invalid page offset\n");

        else
        {
            int physicalAddress = (pageTable[n - 1][pageNumber] * pageSize) + pageOffset;
            printf("The physical Address is %d\n", physicalAddress);
        }

        printf("\nTry another address? (y/n) : ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');
}