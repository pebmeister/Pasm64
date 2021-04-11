#pragma once

// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
// ***********************************************************************
#pragma once

/* prototypes */
extern parseNodePtr Opr(int op, int nops, ...);
extern parseNodePtr Opcode(int opr, int mode, int nops, ...);
extern parseNodePtr Id(char* name);
extern parseNodePtr MacroId(char* name);
extern parseNodePtr Con(int value, int isPc);
extern parseNodePtr Str(char* value);
extern parseNodePtr MacroEx(char* name, parseNodePtr macroParams);
extern parseNodePtr Data(int dataSize, parseNodePtr data);
extern void PrintNode(parseNodePtr p);
extern char* SantizeString(char* str, int* outlen);
extern void FreeNode(parseNodePtr p);
extern void FreeTree(void);

extern parseNodePtr HeadNode;
extern parseNodePtr CurrentNode;