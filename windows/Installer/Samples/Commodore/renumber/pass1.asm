;****************************************
;*                                      *
;* PASS1                                *
;*                                      *
;*  create table for old and new lines  *
;*  update line numbers                 *
;*  gotos etc will be fixes in pass2    *
;*                                      *
;****************************************
PASS1
                ;
                ; check for last line of basic
                ;
                jsr LASTLINE
                bne +
                jmp ++++
+
                ;
                ; save original line number in table
                ;
                jsr SAVETBL

                ;
                ; update the line number in basic
                ;
                ldy #LNOFF
                lda LNUM
                sta (NXTLN),y
                lda LNUM + 1
                iny
                sta (NXTLN),y

                ;
                ; add line increment to line number
                ;
                clc
                lda LNUM
                adc INCR
                sta LNUM
                lda LNUM + 1
                adc INCR + 1
                sta LNUM + 1

                bcc ++

                ;
                ;   We wrapped. Line number too big
                ;   restore original lines and then error out

                ;
                ;   set NXTLN
                ;
                lda TXTTAB              ;   load start of basic
                sta NXTLN               ;   into next line
                lda TXTTAB + 1
                sta NXTLN + 1

                lda TBL
                sta TBLTMP
                lda TBL + 1
                sta TBLTMP + 1
-
                ldy #0
                lda (TBLTMP),y
                ldy #LNOFF
                sta (NXTLN),y
                ldy #1
                lda (TBLTMP),y
                ldy #LNOFF + 1
                sta (NXTLN),y

                lda TBLSZ
                bne +
                lda TBLSZ + 1
                bne +

                sec
                rts
+
                sec
                lda TBLSZ
                sbc #<1
                sta TBLSZ
                lda TBLSZ + 1
                sbc #>1
                sta TBLSZ + 1

                clc
                lda TBLTMP
                adc #<2
                sta TBLTMP
                lda TBLTMP + 1
                adc #>2
                sta TBLTMP + 1

                ldy #NXOFF
                lda (NXTLN),y
                tax
                iny
                lda (NXTLN),y
                stx NXTLN
                sta NXTLN + 1
                jmp -

                ;
                ; get the next line ptr
                ; store in nxtln
                ;
+
                ldy #NXOFF
                lda (NXTLN),y
                tax
                iny
                lda (NXTLN),y
                stx NXTLN
                sta NXTLN + 1

                ;
                ; increment table size
                ;
                clc
                lda TBLSZ
                adc #<1
                sta TBLSZ
                lda TBLSZ + 1
                adc #>1
                sta TBLSZ + 1
                jmp PASS1

+
                ;
                ; clear carry to signal success
                ;
                clc
                rts

;****************************************
;*                                      *
;* SAVETBL                              *
;*                                      *
;*  add the cuurent line to the table   *
;*  nxtln must point to start of line   *
;*                                      *
;*  destroys a,y                        *
;*                                      *
;****************************************
SAVETBL
                ;
                ; move line number to bnvar
                ;
                ldy #LNOFF
                lda (NXTLN),y
                tax
                iny
                lda (NXTLN),y
                stx BNVAR
                sta BNVAR + 1

                ;
                ; tbltmp points to next spot in table
                ; store line number contained bnvar in table
                ;
                ldy #0
                lda BNVAR
                sta (TBLTMP),y
                lda BNVAR + 1
                iny
                sta (TBLTMP),y

                ;
                ; increment table ptr by 2 bytes
                ;
                clc
                lda TBLTMP
                adc #<2
                sta TBLTMP
                lda TBLTMP + 1
                adc #>2
                sta TBLTMP + 1
                rts
