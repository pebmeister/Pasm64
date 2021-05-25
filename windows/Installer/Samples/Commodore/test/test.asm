;********************************************
;*                                          *
;*  MULT16                                  *
;*                                          *
;*  16bit multiplication                    *
;*                                          *
;*  destroys    a,x,y                       *
;*                                          *
;********************************************
                .macro MULT16
                lda \2
                pha
                lda \2 + 1
                pha
                lda #$00
                sta \3 + 2              ;   clear upper bits of \3
                sta \3 + 3
                ldx #$10                ;   set binary count to 16
@M000
                lsr \2 + 1              ;   divide \2 by 2
                ror \2

                bcc @M001               ;
                
                lda \3 + 2              ;   get upper half of \3 and add \1
                clc
                adc \1
                sta \3 + 2
                lda \3 + 3
                adc \1 + 1
@M001
                ror                     ;   rotate partial \3
                sta \3 + 3
                ror \3 + 2
                ror \3 + 1
                ror \3
                dex
                bne @M000
                pla
                sta \2 + 1
                pla
                sta \2
                .endm

                .org $1000
TEST
                MULT16 @A,@B,@C
                MULT16 @A,@B,@C
                rts

@A              .word $1234
@B              .word $0002
@C              .word 0
