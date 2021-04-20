#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "genlist.h"
#include "pasm64.h"
#include "str.h"
#include "mem.h"

char Path[4096] = { 0 };

FILE* OpenFile(const char* file, char* mode)
{
    FILE* fd = fopen(file, mode);
    if (fd != NULL) return fd;

    if (Directories == NULL) return NULL;

    for (char* dir = Directories; *dir != 0;)
    {
        char* p = Path;
        while (*dir != 0 && *dir != ';')
        {
            *p++ = *dir++;
        }
        *p = 0;
        strcat(Path, file);
        fd = fopen(Path, mode);
        if (fd != NULL)
            return fd;

        if (*dir == ';')
            dir++;
    }
    return NULL;
}

FileLine* ReadFileLines(const char* fileName)
{
    int line = 1;
    const char* module = "ReadFileLines";
    FileLine* headFileNode = NULL;
    FileLine* fileNode = NULL;
    FILE* file = OpenFile(fileName, "r");
    if (file == NULL)
    {
        Error(module, error_opening_list_file);
        return NULL;
    }
    while (!feof(file))
    {
        InternalBuffer[0] = 0;
        if (fgets(InternalBuffer, MAX_LINE_LEN, file))
        {
            if (fileNode == NULL)
            {
                fileNode = (FileLine*)ALLOCATE(sizeof(FileLine));
                headFileNode = fileNode;
            }
            else
            {
                fileNode->next = (FileLine*)ALLOCATE(sizeof(FileLine));
                fileNode = fileNode->next;
            }
            if (fileNode == NULL)
            {
                Error(module, error_outof_memory);
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
