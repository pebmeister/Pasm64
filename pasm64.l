%option case-insensitive yylineno noyywrap
 
%{
#pragma warning(disable:4996)
#pragma warning(disable:6011)
#pragma warning(disable:6387)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "opcodes.h"
#include "pasm64.h"
#include "pasm64.tab.h"
#include "symbol.h"
#include "node.h"
#include "str.h"
#include "genlist.h"
#include "file.h"
#include "error.h"

extern char* CurFileName;

#define MAX_INCLUDE_STACK   100

char* fileStack [MAX_INCLUDE_STACK] = { 0 };
int fileLineStack [MAX_INCLUDE_STACK] = { 0 };
int fileStackIndex = 0;

int inDoLoop = 0;
int inMacroDef = 0;

#define OP(op)              { yylval.iValue = _ ## op; return OPCODE; }
#define OP_REL(op)          { yylval.iValue = _ ## op ## 0 + yytext[3] - '0'; return OPCODE; }
#define OP_ILLEGAL(op)      { OP(op); }
#define OP_65C02(op)        { OP(op); }
#define OP_65C02_REL(op)    { OP_REL(op); }
#define INT(off, base)      { yylval.iValue = (int) strtol (yytext + off, NULL, base); \
                                return INTEGER; \
                            }
#define INT_1BYTE           { int outlen; \
                                char* tmpStr = SantizeString(yytext, &outlen); \
                                yylval.iValue = (int)tmpStr[1]; \
                                free(tmpStr); \
                                return INTEGER; \
                            }
%}

%x C_COMMENT

ES                          (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
LOGOR                       [|][|]
BITOR                       [|]
LOGAND                      [&][&]
BITAND                      [&]
STRVALUE					(\"([^"\\\n]|{ES})*\")+	

%%

"ORA"                       OP(ora)
"AND"                       OP(and)
"EOR"                       OP(eor)
"ADC"                       OP(adc)
"SBC"                       OP(sbc)
"CMP"                       OP(cmp)
"CPX"                       OP(cpx)
"CPY"                       OP(cpy)
"DEC"                       OP(dec)
"DEC"[ /t]*"A"              OP(dec)
"DEX"                       OP(dex)
"DEY"                       OP(dey)
"INC"                       OP(inc)
"INC"[ /t]*"A"              OP(inc)
"INX"                       OP(inx)
"INY"                       OP(iny)
"ASL"                       OP(asl)
"ASL"[ /t]*"A"              OP(asl)
"ROL"                       OP(rol)
"ROL"[ /t]*"A"              OP(rol)
"LSR"                       OP(lsr)
"LSR"[ /t]*"A"              OP(lsr)
"ROR"                       OP(ror)
"ROR"[ /t]*"A"              OP(ror)
"LDA"                       OP(lda)
"STA"                       OP(sta)
"LDX"                       OP(ldx)
"STX"                       OP(stx)
"LDY"                       OP(ldy)
"STY"                       OP(sty)
"TAX"                       OP(tax)
"TXA"                       OP(txa)
"TAY"                       OP(tay)
"TYA"                       OP(tya)
"TSX"                       OP(tsx)
"TXS"                       OP(txs)
"PLA"                       OP(pla)
"PHA"                       OP(pha)
"PLP"                       OP(plp)
"PHP"                       OP(php)
"BPL"                       OP(bpl)
"BMI"                       OP(bmi)
"BVC"                       OP(bvc)
"BVS"                       OP(bvs)
"BCC"                       OP(bcc)
"BCS"                       OP(bcs)
"BNE"                       OP(bne)
"BEQ"                       OP(beq)
"BRK"                       OP(brk)
"RTI"                       OP(rti)
"JSR"                       OP(jsr)
"RTS"                       OP(rts)
"JMP"                       OP(jmp)
"BIT"                       OP(bit)
"CLC"                       OP(clc)
"SEC"                       OP(sec)
"CLD"                       OP(cld)
"SED"                       OP(sed)
"CLI"                       OP(cli)
"SEI"                       OP(sei)
"CLV"                       OP(clv)
"NOP"                       OP(nop)
"SLO"                       OP_ILLEGAL(slo)
"RLA"                       OP_ILLEGAL(rla)
"SRE"                       OP_ILLEGAL(sre)
"RRA"                       OP_ILLEGAL(rra)
"SAX"                       OP_ILLEGAL(sax)
"LAX"                       OP_ILLEGAL(lax)
"DCP"                       OP_ILLEGAL(dcp)
"ISC"                       OP_ILLEGAL(isc)
"ANC"                       OP_ILLEGAL(anc)
"ANC2"                      OP_ILLEGAL(anc2)
"ALR"                       OP_ILLEGAL(alr)
"ARR"                       OP_ILLEGAL(arr)
"XAA"                       OP_ILLEGAL(xaa)
"LAX2"                      OP_ILLEGAL(lax2)
"AXS"                       OP_ILLEGAL(axs)
"SBC2"                      OP_ILLEGAL(sbc2)
"AHX"                       OP_ILLEGAL(ahx)
"SHY"                       OP_ILLEGAL(shy)
"SHX"                       OP_ILLEGAL(shx)
"TAS"                       OP_ILLEGAL(tas)
"LAS"                       OP_ILLEGAL(las)
"BRA"                       OP_65C02(bra)
"PHX"                       OP_65C02(phx)
"PHY"                       OP_65C02(phy)
"PLX"                       OP_65C02(plx)
"PLY"                       OP_65C02(ply)
"STZ"                       OP_65C02(stz)
"TRB"                       OP_65C02(trb)
"TSB"                       OP_65C02(tsb)
"STP"                       OP_65C02(stp)
"WAI"                       OP_65C02(wai)
"BBR"[0-7]                  OP_65C02_REL(bbr)
"BBS"[0-7]                  OP_65C02_REL(bbs)
"RMB"[0-7]                  OP_65C02_REL(rmb)
"SMB"[0-7]                  OP_65C02_REL(smb)

