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
#include <stdio.h>

#define MAX_LINE_LEN  102400

enum OutputFileType
{
    none,
    c64
};

typedef enum { type_unknown = 0, type_head_node = 1, type_con, type_id, type_macro_id, type_macro_ex, type_opr, type_op_code, type_data, type_str } NodeEnum;

typedef struct symbol_table
{
    int value;
    int initialized;
    int ismacroname;
    int ismacroparam;
    int isvar;
    int isminus;
    char* scope;
    char* name;
    char* fullname;
    void* macro_node;
} SymbolTable, *SymbolTablePtr;

#ifndef FALSE
#   define FALSE 0
#endif
#ifndef TRUE
#   define TRUE (!FALSE)
#endif

/* constants */
typedef struct 
{
    int value;                  /* value of constant */
    int IsPC;                   /* TRUE is value is PC */
} ConParseNode;

typedef struct 
{
    char* value;                 /* value of string */
	char* allocated;			 /* allocated string */
	int len;
} StrParseNode;

/* identifiers */
typedef struct 
{
    char*  name;
    SymbolTablePtr i;          /* symbol entry */
} IdParseNode;

/* operators */
typedef struct 
{
    int oper;                   /* operator */
} OprParseNode;

/* opcodes */
typedef struct 
{
    int instruction;            /* untranslated instruction */
    int opcode;                 /* opcode */
    int mode;                   /* mode */
    int pc;                     /* program counter */
} opParseNode;

/* macro execution node */
typedef struct 
{
    void* macro;
    void* macro_params;
} MacParseNode;

/* data definition node */
typedef struct 
{
    int size;                   /* 1 = byte 2 = word, 0 = string */
    void* data;
} DataParseNode;

/* nodes union */
typedef struct parse_node
{
    NodeEnum type;              /* type of node */

    union 
    {
        ConParseNode con;        /* constants */
        IdParseNode id;          /* identifiers */
        OprParseNode opr;        /* operators */
        opParseNode opcode;      /* opcodes */
        MacParseNode macro;      /* macro execution */
        DataParseNode data;      /* numeric data node */
		StrParseNode str;		 /* string node */
    };
    int allocated;
    int nops;                    /* number of operands */
    struct parse_node **op;       /* operands */
    struct parse_node* next;      /* next node in tree */
    struct parse_node* prev;      /* previous node */
} ParseNode, *ParseNodePtr;

extern int yylineno;
extern FILE* yyin;
extern int yylex(void);
extern void yyerror(const char *s);
extern void yyrestart(FILE * input_file );
extern int yyparse (void);


extern int OriginSpecified;
extern int End;
extern int FinalPass;
extern int ErrorCount;
extern int Pass;
extern int Org;
extern int PC;
extern int DataSize;
extern int UnRollLoop;
extern FILE* OutputFile;
extern FILE* ListFile;
extern FILE* SymFile;
extern FILE* LogFile;
extern char* CurFileName;
extern char* LogFileName;
extern char* SymFileName;
extern char* OutputFileName;
extern char* CurrentScope;
extern char* ListFileName;
extern int MaxAddress;
extern char* Directories;

extern enum OutputFileType OutFileFormat;

extern int TotalBytesWritten;
extern int SymbolValueChanged;
extern char* InternalBuffer;
extern int NoWarnings;

/* our api */ 
extern int Ex(ParseNode *p);
extern void InitEx(void);
extern int HasUnInitializedSymbol(ParseNodePtr p);
extern void yywarn(const char *s);
extern int OpenIncludeFile(char* file);

#define LOG(n,p)      if (LogFile != NULL) \
{\
    fprintf(LogFile, "%s  [line %d]\n", n, yylineno);\
    PrintNode(p);\
    fprintf(LogFile, "\n");\
}
