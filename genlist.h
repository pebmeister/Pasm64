#pragma once

#include "pasm64.h"

// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
//
// copyright (c) 2015 Paul Baxter
//
// ***********************************************************************

typedef struct list_table
{
    int line;
    char* filename;
    char* output;
    struct list_table* next;
} ListTable, *ListTablePtr;

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

extern void GenerateListFile(FILE* lstFile);
extern int GenerateListNode(ParseNodePtr p);
extern FileLine* GetFileLine(char* file, int line);
extern void FreeListTable(void);
extern void FreeFileTable(void);
extern ListTablePtr AddList(char* file, int line, char* output);
extern FileEntry* SourceFileList;
extern void ResetFileLines(void);

