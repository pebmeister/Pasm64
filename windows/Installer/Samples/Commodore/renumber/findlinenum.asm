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
                lda TBLSZ
                sta MAXIDX
                lda TBLSZ + 1
                sta MAXIDX + 1

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
                sec
                lda MAXIDX              ;   curidx = maxidx - minidx
                sbc MINIDX
                sta CURIDX
                lda MAXIDX + 1
                sbc MINIDX + 1
                sta CURIDX + 1

                ;
                ;   divide by 2
                ;
                lsr CURIDX  + 1         ;   curidx >> 1
                ror CURIDX

                ;
                ;   add minidx
                ;
                clc                     ;   curidx += minidx
                lda CURIDX
                adc MINIDX
                sta CURIDX
                lda CURIDX  + 1
                adc MINIDX  + 1
                sta CURIDX  + 1

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
                lda CURIDX
                sta LASTIDX
                lda CURIDX + 1
                sta LASTIDX + 1

                ;
                ;   load tbl[curinx]
                ;
                clc
                lda TBL
                adc CURIDX
                sta TBLPTR
                lda TBL + 1
                adc CURIDX + 1
                sta TBLPTR + 1
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
                lda CURIDX
                sta MAXIDX
                lda CURIDX + 1
                sta MAXIDX + 1
                jmp -                   ;   try next guess
+
.ifdef debug
                jsr DUMP_MINUS
.endif
                ;
                ;   table entry less than lnum
                ;
                lda CURIDX
                sta MINIDX
                lda CURIDX + 1
                sta MINIDX + 1
                jmp -                   ;   try next guess
+
.ifdef debug
                jsr DUMP_FOUNDLINE
.endif
                rts
