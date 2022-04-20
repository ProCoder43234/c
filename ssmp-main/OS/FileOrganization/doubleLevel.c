#include <stdio.h>
#include <string.h>

#define SIZE 30

typedef struct file
{
    int id;
    char name[50];
} file;

typedef struct folder
{
    int id;
    char name[50];
    int fileIndex;
    file files[SIZE];
} folder;

int searchDirectory(folder *rootdirectory, int n, char *foldername)
{
    int searchID = -1;

    for (int i = 0; i < n; ++i)
    {
        if (strcmp(rootdirectory[i].name, foldername) == 0)
        {
            searchID = rootdirectory[i].id;
            break;
        }
    }

    return searchID;
}

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
    folder rootdirectory[SIZE];
    int rootdirectoryIndex = 0;

    char filename[50], directoryName[50], searchFilename[50];
    int choice, id = 0, index = 0;

    printf("Enter directory name: ");
    scanf("%s", directoryName);

    do
    {
        printf("\n1.Add files\n2.Add folder\n3.Search files\n4.Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter the file name: ");
            scanf("%s", filename);

            char searchDirectoryName[50];
            printf("\nEnter directory name:");
            scanf("%s", searchDirectoryName);

            int searchDirectoryID = searchDirectory(rootdirectory, rootdirectoryIndex, searchDirectoryName);
            if (searchDirectoryID == -1)
                printf("\nDirectory does not exist!");
            else
            {
                int fsid = searchFile(rootdirectory[searchDirectoryID].files, rootdirectory[searchDirectoryID].fileIndex, filename);

                if (fsid != -1)
                    printf("\nFile already exists!");
                else
                {
                    int fileIndex = rootdirectory[searchDirectoryID].fileIndex++;
                    rootdirectory[searchDirectoryID].files[fileIndex].id = fileIndex;
                    strcpy(rootdirectory[searchDirectoryID].files[fileIndex].name, filename);
                    printf("\nFile %s added to directory %s", filename, searchDirectoryName);
                }
            }

            break;

        case 2:
            printf("Enter the folder name: ");
            char foldername[50];
            scanf("%s", foldername);

            int sid = searchDirectory(rootdirectory, rootdirectoryIndex, foldername);
            if (sid != -1)
                printf("\nFolder already exists!");
            else
            {
                rootdirectory[rootdirectoryIndex].id = id++;
                strcpy(rootdirectory[rootdirectoryIndex].name, foldername);
                rootdirectory[rootdirectoryIndex].fileIndex = 0;
                printf("\nFolder %s added\n", rootdirectory[rootdirectoryIndex].name);
                rootdirectoryIndex++;
            }
            break;

        case 3:
            printf("\nEnter the file name to search: ");
            scanf("%s", searchFilename);
            int flag = -1;
            for (int i = 0; i < rootdirectoryIndex; ++i)
            {
                int searchID = searchFile(rootdirectory[i].files, rootdirectory[i].fileIndex, searchFilename);

                if (searchID != -1)
                {
                    flag = 1;
                    printf("\nFile found\nFilepath = %s/%s/%s\n", directoryName, rootdirectory[i].name, searchFilename);
                    break;
                }
            }

            if (flag == -1)
                printf("\nFile not found!");

            break;
        }
    } while (choice != 4);
}