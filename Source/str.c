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

/// <summary>
/// duplicates the specified string.
/// </summary>
/// <param name="string">The string.</param>
/// <returns>char *.</returns>
char* Strdup(const char* string)
{
    const int len = (int)strlen(string);
    const char* module = "Strdup";
    char* buffer = (char*)malloc(len + 1);

    if (buffer == NULL)
    {
        FatalError(module, ErrorOutofMemory);
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
int Stricmp(const char* pStr1, const char* pStr2)
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
char* Strlower(const char* string)
{
    const char* module = "Strlower";
    const int len = (int) strlen(string);
    char* buffer = (char*)malloc(len + 1);

    if (buffer == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    char* strOut = buffer;
    do
    {
        *strOut++ =  (char)tolower(*string);
    } while (*string++);
    return buffer;
}
