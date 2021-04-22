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

typedef enum
{
    cpu_6502,
    cpu_65C02
} CPU;

//
// This order MUST match the tables in opcodes.c
// this serves as an index into the tables
//
typedef enum
{
    _ora = 0,
    _and,
    _eor,
    _adc,
    _sbc,
    _cmp,
    _cpx,
    _cpy,
    _dec,
    _dex,
    _dey,
    _inc,
    _inx,
    _iny,
    _asl,
    _rol,
    _lsr,
    _ror,
    _lda,
    _sta,
    _ldx,
    _stx,
    _ldy,
    _sty,
    _rmb0,
    _rmb1,
    _rmb2,
    _rmb3,
    _rmb4,
    _rmb5,
    _rmb6,
    _rmb7,
    _smb0,
    _smb1,
    _smb2,
    _smb3,
    _smb4,
    _smb5,
    _smb6,
    _smb7,
    _stz,
    _tax,
    _txa,
    _tay,
    _tya,
    _tsx,
    _txs,
    _pla,
    _pha,
    _plp,
    _php,
    _phx,
    _phy,
    _plx,
    _ply,
    _bra,
    _bpl,
    _bmi,
    _bvc,
    _bvs,
    _bcc,
    _bcs,
    _bne,
    _beq,
    _bbr0, 
    _bbr1, 
    _bbr2, 
    _bbr3, 
    _bbr4, 
    _bbr5, 
    _bbr6, 
    _bbr7, 
    _bbs0, 
    _bbs1, 
    _bbs2, 
    _bbs3, 
    _bbs4, 
    _bbs5, 
    _bbs6, 
    _bbs7,
    _stp,
    _wai,
    _brk,
    _rti,
    _jsr,
    _rts,
    _jmp,
    _bit,
    _trb,
    _tsb,
    _clc,
    _sec,
    _cld,
    _sed,
    _cli,
    _sei,
    _clv,
    _nop,

    /* below are illegal opcodes */
    _illegalStart,
    _slo = _illegalStart,
    _rla,
    _sre,
    _rra,
    _sax,
    _lax,
    _dcp,
    _isc,
    _anc,
    _anc2,
    _alr,
    _arr,
    _xaa,
    _lax2,
    _axs,
    _sbc2,
    _ahx,
    _shy,
    _shx,
    _tas,
    _las,
    _maxOpcode
} Instruction;

typedef enum
{
    i = 0,  /* implied              */
    I,      /* immediate            */
    zp,     /* zero page            */
    zpi,    /* zero page indirect   */
    zpx,    /* zero page x          */
    zpy,    /* zero page y          */
    zpix,   /* zero page indirect x */
    zpiy,   /* zero page indirect y */
    a,      /* absolute             */
    aix,    /* absolute indirect x  */
    ax,     /* absolute x           */
    ay,     /* absolute y           */
    ind,    /* absolute indirect    */
    r,      /* relative             */
    zr,     /* zero page relative   */
    A,      /* Accumulator          */
    maxAddressingMode
} AddressingModes;

extern int AllowIllegalOpCodes;
extern CPU CPUMode;
extern int GetOpCode(int instruction, int addressingMode);
extern char * InstructionToString(int instruction);
extern char* ModeToString(int mode);

