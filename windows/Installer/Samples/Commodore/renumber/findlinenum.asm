;********************************************
;*                                          *
;* FINDLINENUM                              *
;*                                          *
;*  find line number in a sorted table      *
;*  using a binary search                   *
;*                                          *
;********************************************
FINDLINENUM
        ;
        ;   init maxidx
        ;
        MOVE16 TBLSZ,MAXIDX

        ;
        ;   init lastidx
        ;
        lda #$FF
        sta LASTIDX
        sta LASTIDX + 1

        ;
        ;   convert maxidx to bytes
        ;
        sec
        asl MAXIDX
        rol MAXIDX  + 1

        ;
        ;   init minidx
        ;
        lda #0
        sta MINIDX
        sta MINIDX  + 1

.ifdef debug
        jsr DUMP_LN
        jsr DUMP_STAR
.endif
-
.ifdef debug
        jsr DUMP_MX
        jsr DUMP_MN
        jsr DUMP_TS
.endif
        ;
        ;   calculate next index to table
        ;   table is sorted so binary search
        ;   maxidx  - minidx
        ;
        SUB16 MAXIDX,MINIDX,CURIDX

        ;
        ;   divide by 2
        ;
        lsr CURIDX  + 1         ;   curidx >> 1
        ror CURIDX

        ;
        ;   add minidx
        ;
        ;   curidx += minidx
        ADD16 CURIDX,MINIDX,CURIDX

        ;
        ;   make CURIDX even (low byte)
        ;
        lda CURIDX              ;   curidx &= 0xFFFE
        and #~%00000001
        sta CURIDX

        ;
        ;   check to see if we tried this already
        ;
        cmp LASTIDX
        bne +
        lda CURIDX  + 1
        cmp LASTIDX + 1
        bne +

        ;
        ;   we can't find the line
        ;
        rts
+
        ;
        ;   save current index
        ;
        MOVE16 CURIDX,LASTIDX

        ;
        ;   load tbl[curinx]
        ;
        ADD16 TBL,CURIDX,TBLPTR

.ifdef debug
        jsr DUMP_NEWLINE
        jsr DUMP_I
        jsr DUMP_TP
        jsr DUMP_TE
.endif
        ;
        ;   compare high byte
        ;
        ldy #1
        lda (TBLPTR),y
        cmp LNUM + 1
        bne +
        ;
        ;   compare low byte
        ;
        dey
        lda (TBLPTR),y
        cmp LNUM
        beq +++
+
        ;
        ;   not equal
        ;
        bcc +

.ifdef debug
        jsr DUMP_PLUS
.endif
        ;
        ;   table entry greater than lnum
        ;
        MOVE16 CURIDX, MAXIDX
        jmp -                   ;   try next guess
+
.ifdef debug
        jsr DUMP_MINUS
.endif
        ;
        ;   table entry less than lnum
        ;
        MOVE16 CURIDX,MINIDX
        jmp -                   ;   try next guess
+
.ifdef debug
        jsr DUMP_FOUNDLINE
.endif
        rts
