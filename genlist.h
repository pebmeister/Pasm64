#pragma once

// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
//
// copyright (c) 2015 Paul Baxter
//
// Last Modified By : Paul
// Last Modified On : 11-29-2015
// ***********************************************************************
#pragma once

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

