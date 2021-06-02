
;********************************************
;*                                          *
;* INSERTLINENUM                            *
;*                                          *
;*  insert new linenumber in basic program  *
;*                                          *
;********************************************
INSERTLINENUM
        PUSHAY
        ;
        ;   we found the line
        ;   now calculate the new line number based on index
        ;
        lsr CURIDX + 1          ; curidx >>= 1
        ror CURIDX

        ;
        ; multiply by line increment and store in product
        ;
        MULT16 CURIDX,INCR,PRODUCT

        ;
        ;   add start line
        ;   store in BNVAR
        ;
        clc
        lda LSTART
        adc PRODUCT
        sta BNVAR
        lda LSTART + 1
        adc PRODUCT + 1
        sta BNVAR + 1

        jsr BINBCD16

.ifdef debug
        PUSHAY
        jsr PRINTBCDSTR
        POPAY
.endif
        jsr BCDLENGTH

.ifdef debug
        jsr DUMP_LENGTH
        lda BCDLEN
        jsr DUMP_BYTE
        jsr DUMP_EQUALS
        lda LNUMLEN
        jsr DUMP_BYTE
        jsr DUMP_NEWLINE
.endif
        lda LNUMLEN
        cmp BCDLEN
        bne +

        ;
        ;   line numbers are the same length
        ;
        ldy LININS
        ;
        ;   get offset to bcdstring
        ;
-
        sec
        lda #5
        sbc BCDLEN
        tax
        ;
        ;   copy string into line
        ;
-
        lda BCDSTR,x
        sta (NXTLN),y
        iny
        inx
        cpx #5
        bne -

        tya
        tax
        dex

        POPAY
        rts
+
        bcc +

        ;
        ;   new line number is smaller
        ;
        jsr MOVELINESDOWN
-
        ldy LININS
        bne ---

        ;
        ;   new line number is larger
        ;
+
        jsr MOVELINESUP
        jmp -
