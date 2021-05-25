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

typedef struct plus_minus_sym
{
    const char* file;
    int line;
    int value;
} PlusMinusSym;

extern PlusMinusSym* MinusSymTable;
extern int FindMinusSym(int depth, const char* file, int line);
extern int FindMinusSymDef(const char* file, int line);
extern void AddMinusSym(const char* file, int line, int value);
extern char* FormatLocalSym(char* name, char* lastLabel);
extern PlusMinusSym* PlusSymTable;
extern int FindPlusSym(int depth, const char* file, int line);
extern int FindPlusSymDef(const char* file, int line);
extern void AddPlusSym(const char* file, int line, int value);
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
