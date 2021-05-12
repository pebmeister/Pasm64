%no-lines

%{

// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
// ***********************************************************************

#pragma warning(disable:4065)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "pasm64.h"
#include "opcodes.h"
#include "node.h"
#include "genlist.h"
#include "pasm64.tab.h"
#include "symbol.h" 
#include "str.h" 
#include "mem.h"

%}

%union 
{
    int iValue;                 /* integer value */
    char* strValue;      		/* string */
    char* sIndex;               /* symbol table pointer */
    struct parse_node *nPtr;    /* node pointer */
};

%token <iValue> INTEGER
%token <iValue> OPCODE
%token <sIndex> SYMBOL MACROPARAM
%token <strValue> STRING_LITERAL

%token WHILE ENDDO REPEAT UNTIL IF PRINT PRINTALL EQU ORG PCASSIGN 
%token END DO MACRO ENDMACRO ENDIF WEND STATEMENT EXPRLIST STR
%token FOR NEXT TO DOWNTO STEP NOT
%token EOL BYTE WORD LOBYTE HIBYTE DS INC LOAD
%token REGX REGY VAR MSYM PSYM
%token SECTION ENDSECTION

%nonassoc ELSE UMINUS '~'

%left SHIFT_LEFT SHIFT_RIGHT
%left OR AND GE LE EQ NE '>' '<' 
%left BIT_OR BIT_AND '^'
%left '+' '-'
%left '*' '/'

%type <nPtr> stmt_list stmt include_file load_file
%type <nPtr> opcode regloopexpr
%type <nPtr> macrodef macrocall expr_list symbol_list
%type <nPtr> symbol_assign symbol_value var_def pc_assign 
%type <nPtr> expr subexpr ifexpr loopexpr
%type <nPtr> section endsection
%%

program 
    : program stmt                      { Ex($2);                                       }
    | /* NULL */
    ;
        
stmt    
    : opcode EOL                        { $$ = $1;                                      }
    | symbol_value EOL                  { $$ = $1;                                      }
    | symbol_value opcode EOL           { Ex($1); $$ = $2;                              }
    | symbol_assign EOL                 { $$ = $1;                                      }
    | pc_assign EOL                     { $$ = $1;                                      }
    | ifexpr EOL                        { $$ = $1;                                      }
    | loopexpr EOL                      { $$ = $1;                                      }
    | regloopexpr EOL                   { $$ = $1;                                      }
    | macrodef EOL                      { $$ = $1;                                      }
    | macrocall EOL                     { $$ = $1;                                      }
    | section EOL                       { $$ = $1;                                      }
    | endsection EOL                    { $$ = $1;                                      }
    | var_def EOL                       { $$ = $1;                                      }
    | include_file EOL                  { $$ = $1;                                      }
    | load_file EOL                     { $$ = $1;                                      }
    | EOL                               { $$ = Opr(STATEMENT, 0);                       }
    ;

stmt_list
    : stmt                              { $$ = $1;                                      }
    | stmt_list stmt                    { $$ = Opr(STATEMENT, 2, $1, $2);               }
    ;

section
    : SECTION SYMBOL                    { $$ = Opr(SECTION, 1, Id($2));                 }
    ;

endsection
    : ENDSECTION                        { $$ = Opr(ENDSECTION, 0);                      }
    ;

include_file
    : INC STRING_LITERAL                { $$ = Opr(INC, 1, Str($2));                    }
    ;

load_file
    : LOAD STRING_LITERAL               { $$ = Opr(LOAD, 1, Str($2));                   }
    ;

ifexpr 
    : IF subexpr stmt_list ELSE stmt_list ENDIF                                 { $$ = Opr(IF, 3, $2, $3, $5);                  }
    | IF subexpr stmt_list ENDIF                                                { $$ = Opr(IF, 2, $2, $3);                      }
    ;

