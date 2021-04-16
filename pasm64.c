// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
// ***********************************************************************

// ReSharper disable CppClangTidyMiscMisplacedConst
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pasm64.h"
#include "node.h"
#include "symbol.h"
#include "opcodes.h"
#include "pasm64.tab.h"
#include "genlist.h"
#include "genoutput.h"
#include "str.h"
#include "error.h"
#include "file.h"

#ifndef INT16_MAX
#define INT16_MAX 32767
#endif

// for 6502 and 65C02
int MaxAddress = 0xFFFF;

// number of symbols whose values changed
int SymbolValueChanged = 0;

// nest level of ex();
int ExLevel = 0;

//
// how to expand an expression
//
// ReSharper disable once CppInconsistentNaming
enum ExprExpansionType
{
    macro_parameter,
    data_byte,
    data_string,
    print,
    print_all,
    symbol
};

//
// function pointer to expand node
//
typedef int (*Expr)(parseNodePtr p);

//
// table lookup for operators
//
struct OpTable
{
    int tag;
    Expr function;
};

//
// table for FOR REGX REGY
const int Cmp[] =
{
    _cpy,
    _cpx
};
const int Ld[] =
{
    _ldy,
    _ldx
};
const int Inc[] =
{
    _iny,
    _inx
};
const int Dec[] =
{
    _dey,
    _dex
};

#define CHECK_OPS(mn, mx) if (ExLevel == 1) LOG(method,p); \
    if ((p->nops < (mn)) || (p->nops >(mx))) FatalError(method, error_invalid_number_of_ops); \
    if (PC > MaxAddress) FatalError(method, error_program_counter_out_of_range)

char* CurrentSection = NULL;

// functions to determine if a symbol is defined
int IsUnInitializedSymbol(parseNodePtr p);

// 
// function prototypes
//
int ExConstant(parseNodePtr p);
int ExSymbol(parseNodePtr p);
int ExMacroExpansion(parseNodePtr p);
int ExMacroSymbol(parseNodePtr p);
int ExData(parseNodePtr p);
int ExOpCode(parseNodePtr p);
int ExOperator(parseNodePtr p);
int ExOprLoByte(parseNodePtr p);
int ExOprHiByte(parseNodePtr p);
int ExOprPcAssign(parseNodePtr p);
int ExOprOrg(parseNodePtr p);
int ExOprExpressionList(parseNodePtr p);
int ExOprMacroDefinition(parseNodePtr p);
int ExOprWhile(parseNodePtr p);
int ExOprRepeat(parseNodePtr p);
int ExOprDo(parseNodePtr p);
int ExOprFor(parseNodePtr p);
int ExOprIf(parseNodePtr p);
int ExOprPrint(parseNodePtr p);
int ExOprPrintAll(parseNodePtr p);
int ExOprDs(parseNodePtr p);
int ExOprStatement(parseNodePtr p);
int ExOprEnd(parseNodePtr p);
int ExOprEqu(parseNodePtr p);
int ExOprUMinus(parseNodePtr p);
int ExOprOnesComp(parseNodePtr p);
int ExOprPlus(parseNodePtr p);
int ExOprMinus(parseNodePtr p);
int ExOprMultiply(parseNodePtr p);
int ExOprDivide(parseNodePtr p);
int ExOprBitOr(parseNodePtr p);
int ExOprBitAnd(parseNodePtr p);
int ExOprXor(parseNodePtr p);
int ExOprLessThan(parseNodePtr p);
int ExOprGreaterThan(parseNodePtr p);
int ExOprOr(parseNodePtr p);
int ExOprAnd(parseNodePtr p);
int ExOprEqual(parseNodePtr p);
int ExOprNotEqual(parseNodePtr p);
int ExOprGreaterThanOrEqual(parseNodePtr p);
int ExOprLessThanOrEqual(parseNodePtr p);
int ExOprShiftLeft(parseNodePtr p);
int ExOprShiftRight(parseNodePtr p);
int ExOprNot(parseNodePtr p);
int ExOprForReg(parseNodePtr p);
int ExOprSection(parseNodePtr p);
int ExOprEndSection(parseNodePtr p);
int ExOprVar(parseNodePtr p);
int ExOprInclude(parseNodePtr p);
int ExOprLoad(parseNodePtr p);

//
// Program Counter
//
// ReSharper disable once CppInconsistentNaming
int PC = 0;

//
// End flag
int End = 0;

//
// number of bytes in data
// 0 = string
int DataSize = 1;

//
// MacroParameterIndex Index
//
int MacroParameterIndex = 0;

//
// flag to check if Org specified more than once
int OriginSpecified = 0;

//
// flag to unroll loops
// always true for now
//
int UnRollLoop = TRUE;

//
// Count nest level for FORX
//
int ForXCount = 0;

//
// Count nest level for FORY
//
int ForYCount = 0;

//
// node to inject a byte
//
parseNodePtr GenByteNode = NULL;

//
// expansion type for expressions
//
enum ExprExpansionType ExpansionType = macro_parameter;