".BYTE"                     return BYTE;
".DB"                       return BYTE;
".DCB"                      return BYTE;
".WORD"                     return WORD;
".DW"                       return WORD;
".DCW"                      return WORD;
".DS"                       return DS;
".EQU"                      return EQU;
"NOT"                       return NOT;
">="                        return GE;
"<="                        return LE;
"=="                        return EQ;
"!="                        return NE;
"<>"                        return NE;
"<<"                        return SHIFT_LEFT;
">>"                        return SHIFT_RIGHT;
{LOGOR}                     return OR;
{BITOR}                     return BIT_OR;
{LOGAND}                    return AND;
{BITAND}                    return BIT_AND;
".REPEAT"                   return REPEAT;
".UNTIL"                    return UNTIL;
".END"                      return END;
".ENDIF"                    return ENDIF;
".IF"                       return IF;
".ELSE"                     return ELSE;
".PRINT"                    return PRINT;
"\?"                        return PRINT;
".PRINTALL"                 return PRINTALL;                   
"\?\?"                      return PRINTALL;
".FOR"                      return FOR;
".NEXT"                     return NEXT;
".STEP"                     return STEP;
".TO"                       return TO;
".DOWNTO"                   return DOWNTO;
".STR"						return STR;
".STRING"				    return STR;
".ORG"                      return ORG;
".SECTION"                  return SECTION;
".ENDSECTION"               return ENDSECTION;
 ".SECT"                    return SECTION;
 ".ENDS"                    return ENDSECTION;
 ".INC"                     return INC;
 ".LOAD"                    return LOAD;
".WHILE"                    { 
                                if (inDoLoop > 0) 
                                { 
                                    inDoLoop--; 
                                    return ENDDO; 
                                } 
                                else 
                                { 
                                    inDoLoop = 0;
                                    return WHILE;
                                }
                            }
