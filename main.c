// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
//
// copyright (c) 2015 Paul Baxter
//
// Last Modified By : Paul
// Last Modified On : 11-07-2015
// ***********************************************************************
#pragma warning(disable:4065)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#include "pasm64.h"
#include "opcodes.h"
#include "node.h"
#include "genlist.h"
#include "symbol.h"
#include "str.h"
#include "error.h"
#include "file.h"

// If we have this many passes there is an infinite loop
const int MaxPasses =  20;
enum OutputFileType OutFileFormat = none;

int WarningCount = 0;
int ErrorCount = 0;
int Pass = 0;
int FinalPass = 0;
// ReSharper disable once CppInconsistentNaming
int CPUSpecifed = 0;
int IllegalSpecifed = 0;
int LogFileSpecified = 0;
int NoWarnings = 0;

FILE* OutputFile = NULL;
FILE* ListFile = NULL;
FILE* SymFile = NULL;
FILE* LogFile = NULL;
char* CurFileName = NULL;
char* LogFileName = NULL;
char* SymFileName = NULL;
char* OutputFileName = NULL;
char* InternalBuffer = NULL;
char* ListFileName = NULL;
char* Directories = NULL;

// ReSharper disable once CppInconsistentNaming
// ReSharper disable once IdentifierTypo
extern int yylex_destroy(void);
// ReSharper disable once CppInconsistentNaming
// ReSharper disable once IdentifierTypo
void yymessage(const char* s);

/// <summary>
/// Reset lex
/// Must be done before each pass
/// </summary>
void ResetLex(void)
{
    const char* module = "ResetLex";

    SymbolValueChanged = 0;

    // reset the Program Counter
    PC = 0x1000;

    // reset End flag
    End = 0;

    // reset Org flag
    OriginSpecified = FALSE;

    if (InternalBuffer == NULL)
    {
        InternalBuffer = (char*)malloc(MAX_LINE_LEN);
        if (InternalBuffer == NULL)
        {
            FatalError(module, error_outof_memory);
            return;
        }
    }

    // reset the the head node
    CurrentNode = HeadNode = (parseNode *) malloc(sizeof(parseNode));
    if (CurrentNode == NULL)
    {
        FatalError(module, error_outof_memory);
        return;
    }
    memset(HeadNode, 0, sizeof(parseNode));
}

//
// print the usage
//
void Usage(void)
{
    printf("Usage:\n");
    printf("  pasm64 [-o outputfile] [-dir directory] [-s symbolfile] [-l listfile] [-log logfile] [-i] [-c64] [-65c02 | -6502] [-?] [-nowarn] inputfile1 inputfile2 ...\n\n");
    printf("         -o outputfile   specifies output file\n");
    printf("         -dir directory  specifies directories to search for source files and include files separated by ';'\n");
    printf("         -s symbolfile   specifies symbol file\n");
    printf("         -l listfile     specifies listing file\n");
    printf("         -log logfile    specifies log file\n");
    printf("         -i              allow illegal instructions\n");
    printf("         -c64            write load address in first 2 bytes of output file\n");
    printf("         -6502           use 6502 instruction set (default)\n");
    printf("         -65C02          use 65C02 instruction set\n");
    printf("         -nowarn         turn off warnings\n");
    printf("         -?              print this help\n");
}

