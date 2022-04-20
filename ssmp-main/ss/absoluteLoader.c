#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    FILE *fp;
    int i, addr1, l, j, staddr1;
    char name[10], line[100], name1[10], addr[10], rec[10], ch, staddr[10];
    printf("enter program name : ");
    scanf("%s", name);
    fp = fopen("input.txt", "r");
    fscanf(fp, "%s", line);
    i = 2, j = 0;
    while (line[i] != '^')
    {
        name1[j] = line[i];
        i++;
        j++;
    }
    name1[j] = '\0';
    printf("\nThe contents of output file from obj.%s\n\n", name1);
    printf("Memory Address\tContent\n");
    printf("------------------------\n");
    if (strcasecmp(name, name1) == 0)
    {
        do
        {
            fscanf(fp, "%s", line);
            if (line[0] == 'T')
            {
                for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
                    staddr[j] = line[i];
                staddr[j] = '\0';
                staddr1 = (int)strtol(staddr, NULL, 16);
                i = 12;
                while (line[i] != '\0')
                {
                    if (line[i] != '^')
                    {
                        printf("    00%X \t   %c%c\n", staddr1, line[i], line[i + 1]);
                        staddr1++;
                        i = i + 2;
                    }
                    else
                        i++;
                }
            }
            else if (line[0] == 'E')
            {
                fclose(fp);
                break;
            }
        } while (!feof(fp));
    }

    return 0;
}