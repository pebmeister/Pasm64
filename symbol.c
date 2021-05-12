// ***********************************************************************
// Assembly         : 
// Author           : Paul
// Created          : 02-23-2015
//
// Last Modified By : Paul
// Last Modified On : 02-23-2015
// ***********************************************************************
// ReSharper disable CppClangTidyReadabilityRedundantDeclaration
#pragma warning(disable:4996)

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "pasm64.h"
#include "symbol.h"
#include "error.h"
#include "str.h"
#include "dictionary.h"
#include "mem.h"

int MacroStackSize = 0;
int MaxMacroParam = 0;

DictionaryPtr SymbolDictionary = NULL;
MacroStackEntry * MacroStack = NULL;

#define MINUS_SYM_GROW_SIZE 1000
#define GROW_THRESHOLD 100

PlusMinusSym* MinusSymTable = NULL;
int MinusSymTableSize = 0;
int MinusSymTableIndex = 0;

PlusMinusSym* PlusSymTable = NULL;
int PlusSymTableSize = 0;
int PlusSymTableIndex = 0;


int PlusMinusSymCmpFunction(const void* a, const void* b);

int MacroIndex = 0;
void SanitizeSymbol(SymbolTablePtr symbol);
int SymCmpFunction(const void* a, const void* b);
int ComparePluMinusSymValue(const struct plus_minus_sym* a, const char* file, int line);
int PlusMinusSymCmpFunction(const void* a, const void* b);

int ComparePluMinusSym(const struct plus_minus_sym* a, const struct plus_minus_sym* b)
{
    const int result = StrICmp(a->file, b->file);
    if (result != 0) return result;
    return a->line - b->line;
}

//
// Compare function for qsort
//
int PlusMinusSymCmpFunction(const void* a, const void* b)
{
    return ComparePluMinusSym(a,  b);
}

int ComparePluMinusSymValue(const struct plus_minus_sym* a, const char* file, int l)
{
    struct plus_minus_sym b = { file, l, 0 };
    return ComparePluMinusSym(a, &b);
}


int FindMinusSymDef(const char* file, const int line)
{
    if (MinusSymTableSize <= 0) return -1;

    for (int index = 0; index < MinusSymTableIndex; ++index)
    {
        if (ComparePluMinusSymValue(&MinusSymTable[index], file, line) == 0)
        {
            return index;
        }
    }
    return -1;
}

int FindPlusSymDef(const char* file, const int line)
{
    if (PlusSymTableSize <= 0) return -1;

    for (int index = 0; index < PlusSymTableIndex; ++index)
    {

        if (ComparePluMinusSymValue(&PlusSymTable[index], file, line) == 0)
        {
            return index;
        }
    }
    return -1;
}

int FindMinusSym(const int depth, const char* file, const int line)
{
    if (MinusSymTableSize <= 0) return -1;
    int foundIndex = -1;
    for (int index = 0; index < MinusSymTableIndex; ++index)
    {
        if (StrICmp(file, MinusSymTable[index].file))
            continue;

        if (MinusSymTable[index].line <= line) 
        {
            foundIndex = index;
        }
    }
    if (foundIndex >= 0)
    {
        return foundIndex + 1 - depth;
    }
    return -1;
}

int FindPlusSym(const int depth, const char* file, const int line)
{
    IsTreeValid();

    if (PlusSymTableSize <= 0) return -1;
    for (int index = 0; index < PlusSymTableIndex; ++index)
    {
        if (StrICmp(file, PlusSymTable[index].file))
            continue;

        if (PlusSymTable[index].line > line)
        {
            const int foundIndex = index + (depth -1);
            if (foundIndex < PlusSymTableIndex)
                return foundIndex;

            IsTreeValid();
            return -1;
        }
    }
    IsTreeValid();
    return -1;
}

