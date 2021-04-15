// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
//
// copyright (c) 2015 Paul Baxter
//
// Last Modified By : Paul
// Last Modified On : 11-29-2015
// ***********************************************************************
#pragma once

#define MAX_MACRO_PARAM_NAME_LEN 25

typedef struct
{
    const char* name;
    int value;
} Sym, * SymPtr;

typedef struct  macro_stack_entry
{
    int num_nodes;
    int* values;
} MacroStackEntry;

typedef struct minus_sym
{
    int value;
    char* file;
    int line;
} MinusSym;

typedef struct plus_sym
{
    int value;
    char* file;
    int line;
} PlusSym;

extern MinusSym* MinusSymTable;
extern int FindMinusSym(int depth, char* file, int line);
extern int FindMinusSymDef(char* file, int line);
extern void AddMinusSym(char* file, int line);

extern PlusSym* PlusSymTable;
extern int FindPlusSym(int depth, char* file, int line);
extern int FindPlusSymDef(char* file, int line);
extern void AddPlusSym(char* file, int line);

extern void PushMacroParams(void);
extern void PopMacroParams(void);
extern SymbolTablePtr AddSymbol(char* name);
extern SymbolTablePtr LookUpSymbol(char* name);
extern void DumpSymbols(FILE* symfile);
extern void DumpUnResolvedSymbols(void);
extern int UnResolvedSymbols(void);
extern SymbolTablePtr SetSymbolValue(SymbolTablePtr sym, int value);
extern SymbolTablePtr LookUpMacroParam(int paramNumber);
extern void DeleteSymbolTable(void);
extern void SanitizeSymbol(SymbolTablePtr symbol);
extern int MacroIndex;
extern int MaxMacroParam;