//
// function table for 
// operator expansion
//
struct OpTable ExOprTable [] =
{
    { LOBYTE,       ExOprLoByte             },
    { HIBYTE,       ExOprHiByte             },
    { PCASSIGN,     ExOprPcAssign           },
    { ORG,          ExOprOrg                },
    { EXPRLIST,     ExOprExpressionList     },
    { MACRO,        ExOprMacroDefinition    },
    { WHILE,        ExOprWhile              },
    { REPEAT,       ExOprRepeat             },
    { SECTION,      ExOprSection            },
    { ENDSECTION,   ExOprEndSection         },
    { DO,           ExOprDo                 },
    { FOR,          ExOprFor                },
    { REGX,         ExOprForReg             },
    { REGY,         ExOprForReg             },
    { IF,           ExOprIf                 },
    { PRINT,        ExOprPrint              },
    { PRINTALL,     ExOprPrintAll           },
    { DS,           ExOprDs                 },
    { STATEMENT,    ExOprStatement          },
    { END,          ExOprEnd                },
    { EQU,          ExOprEqu                },
    { '=',          ExOprEqu                },
    { UMINUS,       ExOprUMinus             },
    { '~',          ExOprOnesComp           },
    { '+',          ExOprPlus               },
    { '-',          ExOprMinus              },
    { '*',          ExOprMultiply           },
    { '/',          ExOprDivide             },
    { BIT_OR,       ExOprBitOr              },
    { BIT_AND,      ExOprBitAnd             },
    { '^',          ExOprXor                },
    { '<',          ExOprLessThan           },
    { '>',          ExOprGreaterThan        },
    { EQ,           ExOprEqual              },
    { NE,           ExOprNotEqual           },
    { GE,           ExOprGreaterThanOrEqual },
    { LE,           ExOprLessThanOrEqual    },
    { OR,           ExOprOr                 },
    { AND,          ExOprAnd                },
    { NOT,          ExOprNot                },
    { SHIFT_LEFT,   ExOprShiftLeft          },
    { SHIFT_RIGHT,  ExOprShiftRight         },    
    { VAR,          ExOprVar                },
    { INC,          ExOprInclude            },
    { LOAD,         ExOprLoad               },
};
#define NUM_OPR_EXP (sizeof(ExOprTable) / sizeof(struct OpTable))

//
// function table for node expansion
//
struct OpTable ExTable[] =
{
    { type_con,      ExConstant              },
    { type_id,       ExSymbol                },
    { type_macro_id,  ExMacroSymbol           },
    { type_macro_ex,  ExMacroExpansion        },
    { type_data,     ExData                  },
    { type_op_code,   ExOpCode                },
    { type_opr,      ExOperator              }
};
#define NUM_EX_EXP (sizeof(ExTable) / sizeof(struct OpTable))

//
// Compare function for qsort
//
int OpCmpfunc (const void * a, const void * b)
{
    return ((const struct OpTable*)a)->tag - ((const struct OpTable*)b)->tag;
}

// 
// Init Ex
// sort tables
//
void InitEx(void)
{
    qsort(&ExOprTable, NUM_OPR_EXP, sizeof(struct OpTable), OpCmpfunc);
    qsort(&ExTable, NUM_EX_EXP, sizeof(struct OpTable), OpCmpfunc);
}

int PlusMinusSymNameIsValid(char* name)
{
    if (name == NULL) return 0;
    if (name[0] != '-' && name[0] != '+') return 0;

    for (char* ptr = name; *ptr; ++ptr)
        if (name[0] != *ptr)
            return 0;
    return -1;
}

//
// search a an entry in a table
//
struct OpTable* BSearch(const int search, struct OpTable* table, const int size)
{
    int first = 0;
    int last = size - 1;

    while (first <= last) 
    {
        const int middle = (first + last)/2;

        if (table[middle].tag < search)
            first = middle + 1;    
        else if (table[middle].tag == search) 
            return &table[middle];
        else
            last = middle - 1;

    }
    if (first > last)
        return NULL;

    return table;
}

//
// constant node
//
int ExConstant(parseNodePtr p)
{
    const char* method = "ExConstant";
    CHECK_OPS(0, 0);

    if (p->con.IsPC)
    {
        if (p->con.value != PC)
        {
            SymbolValueChanged++;
            p->con.value = PC;
        }
    }
    return p->con.value;
}

int ExOprInclude(parseNodePtr p)
{
    const char* method = "ExOprInclude";
    CHECK_OPS(1, 1);

    char* file = p->op[0]->str.value;

    OpenIncludeFile(file);

    return 1;
}

int ExOprLoad(parseNodePtr p)
{
    const char* method = "ExOprLoad";
    CHECK_OPS(1, 1);

    char* file = p->op[0]->str.value;
    FILE* fd = OpenFile(file, "rb");
    if (fd == NULL)
    {
        FatalError(method, error_opening_input_file);
    }

    fseek(fd, 0, SEEK_END);
    const size_t len = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    size_t pos = ftell(fd);

    while (!feof(fd) && len - pos > 0)
    {
        pos = ftell(fd);
        if (len - pos > 1)
        {
            const unsigned char a = (unsigned char)fgetc(fd);
            const unsigned char b = (unsigned char)fgetc(fd);

            DataSize = 2;
            Ex(Data(DataSize, Opr(EXPRLIST, 1, Con(((a | b << 8) & 0xFFFF), 0))));
            continue;
        }
        if (len - pos > 0)
        {
            DataSize = 1;
            const unsigned char ch = (unsigned char)fgetc(fd);
            Ex(Data(DataSize, Opr(EXPRLIST, 1, Con(ch, 0))));
        }
        pos = ftell(fd);
    }
    fclose(fd);
    return 1;
}