void AddMinusSym(const char* file, const int line, const int value)
{
    const char* module = "AddMinusSym";
    IsTreeValid();

    if (MinusSymTable == NULL)
    {
        MinusSymTableSize = MINUS_SYM_GROW_SIZE;
        MinusSymTable = (struct plus_minus_sym*)ALLOCATE(sizeof(struct plus_minus_sym) * MinusSymTableSize);
        if (MinusSymTable == NULL)
        {
            FatalError(module, error_out_of_memory);
        }

        memset(MinusSymTable, 0, sizeof(struct plus_minus_sym) * MinusSymTableSize);
    }
    if (MinusSymTableSize - MinusSymTableIndex < GROW_THRESHOLD)
    {
        MinusSymTableSize += MINUS_SYM_GROW_SIZE;
        MinusSymTable = (struct plus_minus_sym*)REALLOCATE(MinusSymTable, sizeof(struct plus_minus_sym) * MinusSymTableSize);
        if (MinusSymTable == NULL)
        {
            FatalError(module, error_out_of_memory);
        }        
    }

    MinusSymTable[MinusSymTableIndex].file = STR_DUP(file);
    MinusSymTable[MinusSymTableIndex].line = line;
    MinusSymTable[MinusSymTableIndex].value = value;
    ++MinusSymTableIndex;

    IsTreeValid();

    qsort(MinusSymTable, MinusSymTableIndex, sizeof(struct plus_minus_sym), PlusMinusSymCmpFunction);

    IsTreeValid();
}

void AddPlusSym(const char* file, const int line, const int value)
{
 
    const char* module = "AddPlusSym";

    // printf("%s %s %d\n", module, file, value);

    IsTreeValid();

    if (PlusSymTable == NULL)
    {
        PlusSymTableSize = MINUS_SYM_GROW_SIZE;
        PlusSymTable = (struct plus_minus_sym*) ALLOCATE(sizeof(struct plus_minus_sym) * PlusSymTableSize);
        if (PlusSymTable == NULL)
        {
            FatalError(module, error_out_of_memory);
        }

        memset(PlusSymTable, 0, sizeof(struct plus_minus_sym) * PlusSymTableSize);
    }
    if (PlusSymTableSize - PlusSymTableIndex < GROW_THRESHOLD)
    {
        PlusSymTableSize += MINUS_SYM_GROW_SIZE;
        PlusSymTable = (struct plus_minus_sym*)REALLOCATE(PlusSymTable, sizeof(struct plus_minus_sym) * PlusSymTableSize);
        if (PlusSymTable == NULL)
        {
            FatalError(module, error_out_of_memory);
        }
    }
    IsTreeValid();

    PlusSymTable[PlusSymTableIndex].file = STR_DUP(file);
    PlusSymTable[PlusSymTableIndex].line = line;
    PlusSymTable[PlusSymTableIndex].value = value;
    ++PlusSymTableIndex;

    IsTreeValid();
    qsort(PlusSymTable, PlusSymTableIndex, sizeof(struct plus_minus_sym), PlusMinusSymCmpFunction);

    IsTreeValid();
}

/// <summary>
/// Add a symbol to the SymbolTable.
/// </summary>
/// <param name="name">The name.</param>
/// <returns>int.</returns>
SymbolTablePtr AddSymbol(char* name)
{
    if (name == NULL) return NULL;

    SymbolTable sym = { 0 };
    char* tempSection = CurrentScope;
    const char* module = "AddSymbol";
    
    if (SymbolDictionary == NULL)
    {
        SymbolDictionary = DictCreate(sizeof(SymbolTable));
        if (SymbolDictionary == NULL)
        {
            FatalError(module, error_out_of_memory);
            return NULL;
        }
    }

    if (strstr(name, "."))
        CurrentScope = NULL;
   
    if (name[0] == '.')
    {
        name++;
    }

    int len = (int)strlen(name);
    if (name[len-1] == ':')
        name[len-1] = 0;

    SymbolTablePtr tmpPtr = LookUpSymbol(name);
    if (tmpPtr != NULL)
    {
        CurrentScope = tempSection;
        return tmpPtr;
    }

    sym.name = STR_DUP(name);
    if (sym.name == NULL)
    {
        FatalError(module, error_out_of_memory);
        return NULL;
    }

    sym.ismacroparam = name[0] == '@';
    if (CurrentScope)
    {
        sym.scope = STR_DUP(CurrentScope);
        if (sym.scope == NULL)
        {
            FatalError(module, error_out_of_memory);
            return NULL;
        }
    }
    if (sym.scope)
    {
        len = (int)strlen(sym.name) + (int)strlen(sym.scope) + 2;
        sym.fullname = (char*)ALLOCATE(len);
        if (sym.fullname == NULL)
        {
            FatalError(module, error_out_of_memory);
            return NULL;
        }
        sprintf(sym.fullname, "%s.%s", sym.scope, sym.name);
    }
    else
    {
        sym.fullname = STR_DUP(sym.name);
        if (sym.fullname == NULL)
        {
            FatalError(module, error_out_of_memory);
            return NULL;
        }
    }
    CurrentScope = tempSection;

    tmpPtr = (SymbolTablePtr) DictInsert(&SymbolDictionary, sym.fullname, &sym);
    SanitizeSymbol(tmpPtr);

    return tmpPtr;
}

