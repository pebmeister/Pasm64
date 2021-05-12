;********************************************
;*                                          *
;*  WEDGE                                   *
;*                                          *
;********************************************
WEDGE
                lda CURLIN + 1
                cmp #$FF
                beq +

                jmp (IGONE_SV)
                
+
                ldy #1
-
                lda RENUMCMD,y
                beq +

                cmp (TXTPTR),y
                bne +++++
                iny
                bne -
+
                dey
-
                jsr CHRGET
                dey
                bne -
                ;
                ;   init line number to 100
                ;
                lda #<100
                sta LSTART
                lda #>100
                sta LSTART + 1

                ;
                ;   init line increment
                ;
                lda #<10
                sta INCR
                lda #>10
                sta INCR + 1

                ldy #1
                lda (TXTPTR),y
                beq +++

                jsr CHRGET
+
                jsr GETLN
                ldy LNUMLEN
                beq +++
                jsr VALIDATE

                lda LNUM
                sta LSTART
                lda LNUM + 1
                sta LSTART + 1
                dey
                beq +
-
                jsr CHRGET
                dey
                bne -
+
                ldy #1
                lda (TXTPTR),y
                beq +

                jsr CHRGET
                cmp #','
                bne ++

                ldy #1
                lda (TXTPTR),y
                beq +

                jsr CHRGET

                jsr GETLN
                ldy LNUMLEN
                beq ++
                jsr VALIDATE

                lda LNUM
                sta INCR
                lda LNUM + 1
                sta INCR + 1
                dey
                beq +
-
                jsr CHRGET
                dey
                bne -
+
                jsr START
                bcc +

                ldx #ILLEGALQUANITY
                jmp ERROR

+
                jmp (IGONE_SV)
GETLN
                lda TXTPTR
                sta NXTLN
                lda TXTPTR + 1
                sta NXTLN + 1
                ldy #0
                jsr GETLINENUM
                rts

RENUMCMD        .byte " RENUM",0

VALIDATE
                PUSHAY
                lda LNUMLEN
                cmp #6
                bcs ++

                cmp #5
                bcc +

                ldy LININS
                lda (NXTLN),y
                cmp #'7'
                bcs ++

                iny
                lda (NXTLN),y
                cmp #'4'
                bcs ++
+
                POPAY
                rts
+
                ldx #ILLEGALQUANITY
                jmp ERROR
