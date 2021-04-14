#pragma once

#include "pasm64.h"

// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
//
// copyright (c) 2015 Paul Baxter
//
// Last Modified By : Paul
// Last Modified On : 11-29-2015
// ***********************************************************************

typedef struct ListTable
{
    int line;
    char* filename;
    char* output;
    struct ListTable* next;
} ListTable, *ListTablePtr;

extern void GenerateListFile(FILE* lstFile);
extern int GenerateListNode(parseNodePtr p);
extern void FreeListTable(void);

ListTablePtr AddList(char* file, int line, char* output);


typedef struct file_line
{
    char* line;
    int line_number;
    int displayed;
    struct file_line* next;
} FileLine;

typedef struct file_entry
{
    char* filename;
    FileLine* lines;
    struct file_entry* next;
} FileEntry;

extern FileEntry* SourceFileList;
