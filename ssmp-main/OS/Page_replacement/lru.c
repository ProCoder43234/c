#include <stdio.h>

int main()
{
    int pages;
    printf("\nEnter the number of Pages: ");
    scanf("%d", &pages);
    int referenceString[pages];
    printf("Enter the reference string values: ");
    for (int i = 0; i < pages; i++)
    {
        scanf("%d", &referenceString[i]);
    }
    int frames;
    printf("Enter the total number of frames: ");
    scanf("%d", &frames);
    int frame_set[frames];
    for (int i = 0; i < frames; i++)
    {
        frame_set[i] = -1;
    }
    int page_faults = 0;
    printf("\n LRU Page Replacement Algorithm \n");
    printf("   Reference string \t Page Frames\n");
    printf("\n");
    for (int i = 0; i < pages; i++)
    {
        int flag = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame_set[j] == referenceString[i])
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            if (page_faults <= frames - 1)
                frame_set[page_faults] = referenceString[i];
            else
            {
                int min_index = pages;
                int lru_frame_index = -1;
                for (int j = 0; j < frames; j++)
                {
                    for (int k = i - 1; k >= 0; k--)
                    {
                        if (referenceString[k] == frame_set[j])
                        {
                            if (min_index > k)
                            {
                                min_index = k;
                                lru_frame_index = j;
                            }
                            break;
                        }
                    }
                }
                frame_set[lru_frame_index] = referenceString[i];
            }
            page_faults++;
        }
        printf("\t%d\t\t", referenceString[i]);
        for (int j = 0; j < frames; j++)
            printf("%d\t", frame_set[j]);
        printf("\n");
    }

    printf("\nTotal Page Faults: %d \n", page_faults);
    return 0;
}