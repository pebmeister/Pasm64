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

int MacroStackSize = 0;
int MaxMacroParam = 0;

DictionaryPtr SymbolDictionary = NULL;
MacroStackEntry * MacroStack = NULL;

#define MINUS_SYM_GROW_SIZE 20
#define GROW_THRESHOLD 5

MinusSym* MinusSymTable = NULL;
int MinusSymTableSize = 0;
int MinusSymTableIndex = 0;

PlusSym* PlusSymTable = NULL;
int PlusSymTableSize = 0;
int PlusSymTableIndex = 0;

int MinusSymCmpFunction(const void* a, const void* b);
int PlusSymCmpFunction(const void* a, const void* b);

int MacroIndex = 0;
void SanitizeSymbol(SymbolTablePtr symbol);
int SymCmpFunction(const void* a, const void* b);

//
// Compare function for qsort
//
int MinusSymCmpFunction(const void* a, const void* b)
{
    int result = StrICmp(((const struct minus_sym*)a)->file, ((const struct minus_sym*)b)->file);
    if (result != 0) return result;

    result = ((const struct minus_sym*)a)->line - ((const struct minus_sym*)b)->line;
    return result;
}

int PlusSymCmpFunction(const void* a, const void* b)
{
    int result = StrICmp(((const struct plus_sym*)a)->file, ((const struct plus_sym*)b)->file);
    if (result != 0) return result;

    result = ((const struct plus_sym*)a)->line - ((const struct plus_sym*)b)->line;
    return result;
}

int FindMinusSymDef(char* file, const int line)
{
    if (MinusSymTableSize <= 0) return -1;

    for (int index = 0; index < MinusSymTableIndex; ++index)
    {
        if (StrICmp(MinusSymTable[index].file, file) != 0)
            continue;

        if (MinusSymTable[index].line == line)
        {
            return index;
        }
    }
    return -1;
}

int FindPlusSymDef(char* file, const int line)
{
    if (PlusSymTableSize <= 0) return -1;

    for (int index = 0; index < PlusSymTableIndex; ++index)
    {
        if (StrICmp(PlusSymTable[index].file, file) != 0)
            continue;

        if (PlusSymTable[index].line == line)
        {
            return index;
        }
    }
    return -1;
}

int FindMinusSym(const int depth, char* file, int line)
{
    if (MinusSymTableSize <= 0) return -1;
    int foundIndex = -1;
    for (int index = 0; index < MinusSymTableIndex; ++index)
    {
        if (StrICmp(MinusSymTable[index].file, file) != 0)
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

int FindPlusSym(const int depth, char* file, int line)
{
    if (PlusSymTableSize <= 0) return -1;
    for (int index = 0; index < PlusSymTableIndex; ++index)
    {
        if (StrICmp(PlusSymTable[index].file, file) != 0)
            continue;

        if (PlusSymTable[index].line > line)
        {
            const int foundIndex = index + (depth -1);
            if (foundIndex < PlusSymTableIndex)
                return foundIndex;

            return -1;
        }
    }
    return -1;
}

void AddMinusSym(char* file, int line)
{
    const char* module = "AddMinusSym";

    if (MinusSymTable == NULL)
    {
        MinusSymTable = (MinusSym*)malloc(sizeof(struct minus_sym) * MINUS_SYM_GROW_SIZE);
        if (MinusSymTable == NULL)
        {
            FatalError(module, error_outof_memory);
        }

        MinusSymTableSize = MINUS_SYM_GROW_SIZE;
        memset(MinusSymTable, 0, sizeof(struct minus_sym) * MinusSymTableSize);
    }
    if (MinusSymTableSize - MinusSymTableIndex < GROW_THRESHOLD)
    {
        MinusSymTableSize += MINUS_SYM_GROW_SIZE;
        MinusSymTable = (MinusSym*)realloc(MinusSymTable, sizeof(struct minus_sym) * MinusSymTableSize);
        if (MinusSymTable == NULL)
        {
            FatalError(module, error_outof_memory);
        }        
    }

    MinusSymTable[MinusSymTableIndex].file = StrDup(file);
    MinusSymTable[MinusSymTableIndex].line = line;
    ++MinusSymTableIndex;

    qsort(MinusSymTable, MinusSymTableIndex, sizeof(struct minus_sym), MinusSymCmpFunction);

}

void AddPlusSym(char* file, int line)
{
    const char* module = "AddPlusSym";

    if (PlusSymTable == NULL)
    {
        PlusSymTable = (PlusSym*)malloc(sizeof(struct plus_sym) * MINUS_SYM_GROW_SIZE);
        if (PlusSymTable == NULL)
        {
            FatalError(module, error_outof_memory);
        }

        PlusSymTableSize = MINUS_SYM_GROW_SIZE;
        memset(PlusSymTable, 0, sizeof(struct plus_sym) * PlusSymTableSize);
    }
    if (PlusSymTableSize - PlusSymTableIndex < GROW_THRESHOLD)
    {
        PlusSymTableSize += MINUS_SYM_GROW_SIZE;
        PlusSymTable = (PlusSym*)realloc(PlusSymTable, sizeof(struct plus_sym) * PlusSymTableSize);
        if (PlusSymTable == NULL)
        {
            FatalError(module, error_outof_memory);
        }
    }

    PlusSymTable[PlusSymTableIndex].file = StrDup(file);
    PlusSymTable[PlusSymTableIndex].line = line;
    ++PlusSymTableIndex;

    qsort(PlusSymTable, PlusSymTableIndex, sizeof(struct plus_sym), PlusSymCmpFunction);
}

/// <summary>
/// Add a symbol to the SymbolTable.
/// </summary>
/// <param name="name">The name.</param>
/// <returns>int.</returns>
SymbolTablePtr AddSymbol(char* name)
{
    SymbolTable sym = { 0 };
    char* tempSection = CurrentSection;
    const char* module = "AddSymbol";
    
    if (SymbolDictionary == NULL)
    {
        SymbolDictionary = DictCreate(sizeof(SymbolTable));
        if (SymbolDictionary == NULL)
        {
            FatalError(module, error_outof_memory);
            return NULL;
        }
    }

    if (strstr(name, "."))
        CurrentSection = NULL;
   
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
        CurrentSection = tempSection;
        return tmpPtr;
    }

    sym.name = StrDup(name);
    if (sym.name == NULL)
    {
        FatalError(module, error_outof_memory);
        return NULL;
    }
    sym.ismacroparam = name[0] == '@';
    if (CurrentSection)
    {
        sym.section = StrDup(CurrentSection);
        if (sym.section == NULL)
        {
            FatalError(module, error_outof_memory);
            return NULL;
        }
    }
    if (sym.section)
    {
        len = (int)strlen(sym.name) + (int)strlen(sym.section) + 2;
        sym.fullname = (char*)malloc(len);
        if (sym.fullname == NULL)
        {
            FatalError(module, error_outof_memory);
            return NULL;
        }
        sprintf(sym.fullname, "%s.%s", sym.section, sym.name);
    }
    else
    {
        sym.fullname = StrDup(sym.name);
        if (sym.fullname == NULL)
        {
            FatalError(module, error_outof_memory);
            return NULL;
        }
    }
    CurrentSection = tempSection;

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
        if (symbol->section)
        {
            free(symbol->section);
            symbol->section = NULL;
            return;
        }
    }

    if (strstr(symbol->name, ".") == NULL)
        return;

    int len = (int)strlen(symbol->name);
    while (symbol->name[len] != '.')
        len--;
    symbol->name[len] = 0;
    char* tempSection = symbol->name;
    char* tempName = StrDup(&symbol->name[len + 1]);
    if (tempName == NULL)
    {
        FatalError(module, error_outof_memory);
        return;
    }
    symbol->name = tempName;
    if (symbol->section)
    {
        len = (int)strlen(symbol->section) + (int)strlen(tempSection) + 2;
        combinedSection = (char*)malloc(len);
        if (combinedSection == NULL)
        {
            FatalError(module, error_outof_memory);
            return;
        }
        sprintf(combinedSection, "%s.%s", symbol->section, tempSection);
        free(symbol->section);
        symbol->section = combinedSection;
    }
    else
    {
        len = (int)strlen(tempSection) + 1;
        combinedSection = (char*)malloc(len);
        if (combinedSection == NULL)
        {
            FatalError(module, error_outof_memory);
            return;
        }
        strcpy(combinedSection, tempSection);
        symbol->section = combinedSection;
    }
    free(tempSection);
}