loopexpr
    : REPEAT EOL  stmt_list UNTIL subexpr                                       { $$ = Opr(REPEAT, 2, $3, $5);                  }
    | DO stmt_list ENDDO subexpr                                                { $$ = Opr(DO, 2, $2, $4);                      }
    | WHILE subexpr EOL  stmt_list WEND                                         { $$ = Opr(WHILE, 2, $2, $4);                   }   
    | FOR symbol_assign TO subexpr EOL  stmt_list NEXT SYMBOL                   { $$ = Opr(FOR, 4, $2, $4, $6, Id($8));         }
    | FOR symbol_assign TO subexpr STEP subexpr EOL  stmt_list NEXT SYMBOL      { $$ = Opr(FOR, 5, $2, $4, $8, Id($10), $6);    }
    ;

regloopexpr
    : FOR REGX '=' subexpr TO subexpr EOL  stmt_list NEXT 'X'                   { $$ = Opr(REGX, 4, $4, $6, $8, Con(1, 0));     }
    | FOR REGX '=' subexpr DOWNTO subexpr EOL  stmt_list NEXT 'X'               { $$ = Opr(REGX, 4, $4, $6, $8, Con(-1,0));     }
    | FOR REGY '=' subexpr TO subexpr EOL  stmt_list NEXT 'Y'                   { $$ = Opr(REGY, 4, $4, $6, $8, Con(1,0));      }
    | FOR REGY '=' subexpr DOWNTO subexpr EOL  stmt_list NEXT 'Y'               { $$ = Opr(REGY, 4, $4, $6, $8, Con(-1,0));     }
    ;

expr_list
    : subexpr                           { $$ = Opr(EXPRLIST, 1, $1);                    }
    | STRING_LITERAL                    { $$ = Opr(EXPRLIST, 1, Str($1));               }
    | expr_list ',' subexpr             { $$ = Opr(EXPRLIST, 2, $1, $3);                }
    | expr_list ',' STRING_LITERAL      { $$ = Opr(EXPRLIST, 2, $1, Str($3));           }
    ;
          
macrodef
    : MACRO SYMBOL stmt_list ENDMACRO   { $$ = Opr(MACRO, 2, MacroId($2), $3);          }
    ;

macrocall
    : SYMBOL expr_list                  { $$ = MacroEx($1, $2);                         }
    ;

symbol_list
    : SYMBOL                            { $$ = Opr(EXPRLIST, 1, Id($1));                }
    | symbol_list ',' SYMBOL            { $$ = Opr(EXPRLIST, 2, $1, Id($3));            }
    | SYMBOL '=' subexpr                { $$ = Opr(EXPRLIST, 3, Id($1), $3);            }
    | symbol_list ',' SYMBOL '=' subexpr{ $$ = Opr(EXPRLIST, 3, $1, Id($3), $5);        }
    ;

var_def
    : VAR symbol_list                   { $$ = Opr(VAR, 1, $2);                         }
    ;

symbol_assign
    : SYMBOL '=' subexpr                { $$ = Opr('=', 2, Id($1), $3);                 }
    | SYMBOL EQU subexpr                { $$ = Opr(EQU, 2, Id($1), $3);                 }
    ;
 
pc_assign
    : PCASSIGN '=' subexpr              { $$ = Opr(PCASSIGN, 1, $3);                    }
    | PCASSIGN EQU subexpr              { $$ = Opr(PCASSIGN, 2, $3);                    }
    ;

symbol_value
    : SYMBOL                            {   
                                            SymbolTablePtr sym = LookUpSymbol($1);
                                            if (sym && sym->ismacroname)
                                            {
                                                $$ = MacroEx($1, NULL);
                                            }
                                            else
                                            {
                                                $$ = Opr('=', 2, Id($1), Con(PC, TRUE));
                                            }
                                        }
    ;