//
// Variable
//
int ExOprVar(parseNodePtr p)
{
    const char* method = "ExOprVar";

    CHECK_OPS(1, 2);

    const parseNodePtr pp = p->op[0];
    if (pp)
    {
        ExpansionType = symbol;
        return Ex(pp);
    }
    Error(method, error_invalid_parameters);
    return 0;
}

//
// symbol
//
int ExSymbol(parseNodePtr p)
{
    const char* method = "ExSymbol";

    CHECK_OPS(0, 0);

    if (p->id.name[0] == '-')
    {
        if (!PlusMinusSymNameIsValid(p->id.name))
        {
            Error(method, error_adding_symbol);
            return 0;
        }

        const int index = FindMinusSym((int)strlen(p->id.name), CurFileName, yylineno);
        if (index >= 0)
            return MinusSymTable[index].value;

        return 0;
    }

    if (p->id.name[0] == '+')
    {
        if (!PlusMinusSymNameIsValid(p->id.name))
        {
            Error(method, error_adding_symbol);
            return 0;
        }

        const int index = FindPlusSym((int)strlen(p->id.name), CurFileName, yylineno);
        if (index >= 0)
            return PlusSymTable[index].value;

        return 0;
    }

    SymbolTablePtr sym = p->id.i;
    if (sym == NULL)
    {
        p->id.i = AddSymbol(p->id.name);    
        sym = p->id.i;
        if (sym == NULL)
        {
            FatalError(method, error_outof_memory);
            return 0;
        }
    }
    return sym->initialized ? sym->value : 0;
}

//
// Reg loop
//
int ExOprForReg(parseNodePtr p)
{
    const char* method = "ExOprForReg";

    // must convert to 1 or 0
    const int isRegX = p->opr.oper == REGX ? 1 : 0;

    parseNodePtr cmpNode;
    parseNodePtr loopBranch = NULL;

    const int cmpOp = Cmp[isRegX];
    const int ldOp = Ld[isRegX];
    int incOp = Inc[isRegX];
    int decOp = Dec[isRegX];
    int* forLoopCounter = isRegX ? &ForXCount : &ForYCount;

    CHECK_OPS(4, 4);

    // check for nested loop
    if (*(forLoopCounter) > 0)
    {
        Error(method, error_for_reg_cant_be_nested);
        return 0;
    }

    // get the start value
    const int start = Ex(p->op[0]);

    // range check
    if (start < 0 || start > 255)
    {
        Error(method, error_value_outof_range);
        return 0;
    }

    // get the end value
    const int end = Ex(p->op[1]);

    // range check
    if (end < 0 || end > 255)
    {
        Error(method, error_value_outof_range);
        return 0;
    }

    // get flag for increment / decrement
    const int incflag = Ex(p->op[3]);

    // check for loop that would have zero iterations
    // we may want to warn user
    if ((incflag > 0 && start > end) || (incflag < 0 && start < end))
    {
        return 0;
    }

    // increment nest level
    if ( ++(*forLoopCounter) != 1)
    {
        Error(method, error_value_outof_range);
    }

    // inject (ldx | ldy) #start opcode node
    const parseNodePtr loopInitialize = Opcode(ldOp, I, 1, Con(start, 0));
    Ex(loopInitialize);

    // save program counter
    const int startLoopPc = PC;

    // loop body
    Ex(p->op[2]);

    // optimize start = end
    if (start == end)
    {
        if (--(*forLoopCounter) != 0)
        {
            Error(method, error_value_outof_range);
        }
        return 0;
    }

    // inject inx or dex | iny or dey
    const parseNodePtr loopNext = Opcode(incflag > 0 ? incOp : decOp, i, 0);
    Ex(loopNext);

    // check to see if we need a compare
    if (end != 0)
    {
        if (incflag > 0 && end < 255)
        {
            cmpNode = Opcode(cmpOp, I, 1, Con(end + 1, 0));
        }
        else
        {
            cmpNode = Opcode(cmpOp, I, 1, Con(end, 0));
        }
        Ex(cmpNode);
    }

    // figure out branch condition
    if (incflag > 0)
    {
        if (end < 255)
        {
            loopBranch = Opcode(_bcc, r, 1, Con(startLoopPc, 0));
        }
        else
        {
            loopBranch = Opcode(_bne, r, 1, Con(startLoopPc, 0));
        }
    }
    else if (incflag < 0)
    {
        loopBranch = Opcode(_bcs, r, 1, Con(startLoopPc, 0));
    }
    Ex(loopBranch);

    if (--(*forLoopCounter) != 0)
    {
        Error(method, error_value_outof_range);
    }
    return 0;
}

//
// Data node
//
int ExData(parseNodePtr p)
{
    const char* method = "ExData";

    CHECK_OPS(0, 0);

    if (p->data.size == 0)
    {
        ExpansionType = data_string;
        DataSize = 0;
    }
    else
    {
        ExpansionType = data_byte;
        DataSize = p->data.size;
    }
    Ex((parseNodePtr)p->data.data);
    return 0;
}