/// <summary>
/// Sets the symbol value.
/// </summary>
/// <param name="sym">The sym.</param>
/// <param name="value">The value.</param>
/// <returns>SymbolTablePtr.</returns>
SymbolTablePtr SetSymbolValue(SymbolTablePtr sym, int value)
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
                FatalError(module, error_outof_memory);
                return NULL;
            }
        }
        return NULL;
    }

    if (CurrentSection)
    {
        const int len = (int)strlen(CurrentSection) + (int)strlen(name) + 2;
        char* tempName = (char*)malloc(len);
        if (tempName == NULL)
        {
            FatalError(module, error_outof_memory);
            return NULL;
        }
        sprintf(tempName, "%s.%s", CurrentSection, name);
        // ReSharper disable once CppLocalVariableMayBeConst
        SymbolTablePtr tmpPtr = (SymbolTablePtr)DictSearch(SymbolDictionary, tempName);
        if (tmpPtr)
        {
            free(tempName);
            return tmpPtr;
        }
        free(tempName);
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
    SymPtr symbolArray = (SymPtr)malloc(SymbolDictionary->number_elements * sizeof(Sym));
    if (symbolArray == NULL)
    {
        FatalError(module, error_outof_memory);
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

    free(symbolArray);

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
            MacroStack = (MacroStackEntry*) malloc(newStackSize * sizeof(MacroStackEntry));
            if (MacroStack == NULL)
            {
                FatalError(module, error_outof_memory);
                return;
            }
        }
        else
        {
            MacroStackEntry* temp = (MacroStackEntry* ) realloc(MacroStack, newStackSize * sizeof(MacroStackEntry));
            if (temp == NULL)
            {
                FatalError(module, error_outof_memory);
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
        MacroStack[MacroIndex].values = (int*) malloc((maxMacro + 1) * sizeof(long));
        if (MacroStack[MacroIndex].values == NULL)
        {
            FatalError(module, error_outof_memory);
            return;
        }

        for (int index = 0; index <= maxMacro; index++)
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
 
    for (int index = 0; index < MacroStack[MacroIndex].num_nodes; index++)
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
        free(MacroStack[MacroIndex].values);
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
                free(MacroStack[macroIndex].values);
            }
        }
        free(MacroStack);
        MacroStack = NULL;
    }
    MacroStackSize = 0;
    MacroIndex = 0;
}