opcode
    : OPCODE                            { $$ = Opcode($1, i, 0);                        }
    | OPCODE '#' subexpr                { $$ = Opcode($1, I, 1, $3);                    }
    | OPCODE expr                       { $$ = Opcode($1, a, 1, $2);                    }
    | OPCODE expr ',' 'X'               { $$ = Opcode($1, ax, 1, $2);                   }
    | OPCODE expr ',' 'Y'               { $$ = Opcode($1, ay, 1, $2);                   }
    | OPCODE '(' subexpr ')'            { $$ = Opcode($1, ind, 1, $3);                  }
    | OPCODE '(' subexpr ',' 'X' ')'    { $$ = Opcode($1, aix, 1, $3);                  }
    | OPCODE '(' subexpr ')' ',' 'Y'    { $$ = Opcode($1, zpiy, 1, $3);                 }
    | OPCODE expr ',' subexpr           { $$ = Opcode($1, zr, 2, $2, $4);               }    

    | ORG subexpr                       { $$ = Opr(ORG, 1, $2);                         }
    | DS subexpr                        { $$ = Opr(DS, 1, $2);                          }
    | BYTE expr_list                    { $$ = Data(1, $2);                             }
    | WORD expr_list                    { $$ = Data(2, $2);                             }
	| STR expr_list					    { $$ = Data(0, $2);	 							}
    | PRINT                             { $$ = Opr(PRINT, 0);                           }
    | PRINT expr_list                   { $$ = Opr(PRINT, 1, $2);                       }
    | PRINTALL                          { $$ = Opr(PRINTALL, 0);                        }
    | PRINTALL expr_list                { $$ = Opr(PRINTALL, 1, $2);                    }
    ;

subexpr
    : expr                              { $$ = $1;                                      }
    | '*'                               { $$ = Con(PC, TRUE);                           }
    | '(' subexpr ')'                   { $$ = $2;                                      }
    ;

expr
    : INTEGER                           { $$ = Con($1, FALSE);                          }
    | SYMBOL                            { $$ = Id($1);                                  }
    | '-' subexpr %prec UMINUS          { $$ = Opr(UMINUS, 1, $2);                      }
    | '~' subexpr %prec UMINUS          { $$ = Opr('~', 1, $2);                         }
    | '<' subexpr %prec UMINUS          { $$ = Opr(LOBYTE, 1, $2);                      }
    | '>' subexpr %prec UMINUS          { $$ = Opr(HIBYTE, 1, $2);                      }
    | NOT subexpr %prec UMINUS          { $$ = Opr(NOT, 1, $2);                         }
    | subexpr OR subexpr                { $$ = Opr(OR, 2, $1, $3);                      }
    | subexpr AND subexpr               { $$ = Opr(AND, 2, $1, $3);                     }
    | subexpr SHIFT_LEFT subexpr        { $$ = Opr(SHIFT_LEFT, 2, $1, $3);              }
    | subexpr SHIFT_RIGHT subexpr       { $$ = Opr(SHIFT_RIGHT, 2, $1, $3);             }
    | subexpr '<' subexpr               { $$ = Opr('<', 2, $1, $3);                     }
    | subexpr '>' subexpr               { $$ = Opr('>', 2, $1, $3);                     }
    | subexpr GE subexpr                { $$ = Opr(GE, 2, $1, $3);                      }
    | subexpr LE subexpr                { $$ = Opr(LE, 2, $1, $3);                      }
    | subexpr NE subexpr                { $$ = Opr(NE, 2, $1, $3);                      }
    | subexpr EQ subexpr                { $$ = Opr(EQ, 2, $1, $3);                      }
    | subexpr BIT_AND subexpr           { $$ = Opr(BIT_AND, 2, $1, $3);                 }
    | subexpr BIT_OR subexpr            { $$ = Opr(BIT_OR, 2, $1, $3);                  }
    | subexpr '^' subexpr               { $$ = Opr('^', 2, $1, $3);                     }
    | subexpr '+' subexpr               { $$ = Opr('+', 2, $1, $3);                     }
    | subexpr '-' subexpr               { $$ = Opr('-', 2, $1, $3);                     }
    | subexpr '*' subexpr               { $$ = Opr('*', 2, $1, $3);                     }
    | subexpr '/' subexpr               { $$ = Opr('/', 2, $1, $3);                     }
    | '-'                               { $$ = Id("-")                                  }
    | '+'                               { $$ = Id("+")                                  }
    ;

%%