/// <summary>
/// Sanitizes the symbol.
/// </summary>
/// <param name="symbol">The symbol.</param>
void SanitizeSymbol(SymbolTablePtr symbol)
{
    char* combinedSection;
    const char* module = "SanitizeSymbol";

    if (symbol->ismacroparam)
    {
        if (symbol->scope)
        {
            FREE(symbol->scope);
            symbol->scope = NULL;
            return;
        }
    }

    if (strstr(symbol->name, ".") == NULL)
        return;

    int len = (int)strlen(symbol->name);
    while (symbol->name[len] != '.')
        len--;
    symbol->name[len] = 0;
    char* tempSection = STR_DUP(symbol->name);
    char* tempName = STR_DUP(&symbol->name[len + 1]);
    if (tempName == NULL)
    {
        FatalError(module, error_out_of_memory);
        return;
    }
    if (symbol->name)
        FREE(symbol->name);
    symbol->name = tempName;
    if (symbol->scope)
    {
        len = (int)strlen(symbol->scope) + (int)strlen(tempSection) + 2;
        combinedSection = (char*)ALLOCATE(len);
        if (combinedSection == NULL)
        {
            FatalError(module, error_out_of_memory);
            return;
        }
        sprintf(combinedSection, "%s.%s", symbol->scope, tempSection);
        FREE(symbol->scope);
        symbol->scope = combinedSection;
    }
    else
    {
        len = (int)strlen(tempSection) + 1;
        combinedSection = (char*)ALLOCATE(len);
        if (combinedSection == NULL)
        {
            FatalError(module, error_out_of_memory);
            return;
        }
        strcpy(combinedSection, tempSection);
        symbol->scope = combinedSection;
    }
    FREE(tempSection);
}

/// <summary>
/// Sets the symbol value.
/// </summary>
/// <param name="sym">The sym.</param>
/// <param name="value">The value.</param>
/// <returns>SymbolTablePtr.</returns>
SymbolTablePtr SetSymbolValue(SymbolTablePtr sym, const int value)
{
    const char* module = "SetSymbolValue";

    if ((sym != NULL) && (sym->value != value))
    {
        if (((value & ~0xFFFF) != 0) && !sym->isvar)
        {
            Error(module, error_value_outof_range);
            return NULL;
        }
        sym->value = value;
        if (!sym->ismacroparam && !sym->isvar)
        {
            SymbolValueChanged++;
        }
    }
    return sym;
}

/// <summary>
/// Looks up macro parameter.
/// </summary>
/// <param name="paramNumber">The parameter number.</param>
/// <returns>SymbolTablePtr.</returns>
SymbolTablePtr LookUpMacroParam(int paramNumber)
{
    char macroParamName[MAX_MACRO_PARAM_NAME_LEN] = { 0 };
    
    sprintf(macroParamName, "@%d", paramNumber);
    return (SymbolTablePtr) DictSearch(SymbolDictionary, macroParamName);
}

