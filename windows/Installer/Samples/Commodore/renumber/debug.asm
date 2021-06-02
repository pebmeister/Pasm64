
.ifdef debug

        .macro DMP_BYT

        PUSHAY

        jsr DUMP_NEWLINE

        lda #>\1
        ldy #<\1
        jsr DUMP_STR
        lda \2       
        jsr DUMP_BYTE

        POPAY            
        .endm

        .macro DMP_WRD

        PUSHAY

        jsr DUMP_NEWLINE

        lda #>\1
        ldy #<\1
        jsr DUMP_STR
        lda \2 
        ldy \2 + 1
        jsr DUMP_BYTE

        POPAY
        
        .endm

;********************************************
;*                                          *
;* DUMP_REGISTERS                           *
;*                                          *
;*  print values of all registers           *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_REGISTER
        php

        sta ACC
        stx XREG
        sty YREG

        pla
        sta PSTATUS

        tsx
        inx                     ;   account for pushed return address
        inx
        stx SP

        ;
        ;   get the return address
        ;
        pla
        sta PC_ORIGINAL
        pla
        sta PC_ORIGINAL + 1

        cld

        sec                     ;   we need to fix pc on stack
        lda PC_ORIGINAL
        sbc #02
        sta PC
        lda PC_ORIGINAL + 1
        sbc #0
        sta PC + 1

        ;
        ;   dump a new line
        ;
        jsr DUMP_NEWLINE
        bne +

-       .byte " SP=",0
-       .byte " Y=",0
-       .byte " X=",0
-       .byte " A=",0
-       .byte " PC=",0

        ;
        ;   Program counter
        ;
+
        DMP_WRD -,PC

        ;
        ;   A Register
        ;
        DMP_BYT --,ACC

        ;
        ;   X Register
        ;
        DMP_BYT ---,XREG

        ;
        ;   Y Register
        ;
        DMP_BYT ----,YREG

        ;
        ;   Stack Pointer
        ;
        DMP_BYT -----,SP + 2

        ;
        ;   pstatus flag
        jsr DUMP_SPACE          ;   dump pstatus flags
        lda #$80                ;   set mask forprocessor
        sta STATTMP
        ldy #0
        ;
        ; fall through
        ;
;********************************************
;*                                          *
;* DUMP_STATUS                              *
;*                                          *
;*  print status register                   *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
DUMP_STATUS
        lda PSTATUS
        and STATTMP
        bne +

        lda #'.'
        bne ++
+
        lda DUMP_BITS,y
+
        jsr CHROUT
        lsr STATTMP
        iny
        cpy #8                  ;   is this the last bit?
        bne DUMP_STATUS

        jsr DUMP_NEWLINE
                                ;   prepare for exit
                                ;   push orginal return address on stack
        lda PC_ORIGINAL + 1
        pha
        lda PC_ORIGINAL
        pha

        lda PSTATUS             ;   push original processor status
        pha
        lda ACC                 ;   restore accumulator
        ldx XREG                ;   restore x
        ldy YREG                ;   restore y
        plp                     ;   pull processor status
        rts                     ;   exit to caller


;   symbolic codes for pstatus register bits

DUMP_BITS       .byte "NV.BDIZC"
PC_ORIGINAL     .word 0
PC              .word 0
ACC             .byte 0
XREG            .byte 0
YREG            .byte 0
SP              .byte 0
PSTATUS         .byte 0
STATTMP         .byte 0

;********************************************
;*                                          *
;* DUMP_LI                                  *
;*                                          *
;*  print line number                       *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_LI
        DMP_BYT +,LININS
        rts
+       .byte " LI=",0

;********************************************
;*                                          *
;* DUMP_LN                                  *
;*                                          *
;*  print line number                       *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_LN
        DMP_WRD +,LNUM
        rts
+       .byte " LN=",0

;********************************************
;*                                          *
;* DUMP_MX                                  *
;*                                          *
;*  print max                               *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_MX
        DMP_WRD +,MAXIDX
        rts
+               .byte " MX=",0

;********************************************
;*                                          *
;* DUMP_MN                                  *
;*                                          *
;*  print min                               *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_MN
        DMP_WRD +,MINIDX
        rts
+       .byte " MN=",0

;********************************************
;*                                          *
;* DUMP_TS                                  *
;*                                          *
;*  print table size                        *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_TS
        DMP_WRD +,TBLSZ
        rts
+       .byte " TS=",0

;********************************************
;*                                          *
;* DUMP_I                                   *
;*                                          *
;*  print index, tablentry                  *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_I
        DMP_WRD +,CURIDX
        rts
+       .byte " I=",0

;********************************************
;*                                          *
;* DUMP_TP                                  *
;*                                          *
;*  print TablePointer                      *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_TP
        DMP_WRD +,TBLPTR
        rts
+       .byte " TP=", 0

;********************************************
;*                                          *
;* DUMP_TE                                  *
;*                                          *
;*  print TableEntry                        *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_TE
        PUSHAY

        lda #>+
        ldy #<+
        jsr DUMP_STR
        ldy #0
        lda (TBLPTR),y
        pha
        iny
        lda (TBLPTR),y
        tay
        pla
        jsr DUMP_WORD
        jsr DUMP_NEWLINE

        POPAY
        rts
+       .byte " TE=", 0

