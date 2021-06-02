// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
// ***********************************************************************

// ReSharper disable CppLocalVariableMayBeConst
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppClangTidyClangDiagnosticExtraSemiStmt
#pragma warning(disable:4996)
#pragma warning(disable:6385)
#pragma warning(disable:6386)

#include <stdio.h>
#include <stdarg.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <stdlib.h>
#include <string.h> 

#include "opcodes.h"
#include "pasm64.h"
#include "pasm64.tab.h"
#include "node.h"
#include "str.h"
#include "error.h"
#include "mem.h"
#include "symbol.h"

int NameIsValid(char* name);

/// <summary>
/// The head node
/// </summary>
ParseNodePtr HeadNode = 0;

/// <summary>
/// The current node
/// </summary>
ParseNodePtr CurrentNode = 0;

/// <summary>
/// The print nest level
/// </summary>
int PrintNestLevel = 0;

/// <summary>
/// Allocates the node.
/// </summary>
/// <returns>parseNode *.</returns>
ParseNodePtr AllocateNode(int nops)
{ 
    const char* module = "AllocateNode";

    ParseNodePtr p;
    size_t size = sizeof(ParseNode);
    if ((p = (ParseNode *)ALLOCATE(size)) == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    memset(p, 0, size);
    p->allocated = 1;
    if (CurrentNode != NULL)
    {
        p->prev = CurrentNode;
        CurrentNode->next = p;
    }
    CurrentNode = p;
    p->nops = nops;

    if (nops > 0)
    {
        size = nops * sizeof(ParseNodePtr);
        if ((p->op = (struct parse_node**)ALLOCATE(size)) == NULL)
        {
            FatalError(module, error_out_of_memory);
            return NULL;
        }
        memset(p->op, 0, size);
    }
    return p;
}

/// <summary>
/// adds a constant value
/// </summary>
/// <param name="value">The value.</param>
/// <param name="isPc"></param>
/// <returns>parseNode *.</returns>
ParseNodePtr Con(const int value, const int isPc) 
{
    const char* module = "con";

    ParseNodePtr p = AllocateNode(0);
    if (p == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    p->type = type_con;
    
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
ParseNodePtr Str(char* value) 
{
    const char* module = "str";

    ParseNodePtr p = AllocateNode(0);

    // char* str = StrDup(value);
    char* str = STR_DUP(value);

    if (str == NULL || p == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }

    p->type = type_str;
	p->str.allocated = str;
    p->str.len = (int)strlen(str);
    if (*str == '\'' || *str == '"')
    {
        str[p->str.len - 1] = 0;
        str++;
    }

    /* copy information */
    if (p->str.value)
        FREE(p->str.value);

    p->str.value = SantizeString(str);
    if (p->str.value == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    p->str.len = (int)strlen(p->str.value);

    return p;
}

ParseNodePtr IdNodeCommon(char* name, NodeEnum  nodeType)
{
    const char* module = "IdNodeCommon";

    /* allocate node */
    // ReSharper disable once CppLocalVariableMayBeConst
    ParseNodePtr p = AllocateNode(0);

    if (p == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }

    /* copy information */
    p->type = nodeType;
    p->id.name = name; // StrDup(name);
    if (p->id.name == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }
    return p;
}

/// <summary>
/// Identifier specified name.
/// </summary>
/// <param name="name">The name of symbol.</param>
/// <returns>parseNodePtr.</returns>
ParseNodePtr Id(char* name) 
{
    return IdNodeCommon(name, type_id);
}

/// <summary>
/// Identifier specified name.
/// </summary>
/// <param name="name">The name of symbol.</param>
/// <returns>parseNodePtr.</returns>
ParseNodePtr Label(char* name)
{
    if (name[0] != '@' && name[0] != '-' && name[0] != '+')
        LastLabel = name;
    else if (LastLabel != NULL && name[0] == '@')
    {
        name = FormatLocalSym(name, LastLabel);
    }
    return IdNodeCommon(name, type_label);
}

/// <summary>
/// Macro Identifier specified name.
/// </summary>
/// <param name="name">The id of symbol.</param>
/// <returns>parseNodePtr.</returns>
ParseNodePtr MacroId(char* name) 
{
    return IdNodeCommon(name, type_macro_id);
}

ParseNodePtr PrintState(int op)
{
    ParseNodePtr p = AllocateNode(0);
    p->type = type_print;
    p->pr.print_state = op;

    return p;
}

/// <summary>
/// Macro execution node
/// </summary>
/// <param name="name">macro to execute.</param>
/// <param name="macroParams">macro parameters.</param>
/// <returns>parseNodePtr.</returns>
ParseNodePtr MacroEx(char* name, ParseNodePtr macroParams) 
{
    // ReSharper disable once CppTooWideScope
    const char* module = "MacroEx";

    ParseNodePtr macro = MacroId(name);
    /* allocate node */
    ParseNodePtr p = AllocateNode(0);

    if (p == NULL || macro == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }

    /* copy information */
    p->type = type_macro_ex;
    p->macro.macro = macro;
    p->macro.name = name;
    p->macro.macro_params = macroParams;
  
    return p;
}

/// <summary>
/// adds a data node BYTE, WORD, STRING
/// </summary>
/// <param name="dataSize">size of data.</param>
/// <param name="data">macro parameters.</param>
/// <returns>parseNodePtr.</returns>
ParseNodePtr Data(const int dataSize, ParseNodePtr data) 
{
    const char* module = "data";

    /* allocate node */
    ParseNodePtr p = AllocateNode(0);

    if (p == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }

    /* copy information */
    p->type = type_data;
    p->data.size = dataSize;
    p->data.data = data;

    return p;
}

/// <summary>
/// Operator.
/// </summary>
/// <param name="op">The operator.</param>
/// <param name="nops">The number of ops.</param>
/// <param name="...">...</param>
/// <returns>parseNodePtr.</returns>
ParseNodePtr Opr(int op, int nops, ...) 
{
    va_list ap;
    const char* module = "opr";

    /* allocate node */
    ParseNodePtr p = AllocateNode(nops);
    if (p == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }

    /* copy information */
    p->type = type_opr;
    p->opr.oper = op;

    if (nops > 0)
    {
        va_start(ap, nops);
        for (int i = 0; i < nops; i++)
            p->op[i] = va_arg(ap, ParseNodePtr);
        va_end(ap);
    }

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
ParseNodePtr Opcode(int opr, int mode, int nops, ...) 
{
    va_list ap;
    int index;
    const char* module = "opcode";

    ParseNodePtr p = AllocateNode(nops);

    if (p == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }

    p->type = type_op_code;

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
    p->opcode.mode = mode;
    p->opcode.instruction = opr;

    if (nops > 0)
    {
        va_start(ap, nops);
        for (index = 0; index < nops; index++)
            p->op[index] = va_arg(ap, ParseNodePtr);
        va_end(ap);
    }
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
        Error(module, error_invalid_opcode_or_mode);
    }

    return p;
}

/// <summary>
/// Frees the tree.
/// </summary>
void FreeParseTree(void)
{
    for (ParseNodePtr p = HeadNode; p != NULL;)
    {
        ParseNodePtr next = p->next;
        FreeParseNode(p);
        p = next;
    }
    HeadNode = CurrentNode = NULL;
}

//
// Print indent
//
void PrintIndent(void)
{
    for (int index = 0; index < PrintNestLevel; index++)
        fprintf(LogFile, "    ");
}

int IsValidParseTree(void)
{
    for (ParseNodePtr p = HeadNode; p; p = p->next)
    {
        if (!IsValidParseNode(p))
            return 0;
    }
    return 1;
}

int IsValidParseNode(ParseNodePtr p)
{
    if (p == NULL) return 0;

    if (p->type < type_head_node || p->type > type_str)
        return 0;

    for (int i = 0; i < p->nops; i++)
    {
        if (!IsValidParseNode(p->op[i]))
            return 0;
    }

    return 1;
}

size_t Count = 0;
int LastPass = 0;
// 
// free a node
//
void FreeParseNode(ParseNodePtr p)
{
    if (p == NULL) return;

    if (p->allocated)
    {
        if (p->type == type_str)
        {
            FREE(p->str.value);
        }

        if ((p->type == type_id || p->type == type_macro_id) && p->id.name)
        {
            if (NameIsValid(p->id.name))
            {
                if (LastPass != Pass)
                {
                    Count = 1;
                    LastPass = Pass;
                }
                FREE(p->id.name);
                ++Count;
            }
        }
        if (p->nops > 0)
        {
            FREE(p->op);
        }
        FREE(p);
    }
}

int NameIsValid(char* name)
{
    if (name == NULL) return 0;
    
    for (; *name; name++)
    {
        char c = *name;
        if ((c != '+' && c != '-' && c != '@') && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || c == '\\'))
            continue;

        return 0;
    }
    return 1;
}

//
// Print a node
//
void PrintNode(ParseNodePtr p)
{
    if (LogFile == NULL || p == NULL)
        return;

    // ReSharper disable once CppTooWideScope
    int index;

    PrintIndent();
    if (PrintNestLevel > 0)
        fprintf(LogFile, "CHILD ");
    fprintf(LogFile, "NODE [line %d]\n", yylineno);
    PrintNestLevel++;
    // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
    // ReSharper disable once CppIncompleteSwitchStatement
    switch (p->type)  // NOLINT(clang-diagnostic-switch)
    {
        case type_unknown:
            PrintIndent();
            fprintf(LogFile, "type %s\n", "type_unknown");
            PrintIndent();
            break;

        case type_id:
        case type_macro_id:
        case type_label:
            PrintIndent();
            switch (p->type)  // NOLINT(clang-diagnostic-switch-enum)
            {
            case type_id:
                fprintf(LogFile, "type %s\n", "type_id");
                break;

            case type_label:
                fprintf(LogFile, "type %s\n", "type_label");
                break;

            case type_macro_id:
                fprintf(LogFile, "type %s\n", "type_macro_id");
                break;

            default:
                break;
            }
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
                fprintf(LogFile, "     macroNode    %p\n", p->id.i->macro_node);
                PrintIndent();
                fprintf(LogFile, "     scope      %s\n", p->id.i->scope ? p->id.i->scope : "NULL");
                PrintIndent();
                fprintf(LogFile, "     name         %s\n", p->id.i->name);
            }
            break;

        case type_macro_ex:
            break;

        case type_opr:
            PrintIndent();
            fprintf(LogFile, "type typeOpr\n");
            switch (p->opr.oper)
            {
                case INC:
                    PrintIndent();
                    fprintf(LogFile, "opr INC\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

                case LOAD:
                    PrintIndent();
                    fprintf(LogFile, "opr LOAD\n");
                    for (index = 0; index < p->nops; index++)
                        PrintNode(p->op[index]);
                    break;

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

        case type_op_code:
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

        case type_con:
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

        case type_data:
            PrintIndent();
            fprintf(LogFile, "type typeData\n");
            PrintIndent();
            fprintf(LogFile, "size %d\n", p->data.size);
            PrintNode((ParseNodePtr) p->data.data);
            for (index = 0; index < p->nops; index++)
                PrintNode(p->op[index]);
            break;

        case type_str:
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
