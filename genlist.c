// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
// ***********************************************************************
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "opcodes.h"
#include "pasm64.h"
#include "genlist.h"
#include "genoutput.h"
#include "str.h"
#include "error.h"

#define SRC_LST_INDENT  25

ListTablePtr AddList(char* file, int line, char* output);


typedef struct file_line
{
    char* line;
    int lineNumber;
    int displayed;
    struct file_line* next;
} FileLine;

typedef struct file_entry
{
    char* filename;
    FileLine* lines;
    struct file_entry* next;
} FileEntry;

FileEntry* SourceFileList = NULL;
FileLine* ReadFile(const char* fileName);

FileLine* GetFileLine(char* file, const int line)
{
    const char* module = "GetFileLine";
    FileEntry* fileEntry = SourceFileList;
    FileEntry* prev = NULL;
    for (; fileEntry != NULL && StrICmp(fileEntry->filename, file) != 0; fileEntry = fileEntry->next)
        prev = fileEntry;

    if (!fileEntry)
    {
        fileEntry = (FileEntry*)malloc(sizeof(FileEntry));
        if (fileEntry)
        {
            memset(fileEntry, 0, sizeof(FileEntry));
            fileEntry->filename = StrDup(file);
            fileEntry->lines = ReadFile(file);
            if (prev)
                prev->next = fileEntry;
        }
    }
    if (fileEntry)
    {
        if (SourceFileList == NULL)
            SourceFileList = fileEntry;

        if (StrICmp(fileEntry->filename, file) == 0)
        {
            FileLine* lineEntry = fileEntry->lines;
            for (; lineEntry && lineEntry->lineNumber < line; lineEntry = lineEntry->next)
                ;
            return lineEntry;
        }
    }
    Error(module, ErrorOpeningListFile);
    return NULL;
}

/// <summary>
/// The list head
/// </summary>
ListTablePtr ListHead = NULL;

FileLine* ReadFile(const char* fileName)
{
    int line = 1;
    const char* module = "ReadFile";
    FileLine* headFileNode = NULL;
    FileLine* fileNode = NULL;
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        Error(module, ErrorOpeningListFile);
        return NULL;
    }
    while (!feof(file))
    {
        InternalBuffer[0] = 0;
        if (fgets(InternalBuffer, MAXLINE_LEN, file))
        {
            if (fileNode == NULL)
            {
                fileNode = (FileLine*)malloc(sizeof(FileLine));
                headFileNode = fileNode;
            }
            else
            {
                fileNode->next = (FileLine*)malloc(sizeof(FileLine));
                fileNode = fileNode->next;
            }
            if (fileNode == NULL)
            {
                Error(module, ErrorOutofMemory);
                return NULL;
            }
            memset(fileNode, 0, sizeof(FileLine));
            fileNode->line = StrDup(InternalBuffer);
            fileNode->lineNumber = line++;
        }
    }
    fclose(file);
    return headFileNode;
}

