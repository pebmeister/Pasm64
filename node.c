// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
// ***********************************************************************

// ReSharper disable CppLocalVariableMayBeConst
// ReSharper disable CppParameterMayBeConst
#pragma warning(disable:4996)
#pragma warning(disable:6385)
#pragma warning(disable:6386)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h> 
#include <ctype.h>

#include "opcodes.h"
#include "pasm64.h"
#include "pasm64.tab.h"
#include "node.h"
#include "str.h"
#include "error.h"

/// <summary>
/// The head node
/// </summary>
parseNodePtr HeadNode = 0;

/// <summary>
/// The current node
/// </summary>
parseNodePtr CurrentNode = 0;

/// <summary>
/// The print nest level
/// </summary>
int PrintNestLevel = 0;

/// <summary>
/// Allocates the node.
/// </summary>
/// <returns>parseNode *.</returns>
parseNodePtr AllocateNode(void)
{
    const char* module = "AllocateNode";

    parseNodePtr p;
    const size_t size = sizeof(parseNode);
    if ((p = (parseNode *) malloc(size)) == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    memset(p, 0, size);

    p->prev = CurrentNode;
    CurrentNode->next = p;
    CurrentNode = p;
    return p;
}

/// <summary>
/// adds a constant value
/// </summary>
/// <param name="value">The value.</param>
/// <param name="isPc"></param>
/// <returns>parseNode *.</returns>
parseNodePtr Con(const int value, const int isPc) 
{
    const char* module = "con";

    parseNodePtr p = AllocateNode();
    if (p == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    p->type = typeCon;
    
    /* copy information */
    p->con.value = value;
    p->con.IsPC = isPc;
    if (p->con.IsPC)
        p->con.value = PC;

    return p;
}

//
// create a string node
//
parseNodePtr Str(char* value) 
{
    const char* module = "str";
    parseNodePtr p = AllocateNode();
	char* str = Strdup(value);	

    if (str == NULL || p == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    p->type = typeStr;
	p->str.allocated = str;
	
    str[strlen(str)-1] = 0;
	str++;
		    
    /* copy information */
    p->str.value = SantizeString(str, &p->str.len);
    if (p->str.value == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    return p;
}

/// <summary>
/// Identifier specified name.
/// </summary>
/// <param name="name">The name of symbol.</param>
/// <returns>parseNodePtr.</returns>
parseNodePtr Id(char* name) 
{
    const char* module = "id";

    /* allocate node */
    // ReSharper disable once CppLocalVariableMayBeConst
    parseNodePtr p = AllocateNode();

    if (p == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    /* copy information */
    p->type = typeId;
    p->id.name = Strdup(name);
    if (p->id.name == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    return p;
}

/// <summary>
/// Macro Identifier specified name.
/// </summary>
/// <param name="name">The id of symbol.</param>
/// <returns>parseNodePtr.</returns>
parseNodePtr MacroId(char* name) 
{
    const char* module = "MacroId";

    /* allocate node */
    parseNodePtr p = AllocateNode();

    if (p == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    /* copy information */
    p->type = typeMacroId;
    p->id.name = Strdup(name);
    if (p->id.name == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    
    return p;
}

/// <summary>
/// Macro execution node
/// </summary>
/// <param name="name">macro to execute.</param>
/// <param name="macroParams">macro parameters.</param>
/// <returns>parseNodePtr.</returns>
parseNodePtr MacroEx(char* name, parseNodePtr macroParams) 
{
    const char* module = "MacroEx";

    parseNodePtr macro = MacroId(name);
    /* allocate node */
    parseNodePtr p = AllocateNode();

    if (p == NULL || macro == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    /* copy information */
    p->type = typeMacroEx;
    p->macro.macro = macro;
    p->macro.macroParams = macroParams;

    return p;
}

/// <summary>
/// adds a data node BYTE, WORD, STRING
/// </summary>
/// <param name="dataSize">size of data.</param>
/// <param name="data">macro parameters.</param>
/// <returns>parseNodePtr.</returns>
parseNodePtr Data(const int dataSize, parseNodePtr data) 
{
    const char* module = "data";
    /* allocate node */
    parseNodePtr p = AllocateNode();

    if (p == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    /* copy information */
    p->type = typeData;
    p->data.size = dataSize;
    p->data.data = data;

    return p;
}

/// <summary>
/// Operator.
/// </summary>
/// <param name="op">The operator.</param>
/// <param name="nops">The number of ops.</param>
/// <param name="...">The .</param>
/// <returns>parseNodePtr.</returns>
parseNodePtr Opr(int op, int nops, ...) 
{
    va_list ap;
    const char* module = "opr";

    /* allocate node */
    parseNodePtr p = AllocateNode();
    if (p == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    const size_t size = nops * sizeof(parseNodePtr);
    if ((p->op = (struct parseNode **) malloc(size)) == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    /* copy information */
    p->type = typeOpr;
    p->opr.oper = op;
    p->nops = nops;
    va_start(ap, nops);
    for (int i = 0; i < nops; i++)
        p->op[i] = va_arg(ap, parseNodePtr);
    va_end(ap);

    return p;
}

/// <summary>
/// Opcodes
/// </summary>
/// <param name="opr">The operator.</param>
/// <param name="mode">The mode.</param>
/// <param name="nops">The number of ops.</param>
/// <param name="..."></param>
/// <returns>parseNode *.</returns>
parseNodePtr Opcode(int opr, int mode, int nops, ...) 
{
    va_list ap;
    int index;
    const char* module = "opcode";

    parseNodePtr p = AllocateNode();

    if (p == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    const size_t size = nops * sizeof(parseNode*);
    if ((p->op = (struct parseNode **) malloc(size)) == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }

    switch (opr) 
    {   
        case _bra:
        case _bcc:
        case _bcs:
        case _beq:
        case _bmi:
        case _bne:
        case _bpl:
        case _bvc:
        case _bvs:
            mode = r;            
            break;

        default:
            break;
    }

    /* copy information */    
    p->type = typeOpCode;
    p->opcode.mode = mode;
    p->opcode.instruction = opr;
    p->nops = nops;
    va_start(ap, nops);
    for (index = 0; index < nops; index++)
        p->op[index] = va_arg(ap, parseNode*);
    va_end(ap);

    int code = GetOpCode(opr, mode);
    if (code == -1)
    {
        int newMode = mode;
        switch (mode)
        {
            case r:     /* relative             */
            case zr:    /* zero page relative   */
            case A:     /* Accumulator          */
            case I:     /* immediate            */
            case i:     /* implied              */
            case zp:    /* zero page            */
            case zpi:   /* zero page indirect   */
            case zpx:   /* zero page x          */
            case zpy:   /* zero page y          */
            case zpix:  /* zero page indirect x */
            case zpiy:  /* zero page indirect y */                    
                break;

            case a:     /* absolute             */
                newMode = zp;
                break;

            case aix:   /* absolute indirect x  */
                newMode = zpix;
                break;

            case ax:    /* absolute x           */
                newMode = zpx;
                break;

            case ay:    /* absolute y           */
                newMode = zpy;
                break;

            case ind:   /* absolute indirect    */
                newMode = zpi;
                break;

            default:
                break;
        }
        code = GetOpCode(opr, newMode);
        if (code != 0)
        {
            p->opcode.mode = newMode;
        }

    }
    for (index = 0; index < nops; index++)
    {
        Ex(p->op[index]);
    }    

    p->opcode.opcode = code;
    if (code < 0)
    {
        Error(module, ErrorInvalidOpcodeOrMode);
    }
    
    return p;
}

/// <summary>
/// Frees the tree.
/// </summary>
void FreeTree(void)
{
    CurrentNode = HeadNode;
    while (CurrentNode != NULL) 
    {
        parseNodePtr p = CurrentNode->next;
        FreeNode(CurrentNode);
        CurrentNode = p;
    }
    HeadNode = NULL;
}


//
// Print indent
//
void PrintIndent(void)
{
    for (int index = 0; index < PrintNestLevel; index++)
        fprintf(LogFile, "    ");
}

//
// Print a node
//
void PrintNode(parseNodePtr p)
{
    int index;
    if (LogFile == NULL)
        return;

    PrintIndent();
    if (PrintNestLevel > 0)
        fprintf(LogFile, "CHILD ");
    fprintf(LogFile, "NODE [line %d]\n", yylineno);
    PrintNestLevel++;
    switch (p->type)
    {
        case typeId:
        case typeMacroId:
            PrintIndent();
            fprintf(LogFile, "type %s\n", p->type == typeId ? "typeId" : "typeMacroId");
            PrintIndent();
            fprintf(LogFile, "name %s\n", p->id.name);
            PrintIndent();
            fprintf(LogFile, "i    %p\n", (void*)p->id.i);
            if (p->id.i)
            {
                PrintIndent();
                fprintf(LogFile, "     fullname     %s\n", p->id.i->fullname);
                PrintIndent();
                fprintf(LogFile, "     initialized  %d\n", p->id.i->initialized);
                PrintIndent();
                fprintf(LogFile, "     value        %d\n", p->id.i->value);
                PrintIndent();
                fprintf(LogFile, "     ismacroname  %d\n", p->id.i->ismacroname);
                PrintIndent();
                fprintf(LogFile, "     ismacroparam %d\n", p->id.i->ismacroparam);
                PrintIndent();
                fprintf(LogFile, "     isvar        %d\n", p->id.i->isvar);
                PrintIndent();
                fprintf(LogFile, "     macroNode    %p\n", p->id.i->macroNode);
                PrintIndent();
                fprintf(LogFile, "     section      %s\n", p->id.i->section ? p->id.i->section : "NULL");
                PrintIndent();
                fprintf(LogFile, "     name         %s\n", p->id.i->name);
            }
            break;

        case typeMacroEx:
            break;

        case typeOpr:
            PrintIndent();
            fprintf(LogFile, "type typeOpr\n");
            switch (p->opr.oper)
            {
                case LOBYTE:
                    PrintIndent();
                    fprintf(LogFile, "opr LOBYTE\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case HIBYTE:
                    PrintIndent();
                    fprintf(LogFile, "opr HIBYTE\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case PCASSIGN:
                    PrintIndent();
                    fprintf(LogFile, "opr PCASSIGN\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case ORG:
                    PrintIndent();
                    fprintf(LogFile, "opr ORG\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case EXPRLIST:
                    PrintIndent();
                    fprintf(LogFile, "opr EXPRLIST\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case MACRO:
                    PrintIndent();
                    fprintf(LogFile, "opr MACRO\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case WHILE:
                    PrintIndent();
                    fprintf(LogFile, "opr WHILE\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case REPEAT:
                    PrintIndent();
                    fprintf(LogFile, "opr REPEAT\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case SECTION:
                    PrintIndent();
                    fprintf(LogFile, "opr SECTION\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case ENDSECTION:
                    PrintIndent();
                    fprintf(LogFile, "opr ENDSECTION\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case DO:
                    PrintIndent();
                    fprintf(LogFile, "opr DO\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case FOR:
                    PrintIndent();
                    fprintf(LogFile, "opr FOR\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case REGX:
                    PrintIndent();
                    fprintf(LogFile, "opr REGX\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case REGY:
                    PrintIndent();
                    fprintf(LogFile, "opr REGY\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case IF:
                    PrintIndent();
                    fprintf(LogFile, "opr IF\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case PRINT:
                    PrintIndent();
                    fprintf(LogFile, "opr PRINT\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case DS:
                    PrintIndent();
                    fprintf(LogFile, "opr DS\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case STATEMENT:
                    PrintIndent();
                    fprintf(LogFile, "opr STATEMENT\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case END:
                    PrintIndent();
                    fprintf(LogFile, "opr END\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case EQU:
                    PrintIndent();
                    fprintf(LogFile, "opr EQU\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '=':
                    PrintIndent();
                    fprintf(LogFile, "opr '='\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case UMINUS:
                    PrintIndent();
                    fprintf(LogFile, "opr UMINUS\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '~':
                    PrintIndent();
                    fprintf(LogFile, "opr '~'\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '+':
                    PrintIndent();
                    fprintf(LogFile, "opr '+'\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '-':
                    PrintIndent();
                    fprintf(LogFile, "opr '-'\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '*':
                    PrintIndent();
                    fprintf(LogFile, "opr '*'\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '/':
                    PrintIndent();
                    fprintf(LogFile, "opr '/'\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case BIT_OR:
                    PrintIndent();
                    fprintf(LogFile, "opr BIT_OR\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case BIT_AND:
                    PrintIndent();
                    fprintf(LogFile, "opr BIT_AND\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '^':
                    PrintIndent();
                    fprintf(LogFile, "opr '^'\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '<':
                    PrintIndent();
                    fprintf(LogFile, "opr '<'\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case '>':
                    PrintIndent();
                    fprintf(LogFile, "opr '>'\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case EQ:
                    PrintIndent();
                    fprintf(LogFile, "opr EQ\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case NE:
                    PrintIndent();
                    fprintf(LogFile, "opr NE\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case GE:
                    PrintIndent();
                    fprintf(LogFile, "opr GE\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case LE:
                    PrintIndent();
                    fprintf(LogFile, "opr LE\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case OR:
                    PrintIndent();
                    fprintf(LogFile, "opr OR\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case AND:
                    PrintIndent();
                    fprintf(LogFile, "opr AND\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case NOT:
                    PrintIndent();
                    fprintf(LogFile, "opr NOT\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case SHIFT_LEFT:
                    PrintIndent();
                    fprintf(LogFile, "opr SHIFT_LEFT\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case SHIFT_RIGHT:
                    PrintIndent();
                    fprintf(LogFile, "opr SHIFT_RIGHT\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                default:
                    break;
            }
            break;

        case typeOpCode:
            PrintIndent();
            fprintf(LogFile, "type typeOpCode\n");
            PrintIndent();
            fprintf(LogFile, "instruction   %s\n", InstructionToString(p->opcode.instruction));
            PrintIndent();
            fprintf(LogFile, "mode          %s\n", ModeToString(p->opcode.mode));
            PrintIndent();
            fprintf(LogFile, "opCode        %2.2X\n", p->opcode.opcode);
            PrintIndent();
            fprintf(LogFile, "PC            0x%8.8X\n", p->opcode.pc);
            for (index = 0; index < p->nops; index++)
                PrintNode(p->op[index]);
            break;

        case typeCon:
            PrintIndent();
            fprintf(LogFile, "type typeCon\n");
            PrintIndent();
            fprintf(LogFile, "IsPC  %d", p->con.IsPC);
            if (p->con.IsPC)
                    fprintf(LogFile, "     PC = %8.8X",PC);
            fprintf(LogFile, "\n");
            PrintIndent();
            fprintf(LogFile, "value 0x%8.8X", p->con.value);
            for (index = 0; index < p->nops; index++)
                PrintNode(p->op[index]);
            break;

        case typeData:
            PrintIndent();
            fprintf(LogFile, "type typeData\n");
            PrintIndent();
            fprintf(LogFile, "size %d\n", p->data.size);
            PrintNode((parseNodePtr) p->data.data);
            for (index = 0; index < p->nops; index++)
                PrintNode(p->op[index]);
            break;

        case typeStr:
            PrintIndent();
            fprintf(LogFile, "type typeStr\n");
            PrintIndent();
            fprintf(LogFile, "allocated  %s\n", p->str.allocated);
            PrintIndent();
            fprintf(LogFile, "len        0x%8.8X\n", p->str.len);
            PrintIndent();
            fprintf(LogFile, "value %s\n", p->str.value);
            for (index = 0; index < p->nops; index++)
                PrintNode(p->op[index]);
            break;
    }
    
    fprintf(LogFile, "\n");
    PrintNestLevel--;
}

// 
// free a node
//
void FreeNode(parseNodePtr p)
{
    if (p->prev)
        p->prev->next = p->next;
    if (p->next)
        p->next->prev = p->prev;

    switch (p->type)
    {
        case typeMacroId:
        case typeId:
            free(p->id.name);
            break;

        case typeMacroEx:
        case typeOpr:
        case typeOpCode:
        case typeCon:
        case typeData:
            break;

        case typeStr:
            free(CurrentNode->str.allocated);
            free(CurrentNode->str.value);
            break;

    }
    memset(p, 0, sizeof(parseNode));
    free(p);
}

//
// return a string that expands escape sequences
//
char* SantizeString(char* str, int* outlen)
{	
    int outputLen = 0;
    const int len = (int)strlen(str) + 1;
    char* outStr = (char*) malloc(len);
    char* tmpStr = outStr;
    unsigned char esc_char = 0;
    const char* module = "SantizeString";

    if (outStr == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    memset(outStr, 0, len); 

    if (str == NULL)
    {
        Error(module, ErrorSourceStringNull);
        return NULL;
    }

    while (*str)
    {
        if (*str == '\\')
        {
            switch(tolower(*(++str)))
            {
                case 'a':
                    esc_char = '\a';
                    break;

                case 'b':
                    esc_char = '\b';
                    break;

                case 'f':
                    esc_char = '\f';
                    break;

                case 'v':
                    esc_char = '\v';
                    break;

                case 'r':
                    esc_char = '\r';
                    break;

                case 'n':
                    esc_char = '\n';
                    break;

                case 't':
                    esc_char = '\t';
                    break;

                case 'x':
                    str++;
                    if (*str == 0)
                    {
                        Error(module, ErrorUnrecognizedEscapeSequence);
                        break;                                      
                    }
                    while (isxdigit((unsigned char)*str) && isxdigit((unsigned char)*(str+1)))
                    {
                        char temp[3] = { 0 };
                        temp[0] = *str;
                        temp[1] = *(str + 1);
                        *tmpStr++ = (char)(int) strtol (temp, NULL, 16);
                        outputLen ++;
                        str += 2;
                    }
                    continue;

                case '\'':
                case '\"':
                case '\\':
                    esc_char = *str;		
                    break;

                default:
                    esc_char = '?';
                    Error(module, ErrorUnrecognizedEscapeSequence);
                    break;                                      
            }
            *tmpStr++ = (char)esc_char;
            outputLen++;
            str++;
        }
        else
        {
            *tmpStr++ = *str++;		
            outputLen++;
        }
    }
    *tmpStr = 0;
    *outlen = outputLen;
    return outStr;
}