/// <summary>
/// Get SymbolTable for symbol.
/// </summary>
/// <param name="name">The name.</param>
/// <returns>int.</returns>
SymbolTablePtr LookUpSymbol(char* name)
{
    const char* module = "LookUpSymbol";

    if (SymbolDictionary == NULL)
    {
        SymbolDictionary = DictCreate(sizeof(SymbolTable));
        if (SymbolDictionary == NULL)
        {
            SymbolDictionary = DictCreate(sizeof(SymbolTable));
            if (SymbolDictionary == NULL)
            {
                FatalError(module, error_out_of_memory);
                return NULL;
            }
        }
        return NULL;
    }

    if (CurrentScope)
    {
        const int len = (int)strlen(CurrentScope) + (int)strlen(name) + 2;
        char* tempName = (char*)ALLOCATE(len);
        if (tempName == NULL)
        {
            FatalError(module, error_out_of_memory);
            return NULL;
        }
        sprintf(tempName, "%s.%s", CurrentScope, name);
        // ReSharper disable once CppLocalVariableMayBeConst
        SymbolTablePtr tmpPtr = (SymbolTablePtr)DictSearch(SymbolDictionary, tempName);
        FREE(tempName);
        if (tmpPtr)
            return tmpPtr;
    }

    return (SymbolTablePtr) DictSearch(SymbolDictionary, name);
}

/// <summary>
/// Dumps the symbols.
/// </summary>
void DumpSymbols(FILE* symFile)
{
    int index;
    int count = 0;
    const char* module = "DumpSymbols";

    if (SymbolDictionary == NULL)
        return;

    // ReSharper disable once CppLocalVariableMayBeConst
    SymPtr symbolArray = (SymPtr)ALLOCATE(SymbolDictionary->number_elements * sizeof(Sym));
    if (symbolArray == NULL)
    {
        FatalError(module, error_out_of_memory);
        return;
    }

    for (index = 0; index < SymbolDictionary->size; index++)
    {
        ElementPtr elem = SymbolDictionary->table[index];
        for ( ; elem; elem = elem->next)
        {
            // ReSharper disable once CppLocalVariableMayBeConst
            SymbolTablePtr sym = (SymbolTablePtr)(elem->value);

            if (sym->ismacroname == FALSE && sym->isvar == FALSE && sym->ismacroparam == FALSE)
            {
                symbolArray[count].name = sym->fullname;
                symbolArray[count].value = sym->value;
                count++;
            }
        }
    }

    qsort(symbolArray, count, sizeof(Sym), SymCmpFunction);

    for (index = 0; index < count; index++)
    {
        fprintf(symFile, "%24s: $%04X", symbolArray[index].name, symbolArray[index].value);
        if (index % 2)
            fprintf(symFile, "\n");
    }

    FREE(symbolArray);

    fprintf(symFile, "\n");
}

/// <summary>
/// Sym compare function.
/// </summary>
/// <param name="a">a.</param>
/// <param name="b">The b.</param>
/// <returns>int.</returns>
int SymCmpFunction(const void * a, const void * b)
{
    return (((SymPtr)a)->value - ((SymPtr)b)->value);  // NOLINT(clang-diagnostic-cast-qual)
}

/// <summary>
/// Dumps the unresolved symbols.
/// </summary>
void DumpUnResolvedSymbols()
{
    int count = 0;

    if (SymbolDictionary == NULL)
        return;

    fprintf(stderr, "Unresolved symbols:\n");

    for (int index = 0; index < SymbolDictionary->size; index++)
    {
        ElementPtr elem = SymbolDictionary->table[index];
        for ( ; elem; elem = elem->next)
        {
            // ReSharper disable once CppLocalVariableMayBeConst
            SymbolTablePtr sym = (SymbolTablePtr)(elem->value);

            if (sym->ismacroname == FALSE && sym->isvar == FALSE && sym->ismacroparam == FALSE)
            {
                if (!sym->initialized)
                {
                    fprintf(stderr, "%24s ", sym->fullname);
                    count++;

                    if (count %2 == 0)
                        fprintf(stderr, "\n");
                }
            }
        }
    }
    fprintf(stderr, "\n");
}

