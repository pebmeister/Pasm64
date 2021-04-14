#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "error.h"
#include "genlist.h"
#include "pasm64.h"
#include "str.h"


FILE* OpenFile(const char* file, char* mode)
{
    FILE* fd = fopen(file, mode);
    if (fd != NULL) return fd;

    if (Directories == NULL) return NULL;

    char path[1024] = { 0 };

    for (char* dir = Directories; *dir != 0;)
    {
        char* p = path;
        while (*dir != 0 && *dir != ';')
        {
            *p++ = *dir++;
        }
        *p = 0;
        strcat(path, file);
        fd = fopen(path, mode);
        if (fd != NULL)
            return fd;

        if (*dir == ';')
            dir++;
    }
    return NULL;
}

FileLine* ReadFile(const char* fileName)
{
    int line = 1;
    const char* module = "ReadFile";
    FileLine* headFileNode = NULL;
    FileLine* fileNode = NULL;
    FILE* file = OpenFile(fileName, "r");
    if (file == NULL)
    {
        Error(module, ErrorOpeningListFile);
        return NULL;
    }
    while (!feof(file))
    {
        InternalBuffer[0] = 0;
        if (fgets(InternalBuffer, MAXLINE_LEN, file))
        {
            if (fileNode == NULL)
            {
                fileNode = (FileLine*)malloc(sizeof(FileLine));
                headFileNode = fileNode;
            }
            else
            {
                fileNode->next = (FileLine*)malloc(sizeof(FileLine));
                fileNode = fileNode->next;
            }
            if (fileNode == NULL)
            {
                Error(module, ErrorOutofMemory);
                return NULL;
            }
            memset(fileNode, 0, sizeof(FileLine));
            fileNode->line = StrDup(InternalBuffer);
            fileNode->line_number = line++;
        }
    }
    fclose(file);
    return headFileNode;
}