//
// Section
int ExOprSection(parseNodePtr p)
{
    const char* method = "ExOprSection";

    CHECK_OPS(1, 1);

    char* name = p->op[0]->id.name;
    if (CurrentSection != NULL)
    {
        const int len = (int)(strlen(CurrentSection) + strlen(name) + 2);
        char* tempName = (char*)malloc(len);
        if (tempName == NULL)
        {
            FatalError(method, error_outof_memory);
            return 0;
        }

        sprintf(tempName, "%s.%s", CurrentSection, name);
        free(CurrentSection);
        CurrentSection = tempName;
    }
    else
    {
        CurrentSection = StrDup(name);
        if (CurrentSection == NULL)
        {
            FatalError(method, error_outof_memory);
            return 0;
        }
    }

    return 0;
}

/// <summary>
/// end section.
/// </summary>
/// <param name="p">The parseNode.</param>
/// <returns>int.</returns>
int ExOprEndSection(parseNodePtr p)
{
    const char* method = "ExOprSection";

    CHECK_OPS(0, 0);

    if (CurrentSection == NULL)
    {
        Error(method, error_end_section_without_section);
        return 0;
    }

    int index = (int) strlen(CurrentSection);
    while (index >= 0 && CurrentSection[index] != '.')
        index--;
    if (index >= 0)
        CurrentSection[index] = 0;
    else
    {
        free(CurrentSection);
        CurrentSection = NULL;
    }
    return 0;
}

//
// Opcode
//
int ExOpCode(parseNodePtr p)
{
    int modeCheck = p->opcode.mode;
    const int saveMode = p->opcode.mode;
    int code2;
    const int saveOpCode = p->opcode.opcode;
    int opBytes;
    int largeOp = 0;
    int outOfRange = 0;
    const char* method = "ExOpCode";

    p->opcode.pc = PC;

    switch (p->opcode.mode)
    {
    default:
        case A:     /* Accumulator          */
        case i:     /* implied              */
            opBytes = 0;
            break;

        case I:     /* immediate            */
        case zp:    /* zero page            */
        case zpi:   /* zero page indirect   */
        case zpx:   /* zero page x          */
        case zpy:   /* zero page y          */
        case zpix:  /* zero page indirect x */
        case zpiy:  /* zero page indirect y */
            opBytes = 1;
            break;

        case zr:    /* zero page relative   */
        case r:     /* relative             */
        case a:     /* absolute             */
            opBytes = 2;
            modeCheck = zp;
            break;

        case aix:   /* absolute indirect x   */
            opBytes = 2;
            modeCheck = zpix;
            break;

        case ax:    /* absolute x           */
            opBytes = 2;
            modeCheck = zpx;
            break;

        case ay:    /* absolute y           */
            opBytes = 2;
            modeCheck = zpy;
            break;

        case ind:   /* absolute indirect    */
            opBytes = 2;
            modeCheck = zpi;
            break;
    }

    if (!HasUnInitializedSymbol(p))
    {
        for (int index = 0; index < p->nops; index++)
        {
            const int opValue = Ex(p->op[index]);
            largeOp = largeOp | ((opValue & ~0xFF) != 0);
            outOfRange =  outOfRange | ((((opValue & ~0xFFFF) != 0)) || ((opBytes < 2) && (largeOp)));
            if (outOfRange)
            {
                Error(method, error_value_outof_range);
                break;
            }

            if (p->opcode.mode == r && p->nops == 1)
            {
                // make sure a branch is in range
                const int op = opValue - (p->opcode.pc + 2);               

                if (op > 128 || op < -127)
                {
                    // reverse the logic and insert a jmp
                    switch (p->opcode.instruction)
                    {
                        default:
                            break;

                        case _bcs:
                            p->opcode.instruction = _bcc;
                            break;

                        case _bcc:
                            p->opcode.instruction = _bcs;
                            break;

                        case _bne:
                            p->opcode.instruction = _beq;
                            break;

                        case _beq:
                            p->opcode.instruction = _bne;
                            break;

                        case _bmi:
                            p->opcode.instruction = _bpl;
                            break;

                        case _bpl:
                            p->opcode.instruction = _bmi;
                            break;
                    }
                    code2 = GetOpCode(p->opcode.instruction, r);
                    if (code2 != -1)
                    {
                        const parseNodePtr target = p->op[index];
                        const parseNodePtr jmp = Opcode(_jmp, a, 1, target);

                        if (target == NULL || jmp == NULL)
                        {
                            FatalError(method, error_outof_memory);
                            return 0;
                        }

                        p->opcode.opcode = code2;
                        if (FinalPass)
                        {
                            p->op[index] = Con(PC + 5, 0);
                            GenerateListNode(p);
                            GenerateOut(p);
                        }
                        PC += (GetOpByteCount(p) + 1);
                        if (FinalPass)
                        {
                            jmp->opcode.pc = PC;
                            GenerateListNode(jmp);
                            GenerateOut(jmp);

                            Warning(method, error_branch_outof_range);
                        }
                        PC += (GetOpByteCount(jmp) + 1);
                        p->opcode.opcode = saveOpCode;
                        p->opcode.mode = saveMode;

                        return 0;
                    }
                }   
            }
        }    

        // page zero optimization
        if (!largeOp && p->opcode.mode != modeCheck)
        {
            code2 = GetOpCode(p->opcode.instruction, modeCheck);
            if (code2 != -1)
            {
                p->opcode.mode  = modeCheck;
                p->opcode.opcode = code2;
            }
        }

    }

    CHECK_OPS(0, INT16_MAX);

    if (FinalPass)
    {
        GenerateListNode(p);
        GenerateOut(p);
    }

    PC += (GetOpByteCount(p) + 1);

    p->opcode.opcode = saveOpCode;
    p->opcode.mode = saveMode;

    return 0;
}