/// <summary>
/// return number of unresolved symbols.
/// </summary>
/// <returns>int.</returns>
int UnResolvedSymbols()
{
    int count = 0;

    if (SymbolDictionary == NULL)
        return 0;

    for (int index = 0; index < SymbolDictionary->size; index++)
    {
        ElementPtr elem = SymbolDictionary->table[index];
        for ( ; elem; elem = elem->next)
        {
            // ReSharper disable once CppLocalVariableMayBeConst
            SymbolTablePtr sym = (SymbolTablePtr)(elem->value);

            if (sym->initialized == FALSE && sym->ismacroname == FALSE &&
                sym->isvar == FALSE && sym->ismacroparam == FALSE)
            {
                count++;
            }
        }
    }
    return count;
}

/// <summary>
/// Gets the maximum macro parameter.
/// </summary>
/// <returns>int.</returns>
int GetMaxMacroParameter(void)
{
    return MaxMacroParam;
}

/// <summary>
/// Pushes the macro parameters.
/// </summary>
void PushMacroParams(void)
{
    const char* module = "PushMacroParams";

    const int maxMacro = GetMaxMacroParameter();

    if (MacroIndex >= MacroStackSize)
    {
        const int newStackSize = MacroStackSize + 100;
        if (MacroStack == NULL)
        {
            MacroStack = (MacroStackEntry*) ALLOCATE(newStackSize * sizeof(MacroStackEntry));
            if (MacroStack == NULL)
            {
                FatalError(module, error_out_of_memory);
                return;
            }
        }
        else
        {
            MacroStackEntry* temp = REALLOCATE(MacroStack, newStackSize * sizeof(MacroStackEntry));
            if (temp == NULL)
            {
                FatalError(module, error_out_of_memory);
                return;
            }
            MacroStack = temp;
        }
        MacroStackSize = newStackSize;
    }
    if (maxMacro < 0)
    {
        MacroStack[MacroIndex].num_nodes = 0;
    }
    else
    {
        MacroStack[MacroIndex].num_nodes = maxMacro + 1;
        MacroStack[MacroIndex].values = (int*) ALLOCATE((maxMacro + 1) * sizeof(long));
        if (MacroStack[MacroIndex].values == NULL)
        {
            FatalError(module, error_out_of_memory);
            return;
        }

        MacroStack[MacroIndex].values[0] = 0;
        for (int index = 1; index <= maxMacro; index++)
        {
            // ReSharper disable once CppLocalVariableMayBeConst
            SymbolTablePtr tmpPtr = LookUpMacroParam(index);
            if (tmpPtr != NULL)
            {
                #pragma warning(suppress: 6386)
                MacroStack[MacroIndex].values[index] = tmpPtr->value;
            }
            else
            {
                Error(module, error_macro_parameter_not_found);
                return;
            }
        }
    }
    ++MacroIndex;
}

/// <summary>
/// Pops the macro parameters.
/// </summary>
void PopMacroParams(void)
{
    const char* module = "PopMacroParams";

    if (--MacroIndex < 0)
    {
        Error(module, error_macro_parameter_under_flow);
        ++MacroIndex;
        return;
    }
 
    for (int index = 1; index < MacroStack[MacroIndex].num_nodes; index++)
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        SymbolTablePtr tmpPtr = LookUpMacroParam(index);
        if (tmpPtr != NULL)
        {
            SetSymbolValue(tmpPtr, MacroStack[MacroIndex].values[index]);
        }
        else
        {
            Error(module, error_macro_parameter_not_found);
            return;
        }
    }
    if (MacroStack[MacroIndex].num_nodes > 0)
    {
        FREE(MacroStack[MacroIndex].values);
        MacroStack[MacroIndex].values = NULL;
    }
    MacroStack[MacroIndex].num_nodes = 0; 
}

//
// Delete the symbol table
//
void DeleteSymbolTable(void)
{
    DictDestroy(SymbolDictionary);
    SymbolDictionary = NULL;
    if (MacroStack)
    {
        for (int macroIndex = 0; macroIndex <= MacroIndex; macroIndex++)
        {
            if (MacroStack[macroIndex].values)
            {
                FREE(MacroStack[macroIndex].values);
            }
        }
        FREE(MacroStack);
        MacroStack = NULL;
    }
    MacroStackSize = 0;
    MacroIndex = 0;

    FREE(PlusSymTable);
}
