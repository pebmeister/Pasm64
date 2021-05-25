// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
//
// ***********************************************************************
#pragma warning(disable:4065)
#pragma warning(disable:4996)

// ReSharper disable once CommentTypo
// -log renum.log -dir "C:\Users\jaret\source\repos\pebmeister\Pasm64\windows\Installer\Samples\Commodore\renumber\;C:\Users\jaret\source\repos\pebmeister\Pasm64\windows\Installer\Samples\Commodore\include\\" macros.asm pagezero.asm kernal.asm basic.asm install.asm wedge.asm vars.asm main.asm init.asm pass1.asm pass2.asm getlinenum.asm findlinenum.asm insertlinenum.asm movelines.asm util.asm debug.asm storage.asm -C64 -l renumber.lst -v -o renumber.prg

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

#include "pasm64.h"
#include "opcodes.h"
#include "node.h"
#include "genlist.h"
#include "symbol.h"
#include "str.h"
#include "error.h"
#include "file.h"
#include "mem.h"

// If we have this many passes there is an infinite loop
const int MaxPasses =  20;
enum OutputFileType OutFileFormat = none;

int WarningCount = 0;
int ErrorCount = 0;
int Pass = 0;
int FinalPass = 0;
int Verbose = 0;

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
char** InputFiles = NULL;
int InputFileCount = 0;

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

    LastLabel = NULL;

    // reset the Program Counter
    PC = 0x1000;

    // reset End flag
    End = 0;

    // reset Org flag
    OriginSpecified = FALSE;

    if (InternalBuffer == NULL)
    {
        InternalBuffer = (char*)ALLOCATE(MAX_LINE_LEN);
        if (InternalBuffer == NULL)
        {
            FatalError(module, error_out_of_memory);
            return;
        }
    }

    // reset the the head node
    CurrentNode = HeadNode = (ParseNode*)AllocateNode(0);
    if (CurrentNode == NULL)
    {
        FatalError(module, error_out_of_memory);
        return;
    }
    HeadNode->type = type_head_node;

    ResetMacroDict();
}

//
// print the usage
//
void Usage(void)
{
    printf("Usage:\n");
    printf("  pasm64 [-o outputfile] [-d sym val] [-dir directory] [-s symbolfile] [-l listfile] [-log logfile] [-i] [-v] [-c64] [-65c02 | -6502] [-?] [-nowarn] inputfile1 inputfile2 ...\n\n");
    printf("         -o outputfile   specifies output file\n");
    printf("         -d sym value    defines a symbol with a value. This may be specified more than one for multiple symbols\n");
    printf("         -dir directory  specifies directories to search for source files and include files separated by ';'\n");
    printf("         -s symbolfile   specifies symbol file\n");
    printf("         -l listfile     specifies listing file\n");
    printf("         -log logfile    specifies log file\n");
    printf("         -i              allow illegal instructions\n");
    printf("         -v              verbose mode.\n");
    printf("         -c64            Commodore program format. Write load address in first 2 bytes of output file\n");
    printf("         -6502           use 6502 instruction set (default)\n");
    printf("         -65C02          use 65C02 instruction set\n");
    printf("         -nowarn         turn off warnings\n");
    printf("         -?              print this help\n");
}

