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
_MULT10
                asl _MULT10_A
                rol _MULT10_A + 1       ;   multiply by 2

                ;
                ;   save the number * 2 in x and y
                ;
                ldx _MULT10_A           ;   save low byte in x
                ldy _MULT10_A + 1       ;   save high byte in y

                ;
                ;   continue shifting for multiply by 4 and 8
                ;
                asl _MULT10_A
                rol _MULT10_A + 1       ;   multiply by 4
                asl _MULT10_A
                rol _MULT10_A + 1       ;   multiply by 8

                ;
                ;   now add up the result
                ;
                clc                     ;   clear carry
                txa                     ;   load low byte of 2x
                adc _MULT10_A           ;   add to 8x low byte
                sta _MULT10_A           ;   store low byte
                tya                     ;   load the high byte of 2x
                adc _MULT10_A + 1       ;   add to 8x high
                sta _MULT10_A + 1       ;   store high byte
                rts
_MULT10_A       .word 0
