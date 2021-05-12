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
                SAVEZP IGONE,IGONE_SV,2

                lda #<WEDGE
                sta IGONE
                lda #>WEDGE
                sta IGONE + 1

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

                clc
                lda #2
                adc STREND
                sta STREND
                lda #0
                adc STREND + 1
                sta STREND + 1

                lda MEMSIZ
                sta FRETOP
                lda MEMSIZ + 1
                sta FRETOP + 1

                lda STREND
                sta VARTAB
                sta ARYTAB
                lda STREND + 1
                sta VARTAB + 1
                sta ARYTAB + 1

                sei

                jmp WARM