void ParseArguments(const int argc, char* argv[])
{
    const char* module = "ParseArguments";
    InputFiles = (char**)ALLOCATE(sizeof(char*) * argc);
    int argIndex = 1;

    if (InputFiles == NULL)
    {
        FatalError(module, error_out_of_memory);
        exit(-1);
    }

    CPUMode = cpu_6502;

    // Init Ex 
    InitEx();

    while (argIndex < argc)
    {
        if ((StrICmp(argv[argIndex], "-?") == 0) || (StrICmp(argv[argIndex], "/?") == 0)
            || ((StrICmp(argv[argIndex], "-h") == 0) || (StrICmp(argv[argIndex], "/h") == 0)))
        {
            Usage();
            exit(0);
        }
        // get output file
        if ((StrICmp(argv[argIndex], "-o") == 0) || (StrICmp(argv[argIndex], "/o") == 0))
        {
            argIndex++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_output_file);
                Usage();
                exit(-1);
            }
            if (OutputFileName != NULL)
            {
                Error(module, error_output_file_specified_more_than_once);
                Usage();
                exit(-1);
            }
            OutputFileName = argv[argIndex];
            argIndex++;
            continue;
        }

        // get symbol file
        if ((StrICmp(argv[argIndex], "-s") == 0) || (StrICmp(argv[argIndex], "/s") == 0))
        {
            argIndex++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_symbol_file);
                Usage();
                exit(-1);
            }
            if (SymFileName != NULL)
            {
                Error(module, error_symbol_file_specified_more_than_once);
                Usage();
                exit(-1);
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
                exit(-1);
            }
            if (Directories != NULL)
            {
                Error(module, error_symbol_file_specified_more_than_once);
                Usage();
                exit(-1);
            }
            Directories = argv[argIndex];
            argIndex++;
            continue;
        }

        // get log file
        if ((StrICmp(argv[argIndex], "-log") == 0) || (StrICmp(argv[argIndex], "/log") == 0))
        {
            argIndex++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_log_file);
                Usage();
                exit(-1);
            }
            if (LogFileName != NULL)
            {
                Error(module, error_log_file_specified_more_than_once);
                Usage();
                exit(-1);
            }
            LogFileName = argv[argIndex];
            argIndex++;
            LogFileSpecified = TRUE;
            continue;
        }

        // get list file
        if ((StrICmp(argv[argIndex], "-l") == 0) || (StrICmp(argv[argIndex], "/l") == 0))
        {
            argIndex++;
            if (argIndex >= argc)
            {
                Error(module, error_missing_list_file);
                Usage();
                exit(-1);
            }
            if (ListFileName != NULL)
            {
                Error(module, error_list_file_specified_more_than_once);
                Usage();
                exit(-1);
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
                exit(-1);
            }
            OutFileFormat = c64;
            argIndex++;
            continue;
        }

        if ((StrICmp(argv[argIndex], "-v") == 0) || (StrICmp(argv[argIndex], "/v") == 0))
        {
            if (Verbose)
            {
                Error(module, error_verbose_specified_more_than_once);
                Usage();
                exit(-1);
            }

            Verbose = 1;
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
                exit(-1);
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
                exit(-1);
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
                exit(-1);
            }
            IllegalSpecifed = TRUE;
            AllowIllegalOpCodes = TRUE;
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
                exit(-1);
            }
            NoWarnings = TRUE;
            argIndex++;
            continue;
        }

        if ((StrICmp(argv[argIndex], "-d") == 0) || (StrICmp(argv[argIndex], "/d") == 0))
        {
            argIndex++;
            if (argIndex >= argc)
            {
                Error(module, error_invalid_parameters);
                Usage();
                exit(-1);
            }
            char* symName = argv[argIndex];

            argIndex++;
            if (argIndex >= argc)
            {
                Error(module, error_invalid_parameters);
                Usage();
                exit(-1);
            }
            char* val = argv[argIndex];

            int symVal;

            if (val[0] == '$')
            {
                symVal = (int)strtol(val + 1, NULL, 16);
            }
            else if (val[0] == '0' && val[1] == 'x')
            {
                symVal = (int)strtol(val + 2, NULL, 16);
            }
            else if (val[0] == '%')
            {
                symVal = (int)strtol(val + 1, NULL, 2);
            }
            else if (val[0] == '0' && val[1] == 'b')
            {
                symVal = (int)strtol(val + 2, NULL, 2);
            }
            else
            {
                symVal = (int)strtol(val, NULL, 10);
            }

            // ReSharper disable once CppLocalVariableMayBeConst
            SymbolTablePtr sym = AddSymbol(symName);
            if (sym != NULL)
            {
                SetSymbolValue(sym, symVal);
                sym->initialized = TRUE;
            }
            argIndex++;
            continue;
        }
        // add to the input file list
        InputFiles[InputFileCount++] = argv[argIndex];
        argIndex++;
    }
}

//
// Main Entry point
//
int main(const int argc, char* argv[]) 
{
    int cleanPassCount = 0;
    int inFileIndex;
    int lastUnresolvedCount = INT_MAX;

    const char* module = "main";

    ParseArguments(argc, argv);

    // make sure we have at least 1 input file
    if (InputFileCount == 0)
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
        if (Verbose)
            fprintf(stdout, "Pass %d\n", Pass);

        if (LogFileSpecified)
        {
            fprintf(LogFile, "PASS %d\n", Pass);
        }

        // reset lex vars
        ResetLex();

        // loop through each input file
        for (inFileIndex = 0; inFileIndex < InputFileCount; inFileIndex++)
        {
            // initialize line number and set file name
            yylineno = 0;

            CurFileName = InputFiles[inFileIndex];
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
        FreeParseTree();

        // see if there are any more unresolved symbols
        const int unresolvedCount = UnResolvedSymbols();

        if (CurrentScope)
        {
            FREE(CurrentScope);
            CurrentScope = NULL;
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
        Pass++;
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
        if (Verbose)
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
        for (inFileIndex = 0; inFileIndex < InputFileCount; inFileIndex++)
        {
            yylineno = 0;
            CurFileName = InputFiles[inFileIndex];
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

        if (CurrentScope)
        {
            Warning(module, error_missing_end_section);
            FREE(CurrentScope);
            CurrentScope = NULL;
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

        // generate verbose output
        if (Verbose)
        {
            ResetFileLines();
            GenerateListFile(stdout);

            DumpSymbols(stdout);
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

        // close log file
        if (LogFileSpecified)
            fclose(LogFile);

        // free the parse tree
        FreeParseTree();

        // free input file array
        if (InputFiles)
            FREE(InputFiles);

        // free internal buffer
        if (InternalBuffer)
            FREE(InternalBuffer);

        // delete symbol table
        DeleteSymbolTable();

        // free list table
        FreeListTable();

        // Free the file table
        FreeFileTable();

#ifdef _DEBUG
#ifdef DEBUG_MEMORY
        PrintMemoryAllocationSummary();
        PrintMemoryAllocation();
        DumpStrings();
#endif
#endif

        // Free Misc Allocated memory
        FreeAllocatedMemory();

        // free lex buffers
        yylex_destroy();
    }

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
