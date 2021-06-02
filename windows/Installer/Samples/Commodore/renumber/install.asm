        *=  $C000
        TBLLOC  = $A000

.ifdef debug
        .print "debug version"
.endif

;********************************************
;*                                          *
;*  INSTALL                                 *
;*                                          *
;********************************************
INSTALL

        cli

        ;
        ;   install wedge
        ;
        MOVE16 IGONE,IGONE_SV
        MOVE16I IGONE,WEDGE

        ;
        ;   set NXTLN
        ;
        lda TXTTAB              ;   load start of basic
        sta NXTLN               ;   into next line
        sta STREND
        lda TXTTAB + 1
        sta NXTLN + 1
        sta STREND + 1

        lda #0
        ldy #5
-
        sta (NXTLN),y
        dey
        bne -

        ADD16I STREND,2,STREND
        MOVE16 MEMSIZ,FRETOP

        lda STREND
        sta VARTAB
        sta ARYTAB
        lda STREND + 1
        sta VARTAB + 1
        sta ARYTAB + 1

        sei

        jmp WARM