;********************************************
;*                                          *
;* DUMP_NXTLN                               *
;*                                          *
;*  print NXTLN=xxxx                        *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_NXTLN
        DMP_WRD +,NXTLN
        rts
+       .byte " NXTLN=",0

;********************************************
;*                                          *
;* DUMP_FOUNDLINE                           *
;*                                          *
;*  print FOUND LINE                        *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_FOUNDLINE
        PUSHAY

        lda #>+
        ldy #<+
        jsr DUMP_STR

        POPAY
        rts
+       .byte "FOUND LINE ",0

;********************************************
;*                                          *
;* DUMP_LENGTH                              *
;*                                          *
;*  print LENGTH=                           *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_LENGTH
        PUSHAY

        lda #>+
        ldy #<+
        jsr DUMP_STR

        POPAY
        rts
+       .byte "LEN=",0

;********************************************
;*                                          *
;* DUMP_STAR                                *
;*                                          *
;*  print *                                 *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_STAR
        PUSHAY

        lda #>+
        ldy #<+
        jsr DUMP_STR

        POPAY
        rts
+       .byte "      *",0

;********************************************
;*                                          *
;* DUMP_PLUS                                *
;*                                          *
;*  print +                                 *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_PLUS
        PUSHAY

        lda #>+
        ldy #<+
        jsr DUMP_STR

        POPAY
        rts
+       .byte "      +",0

;********************************************
;*                                          *
;* DUMP_MINUS                               *
;*                                          *
;*  print -                                 *
;*                                          *
;*  destroys nothing                        *
;*                                          *
;********************************************
DUMP_MINUS
        PUSHAY

        lda #>+
        ldy #<+
        jsr DUMP_STR

        POPAY
        rts
+       .byte "      -",0

;********************************************
;*                                          *
;* DUMP_NEWLINE                             *
;*                                          *
;*  print 0x0D                              *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
DUMP_NEWLINE
        lda #13
        jmp CHROUT

;********************************************
;*                                          *
;* DUMP_SPACE                               *
;*                                          *
;*  print ' '                               *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
DUMP_SPACE
        lda #' '
        jmp CHROUT

;********************************************
;*                                          *
;* DUMP_EQUALS                              *
;*                                          *
;*  print =                                 *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
DUMP_EQUALS
        lda #'='
        jmp CHROUT

;********************************************
;*                                          *
;* DUMP_WORD                                *
;*                                          *
;*  print number in a(lo) y (hi) in hex     *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
DUMP_WORD
        pha
        tya
        jsr DUMP_BYTE
        pla

;********************************************
;*                                          *
;* DUMP_BYTE                                *
;*                                          *
;*  print number in a  in hex               *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
DUMP_BYTE
        pha
        lsr
        lsr
        lsr
        lsr
        jsr DUMP_NYBBLE
        pla
        and #$0F
        ; fall through

;********************************************
;*                                          *
;* DUMP_NYBBLE                              *
;*                                          *
;*  converts the 4 bit nybble in a to       *
;*  an ascii character and prints it        *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
DUMP_NYBBLE
        ora #'0'
        cmp #'9' + 1
        bcc +
        adc #'A' - ('9' + 2)
+
        jmp CHROUT

;********************************************
;*                                          *
;* DUMP_STR                                 *
;*                                          *
;*  print string pointed to by y and a      *
;*  a low byte y high byte null byte marks  *
;*  end of string                           *
;*  destroys a,y                            *
;*                                          *
;********************************************
DUMP_STR
        sty DUMPSTR
        sta DUMPSTR + 1
        ldy #0
-
        lda (DUMPSTR),y
        beq +
        jsr CHROUT
        iny
        bne -
+
        rts

;********************************************
;*                                          *
;*  PRNTLN                                  *
;*                                          *
;*  print the current line                  *
;*  nxtln must be current line              *
;*                                          *
;*  destroys    a,y                         *
;*                                          *
;********************************************
PRNTLN
        ;
        ;   get current line number
        ;   store in bnvar
        ;
        ldy #LNOFF
        lda (NXTLN),y
        sta BNVAR
        iny
        lda (NXTLN),y
        sta BNVAR+1
        ;
        ;   fall through to printnum
        ;
;********************************************
;*                                          *
;*  PRINTNUM                                *
;*                                          *
;*  print number in bnvar in decimal        *
;*  with a trailing space                   *
;*                                          *
;*  destroys    a,y,x                       *
;*                                          *
;********************************************
PRINTNUM
        ;
        ;   convert to bcd and string
        ;
        jsr BINBCD16

        ;
        ;   fall through to printnum
        ;
;********************************************
;*                                          *
;*  PRINTBCDSTR                             *
;*                                          *
;*  print number in bcdstr in decimal       *
;*  with a trailing space                   *
;*                                          *
;*  destroys    a,y,x                       *
;*                                          *
;********************************************
PRINTBCDSTR
        ;
        ;   loop through 5 chars
        ;
        ldy #0
        sty LDZFLG
-
        lda BCDSTR,y
        cmp #'0'
        bne +

        cpy #4
        beq +

        ldx LDZFLG
        beq ++
+
        jsr CHROUT
        inc LDZFLG
+
        iny
        cpy #5
        bne -

        lda #' '

        jmp CHROUT

.endif