//
// Operator Not
//
int ExOprNot(parseNodePtr p)
{
    const char* method = "ExOprNot"; 
    CHECK_OPS(1, 1);
    return ! Ex(p->op[0]);
}

//
// Operator Shift left
//
int ExOprShiftLeft(parseNodePtr p)
{
    const char* method = "ExOprShiftLeft";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) << Ex(p->op[1]);
}

//
// Operator Shift right
//
int ExOprShiftRight(parseNodePtr p)
{
    const char* method = "ExOprShiftRight";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) >> Ex(p->op[1]);
}

//
// Operator LoByte
//
int ExOprLoByte(parseNodePtr p)
{
    const char* method = "ExOprLoByte";

    CHECK_OPS(1, 1);

    const int value = Ex(p->op[0]) & 0xFFFF;
    const int lo = (value & 0xFF);
    return lo;
}

//
// Operator HiByte
//
int ExOprHiByte(parseNodePtr p)
{
    const char* method = "ExOprHiByte";

    CHECK_OPS(1, 1);

    const int value = Ex(p->op[0]) & 0xFFFF;
    const int hi = (value & 0xFF00) >> 8;
    return hi;
}

//
// Operator PC assign
//
int ExOprPcAssign(parseNodePtr p)
{
    const char* method = "ExOprPcAssign";

    CHECK_OPS(1, 1);

    const int op = Ex(p->op[0]);

    if (OriginSpecified)
    {
        if (op < PC)
        {
            Error(method, error_value_outof_range);
        }
        else if (op > PC)
        {
            if (FinalPass)
            {
                const int len = op - PC;
                if (GenByteNode == NULL)
                    GenByteNode = Data(1, Con(0, 0));
                DataSize = 1;
                while (PC < op)
                {
                    if (len < 20)
                        GenerateListNode(GenByteNode);
                    GenerateOut(GenByteNode);
                    PC++;
                }
            }
        }
    }
    OriginSpecified = TRUE;
    PC = op;
    return 0;
}

//
// Operator Org
//
int ExOprOrg(parseNodePtr p)
{
    const char* method = "ExOprOrg";

    CHECK_OPS(1, 1);

    if (OriginSpecified)
    {
        Error(method, error_org_specified_more_than_once);
        return 0;
    }
    const int op = Ex(p->op[0]);
    PC = op;
    OriginSpecified = TRUE;
    return 0;
}

//
// Operator Expression List
//
int ExOprExpressionList(parseNodePtr p)
{
    SymbolTablePtr sym = NULL;
    const char* method = "ExOprExpressionList";
    char symName[MAX_MACRO_PARAM_NAME_LEN] = { 0 };

    CHECK_OPS(0, INT16_MAX);

    for (int index = 0; index < p->nops; index++)
    {
        const parseNodePtr pp = p->op[index];
        if (pp->type == type_opr && pp->opr.oper == EXPRLIST)
        {
            Ex(pp);
            continue;
        }
        switch (ExpansionType)  // NOLINT(hicpp-multiway-paths-covered)
        {
            case symbol:
                switch (pp->type)  // NOLINT(clang-diagnostic-switch-enum)
                {
                    case type_id:
                        sym = pp->id.i;
                        if (sym == NULL)
                        {
                            pp->id.i = AddSymbol(pp->id.name);    
                            sym = pp->id.i;
                            if (sym == NULL)
                            {
                                Error(method, error_adding_symbol);
                                break;
                            }
                            sym->isvar = TRUE;
                        }
                        sym->value = 0;
                        sym->initialized = TRUE;
                        break;

                    default:
                        if (sym != NULL)
                        {
                            SetSymbolValue(sym, Ex(pp));
                            sym = NULL;
                        }
                        else
                        {
                            Error(method, error_initializing_variable);
                            return 0;
                        }
                        break;
                }
                break;

            case macro_parameter:
                switch (pp->type)  // NOLINT(clang-diagnostic-switch-enum)
                {
                    case type_con:
                    case type_id:
                    case type_opr:
                        break;

                    case type_macro_id:
                    case type_macro_ex:
                    case type_data:
                    case type_str:
                    default:
                        Error(method, error_value_outof_range);
                        return 0;
                }
                if (MacroParameterIndex > MaxMacroParam)
                    MaxMacroParam = MacroParameterIndex;

                sprintf(symName, "@%d", MacroParameterIndex++);
                sym = AddSymbol(symName);
                if (sym != NULL)
                {
                    SetSymbolValue(sym, Ex(pp));
                    sym->initialized = TRUE;
                }
                else
                {
                    FatalError(method, error_outof_memory);
                }
                break;

            case data_byte:
                if (!HasUnInitializedSymbol(pp))
                {
                    if (FinalPass)
                    {
                        switch (pp->type)  // NOLINT(clang-diagnostic-switch-enum)
                        {
                            case type_con:
                            case type_id:
                            case type_opr:
                            case type_str:
                                break;

                            case type_macro_id:
                            case type_macro_ex:
                            case type_data:
                            default:
                                Error(method, error_value_outof_range);
                                return 0;
                        }
                        GenerateListNode(pp);
                        GenerateOut(pp);
                    }
                }
                if (pp->type == type_str)
                {
                    int length = pp->str.len;
                    if (length % 2 && DataSize == 2)
                        length++;
                    PC += length;
                    break;
                }
                PC += DataSize;
                break;

            case data_string:
                if (pp->type != type_str)
                {
                    Error(method, error_value_outof_range);
                    return 0;
                }
                if (FinalPass)
                {
                    GenerateListNode(pp);
                    GenerateOut(pp);
                }
                PC += pp->str.len;
                break;

            case print_all:
            case print:
                if (pp->type == type_str)
                {
                    if (FinalPass || ExpansionType == print_all)
                    {
                        fprintf(stdout, " ");
                        for (int charIndex = 0; charIndex < pp->str.len; charIndex++)
                        {
                            fprintf(stdout, "%c", pp->str.value[charIndex]);
                        }
                    }
                }
                else
                {
                    const int op = Ex(pp);
                    const int hi = (op & 0xFF00) >> 8;
                    const int lo = op & 0xFF;

                    if (FinalPass || ExpansionType == print_all)
                    {
                        if (hi)
                        {
                            fprintf(stdout, " $%02X", hi);
                        }
                        fprintf(stdout, " $%02X", lo);
                    }
                }
                break;
        }
    }
    return 0;
}

