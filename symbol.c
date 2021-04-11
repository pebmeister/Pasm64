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

typedef struct 
{
    const char* name;
    int value;
} Sym, *SymPtr;

typedef struct  MacroStackEntry
{
    int num_nodes;
    int* values; 
} MacroStackEntry;

DictionaryPtr SymbolDictionary = NULL;
MacroStackEntry * MacroStack = NULL;

int MacroIndex = 0;
void SanitizeSymbol(SymbolTablePtr symbol);
int SymCmpFunction (const void * a, const void * b);

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
            FatalError(module, ErrorOutofMemory);
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
        FatalError(module, ErrorOutofMemory);
        return NULL;
    }
    sym.ismacroparam = name[0] == '@';
    if (CurrentSection)
    {
        sym.section = StrDup(CurrentSection);
        if (sym.section == NULL)
        {
            FatalError(module, ErrorOutofMemory);
            return NULL;
        }
    }
    if (sym.section)
    {
        len = (int)strlen(sym.name) + (int)strlen(sym.section) + 2;
        sym.fullname = (char*)malloc(len);
        if (sym.fullname == NULL)
        {
            FatalError(module, ErrorOutofMemory);
            return NULL;
        }
        sprintf(sym.fullname, "%s.%s", sym.section, sym.name);
    }
    else
    {
        sym.fullname = StrDup(sym.name);
        if (sym.fullname == NULL)
        {
            FatalError(module, ErrorOutofMemory);
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
        FatalError(module, ErrorOutofMemory);
        return;
    }
    symbol->name = tempName;
    if (symbol->section)
    {
        len = (int)strlen(symbol->section) + (int)strlen(tempSection) + 2;
        combinedSection = (char*)malloc(len);
        if (combinedSection == NULL)
        {
            FatalError(module, ErrorOutofMemory);
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
            FatalError(module, ErrorOutofMemory);
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
            Error(module, ErrorValueOutofRange);
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
                FatalError(module, ErrorOutofMemory);
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
            FatalError(module, ErrorOutofMemory);
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
    SymPtr symbolArray = (SymPtr)malloc(SymbolDictionary->numberElements * sizeof(Sym));
    if (symbolArray == NULL)
    {
        FatalError(module, ErrorOutofMemory);
        return;
    }

    for (index = 0; index < SymbolDictionary->size; index++)
    {
        elementPtr elem = SymbolDictionary->table[index];
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
        elementPtr elem = SymbolDictionary->table[index];
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
        elementPtr elem = SymbolDictionary->table[index];
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
                FatalError(module, ErrorOutofMemory);
                return;
            }
        }
        else
        {
            MacroStackEntry* temp = (MacroStackEntry* ) realloc(MacroStack, newStackSize * sizeof(MacroStackEntry));
            if (temp == NULL)
            {
                FatalError(module, ErrorOutofMemory);
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
            FatalError(module, ErrorOutofMemory);
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
                Error(module, ErrorMacroParameterNotFound);
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
        Error(module, ErrorMacroParameterUnderFlow);
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
            Error(module, ErrorMacroParameterNotFound);
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
