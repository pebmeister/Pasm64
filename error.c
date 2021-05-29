// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
// ***********************************************************************
#pragma warning(disable:4065)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "pasm64.h"

char* Function;

/// <summary>
/// The errors
/// </summary>
const char* Errors[] =
{
    "Out of memory.",
    "Missing output file name.",
    "Output file name specified more than once.",
    "Missing symbol file name.",
    "Symbol file name specified more than once.",
    "Missing log file name.",
    "Log file name specified more than once.",
    "Missing list file name.",
    "List file name specified more than once.",
    "C64 format specified more than once.",
    "Instruction set specified more than once.",
    "Illegal opcodes specified more than once.",
    "No input file specified.",
    "Error opening log file",
    "Error opening input file",
    "Error opening symbol file",
    "Error opening output file",
    "Error opening list file",
    "Error creating list node.",
    "Value out of range.",
    "Missing parameter.",
    "Error writing list file",
    "Error read source file",
    "Error writing output file",
    "Invalid opcode mode.",
    "Unknown opcode or addressing mode.",
    "Source string NULL.",
    "Unrecognized escape sequence.",
    "Invalid number of ops.",
    "Invalid parameters.",
    "FOR REG# can not be nested.",
    "EndSection without Section.",
    "Org specified more than once.",
    "Error adding symbol",
    "Error initializing variable.",
    "Infinite loop detected.",
    "Expected next.",
    "Divide by zero detected.",
    "Unknown operator type.",
    "Unknown node type.",
    "Unexpected symbol reassignment",
    "Macro parameter not found.",
    "Macro parameter underflow.",
    "NoWarn specified more than once.",
    "Branch out range. Creating branch island.",
    "Program counter out of range.",
    "Missing .EndSection",
    "Circular symbol definition(s) detected.",
    "Include file stack overflow.",
    "Unable to open include file.",
    "Memory corruption detected.",
    "Attempt to free unallocated memory.",
    "Verbose specified more than once.",
    "Plus local symbol not allowed in macro."
};
#define NUM_ERRORS (sizeof(Errors)/sizeof(char*))

static char ErrorBuffer[MAX_LINE_LEN] = { 0 };

/// <summary>
/// MessageBase.
/// </summary>
/// <param name="module">The module.</param>
/// <param name="error">The error.</param>
/// <returns>char *.</returns>
char* MessageBase(const char* module, int error)
{
    if (error >=0 && error < (int)NUM_ERRORS)
    {
        switch (error)
        {
            case error_writing_list_file:
            case error_opening_list_file:
                sprintf(ErrorBuffer, "%s: %s %s.", module, Errors[error], ListFileName);
                break;

            case error_opening_output_file:
                sprintf(ErrorBuffer, "%s: %s %s.", module, Errors[error], OutputFileName);
                break;

            case error_opening_symbol_file:
                sprintf(ErrorBuffer, "%s: %s %s.", module, Errors[error], SymFileName);
                break;

            case error_opening_log_file:
                sprintf(ErrorBuffer, "%s: %s %s.", module, Errors[error], LogFileName);
                break;

            case error_reading_source_file:
            case error_opening_input_file:
                sprintf(ErrorBuffer, "%s: %s %s.", module, Errors[error], CurFileName);
                break;

            default:
                sprintf(ErrorBuffer, "%s: %s", module, Errors[error]);
                break;
        }
    }
    else
    {
        sprintf(ErrorBuffer, "%s: Error %d", module, error);
    }
    return ErrorBuffer;
}
//
// Warning routine
//
void Warning(const char* module, const int error)
{
    yywarn(MessageBase(module, error));
}

//
// Error routine
//
void Error(const char* module, const int error)
{
    yyerror(MessageBase(module, error));
}

//
// Error routine
//
void FatalError(const char* module, const int error)
{  // NOLINT(clang-diagnostic-missing-noreturn)
    yyerror(MessageBase(module, error));
    exit(error);
}

/// <summary>
/// message routine.
/// </summary>
/// <param name="s">The s.</param>
void yymessage(const char* s)
{
    if (yyin && CurFileName != NULL && InternalBuffer != NULL)
    {
        int curline;

        fprintf(stderr, "%s File %s near line %d\n", s, CurFileName, yylineno + 1);

        const long curpos = ftell(yyin);
        fseek(yyin, 0, SEEK_SET);
        for (curline = 1; curline < yylineno - 2; curline++)
            fgets(InternalBuffer, MAX_LINE_LEN, yyin);

        for (; curline < yylineno + 3; curline++)
        {
            if (!feof(yyin))
            {
                *InternalBuffer = 0;
                fgets(InternalBuffer, MAX_LINE_LEN, yyin);
                fprintf(stderr, "%-5d  ", curline);
                fputs(InternalBuffer, stderr);
            }
        }
        fputs("\n", stderr);
        fseek(yyin, curpos, SEEK_SET);
    }
    else
        fprintf(stderr, "%s\n", s);
}

/// <summary>
/// Error routine.
/// </summary>
/// <param name="s">The error string.</param>
void yyerror(const char* s)
{
    yymessage(s);
    ErrorCount++;
}

/// <summary>
/// warn routine.
/// </summary>
/// <param name="s">The warning string.</param>
void yywarn(const char* s)
{
    if (NoWarnings)
        return;

    yymessage(s);
    WarningCount++;
}
