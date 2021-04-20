// ***********************************************************************
// Assembly         : 
// Author           : Paul
// Created          : 02-23-2015
//
// Last Modified By : Paul
// Last Modified On : 02-23-2015
// ***********************************************************************
#pragma warning(disable:4996)

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "mem.h"

/// <summary>
/// duplicates the specified string.
/// </summary>
/// <param name="string">The string.</param>
/// <returns>char *.</returns>
char* StrDup(const char* string)
{
    const int len = (int)strlen(string);
    const char* module = "StrDup";
    char* buffer = (char*)ALLOCATE(len + 1);

    if (buffer == NULL)
    {
        FatalError(module, error_outof_memory);
        return NULL;
    }
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

    const int len = (int)strlen(string) + 1;
    char* buffer = (char*)ALLOCATE(len);
    
    if (buffer == NULL)
    {
        FatalError(module, error_outof_memory);
        return NULL;
    }
    for (int i = 0; i < len; ++i)
        buffer[i] = (char) tolower(string[i] & 0xFF);

    return buffer;
}
