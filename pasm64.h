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

#define MAXLINE_LEN  102400

enum OutputFileType
{
    none,
    c64
};


typedef enum { typeCon = 1, typeId, typeMacroId, typeMacroEx, typeOpr, typeOpCode, typeData, typeStr } nodeEnum;

typedef struct SymbolTable
{
    int value;
    int initialized;
    int ismacroname;
    int ismacroparam;
    int isvar;
    char* section;
    char* name;
    char* fullname;
    void* macroNode;
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
} conParseNode;

typedef struct 
{
    char* value;                 /* value of string */
	char* allocated;			 /* allocated string */
	int len;
} strParseNode;

/* identifiers */
typedef struct 
{
    char*  name;
    SymbolTablePtr i;          /* symbol entry */
} idParseNode;

/* operators */
typedef struct 
{
    int oper;                   /* operator */
} oprParseNode;

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
    void* macroParams;
} macParseNode;

/* data definition node */
typedef struct 
{
    int size;                   /* 1 = byte 2 = word, 0 = string */
    void* data;
} dataParseNode;

/* nodes union */
typedef struct parseNode
{
    nodeEnum type;              /* type of node */

    union 
    {
        conParseNode con;        /* constants */
        idParseNode id;          /* identifiers */
        oprParseNode opr;        /* operators */
        opParseNode opcode;      /* opcodes */
        macParseNode macro;      /* macro execution */
        dataParseNode data;      /* numeric data node */
		strParseNode str;		 /* string node */
    };

    int nops;                    /* number of operands */
    struct parseNode **op;       /* operands */
    struct parseNode* next;      /* next node in tree */
    struct parseNode* prev;      /* previous node */
} parseNode, *parseNodePtr;

extern int yylineno;
extern FILE* yyin;
extern int yylineno;
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
extern char* CurrentSection;
extern char* ListFileName;
extern int MaxAddress;
extern char* Directories;

extern enum OutputFileType OutFileFormat;

extern int TotalBytesWritten;
extern int SymbolValueChanged;
extern char* InternalBuffer;
extern int NoWarnings;

/* our api */ 
extern int Ex(parseNode *p);
extern void InitEx(void);
extern int HasUnInitializedSymbol(parseNodePtr p);
extern void yywarn(const char *s);
extern int OpenIncludeFile(char* file);

#define LOG(n,p)      if (LogFile != NULL) \
{\
    fprintf(LogFile, "%s  [line %d]\n", n, yylineno);\
    PrintNode(p);\
    fprintf(LogFile, "\n");\
}