//
// Expand macro symbol
//
int ExMacroSymbol(parseNodePtr p)
{
    
    const char* method = "ExMacroSymbol";

    CHECK_OPS(0, 0);

    ExSymbol(p);

    const SymbolTablePtr sym = p->id.i;
    if (! sym  || !sym->macro_node)
        return 0;
    Ex((parseNodePtr)(sym->macro_node));
    return sym->value;
}

//
// macro expansion
//
int ExMacroExpansion(parseNodePtr p)
{
    const char* method = "ExMacroExpansion";
    CHECK_OPS(0, 0);

    PushMacroParams();

    ExpansionType = macro_parameter;
    MacroParameterIndex = 0;

    if (p->macro.macroParams != NULL)
        Ex(((parseNodePtr)p->macro.macroParams));

    if (p->macro.macro != NULL)
        Ex(((parseNodePtr)p->macro.macro));

    PopMacroParams();

    return 0;
}

//
// Expand a Macro definition
//
int ExOprMacroDefinition(parseNodePtr p)
{
    const char* method = "ExOprMacroDefinition";

    CHECK_OPS(2, 2);

    const SymbolTablePtr sym = AddSymbol(p->op[0]->id.name);
    if (sym == NULL)
    {
        FatalError(method, error_outof_memory);
        return 0;
    }
    p->id.i = sym;
    sym->ismacroname = TRUE;
    sym->initialized = TRUE;
    sym->macro_node = p->op[1];
     
    return 0;
}

//
// Operator While
//
int ExOprWhile(parseNodePtr p)
{
    const char* method = "ExOprWhile";

    CHECK_OPS(2, 2);

    while(Ex(p->op[0]))
    {
        Ex(p->op[1]);
            
        if (PC > MaxAddress)
        {
            Error(method, error_infinite_loop_detected);
            return 0;
        }
    }
    return 0;
}

//
// Operator Repeat
//
int ExOprRepeat(parseNodePtr p)
{
    const char* method = "ExOprRepeat";

    CHECK_OPS(2, 2);

    do
    {
        Ex(p->op[0]);

        if (PC > MaxAddress)
        {
            Error(method, error_infinite_loop_detected);
            return 0;
        }
    } while (Ex(p->op[1]) == 0);
    return 0;
}

//
// Operator Do
//
int ExOprDo(parseNodePtr p)
{
    const char* method = "ExOprDo";

    CHECK_OPS(2, 2);

    do
    {
        Ex(p->op[0]);
        if (PC > MaxAddress)
        {
            Error(method, error_infinite_loop_detected);
            return 0;
        }
    } while (Ex(p->op[1]));
    return 0;
}

