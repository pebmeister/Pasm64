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

    const int len = (int)strlen(string);
    char* buffer = StrDup(string);
    
    if (buffer == NULL)
    {
        FatalError(module, error_outof_memory);
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
        FatalError(module, error_outof_memory);
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
