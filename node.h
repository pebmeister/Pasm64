#pragma once

// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
// ***********************************************************************
#pragma once

/* prototypes */
extern ParseNodePtr Opr(int op, int nops, ...);
extern ParseNodePtr Opcode(int opr, int mode, int nops, ...);
extern ParseNodePtr Id(char* name);
extern ParseNodePtr MacroId(char* name);
extern ParseNodePtr Con(int value, int isPc);
extern ParseNodePtr Str(char* value);
extern ParseNodePtr MacroEx(char* name, ParseNodePtr macroParams);
extern ParseNodePtr Data(int dataSize, ParseNodePtr data);
extern void PrintNode(ParseNodePtr p);
extern void FreeParseNode(ParseNodePtr p);
extern void FreeParseTree(void);

extern ParseNodePtr HeadNode;
extern ParseNodePtr CurrentNode;

extern ParseNodePtr AllocateNode(int nops);

extern int IsValidParseNode(ParseNodePtr p);
extern int IsValidParseTree(void);