//
// Main Entry point
//
int main(const int argc, char* argv[]) 
{
    int cleanPassCount = 0;
    int argIndex = 1;
    int inputFileCount = 0;
    int inFileIndex;
    int lastUnresolvedCount = INT_MAX;

    const char* module = "main";
    
    char** inputFiles = (char**) malloc(sizeof(char*) * argc);

    if (inputFiles == NULL)
    {
        FatalError(module, error_outof_memory);
        return -1;
    }

    CPUMode = cpu_6502;

    // Init Ex 
    InitEx();

    while (argIndex < argc)
    {
        if ((StrICmp(argv[argIndex], "-?") == 0) || (StrICmp(argv[argIndex], "/?") == 0))
        {
            Usage();
            continue;
        }
        // get output file
        if ((StrICmp(argv[argIndex], "-o") == 0) || (StrICmp(argv[argIndex], "/o") == 0))
        {
            argIndex ++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_output_file);
                Usage();
                return -1;
            }
            if (OutputFileName != NULL)
            {
                Error(module, error_output_file_specified_more_than_once);
                Usage();
                return -1;
            }
            OutputFileName = argv[argIndex];
            argIndex++;
            continue;
        }

        // get symbol file
        if ((StrICmp(argv[argIndex], "-s") == 0) || (StrICmp(argv[argIndex], "/s") == 0))
        {
            argIndex ++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_symbol_file);
                Usage();
                return -1;
            }
            if (SymFileName != NULL)
            {
                Error(module, error_symbol_file_specified_more_than_once);
                Usage();
                return -1;
            }
            SymFileName = argv[argIndex];
            argIndex++;
            continue;
        }

        if ((StrICmp(argv[argIndex], "-dir") == 0) || (StrICmp(argv[argIndex], "/dir") == 0))
        {
            argIndex++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_parameter);
                Usage();
                return -1;
            }
            if (Directories != NULL)
            {
                Error(module, error_symbol_file_specified_more_than_once);
                Usage();
                return -1;
            }
            Directories = argv[argIndex];
            argIndex++;
            continue;
        }

        // get log file
        if ((StrICmp(argv[argIndex], "-log") == 0) || (StrICmp(argv[argIndex], "/log") == 0))
        {
            argIndex ++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_log_file);
                Usage();
                return -1;
            }
            if (LogFileName != NULL)
            {
                Error(module, error_log_file_specified_more_than_once);
                Usage();
                return -1;
            }
            LogFileName = argv[argIndex];
            argIndex++;
            LogFileSpecified = TRUE;
            continue;
        }

        // get list file
        if ((StrICmp(argv[argIndex], "-l") == 0) || (StrICmp(argv[argIndex], "/l") == 0))
        {
            argIndex ++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_list_file);
                Usage();
                return -1;
            }
            if (ListFileName != NULL)
            {
                Error(module, error_list_file_specified_more_than_once);
                Usage();
                return -1;
            }
            ListFileName = argv[argIndex];
            argIndex++;
            continue;
        }

        // C64 mode - write load address
        if ((StrICmp(argv[argIndex], "-c64") == 0) || (StrICmp(argv[argIndex], "/c64") == 0))
        {
            if (OutFileFormat != none)
            {
                Error(module, error_c64_output_format_specified_more_than_once);
                Usage();
                return -1;
            }
            OutFileFormat = c64;
            argIndex++;
            continue;
        }

        // 65c02 opcodes enabled
        if ((StrICmp(argv[argIndex], "-65c02") == 0) || (StrICmp(argv[argIndex], "/65c02") == 0))
        {
            if (CPUSpecifed)
            {
                Error(module, error_instruction_set_specified_more_than_once);
                Usage();
                return -1;
            }
            CPUSpecifed = TRUE;
            CPUMode = cpu_65C02;
            argIndex++;
            continue;
        }

        // 6502 opcodes specified
        if ((StrICmp(argv[argIndex], "-6502") == 0) || (StrICmp(argv[argIndex], "/6502") == 0))
        {
            if (CPUSpecifed)
            {
                Error(module, error_instruction_set_specified_more_than_once);
                Usage();
                return -1;
            }
            CPUSpecifed = TRUE;
            CPUMode = cpu_6502;
            argIndex++;
            continue;
        }

        // illegal opcodes allowed specified
        if ((StrICmp(argv[argIndex], "-i") == 0) || (StrICmp(argv[argIndex], "/i") == 0))
        {
            if (IllegalSpecifed)
            {
                Error(module, error_illegal_opcodes_specified_more_than_once);
                Usage();
                return -1;
            }
            IllegalSpecifed = TRUE;
            AllowIllegalOpCpodes = TRUE;
            argIndex++;
            continue;
        }

        // no warnings
        if ((StrICmp(argv[argIndex], "-nowarn") == 0) || (StrICmp(argv[argIndex], "/nowarn") == 0))
        {
            if (NoWarnings)
            {
                Error(module, error_illegal_opcodes_specified_more_than_once);
                Usage();
                return -1;
            }
            NoWarnings = TRUE;
            argIndex++;
            continue;
        }

        // add to the input file list
        inputFiles[inputFileCount++] = argv[argIndex];
        argIndex ++;
    }

    // make sure we have at least 1 input file
    if (inputFileCount == 0)
    {
        Error(module, error_no_input_file_specified);
        Usage();
        return -1;
    }        

    // Pass Loop
    // loop until all symbols are resolved
    //
    Pass = 1;
    if (LogFileSpecified && LogFileName)
    {
        LogFile = fopen(LogFileName, "w");
        if (LogFile == NULL)
        {
            Error(module, error_opening_log_file);
            return -1;
        }
    }

    do
    {
        fprintf(stdout, "Pass %d\n", Pass);
        Pass++;

        if (LogFileSpecified)
        {
            fprintf(LogFile, "PASS %d\n", Pass);
        }

        // reset lex vars
        ResetLex();

        // loop through each input file
        for (inFileIndex = 0; inFileIndex < inputFileCount; inFileIndex++)
        {
            // initialize line number and set file name
            yylineno = 0;

            CurFileName = inputFiles[inFileIndex];
            yyin = OpenFile(CurFileName, "r");
            if (yyin == NULL)
            {
                FatalError(module, error_opening_input_file);
                return -1;
            }

            if (LogFileSpecified)
            {
                fprintf(LogFile, "Current File %s\n", CurFileName);
            }

            // seek to start (could be redundant)
            fseek(yyin, 0, SEEK_SET);

            // reset parser
            yyrestart(yyin);

            // parse the file
            yyparse();

            // close the file
            fclose(yyin);
        }

        // free the parse tree
        FreeTree();

        // see if there are any more unresolved symbols
        const int unresolvedCount = UnResolvedSymbols();

        if (CurrentSection)
        {
            free(CurrentSection);
            CurrentSection = NULL;
        }

        // if there are no more symbols resolved then
        // the symbol is not defined 
        if (unresolvedCount > 0 && unresolvedCount >= lastUnresolvedCount)
        {
            ErrorCount = unresolvedCount;
            DumpUnResolvedSymbols();
            break;
        }
        lastUnresolvedCount = unresolvedCount;
        if (ErrorCount == 0 && SymbolValueChanged == 0 && unresolvedCount == 0)
            cleanPassCount++;
        else
            cleanPassCount = 0;

        if (LogFileSpecified)
        {
            DumpSymbols(LogFile);
        }
    } while (Pass < MaxPasses && ErrorCount == 0 && cleanPassCount < 1);   

    if (Pass >= MaxPasses)
    {
        FatalError(module, error_circular_symbol_definitions);
        return 0;
    }
    if (ErrorCount > 0)
    {
        fprintf(stderr, "%d error(s)\n", ErrorCount);
    }
    else
    {
        printf("Final Pass\n");

        // Make a FinalPass
        ResetLex();

        // set final pass flag
        FinalPass = TRUE;
        if (LogFileSpecified)
        {
            fprintf(LogFile, "Final Pass\n");
        }

        // create the output file
        if (OutputFileName != NULL)
        {
            OutputFile = fopen(OutputFileName, "wb");
            if (OutputFile == NULL)
            {
                FatalError(module, error_opening_output_file);
                return -1;
            }
        }

        // loop through the input files
        for (inFileIndex = 0; inFileIndex < inputFileCount; inFileIndex++)
        {
            yylineno = 0;
            CurFileName = inputFiles[inFileIndex];
            yyin = OpenFile(CurFileName, "r");
            if (yyin == NULL)
            {                
                FatalError(module, error_opening_input_file);
                return -1;
            }
            if (LogFileSpecified)
            {
                fprintf(LogFile, "Current File %s\n", CurFileName);           
            }
            
            // make sure file gets included for a listing
            GenerateListNode(NULL);

            fseek(yyin, 0, SEEK_SET);               
            yyrestart(yyin);
            yyparse();
            fclose(yyin);
            GenerateListNode(NULL);
        }

        if (CurrentSection)
        {
            Warning(module, error_missing_end_section);
            free(CurrentSection);
            CurrentSection = NULL;
        }

        // close output file
        if (OutputFile != NULL)
            fclose(OutputFile);

        // generate symbol file
        if (SymFileName != NULL)
        {
            SymFile = fopen(SymFileName, "w");
            if (SymFile == NULL)
            {
                FatalError(module, error_opening_symbol_file);
                return -1;
            }
            // display the symbols
            DumpSymbols(SymFile);
            fclose(SymFile);
        }

        // generate the list file
        if (ListFileName != NULL)
        {
            ListFile = fopen(ListFileName, "w");
            if (ListFile == NULL)
            {
                Error(module, error_opening_list_file);
            }
            else
            {
                GenerateListFile(ListFile);
                fclose(ListFile);
            }
        }

        if (WarningCount > 0)
        {
            fprintf(stderr, "%d warning(s)\n", WarningCount);
        }
        if (ErrorCount > 0)
        {
            fprintf(stderr, "%d error(s)\n", ErrorCount);
        }
        else if (OutputFile)
        {
           fprintf(stdout, "Total bytes written: %d\n", TotalBytesWritten);
        }
    }

    // free lex buffers
    yylex_destroy();

    // free the parse tree
    FreeTree();

    // close log file
    if (LogFileSpecified)
        fclose(LogFile);

    // free input file array
    if (inputFiles)
        free(inputFiles);
  
    // free internal buffer
    if (InternalBuffer)
        free(InternalBuffer);

    // delete symbol table
    DeleteSymbolTable();
    
    // free list table
    FreeListTable();
    
    return 0;
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
void yyerror(const char *s)
{
    yymessage(s);
    ErrorCount++;
}

/// <summary>
/// warn routine.
/// </summary>
/// <param name="s">The warning string.</param>
void yywarn(const char *s)
{
    if (NoWarnings)
        return;

    yymessage(s);
    WarningCount++;
}
