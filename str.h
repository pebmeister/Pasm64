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

typedef struct str_node
{
    char* str;
    char* file;
    int line;
    struct str_node* next;
} StrNode;

StrNode* StrTable;

#ifdef MEM_DEBUG
#define STR_DUP(s)   StrDuplicate((s), __FILE__,__LINE__)
#else
#define STR_DUP(s)   strdup(s)
#endif

extern void AddStringNode(char* str, char* file, int line);
extern void RemoveStringNode(const void* str);
extern char* StrDuplicate(const char* string, char* file, int line);
extern int StrICmp(const char* str1, const char*str2);
extern char* StrLower(const char* string);
extern char* SantizeString(char* str);
extern void DumpStrings(void);