// 
// Generate a list node entry
// based on node
//
// This should only be called on the FinalPass
// when all symbols/macros are resolved
int GenerateListNode(parseNodePtr p)
{
    int col = 0;
    int bytes = 0;
    int len;
    char* curptr = InternalBuffer;
    const char* module = "GenerateListNode";

    // passing NULL will cause an empty node which forces a the
    // current file to listed even if no code is generated
    if (p == NULL)
    {
        if (AddList(CurFileName, yylineno, "") == NULL)
        {
            Error(module, ErrorCreatingListNode);
        }
        return 0;
    }

    // get the program counter
    // if the node is an opcode get the PC from the opcode itself
    // otherwise use PC
    int op = p->type == typeOpCode ? p->opcode.pc & 0xFFFF : PC & 0xFFFF;
    sprintf(curptr, "$%02X%02X:", ((op) >> 8), op & 0xFF);
    curptr += strlen(curptr);

    // generate a list node for a string
    if (p->type == typeStr)
    {
        char* strStart = NULL;
        char* str = p->str.value;
        int outLen = p->str.len;
        int pad = 0;
        while (outLen--)
        {
            // output the PC on column zero
            if (col == 0)
            {
                strStart = str;
                curptr = InternalBuffer;
                op = (PC + bytes) & 0xFFFF;
                sprintf(curptr, "$%02X%02X:", ((op) >> 8), op & 0xFF);
                curptr += strlen(curptr);							
            }

            col++;
            sprintf(curptr, " $%02X", *str & 0xFF);
            curptr += strlen(curptr);
            str++;
            bytes++;

            // at column 3 create a node and reset to column 0
            if (col == 3)
            {
                len = (int)strlen(InternalBuffer);
                while (len++ < SRC_LST_INDENT)
                {
                    *curptr++ = ' ';
                }
                sprintf(curptr, ".db ");
                curptr += strlen(curptr);
                for (len = 0; len < col; len++)
                {
                    if (len > 0)
                    {
                        sprintf(curptr, ", ");
                        curptr += strlen(curptr);
                    }
                    sprintf(curptr, "'%c'", strStart[len]);
                    curptr += strlen(curptr);
                }

                if (AddList(CurFileName, yylineno, InternalBuffer) == NULL)
                {
                    Error(module, ErrorCreatingListNode);
                    return 0;
                }
                col = 0;
            }
        }

        // if using a string with WORD then pad to a word boundary
        if (DataSize == 2 && p->str.len % 2)
        {
            col++;
            sprintf(curptr, " $%02X", *str & 0xFF);
            curptr += strlen(curptr);
            pad = 1;
        }

        // output final node
        if (col != 0)
        {
            len = (int)strlen(InternalBuffer);
            while (len++ < SRC_LST_INDENT)
            {
                *curptr++ = ' ';
            }
            sprintf(curptr, ".db ");
            curptr += strlen(curptr);
            for (len = 0; len < col; len++)
            {
                if (len > 0)
                {
                    sprintf(curptr, ", ");
                    curptr += strlen(curptr);
                }
                if (len == col -1 && pad)
                {
                    sprintf(curptr, "$%02X", strStart[len]);
                }
                else
                {
                    sprintf(curptr, "'%c'", strStart[len]);
                }
                curptr += strlen(curptr);
            }

            if (AddList(CurFileName, yylineno, InternalBuffer) == NULL)
            {
                Error(module, ErrorCreatingListNode);
                return 0;
            }
        }
        return bytes;
    }

    // output numeric value
    // DataSize contain number of bytes to output
    if (p->type != typeOpCode)
    {
        // expand the node
        op = Ex(p);

        const unsigned char hi = (unsigned char)((op & 0xFF00) >> 8);
        const unsigned char lo = (unsigned char)(op & 0xFF);

        // check for overflow
        if (hi != 0 && DataSize < 2)
        {
            // This error is reported in genoutput
            // we don't want duplicated errors
            // Error(module, ValueOutofRange);
            return 0;
        }

        // see if we can append to last node
        ListTablePtr curlistptr = ListHead;
        if (curlistptr)
        {
            while (curlistptr->next)
            {
                curlistptr = curlistptr->next;
            }
        }

        // output lo byte
        sprintf(curptr, " $%02X", lo);
        curptr += strlen(curptr);

        // output hi byte
        if (DataSize > 1)
        {
            sprintf(curptr, " $%02X", hi);
            curptr += strlen(curptr);
        }
        len = (int)strlen(InternalBuffer);
        while (len++ < SRC_LST_INDENT)
        {
            *curptr++ = ' ';
        }
        sprintf(curptr, ".db ");
        curptr += strlen(curptr);
        sprintf(curptr, "$%02X", lo);
        curptr += strlen(curptr);
        if (DataSize > 1)
        {
            sprintf(curptr, ", $%02X", hi);
            // ReSharper disable once CppAssignedValueIsNeverUsed
            curptr += strlen(curptr);
        }
        // add the node
        if (AddList(CurFileName, yylineno, InternalBuffer) == NULL)
        {
            Error(module, ErrorCreatingListNode);
            return 0;
        }
        return 0;
    }

    // output an opcode list node

    // get the opcode
    sprintf(curptr, " $%02X", p->opcode.opcode);
    curptr += strlen(curptr);

    // get number of bytes used by opcode
    bytes = GetOpByteCount(p);
    if (bytes > 0)
    {
        unsigned char hi;

        // expand the data
        op = Ex(p->op[0]);

        if (p->opcode.mode == zr)
        {            
            if (p->nops != 2)
            {
                Error(module, ErrorMissingParameter);
                return 0;
            }
            op = Ex(p->op[1]);

            // make sure a branch is in range
            op -= (p->opcode.pc + 2);               

            if (op > 128 || op < -127)
            {
                // This error is reported in genoutput
                // we don't want duplicated errors
                // Error(module, ValueOutofRange);
                return 0;
            }
            op &= 0xFF;
            sprintf(curptr, " $%02X", op);
            curptr += strlen(curptr);

            bytes = 1;
            op = Ex(p->op[0]);
            hi = (unsigned char)((op & 0xFF00) >> 8);
            // lo = (unsigned char)(op & 0xFF);
            if (hi != 0)
            {
                // This error is reported in genoutput
                // we don't want duplicated errors
                // Error(module, ValueOutofRange);
                return 0;
            }
        }

        // if relative mode check range
        else if (p->opcode.mode == r)
        {
            op -= (p->opcode.pc + 2);                       
            if (op > 128 || op < -127)
            {
                // This error is reported in genoutput
                // we don't want duplicated errors
                // Error(module, ValueOutofRange);
                return 0;
            }
            op &= 0xFF;
        }

        // get the hi and lo byte
        hi = (unsigned char)((op & 0xFF00) >> 8);
        const unsigned char lo = (unsigned char)(op & 0xFF);

        // output the lo byte
        sprintf(curptr, " $%02X", lo);
        curptr += strlen(curptr);

        // output hi byte if needed
        if (bytes > 1)
        {
            sprintf(curptr, " $%02X", hi);
            curptr += strlen(curptr);
        }
    }

    col = (int)strlen(InternalBuffer);
    while (col++ < SRC_LST_INDENT)
    {
        *curptr++ = ' ';
    }
    sprintf(curptr, "%s ", InstructionToString(p->opcode.instruction));
    curptr += strlen(curptr);
    if (bytes > 0 && (p->nops > 0))
    {
        int op2  = 0;

        op = Ex(p->op[0]);
        if (p->nops > 1)
        {
            op2 = Ex(p->op[1]);
        }
        // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
        switch (p->opcode.mode)
        {
            case i:      /* implied *           */
            case A:      /* Accumulator         */
                break;

            case I:      /* immediate           */
                sprintf(curptr, "#$%02X ", op);
                break;

            case zp:     /* zero page            */
                sprintf(curptr, "$%02X ", op);
                break;

            case zpi:    /* zero page indirect   */
                sprintf(curptr, "($%02X) ", op);
                break;

            case zpx:    /* zero page x          */
                sprintf(curptr, "$%02X,x ", op);
                break;

            case zpy:    /* zero page y          */
                sprintf(curptr, "$%02X,y ", op);
                break;

            case zpix:   /* zero page indirect x */
                sprintf(curptr, "($%02X,x) ", op);
                break;

            case zpiy:   /* zero page indirect y */
                sprintf(curptr, "($%02X),y ", op);
                break;

            case a:      /* absolute             */
                sprintf(curptr, "$%04X ", op);
                break;

            case aix:    /* absolute indirect x  */  // NOLINT(bugprone-branch-clone)
                sprintf(curptr, "$%04X,x ", op);
                break;

            case ax:     /* absolute x           */
                sprintf(curptr, "$%04X,x ", op);
                break;

            case ay:     /* absolute y           */
                sprintf(curptr, "$%04X,y ", op);
                break;

            case ind:    /* absolute indirect    */
                sprintf(curptr, "($%04X) ", op);
                break;

            case r:      /* relative             */
                sprintf(curptr, "$%04X ", op);
                break;

            case zr:     /* zero page relative   */
                sprintf(curptr, "$%02X,%02X ", op, op2);
                break;

        }
        // curptr += strlen(curptr);
    }

    // add the node
    if (AddList(CurFileName, yylineno, InternalBuffer) == NULL)
    {
        Error(module, ErrorCreatingListNode);
        return 0;
    }
    return bytes + 1;
}