//
// Operator For
//
int ExOprFor(parseNodePtr p)
{
    SymbolTablePtr startSym = NULL;
    int val = 1;
    const char* method = "ExOprFor";

    CHECK_OPS(4, 5);

    if (p->nops == 5)
        val = Ex(p->op[4]);

    const parseNodePtr pp = p->op[0];
    if (pp->op[0]->type == type_id)
    {
        if (pp->op[0]->id.i == NULL)
            pp->op[0]->id.i = AddSymbol(pp->op[0]->id.name);
        startSym = pp->op[0]->id.i;
        if (startSym == NULL)
        {
            FatalError(method, error_outof_memory);
            return 0;
        }
    }
    Ex(p->op[0]);
    if (p->op[3]->id.i == NULL)
        p->op[3]->id.i = AddSymbol(p->op[3]->id.name);

    const SymbolTablePtr sym = p->op[3]->id.i;
    if (sym == NULL)
    {
        FatalError(method, error_outof_memory);
        return 0;
    }
    const int endval = Ex(p->op[1]);

    if (startSym && startSym != sym)
    {
        Error(method, error_expected_next);
        return 0;
    }
    if (UnRollLoop && (endval < 0) && (endval > 255))
    {
        Error(method, error_value_outof_range);
        return 0;
    }
    if (UnRollLoop)
    {
        do
        {
            if (val > 0 && sym->value > endval)
                break;
            if (val < 0 && sym->value < endval)
                break;

            Ex(p->op[2]);

            if (PC > MaxAddress)
            {
                Error(method, error_infinite_loop_detected);
                return 0;
            }
            SetSymbolValue(sym, sym->value + val);
        } while (TRUE);
    }
    else
    {
        Error(method, error_value_outof_range);
    }
    return 0;
}

//
// ExOperator If
//
int ExOprIf(parseNodePtr p)
{
    const char* method = "ExOprIf";
    CHECK_OPS(2, 3);

    if (Ex(p->op[0]))
    {
        Ex(p->op[1]);
    }
    else if (p->nops > 2)
    {
        Ex(p->op[2]);
    }
    return 0;
}

//
// Operator PrintAll
//
int ExOprPrintAll(parseNodePtr p)
{
    const char* method = "ExOprPrintAll";

    CHECK_OPS(0, 1);

    ExpansionType = print_all;
    for (int index = 0; index < p->nops; index++)
    {
        Ex(p->op[index]);
    }
    fprintf(stdout, "\n");
    return 0;                               
}

//
// Operator Print
//
int ExOprPrint(parseNodePtr p)
{
    const char* method = "ExOprPrint";

    CHECK_OPS(0, 1);

    ExpansionType = print;
    for (int index = 0; index < p->nops; index++)
    {
        Ex(p->op[index]);
    }
    if (FinalPass)
        fprintf(stdout, "\n");
    return 0;                               
}

//
// Operator Ds
//
int ExOprDs(parseNodePtr p)
{
    const char* method = "ExOprDs";

    CHECK_OPS(0, 1);

    const int op = Ex(p->op[0]);
    if (FinalPass)
    {
        if (GenByteNode == NULL)
            GenByteNode = Data(1, Con(0, FALSE));
        for (int index = 0; index < op; index++)
        {
            DataSize = 1;
            GenerateListNode(GenByteNode);
            GenerateOut(GenByteNode);
            PC = PC + 1;
        }
    } 
    else
    {
        PC = PC + op;
    }
    return 0;
}

//
// Operator Statement
//
int ExOprStatement(parseNodePtr p)
{
    const char* method = "ExOprStatement";

    if (p->nops < 1)
        return 0;

    CHECK_OPS(0, INT16_MAX);

    for (int index = 0; index < p->nops; index++)
    {
        Ex(p->op[index]);
    }
    return 0;
}

//
// Operator End
//
int ExOprEnd(parseNodePtr p)
{
    const char* method = "ExOprEnd";
 
    CHECK_OPS(0, 0);
    End = -1;
    return 0;
}

//
// Operator Equate
//
int ExOprEqu(parseNodePtr p)
{
    const char* method = "ExOprEqu";

    CHECK_OPS(2, 2);

    if (StrICmp(p->op[0]->id.name, "-" ) == 0)
    {
        int index = FindMinusSymDef(CurFileName, yylineno);
        if (index < 0) AddMinusSym(CurFileName, yylineno);

        index = FindMinusSym((int)strlen(p->op[0]->id.name), CurFileName, yylineno);

        const int op = Ex(p->op[1]);
        if (MinusSymTable[index].value != op)
        {
            MinusSymTable[index].value = op;
            SymbolValueChanged++;
        }
        return op;
    }

    if (StrICmp(p->op[0]->id.name, "+") == 0)
    {
        int index = FindPlusSymDef(CurFileName, yylineno);
        if (index < 0) AddPlusSym(CurFileName, yylineno);

        index = FindPlusSym((int)strlen(p->op[0]->id.name), CurFileName, yylineno - 1);

        const int op = Ex(p->op[1]);
        if (PlusSymTable[index].value != op)
        {
            PlusSymTable[index].value = op;
            SymbolValueChanged++;
        }
        return op;
    }

    if ((p->op[0])->id.i == NULL)
        (p->op[0])->id.i = AddSymbol((p->op[0])->id.name);
    SymbolTablePtr sym = (p->op[0])->id.i;
    if (sym == NULL)
    {
        FatalError(method, error_outof_memory);
        return 0;
    }
    const int op = Ex(p->op[1]);
    if (!sym->initialized || sym->value != op)
    {
        if (!sym->section && CurrentSection)
        {
            const int len = (int)(strlen(sym->name) + strlen(CurrentSection) + 2);
            char* temp = (char*)malloc(len);
            if (temp == NULL)
            {
                FatalError(method, error_outof_memory);
                return 0;
            }

            sprintf(temp, "%s.%s", CurrentSection, sym->name);
            sym = AddSymbol(temp);
            free(temp);
        }
        SetSymbolValue(sym, op);
        sym->initialized = TRUE;
    }
    return 0;
}

