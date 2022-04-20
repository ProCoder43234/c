#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30
int nodeID = 0;

typedef struct Stack
{
    char name[50];
} Stack;

typedef struct file
{
    int id;
    char fileName[50];
} file;

typedef struct treeNode
{
    int id;
    char directoryName[SIZE];
    int fileIndex;
    file files[50];
    int subDirectoryIndex;
    struct treeNode *subDirectories;
    struct treeNode *parent;
} treeNode;

treeNode *initNode(int id, char directoryName[50], treeNode *parent)
{
    treeNode *node = (treeNode *)malloc(sizeof(treeNode));
    node->id = id;
    strcpy(node->directoryName, directoryName);
    node->fileIndex = 0;
    node->subDirectoryIndex = 0;
    node->subDirectories = (treeNode *)malloc(sizeof(treeNode) * SIZE);
    node->parent = parent;

    return node;
}

int searchFile(treeNode *node, char searchFileName[50])
{
    int searchID = -1;
    for (int i = 0; i < node->fileIndex; ++i)
        if (strcmp(node->files[i].fileName, searchFileName) == 0)
        {
            searchID = i;
            break;
        }

    return searchID;
}

int searchFolder(treeNode *node, char searchFolderName[50])
{
    int searchID = -1;
    for (int i = 0; i < node->subDirectoryIndex; ++i)
        if (strcmp(node->subDirectories[i].directoryName, searchFolderName) == 0)
        {
            searchID = i;
            break;
        }

    return searchID;
}

int treeSearch(treeNode *root, char searchFileName[50])
{
    Stack stack[100];
    int stackIndex = 0;

    int searchID = -1;
    for (int i = 0; i < root->subDirectoryIndex; ++i)
        if (searchFile(&root->subDirectories[i], searchFileName) != -1)
        {
            searchID = 1;
            printf("\nFile found!\nFile path: ");
            treeNode *tmp = &root->subDirectories[i];
            while (tmp != NULL)
            {
                strcpy(stack[stackIndex++].name, tmp->directoryName);
                tmp = tmp->parent;
            }
            while (stackIndex--)
                printf("%s/", stack[stackIndex].name);
            printf("%s", searchFileName);

            break;
        }
        else
        {
            int searchID = treeSearch(&root->subDirectories[i], searchFileName);
            if (searchID != -1)
                return searchID;
        }

    return searchID;
}

void createFile(treeNode *root, char filename[50])
{
    printf("\nCurrent Directory: %s", root->directoryName);
    printf("\nNo:of subdirectories = %d", root->subDirectoryIndex);

    char choice;

    printf("\n\nCreate file here? (y/n) :");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        if (searchFile(root, filename) != -1)
        {
            printf("File already exists!");
            return;
        }

        else
        {
            file tmpFile;
            tmpFile.id = root->fileIndex;
            strcpy(tmpFile.fileName, filename);
            root->files[root->fileIndex++] = tmpFile;
            printf("\nFile %s created", filename);
        }
    }

    else
    {
        if (root->subDirectoryIndex == 0)
        {
            printf("\nThere are no subdirectories!");
            return;
        }
        else
        {
            printf("\nSubdirectories:\n");
            for (int i = 0; i < root->subDirectoryIndex; ++i)
                printf("\n%d. %s", i + 1, root->subDirectories[i].directoryName);

            int subDirectoryIndex;
            printf("\n\nEnter a subdirectory: ");
            scanf("%d", &subDirectoryIndex);

            if (subDirectoryIndex > root->subDirectoryIndex)
            {
                printf("\nInvalid option");
                return;
            }

            else
                createFile(&root->subDirectories[subDirectoryIndex - 1], filename);
        }
    }
}

void createFolder(treeNode *root, char folderName[50])
{
    printf("\nCurrent directory: %s", root->directoryName);
    char choice;

    printf("\nCreate directory here? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        if (searchFolder(root, folderName) != -1)
        {
            printf("\nFolder already exists");
            return;
        }

        else
        {
            treeNode *node = initNode(nodeID++, folderName, root);
            root->subDirectories[root->subDirectoryIndex++] = *node;
            printf("\nDirectory %s created!", folderName);
        }
    }
    else
    {
        if (root->subDirectoryIndex == 0)
        {
            printf("\nThere are no subdirectories!");
            return;
        }
        else
        {
            printf("\nSubdirectories:\n");
            for (int i = 0; i < root->subDirectoryIndex; ++i)
                printf("\n%d. %s", i + 1, root->subDirectories[i].directoryName);

            int subDirectoryIndex;
            printf("\n\nEnter a subdirectory:");
            scanf("%d", &subDirectoryIndex);

            if (subDirectoryIndex > root->subDirectoryIndex)
            {
                printf("\nInvalid option");
                return;
            }

            else
                createFolder(&root->subDirectories[subDirectoryIndex - 1], folderName);
        }
    }
}

void main()
{
    char rootDirectoryName[50];
    int choice;
    printf("Enter the name of directory: ");
    scanf("%s", &rootDirectoryName);

    treeNode *root = initNode(nodeID++, rootDirectoryName, NULL);

    do
    {
        printf("\n\n1.Add files\n2.Add folder\n3.Search files\n4.Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter the file name: ");
            char filename[50];
            scanf("%s", filename);
            createFile(root, filename);
            break;

        case 2:
            printf("\nEnter the folder name: ");
            char foldername[50];
            scanf("%s", foldername);
            createFolder(root, foldername);
            break;

        case 3:
            printf("\nEnter the file name to search: ");
            char searchFilename[50];
            scanf("%s", searchFilename);
            int res = treeSearch(root, searchFilename);
            if (res == -1)
                printf("\nFile not found!!");
            break;
        }
    } while (choice != 4);
}