/// <summary>
/// Add node to the ListTable.
/// </summary>
/// <param name="file">The name to add.</param>
/// <param name="line">The line number to add.</param>
/// <param name="output">The line number to add.</param>
/// <returns>int.</returns>
ListTablePtr AddList(char* file, const int line, char* output)
{
    const char* module = "AddList";

    // ReSharper disable once CppLocalVariableMayBeConst
    ListTablePtr varPtr = (ListTablePtr)malloc(sizeof(ListTable));
    if (varPtr == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    memset(varPtr, 0, sizeof(ListTable));

    varPtr->filename = StrDup(file);
    if (varPtr->filename == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    varPtr->line = line + 1;
    varPtr->output = StrDup(output);
    if (varPtr->output == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    ListTablePtr tmpPtr = ListHead;

    if (ListHead == NULL)
    {
        ListHead = varPtr;
        return varPtr;
    }

    while (tmpPtr->next != NULL)
        tmpPtr = tmpPtr->next;

    tmpPtr->next = varPtr;

    return varPtr;
}

//
// Generate the list file
//
void GenerateListFile(FILE* lstFile)
{
    // ReSharper disable once CppDeclaratorNeverUsed
    const char* module = "GenerateListFile";

    ListTablePtr listNode = ListHead;
    CurFileName = NULL;

    // loop through all list  nodes
    for (; listNode; listNode = listNode->next)
    {
        if (CurFileName == NULL || StrICmp(CurFileName, listNode->filename))
        {
            CurFileName = listNode->filename;
            fprintf(lstFile, "\nProcessing %s\n\n", CurFileName);
        }

        const int startLine = listNode->line;
        int endLine = startLine;
        if (listNode->next && StrICmp(listNode->filename, listNode->next->filename) == 0 && listNode->next->line > listNode->line)
            endLine = listNode->next->line - 1;

        FileLine* lst = GetFileLine(listNode->filename, startLine);
        if (lst == NULL)
            continue;

        InternalBuffer[0] = 0;
        if (lst->displayed == 0)
        {
            sprintf(InternalBuffer, "%-50s%s", listNode->output, lst->line);
            lst->displayed++;
        }
        else
        {
            sprintf(InternalBuffer, "%-50s\n", listNode->output);
        }
        fputs(InternalBuffer, lstFile);

        for (lst = lst->next;  lst && lst->lineNumber <= endLine; lst = lst->next)
        {
            InternalBuffer[0] = 0;
            sprintf(InternalBuffer, "%-50s", " ");
            fputs(InternalBuffer, lstFile);
            if (lst->displayed == 0)
            {
                fputs(lst->line, lstFile);
                lst->displayed++;
            }
            else
                fputs("\n", lstFile);
        }
    }
}

//
// Free the list table
void FreeListTable(void)
{    
    ListTablePtr tmpPtr = ListHead;

    for (; tmpPtr != NULL;)
    {
        if (tmpPtr->filename)
            free(tmpPtr->filename);

        if (tmpPtr->output)
            free(tmpPtr->output);

        // ReSharper disable once CppLocalVariableMayBeConst
        ListTablePtr nextNode = tmpPtr->next;
        free(tmpPtr);

        tmpPtr = nextNode;
    }
}
