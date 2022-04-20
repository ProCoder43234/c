#include <stdio.h>
#include <string.h>

#define SIZE 30

typedef struct file
{
    int id;
    char name[50];
} file;

int searchFile(file *directory, int n, char *filename)
{
    int searchID = -1;

    for (int i = 0; i < n; ++i)
    {
        if (strcmp(directory[i].name, filename) == 0)
        {
            searchID = directory[i].id;
            break;
        }
    }

    return searchID;
}

void main()
{
    file directory[SIZE];

    char filename[50], directoryName[50], searchFilename[50];
    int choice, id = 0, index = 0;

    printf("Enter directory name: ");
    scanf("%s", directoryName);

    do
    {
        printf("\n1.Add files\n2.Search files\n3.Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter the file name: ");
            scanf("%s", filename);

            int sid = searchFile(directory, index, searchFilename);
            if (sid != -1)
                printf("\nFile already exists!");
            else
            {
                directory[index].id = id++;
                strcpy(directory[index].name, filename);
                printf("\nFile %s added\n", directory[index].name);
                index++;
            }
            break;

        case 2:
            printf("\nEnter the file name to search: ");
            scanf("%s", searchFilename);
            int searchID = searchFile(directory, index, searchFilename);

            if (searchID == -1)
                printf("\nFile not found\n");
            else
                printf("\nFile found\nFile ID = %d\nFilepath = %s/%s\n", searchID, directoryName, searchFilename);

            break;
        }
    } while (choice != 3);
}