".WEND"                     { return WEND; }
".DO"                       { inDoLoop++; return DO; }
".MACRO"                    { inMacroDef++; return MACRO; }
".MAC"                      { inMacroDef++; return MACRO; }
".ENDMACRO"                 { inMacroDef--; return ENDMACRO; }
".ENDM"                     { inMacroDef--; return ENDMACRO; }
".REGX"                     { return REGX; }
".REGY"                     { return REGY; }
".VAR"                      { return VAR;  }
".6502"[ /t]*"ON"           { CPUMode = cpu_6502; }
".65C02"[ /t]*"ON"          { CPUMode = cpu_65C02; }
".ILLEGAL"[ /t]*"ON"        { AllowIllegalOpCpodes = TRUE; }
".ILLEGAL"[ /t]*"OFF"       { AllowIllegalOpCpodes = FALSE; }
".WARN"[ /t]*"ON"           { NoWarnings = FALSE; }
".WARN"[ /t]*"OFF"          { NoWarnings = TRUE; }
".C64"                      { OutFileFormat = c64; }
^"-"                        { yylval.strValue = StrDup(yytext); return SYMBOL; }
^"+"                        { yylval.strValue = StrDup(yytext); return SYMBOL; }
[@][0-9]+                   {
                                if (!inMacroDef)
                                    REJECT;
                                yylval.strValue = StrDup(yytext); 
                                return SYMBOL;
                            }
[\+|\-]+                    {
                                if (strlen(yytext) > 1)
                                {
                                    yylval.strValue = StrDup(yytext); 
                                    return SYMBOL;
                                }
                                else
                                {
                                    return *yytext;
                                }
                            }
[\'].[\']                   INT_1BYTE
[\'][\\].[\']               INT_1BYTE
$[0-9A-Fa-f]*               INT(1, 16)
[\'][\\]x[0-9A-Fa-f]+[\']   INT(3, 16)
[0-9]*                      INT(0, 10)
%[0-1]*                     INT(1, 2)
0b[0-1]*                    INT(2, 2)
[\'][\\][0-7]{3}[\']        INT(2, 8)

{STRVALUE}					{ yylval.strValue = StrDup(yytext); return STRING_LITERAL; }
"*"[ /t]*[=]                { unput('='); return PCASSIGN; }
"*"[ /t]*".EQU"             { unput('='); return PCASSIGN; }
"X"                         { return 'X'; }
"Y"                         { return 'Y'; }
[A-Za-z_][A-Za-z0-9_.]*:?   { yylval.strValue = StrDup(yytext); return SYMBOL; }
"/*"                        { BEGIN(C_COMMENT); }
<C_COMMENT>"*/"             { BEGIN(INITIAL); }
<C_COMMENT>.|[\n]           { /* ignore comments */ }
;[^\n]*                     { /* ignore comments */ }
[/][/][^\n]*                { /* ignore comments */ }
"~"                         { return '~'; }
"^"                         { return '^'; }
[-<>=+*/#,();=\n]           { return *yytext; }
[ \t]+                      { /* ignore white space */ }
<<EOF>>                     {
                                yypop_buffer_state();
                                if (fileStackIndex > 0)
                                {
                                    if (FinalPass) GenerateListNode(NULL);

                                    CurFileName = fileStack[--fileStackIndex];
                                    yylineno = fileLineStack[fileStackIndex];

                                    if (FinalPass) GenerateListNode(NULL);
                                }
                                if ( !YY_CURRENT_BUFFER )
                                {
                                    yyterminate();
                                }
                            }
.                           { yyerror("syntax error"); }

%%

int OpenIncludeFile(char* file)
{
    const char* module = "OpenIncludeFile";

    if (FinalPass) GenerateListNode(NULL);

    if (fileStackIndex + 1 >= MAX_INCLUDE_STACK)
    {
        FatalError(module, error_include_file_stack_overflow);
    }
    fileLineStack[fileStackIndex] = yylineno;
    fileStack[fileStackIndex++] = CurFileName;
    CurFileName = file;

    yyin = OpenFile( file, "r" );
    yylineno = 0;

    if (FinalPass) GenerateListNode(NULL);

    if ( ! yyin )
    {
        yyerror(file);
        FatalError(module, error_cant_open_include_file);
    }
	yypush_buffer_state(yy_create_buffer( yyin, YY_BUF_SIZE ));
    return 0;
}
