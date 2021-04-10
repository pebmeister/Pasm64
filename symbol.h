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