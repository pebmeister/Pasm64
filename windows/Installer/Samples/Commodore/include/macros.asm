
;********************************************
;*                                          *
;* SAVEZP                                   *
;*                                          *
;*  save a zero page variable               *
;*                                          *
;*  destroys a, y                           *
;*                                          *
;********************************************
                .macro SAVEZP
.if \3 > 2
                ldy #\3 -1
-
                lda \1,y
                sta \2,y
                dey
                bpl -
.else
                lda \1
                sta \2
    .if \3 > 1
                lda \1 + 1
                sta \2 + 1
    .endif          
.endif      
                .endm

;********************************************
;*                                          *
;* PUSHREG                                  *
;*                                          *
;*  push registers on the stack             *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
                .macro PUSHREG
                pha
                tya
                pha
                txa
                pha
                .endm

;********************************************
;*                                          *
;* POPREG                                   *
;*                                          *
;*  restore registers on the stack          *
;*                                          *
;*  destroys a,x,y                          *
;*                                          *
;********************************************
                .macro POPREG
                pla
                txa
                pla
                tay
                pla
                .endm

;********************************************
;*                                          *
;* PUSHAY                                   *
;*                                          *
;*  push a nd y on the stack                *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
                .macro PUSHAY
                pha
                tya
                pha
                .endm

;********************************************
;*                                          *
;* POPAY                                    *
;*                                          *
;*  restore registers on the stack          *
;*                                          *
;*  destroys a,y                            *
;*                                          *
;********************************************
                .macro POPAY
                pla
                tay
                pla
                .endm

;********************************************
;*                                          *
;* BCD2STR                                  *
;*                                          *
;*  converts 1 byte bcd to 2 byte string    *
;*                                          *
;*  destroys a                              *
;*                                          *
;********************************************
                .macro BCD2STR
                lda \1                  ;   load the byte to convert
                and #$F0                ;   get the high nibble
                lsr                     ;   shift to low nibble
                lsr
                lsr
                lsr
                ora #'0'                ;   or '0' to make it numeric
                sta \2                  ;   save the PETASCII low byte
                lda \1                  ;   reload the byte to convert
                and #$0F                ;   get the lo nibble
                ora #'0'                ;   or '0' to make it numeric
                sta \2 + 1              ;   save the PETASCII high byte
                .endm

;********************************************
;*                                          *
;* MULT10                                   *
;*                                          *
;*  multiplies 2 byte number by 10          *
;                                           *
;*  n * 10 = n * 8 + n * 2                  *
;*                                          *
;*  destroys a,x,y                          *
;*                                          *
;********************************************
                .macro MULT10
                asl \1
                rol \1 + 1              ;   multiply by 2

                ;
                ;   save the number * 2
                ;
                ldx \1                  ;   save low byte in x
                ldy \1 + 1              ;   save high byte in y

                ;
                ;   continue shifting for multiply by 4 and 8
                ;
                asl \1
                rol \1 + 1              ;   multiply by 4
                asl \1
                rol \1 + 1              ;   multiply by 8

                ;
                ;   now add up the result
                ;
                clc                     ;   clear carry
                txa                     ;   load low byte of 2x
                adc \1                  ;   add to 8x low byte
                sta \1                  ;   store low byte
                tya                     ;   load the high byte of 2x
                adc \1 + 1              ;   add to 8x high
                sta \1 + 1              ;   store high byte
                .endm

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

                bcc @M001               ;   bcc +  FOWARD  labels dont work yet
                                        ;   in macros so use local label
                
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
