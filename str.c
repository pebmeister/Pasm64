// ***********************************************************************
// Assembly         : 
// Author           : Paul
// Created          : 02-23-2015
// ***********************************************************************
#pragma warning(disable:4996)

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "error.h"
#include "mem.h"

StrNode* StrTable = NULL;

void AddStringNode(char* str, char* file, const int line)
{
    const char* module = "AddStringNode";
    StrNode* node = malloc(sizeof(StrNode));
    if (node == NULL)
    {
        FatalError(module, error_out_of_memory);
        return;
    }
    memset(node, 0, sizeof(StrNode));

    node->str = str;
    const int len = (int)strlen(file);
    node->file = (char*)malloc(len + 1);
    if (node->file == NULL)
    {
        FatalError(module, error_out_of_memory);
        return;
    }
    strcpy(node->file, file);
    node->line = line;

    if (StrTable == NULL)
    {
        StrTable = node;
        return;
    }
    StrNode* n = StrTable;
    for (; n->next; n = n->next)
        ;
    n->next = node;
}

void RemoveStringNode(const void* str)
{
    if (StrTable == NULL)
        return;

    if (StrTable->str == str)
    {
        StrNode* next = StrTable->next;
        FreeStrInternal(StrTable->file);
        FreeMemoryInternal(StrTable, sizeof(StrNode));
        StrTable = next;
        return;
    }

    for (StrNode* n = StrTable; n->next; n = n->next)
    {
        StrNode* next = n->next;
        if (next->str == str)
        {
            n->next = next->next;
            FreeStrInternal(next->file);
            FreeMemoryInternal(next, sizeof(StrNode));
            return;
        }
    }
}

/// <summary>
/// duplicates the specified string.
/// </summary>
/// <param name="string">The string.</param>
/// <param name="file"></param>
/// <param name="line"></param>
/// <returns>char *.</returns>
char* StrDuplicate(const char* string, char* file, const int line)
{
    const int len = (int)strlen(string);
    const char* module = "StrDuplicate";
    char* buffer = (char*)ALLOCATE(len + 1);

    if (buffer == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    AddStringNode(buffer, file, line);

    return strcpy(buffer, string);
}

/// <summary>
/// compares the specified strings.
/// </summary>
/// <param name="pStr1">STR1.</param>
/// <param name="pStr2">STR2.</param>
/// <returns>int.</returns>
int StrICmp(const char* pStr1, const char* pStr2)
{
    char c1;
    int v;

    do 
    {
        c1 = (char)tolower(*pStr1++);
        const char c2 = (char)tolower(*pStr2++);
        /* the casts are necessary when pStr1 is shorter & char is signed */
        v = (int)((unsigned int)c1 - (unsigned int)c2);
    } while ((v == 0) && (c1 != '\0'));

    return v;
}

/// <summary>
/// Copies the specified string to lower case.
/// </summary>
/// <param name="string">The string.</param>
/// <returns>char *.</returns>
char* StrLower(const char* string)
{
    const char* module = "StrLower";

    const int len = (int)strlen(string);
    char* buffer = STR_DUP(string);
    
    if (buffer == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    for (int i = 0; i < len; ++i)
        buffer[i] = (char) tolower(string[i] & 0xFF);

    return buffer;
}

//
// return a string that expands escape sequences
//
char* SantizeString(char* str)
{
    const int len = (int)strlen(str) + 1;

    char* outStr = (char*)ALLOCATE(len);
    char* tmpStr = outStr;
    unsigned char escChar = 0;
    const char* module = "SantizeString";

    if (outStr == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    memset(outStr, 0, len);

    if (str == NULL)
    {
        Error(module, error_source_string_null);
        return NULL;
    }

    while (*str)
    {
        if (*str == '\\')
        {
            switch (tolower(*(++str)))
            {
            case 'a':
                escChar = '\a';
                break;

            case 'b':
                escChar = '\b';
                break;

            case 'f':
                escChar = '\f';
                break;

            case 'v':
                escChar = '\v';
                break;

            case 'r':
                escChar = '\r';
                break;

            case 'n':
                escChar = '\n';
                break;

            case 't':
                escChar = '\t';
                break;

            case 'x':
                str++;
                if (*str == 0)
                {
                    Error(module, error_unrecognized_escape_sequence);
                    break;
                }
                while (isxdigit((unsigned char)*str) && isxdigit((unsigned char)*(str + 1)))
                {
                    char temp[3] = { 0 };
                    temp[0] = *str;
                    temp[1] = *(str + 1);
                    *tmpStr++ = (char)(int)strtol(temp, NULL, 16);
                    str += 2;
                }
                continue;

            case '\'':
            case '\"':
            case '\\':
                escChar = *str & 0xFF;
                break;

            default:
                escChar = '?';
                Error(module, error_unrecognized_escape_sequence);
                break;
            }
            *tmpStr++ = (char)escChar;
            str++;
        }
        else if (*str)
        {
            *tmpStr++ = *str++;
        }
    }

    return outStr;
}

void DumpStrings(void)
{
    for (StrNode* node = StrTable; node; node = node->next)
    {
        printf("%-70s %-5d %s\n", node->file, node->line, node->str);
    }
}
