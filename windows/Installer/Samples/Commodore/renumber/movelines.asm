
FROM    = MINIDX
TO      = MAXIDX
SIZEL   = CURIDX
SIZEH   = CURIDX + 1
;********************************************
;*                                          *
;* MOVELINESDOWN                            *
;*                                          *
;*  move basic lines to get rid of extra    *
;*  space                                   *
;*                                          *
;********************************************
MOVELINESDOWN
                ;
                ;   save nxtln
                ;
                SAVEZP NXTLN,+,2

                ;
                ;   set MINIDX to endptr
                ;
                lda NXTLN
                sta MINIDX
                lda NXTLN + 1
                sta MINIDX + 1
                clc
                lda LININS
                adc MINIDX
                sta MINIDX
                lda #0
                adc MINIDX + 1
                sta MINIDX + 1

                ;
                ;   find out how many more bytes we need
                ;
                sec
                lda LNUMLEN
                sbc BCDLEN
                sta LASTIDX

                ;
                ;   fix basic variables
                ;
                sec
                lda STREND
                sbc LASTIDX
                sta STREND
                lda STREND+1
                sbc #0
                sta STREND+1

                ;
                ;   subtract from the line start pointers
                ;
-
                ldy #NXOFF
                sec
                lda (NXTLN),y
                sta MAXIDX
                sbc LASTIDX
                sta (NXTLN),y
                iny
                lda (NXTLN),y
                sta MAXIDX + 1
                sbc #0
                sta (NXTLN),y

                ;
                ;   copy maxidx to nxtln
                ;
                lda MAXIDX
                sta NXTLN
                lda MAXIDX + 1
                sta NXTLN + 1

                ;
                ;   check for end of basic
                ;
                jsr LASTLINE
                bne -

                ;
                ;   figure out numbytes to move
                ;
                sec
                lda MAXIDX
                sbc MINIDX
                sta CURIDX
                lda MAXIDX + 1
                sbc MINIDX + 1
                sta CURIDX + 1

                ;
                ;   add EOL and end of basic marker
                ;
                clc
                lda CURIDX
                adc #4
                sta CURIDX
                lda CURIDX + 1
                adc #0
                sta CURIDX + 1

                ;
                ;   set max to new dest address
                ;
                clc
                lda MINIDX
                adc LASTIDX
                sta MAXIDX
                lda MINIDX + 1
                adc #0
                sta MAXIDX + 1

                ;
                ;   we need to swap maxidx and minidx
                ;
                lda MINIDX
                sta NXTLN
                lda MINIDX + 1
                sta NXTLN + 1
                lda MAXIDX
                sta MINIDX
                lda MAXIDX + 1
                sta MINIDX + 1
                lda NXTLN
                sta MAXIDX
                lda NXTLN + 1
                sta MAXIDX + 1

                jsr MOVEDOWN

                ;
                ;   restore nxtln
                ;
                SAVEZP +,NXTLN,2
                rts

+               .word 0
;********************************************
;*                                          *
;* MOVELINESUP                              *
;*                                          *
;*  move basic lines to add room            *
;*                                          *
;********************************************
MOVELINESUP
                ;
                ;   save nxtln
                ;
                SAVEZP NXTLN,+,2

                ;
                ;   set MINIDX to endptr
                ;
                lda NXTLN
                sta MINIDX
                lda NXTLN + 1
                sta MINIDX + 1
                clc
                lda LININS
                adc MINIDX
                sta MINIDX
                lda #0
                adc MINIDX + 1
                sta MINIDX + 1

                ;
                ;   find out how many more bytes we need
                ;
                sec
                lda BCDLEN
                sbc LNUMLEN
                sta LASTIDX

                ;
                ;   fix basic variables
                ;
                clc
                adc STREND
                sta STREND
                lda #0
                adc STREND+1
                sta STREND+1

                ;
                ;   add to the line start pointers
                ;
-
                ldy #NXOFF
                clc
                lda (NXTLN),y
                sta MAXIDX
                adc LASTIDX
                sta (NXTLN),y
                iny
                lda (NXTLN),y
                sta MAXIDX + 1
                adc #0
                sta (NXTLN),y

                ;
                ;   copy maxidx to nxtln
                ;
                lda MAXIDX
                sta NXTLN
                lda MAXIDX + 1
                sta NXTLN + 1

                ;
                ;   check for end of basic
                ;
                jsr LASTLINE
                bne -

                ;
                ;   figure out numbytes to move
                ;
                sec
                lda MAXIDX
                sbc MINIDX
                sta CURIDX
                lda MAXIDX + 1
                sbc MINIDX + 1
                sta CURIDX + 1

                ;
                ;   add EOL and end of basic marker
                ;
                clc
                lda CURIDX
                adc #4
                sta CURIDX
                lda CURIDX + 1
                adc #0
                sta CURIDX + 1

                ;
                ;   set max to new dest address
                ;
                clc
                lda MINIDX
                adc LASTIDX
                sta MAXIDX
                lda MINIDX + 1
                adc #0
                sta MAXIDX + 1

                jsr MOVEUP

                ;
                ;   restore nxtln
                ;
                SAVEZP +,NXTLN,2

                rts

+               .word 0

;********************************************
;*                                          *
;* Move memory up                           *
;*                                          *
;* FROM = source start address              *
;*   TO = destination start address         *
;* SIZE = number of bytes to move           *
;*                                          *
;********************************************
MOVEUP
                ldx SIZEH               ; the last byte must be moved first
                clc                     ; start at the final pages of from and to
                txa
                adc FROM + 1
                sta FROM + 1
                clc
                txa
                adc TO + 1
                sta TO + 1
                inx                     ; allows the use of bne after the dex below
                ldy SIZEL
                beq ++
                dey                     ; move bytes on the last page first
                beq +
-
                lda (FROM),y
                sta (TO),y
                dey
                bne -
+
                lda (FROM),y            ; handle Y = 0 separately
                sta (TO),y
+
                dey
                dec FROM + 1            ; move the next page (if any)
                dec TO + 1
                dex
                bne -

                rts

;********************************************
; Move memory down                          *
;                                           *
; FROM = source start address               *
;   TO = destination start address          *
; SIZE = number of bytes to move            *
;                                           *
;********************************************
MOVEDOWN
                ldy #0
                ldx SIZEH
                beq +
-
                lda (FROM),y            ;   move a page at a time
                sta (TO),y
                iny
                bne -
                inc FROM + 1
                inc TO + 1
                dex
                bne -
+
                ldx SIZEL
                beq +
-
                lda (FROM),y            ;   move the remaining bytes
                sta (TO),y
                iny
                dex
                bne -
+
                rts