//
// Operator UMinus
//
int ExOprUMinus(parseNodePtr p)
{
    const char* method = "ExOprUMinus";
    CHECK_OPS(1, 1);
    return -Ex(p->op[0]);
}

//
// Operator Ones Complement
//
int ExOprOnesComp(parseNodePtr p)
{
    const char* method = "ExOprOnesComp";
    CHECK_OPS(1, 1);
    return (~ Ex(p->op[0])) & 0xFFFF;
}

//
// Operator Plus
//
int ExOprPlus(parseNodePtr p)
{
    const char* method = "ExOprPlus";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) + Ex(p->op[1]);
}

//
// Operator Minus
//
int ExOprMinus(parseNodePtr p)
{
    const char* method = "ExOprMinus";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) - Ex(p->op[1]);
}

//
// Operator Multiply
//
int ExOprMultiply(parseNodePtr p)
{
    const char* method = "ExOprMultiply";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) * Ex(p->op[1]);
}

//
// Operator Divide
//
int ExOprDivide(parseNodePtr p)
{
    const char* method = "ExOprDivide";
    CHECK_OPS(2, 2);

    if (Ex(p->op[1]) == 0)
    {
        Error(method, error_divide_by_zero);
        return 0;
    }
    return Ex(p->op[0]) / Ex(p->op[1]);
}

//
// Operator BitOr
//
int ExOprBitOr(parseNodePtr p)
{
    const char* method = "ExOprBitOr";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) | Ex(p->op[1]);
}

//
// Operator BitAnd
//
int ExOprBitAnd(parseNodePtr p)
{
    const char* method = "ExOprBitAnd";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) & Ex(p->op[1]);
}

//
// Operator XOR
//
int ExOprXor(parseNodePtr p)
{
    const char* method = "ExOprXor";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) ^ Ex(p->op[1]);
}

//
// Operator LessThan
//
int ExOprLessThan(parseNodePtr p)
{
    const char* method = "ExOprLessThan";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) < Ex(p->op[1]);
}

//
// Operator GreaterThan
//
int ExOprGreaterThan(parseNodePtr p)
{
    const char* method = "ExOprGreaterThan";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) > Ex(p->op[1]);
}

//
// Operator Or
//
int ExOprOr(parseNodePtr p)
{
    const char* method = "ExOprOr";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) || Ex(p->op[1]);
}

//
// Operator And
//
int ExOprAnd(parseNodePtr p)
{
    const char* method = "ExOprAnd";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) && Ex(p->op[1]);
}

//
// Operator Equals
//
int ExOprEqual(parseNodePtr p)
{
    const char* method = "ExOprEqual";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) == Ex(p->op[1]);
}

//
// Operator Not Equal
//
int ExOprNotEqual(parseNodePtr p)
{
    const char* method = "ExOprNotEqual";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) != Ex(p->op[1]);
}

//
// Operator Greater Than Or Equal
//
int ExOprGreaterThanOrEqual(parseNodePtr p)
{
    const char* method = "ExOprGreaterThanOrEqual";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) >= Ex(p->op[1]);
}

//
// Operator LessThan Or Equal
//
int ExOprLessThanOrEqual(parseNodePtr p)
{
    const char* method = "ExOprLessThanOrEqual";
    CHECK_OPS(2, 2);
    return Ex(p->op[0]) <= Ex(p->op[1]);
}

//
// Expand an operator
//
int ExOperator(parseNodePtr p)
{
    const char* method = "ExOperator";

    struct OpTable* entry = BSearch(p->opr.oper, ExOprTable, NUM_OPR_EXP);
    if (entry)
        return entry->function(p);

    Error(method, error_unknown_operator_type);
    return 0;
}

/// <summary>
/// Expands parseNodePtr p
/// </summary>
/// <param name="p">The parseNodePtr p.</param>
/// <returns>int.</returns>
int Ex(parseNodePtr p)
{
    const char* method = "Ex";

    ExLevel++;

    if (End)
    {
        ExLevel--;
        return 0;
    }

    struct OpTable* entry = BSearch(p->type, ExTable, NUM_EX_EXP);
    if (entry)
    {
        const int result = entry->function(p);
        ExLevel--;
        return result;
    }

    Error(method, error_unknown_node_type);

    ExLevel--;
    return 0;
}

/// <summary>
/// Determines if p IS an initialized symbol.
/// </summary>
/// <param name="p">The node pointer.</param>
int IsUnInitializedSymbol(parseNodePtr p)
{
    if (p->type == type_id)
    {
        if (p->id.i == NULL)
             return TRUE;
        const SymbolTablePtr sym = p->id.i;
        if (sym->ismacroparam || sym->ismacroname)
            return FALSE;

        return !sym->initialized;
    }
    return FALSE;
}

/// <summary>
/// Determines p has uninitialized symbol
/// </summary>
/// <param name="p">The p.</param>
int HasUnInitializedSymbol(parseNodePtr p)
{
    for (int index = 0; index < p->nops; index++)
    {
        if (HasUnInitializedSymbol(p->op[index]) || IsUnInitializedSymbol(p->op[index]))
            return TRUE;
    }
    return FALSE;
}
