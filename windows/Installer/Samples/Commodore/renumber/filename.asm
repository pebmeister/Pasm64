; File created from renum.prg by DisAsm6502

          R6510 = $01
          UNUSED1 = $02
          DIMFLG = $0C
          INDEX = $22
          TXTTAB = $2B
          VARTAB = $2D
          ARYTAB = $2F
          STREND = $31
          FRETOP = $33
          MEMSIZ = $37
          CURLIN = $39
          OLDLIN = $3B
          OLDTXT = $3D
          DATLIN = $3F
          DATPTR = $41
          INPPTR = $43
          VARNAM = $45
          FORPNT = $49
          OPPTR = $4B
          OPMASK = $4D
          DEFPNT = $4E
          UNUSED2 = $57
          FAC1 = $61
          FACHO = $62
          FACSSGN = $66
          FAC2 = $69
          ARGHO = $6A
          CHRGET = $73
          TXTPTR = $7A
          TMPDATA = $A3
          FREKZP = $FB
          IGONE = $0308
          ERROR = $A437
          BORDER = $D020
          CIAICR = $DC0D
          CI2ICR = $DD0D
          WARM = $E37B

          .ORG $C000

           CLI                  ; $C000: $58
           LDY #$01             ; $C001: $A0 $01
L_000      LDA IGONE,y          ; $C003: $B9 $08 $03
           STA L_084,y          ; $C006: $99 $34 $C6
           DEY                  ; $C009: $88
           BPL L_000            ; $C00A: $10 $F7
           LDA #<WEDGE          ; $C00C: $A9 $50
           STA IGONE            ; $C00E: $8D $08 $03
           LDA #>WEDGE          ; $C011: $A9 $C0
           STA IGONE + 1        ; $C013: $8D $09 $03
           LDA TXTTAB           ; $C016: $A5 $2B
           STA FREKZP           ; $C018: $85 $FB
           STA STREND           ; $C01A: $85 $31
           LDA TXTTAB + 1       ; $C01C: $A5 $2C
           STA FREKZP + 1       ; $C01E: $85 $FC
           STA STREND + 1       ; $C020: $85 $32
           LDA #$00             ; $C022: $A9 $00
           LDY #$05             ; $C024: $A0 $05
L_001      STA (FREKZP),y       ; $C026: $91 $FB
           DEY                  ; $C028: $88
           BNE L_001            ; $C029: $D0 $FB
           CLC                  ; $C02B: $18
           LDA #$02             ; $C02C: $A9 $02
           ADC STREND           ; $C02E: $65 $31
           STA STREND           ; $C030: $85 $31
           LDA #$00             ; $C032: $A9 $00
           ADC STREND + 1       ; $C034: $65 $32
           STA STREND + 1       ; $C036: $85 $32
           LDA MEMSIZ           ; $C038: $A5 $37
           STA FRETOP           ; $C03A: $85 $33
           LDA MEMSIZ + 1       ; $C03C: $A5 $38
           STA FRETOP + 1       ; $C03E: $85 $34
           LDA STREND           ; $C040: $A5 $31
           STA VARTAB           ; $C042: $85 $2D
           STA ARYTAB           ; $C044: $85 $2F
           LDA STREND + 1       ; $C046: $A5 $32
           STA VARTAB + 1       ; $C048: $85 $2E
           STA ARYTAB + 1       ; $C04A: $85 $30
           SEI                  ; $C04C: $78
           JMP WARM             ; $C04D: $4C $7B $E3
WEDGE
           LDA CURLIN + 1       ; $C050: $A5 $3A
           CMP #$FF             ; $C052: $C9 $FF
           BEQ L_002            ; $C054: $F0 $03
           JMP (L_084)          ; $C056: $6C $34 $C6
L_002      LDY #$01             ; $C059: $A0 $01
L_003      LDA L_012,y          ; $C05B: $B9 $F2 $C0
           BEQ L_004            ; $C05E: $F0 $07
           CMP (TXTPTR),y       ; $C060: $D1 $7A
           BNE L_010            ; $C062: $D0 $7D
           INY                  ; $C064: $C8
           BNE L_003            ; $C065: $D0 $F4
L_004      DEY                  ; $C067: $88
L_005      JSR CHRGET           ; $C068: $20 $73 $00
           DEY                  ; $C06B: $88
           BNE L_005            ; $C06C: $D0 $FA
           LDA #$64             ; $C06E: $A9 $64
           STA L_082            ; $C070: $8D $32 $C6
           LDA #$00             ; $C073: $A9 $00
           STA L_082 + 1        ; $C075: $8D $33 $C6
           LDA #$0A             ; $C078: $A9 $0A
           STA TMPDATA          ; $C07A: $85 $A3
           LDA #$00             ; $C07C: $A9 $00
           STA TMPDATA + 1      ; $C07E: $85 $A4
           LDY #$01             ; $C080: $A0 $01
           LDA (TXTPTR),y       ; $C082: $B1 $7A
           BEQ L_009            ; $C084: $F0 $51
           JSR CHRGET           ; $C086: $20 $73 $00
           JSR L_011            ; $C089: $20 $E4 $C0
           LDY FACSSGN          ; $C08C: $A4 $66
           BEQ L_010            ; $C08E: $F0 $51
           JSR L_013            ; $C090: $20 $F9 $C0
           LDA $FD              ; $C093: $A5 $FD
           STA L_082            ; $C095: $8D $32 $C6
           LDA $FE              ; $C098: $A5 $FE
           STA L_082 + 1        ; $C09A: $8D $33 $C6
           DEY                  ; $C09D: $88
           BEQ L_007            ; $C09E: $F0 $06
L_006      JSR CHRGET           ; $C0A0: $20 $73 $00
           DEY                  ; $C0A3: $88
           BNE L_006            ; $C0A4: $D0 $FA
L_007      LDY #$01             ; $C0A6: $A0 $01
           LDA (TXTPTR),y       ; $C0A8: $B1 $7A
           BEQ L_009            ; $C0AA: $F0 $2B
           JSR CHRGET           ; $C0AC: $20 $73 $00
           CMP #$2C             ; $C0AF: $C9 $2C
           BNE L_010            ; $C0B1: $D0 $2E
           LDY #$01             ; $C0B3: $A0 $01
           LDA (TXTPTR),y       ; $C0B5: $B1 $7A
           BEQ L_009            ; $C0B7: $F0 $1E
           JSR CHRGET           ; $C0B9: $20 $73 $00
           JSR L_011            ; $C0BC: $20 $E4 $C0
           LDY FACSSGN          ; $C0BF: $A4 $66
           BEQ L_010            ; $C0C1: $F0 $1E
           JSR L_013            ; $C0C3: $20 $F9 $C0
           LDA $FD              ; $C0C6: $A5 $FD
           STA TMPDATA          ; $C0C8: $85 $A3
           LDA $FE              ; $C0CA: $A5 $FE
           STA TMPDATA + 1      ; $C0CC: $85 $A4
           DEY                  ; $C0CE: $88
           BEQ L_009            ; $C0CF: $F0 $06
L_008      JSR CHRGET           ; $C0D1: $20 $73 $00
           DEY                  ; $C0D4: $88
           BNE L_008            ; $C0D5: $D0 $FA
L_009      JSR L_016            ; $C0D7: $20 $1E $C1
           BCC L_010            ; $C0DA: $90 $05
           LDX #$0E             ; $C0DC: $A2 $0E
           JMP ERROR            ; $C0DE: $4C $37 $A4
L_010      JMP (L_084)          ; $C0E1: $6C $34 $C6
L_011      LDA TXTPTR           ; $C0E4: $A5 $7A
           STA FREKZP           ; $C0E6: $85 $FB
           LDA TXTPTR + 1       ; $C0E8: $A5 $7B
           STA FREKZP + 1       ; $C0EA: $85 $FC
           LDY #$00             ; $C0EC: $A0 $00
           JSR L_037            ; $C0EE: $20 $EC $C2
           RTS                  ; $C0F1: $60
L_012      .BYTE $20            ; $C0F2: $20
           .BYTE $52            ; $C0F3: $52
           .BYTE $45            ; $C0F4: $45
           .BYTE $4E            ; $C0F5: $4E
           .BYTE $55            ; $C0F6: $55
           .BYTE $4D            ; $C0F7: $4D
           .BYTE $00            ; $C0F8: $00
L_013      PHA                  ; $C0F9: $48
           TYA                  ; $C0FA: $98
           PHA                  ; $C0FB: $48
           LDA FACSSGN          ; $C0FC: $A5 $66
           CMP #$06             ; $C0FE: $C9 $06
           BCS L_015            ; $C100: $B0 $17
           CMP #$05             ; $C102: $C9 $05
           BCC L_014            ; $C104: $90 $0F
           LDY FACHO            ; $C106: $A4 $62
           LDA (FREKZP),y       ; $C108: $B1 $FB
           CMP #$37             ; $C10A: $C9 $37
           BCS L_015            ; $C10C: $B0 $0B
           INY                  ; $C10E: $C8
           LDA (FREKZP),y       ; $C10F: $B1 $FB
           CMP #$34             ; $C111: $C9 $34
           BCS L_015            ; $C113: $B0 $04
L_014      PLA                  ; $C115: $68
           TAY                  ; $C116: $A8
           PLA                  ; $C117: $68
           RTS                  ; $C118: $60
L_015      LDX #$0E             ; $C119: $A2 $0E
           JMP ERROR            ; $C11B: $4C $37 $A4
L_016      JSR L_018            ; $C11E: $20 $2F $C1
           JSR L_022            ; $C121: $20 $A6 $C1
           PHP                  ; $C124: $08
           BCS L_017            ; $C125: $B0 $03
           JSR L_029            ; $C127: $20 $63 $C2
L_017      JSR L_021            ; $C12A: $20 $84 $C1
           PLP                  ; $C12D: $28
           RTS                  ; $C12E: $60
L_018      LDA TMPDATA          ; $C12F: $A5 $A3
           BNE L_019            ; $C131: $D0 $09
           LDA TMPDATA + 1      ; $C133: $A5 $A4
           BNE L_019            ; $C135: $D0 $05
           LDX #$0E             ; $C137: $A2 $0E
           JMP ERROR            ; $C139: $4C $37 $A4
L_019      LDA #$7F             ; $C13C: $A9 $7F
           STA CIAICR           ; $C13E: $8D $0D $DC
           STA CI2ICR           ; $C141: $8D $0D $DD
           LDA TXTTAB           ; $C144: $A5 $2B
           STA FREKZP           ; $C146: $85 $FB
           LDA TXTTAB + 1       ; $C148: $A5 $2C
           STA FREKZP + 1       ; $C14A: $85 $FC
           LDA L_082            ; $C14C: $AD $32 $C6
           STA $FD              ; $C14F: $85 $FD
           LDA L_082 + 1        ; $C151: $AD $33 $C6
           STA $FE              ; $C154: $85 $FE
           LDA #$00             ; $C156: $A9 $00
           STA UNUSED2          ; $C158: $85 $57
           STA UNUSED2 + 1      ; $C15A: $85 $58
           LDA R6510            ; $C15C: $A5 $01
           STA L_081            ; $C15E: $8D $31 $C6
           AND #$01             ; $C161: $29 $01
           BEQ L_020            ; $C163: $F0 $10
           LDA #$00             ; $C165: $A9 $00
           STA L_085            ; $C167: $8D $36 $C6
           LDA #$A0             ; $C16A: $A9 $A0
           STA L_085 + 1        ; $C16C: $8D $37 $C6
           LDA R6510            ; $C16F: $A5 $01
           AND #$FE             ; $C171: $29 $FE
           STA R6510            ; $C173: $85 $01
L_020      LDA L_085            ; $C175: $AD $36 $C6
           STA FORPNT           ; $C178: $85 $49
           STA DATPTR           ; $C17A: $85 $41
           LDA L_085 + 1        ; $C17C: $AD $37 $C6
           STA FORPNT + 1       ; $C17F: $85 $4A
           STA DATPTR + 1       ; $C181: $85 $42
           RTS                  ; $C183: $60
L_021      LDA L_081            ; $C184: $AD $31 $C6
           STA R6510            ; $C187: $85 $01
           LDA #$81             ; $C189: $A9 $81
           STA CIAICR           ; $C18B: $8D $0D $DC
           STA CI2ICR           ; $C18E: $8D $0D $DD
           LDA MEMSIZ           ; $C191: $A5 $37
           STA FRETOP           ; $C193: $85 $33
           LDA MEMSIZ + 1       ; $C195: $A5 $38
           STA FRETOP + 1       ; $C197: $85 $34
           LDA STREND           ; $C199: $A5 $31
           STA VARTAB           ; $C19B: $85 $2D
           STA ARYTAB           ; $C19D: $85 $2F
           LDA STREND + 1       ; $C19F: $A5 $32
           STA VARTAB + 1       ; $C1A1: $85 $2E
           STA ARYTAB + 1       ; $C1A3: $85 $30
           RTS                  ; $C1A5: $60
L_022      JSR L_073            ; $C1A6: $20 $B1 $C5
           BNE L_023            ; $C1A9: $D0 $03
           JMP L_027            ; $C1AB: $4C $3C $C2
L_023      JSR L_028            ; $C1AE: $20 $3E $C2
           LDY #$02             ; $C1B1: $A0 $02
           LDA $FD              ; $C1B3: $A5 $FD
           STA (FREKZP),y       ; $C1B5: $91 $FB
           LDA $FE              ; $C1B7: $A5 $FE
           INY                  ; $C1B9: $C8
           STA (FREKZP),y       ; $C1BA: $91 $FB
           CLC                  ; $C1BC: $18
           LDA $FD              ; $C1BD: $A5 $FD
           ADC TMPDATA          ; $C1BF: $65 $A3
           STA $FD              ; $C1C1: $85 $FD
           LDA $FE              ; $C1C3: $A5 $FE
           ADC TMPDATA + 1      ; $C1C5: $65 $A4
           STA $FE              ; $C1C7: $85 $FE
           BCC L_026            ; $C1C9: $90 $55
           LDA TXTTAB           ; $C1CB: $A5 $2B
           STA FREKZP           ; $C1CD: $85 $FB
           LDA TXTTAB + 1       ; $C1CF: $A5 $2C
           STA FREKZP + 1       ; $C1D1: $85 $FC
           LDA L_085            ; $C1D3: $AD $36 $C6
           STA DATPTR           ; $C1D6: $85 $41
           LDA L_085 + 1        ; $C1D8: $AD $37 $C6
           STA DATPTR + 1       ; $C1DB: $85 $42
L_024      LDY #$00             ; $C1DD: $A0 $00
           LDA (DATPTR),y       ; $C1DF: $B1 $41
           LDY #$02             ; $C1E1: $A0 $02
           STA (FREKZP),y       ; $C1E3: $91 $FB
           LDY #$01             ; $C1E5: $A0 $01
           LDA (DATPTR),y       ; $C1E7: $B1 $41
           LDY #$03             ; $C1E9: $A0 $03
           STA (FREKZP),y       ; $C1EB: $91 $FB
           LDA UNUSED2          ; $C1ED: $A5 $57
           BNE L_025            ; $C1EF: $D0 $06
           LDA UNUSED2 + 1      ; $C1F1: $A5 $58
           BNE L_025            ; $C1F3: $D0 $02
           SEC                  ; $C1F5: $38
           RTS                  ; $C1F6: $60
L_025      SEC                  ; $C1F7: $38
           LDA UNUSED2          ; $C1F8: $A5 $57
           SBC #$01             ; $C1FA: $E9 $01
           STA UNUSED2          ; $C1FC: $85 $57
           LDA UNUSED2 + 1      ; $C1FE: $A5 $58
           SBC #$00             ; $C200: $E9 $00
           STA UNUSED2 + 1      ; $C202: $85 $58
           CLC                  ; $C204: $18
           LDA DATPTR           ; $C205: $A5 $41
           ADC #$02             ; $C207: $69 $02
           STA DATPTR           ; $C209: $85 $41
           LDA DATPTR + 1       ; $C20B: $A5 $42
           ADC #$00             ; $C20D: $69 $00
           STA DATPTR + 1       ; $C20F: $85 $42
           LDY #$00             ; $C211: $A0 $00
           LDA (FREKZP),y       ; $C213: $B1 $FB
           TAX                  ; $C215: $AA
           INY                  ; $C216: $C8
           LDA (FREKZP),y       ; $C217: $B1 $FB
           STX FREKZP           ; $C219: $86 $FB
           STA FREKZP + 1       ; $C21B: $85 $FC
           JMP L_024            ; $C21D: $4C $DD $C1
L_026      LDY #$00             ; $C220: $A0 $00
           LDA (FREKZP),y       ; $C222: $B1 $FB
           TAX                  ; $C224: $AA
           INY                  ; $C225: $C8
           LDA (FREKZP),y       ; $C226: $B1 $FB
           STX FREKZP           ; $C228: $86 $FB
           STA FREKZP + 1       ; $C22A: $85 $FC
           CLC                  ; $C22C: $18
           LDA UNUSED2          ; $C22D: $A5 $57
           ADC #$01             ; $C22F: $69 $01
           STA UNUSED2          ; $C231: $85 $57
           LDA UNUSED2 + 1      ; $C233: $A5 $58
           ADC #$00             ; $C235: $69 $00
           STA UNUSED2 + 1      ; $C237: $85 $58
           JMP L_022            ; $C239: $4C $A6 $C1
L_027      CLC                  ; $C23C: $18
           RTS                  ; $C23D: $60
L_028      LDY #$02             ; $C23E: $A0 $02
           LDA (FREKZP),y       ; $C240: $B1 $FB
           TAX                  ; $C242: $AA
           INY                  ; $C243: $C8
           LDA (FREKZP),y       ; $C244: $B1 $FB
           STX OPPTR            ; $C246: $86 $4B
           STA OPPTR + 1        ; $C248: $85 $4C
           LDY #$00             ; $C24A: $A0 $00
           LDA OPPTR            ; $C24C: $A5 $4B
           STA (DATPTR),y       ; $C24E: $91 $41
           LDA OPPTR + 1        ; $C250: $A5 $4C
           INY                  ; $C252: $C8
           STA (DATPTR),y       ; $C253: $91 $41
           CLC                  ; $C255: $18
           LDA DATPTR           ; $C256: $A5 $41
           ADC #$02             ; $C258: $69 $02
           STA DATPTR           ; $C25A: $85 $41
           LDA DATPTR + 1       ; $C25C: $A5 $42
           ADC #$00             ; $C25E: $69 $00
           STA DATPTR + 1       ; $C260: $85 $42
           RTS                  ; $C262: $60
L_029      LDA BORDER           ; $C263: $AD $20 $D0
           PHA                  ; $C266: $48
           LDA TXTTAB           ; $C267: $A5 $2B
           STA FREKZP           ; $C269: $85 $FB
           LDA TXTTAB + 1       ; $C26B: $A5 $2C
           STA FREKZP + 1       ; $C26D: $85 $FC
L_030      LDA #$00             ; $C26F: $A9 $00
           STA UNUSED1          ; $C271: $85 $02
           JSR L_073            ; $C273: $20 $B1 $C5
           BNE L_031            ; $C276: $D0 $05
           PLA                  ; $C278: $68
           STA BORDER           ; $C279: $8D $20 $D0
           RTS                  ; $C27C: $60
L_031      LDY #$03             ; $C27D: $A0 $03
           LDA #$00             ; $C27F: $A9 $00
L_032      CMP #$20             ; $C281: $C9 $20
           BEQ L_033            ; $C283: $F0 $02
           STA DIMFLG           ; $C285: $85 $0C
L_033      INY                  ; $C287: $C8
           LDA (FREKZP),y       ; $C288: $B1 $FB
           BEQ L_036            ; $C28A: $F0 $4E
           CMP #$22             ; $C28C: $C9 $22
           BEQ L_035            ; $C28E: $F0 $41
           LDX UNUSED1          ; $C290: $A6 $02
           BNE L_032            ; $C292: $D0 $ED
           CMP #$89             ; $C294: $C9 $89
           BEQ L_034            ; $C296: $F0 $12
           CMP #$8D             ; $C298: $C9 $8D
           BEQ L_034            ; $C29A: $F0 $0E
           CMP #$A7             ; $C29C: $C9 $A7
           BEQ L_034            ; $C29E: $F0 $0A
           CMP #$A4             ; $C2A0: $C9 $A4
           BNE L_032            ; $C2A2: $D0 $DD
           LDX DIMFLG           ; $C2A4: $A6 $0C
           CPX #$CB             ; $C2A6: $E0 $CB
           BNE L_032            ; $C2A8: $D0 $D7
L_034      INY                  ; $C2AA: $C8
           LDA (FREKZP),y       ; $C2AB: $B1 $FB
           BEQ L_036            ; $C2AD: $F0 $2B
           CMP #$3A             ; $C2AF: $C9 $3A
           BEQ L_032            ; $C2B1: $F0 $CE
           CMP #$20             ; $C2B3: $C9 $20
           BEQ L_034            ; $C2B5: $F0 $F3
           CMP #$2C             ; $C2B7: $C9 $2C
           BEQ L_034            ; $C2B9: $F0 $EF
           CMP #$30             ; $C2BB: $C9 $30
           BCC L_032            ; $C2BD: $90 $C2
           CMP #$3A             ; $C2BF: $C9 $3A
           BCS L_032            ; $C2C1: $B0 $BE
           JSR L_037            ; $C2C3: $20 $EC $C2
           JSR L_040            ; $C2C6: $20 $34 $C3
           JSR L_046            ; $C2C9: $20 $BB $C3
           TXA                  ; $C2CC: $8A
           TAY                  ; $C2CD: $A8
           JMP L_034            ; $C2CE: $4C $AA $C2
L_035      LDA UNUSED1          ; $C2D1: $A5 $02
           EOR #$01             ; $C2D3: $49 $01
           STA UNUSED1          ; $C2D5: $85 $02
           JMP L_032            ; $C2D7: $4C $81 $C2
L_036      LDY #$00             ; $C2DA: $A0 $00
           LDA (FREKZP),y       ; $C2DC: $B1 $FB
           TAX                  ; $C2DE: $AA
           INY                  ; $C2DF: $C8
           LDA (FREKZP),y       ; $C2E0: $B1 $FB
           STX FREKZP           ; $C2E2: $86 $FB
           STA FREKZP + 1       ; $C2E4: $85 $FC
           INC BORDER           ; $C2E6: $EE $20 $D0
           JMP L_030            ; $C2E9: $4C $6F $C2
L_037      LDA #$00             ; $C2EC: $A9 $00
           STA $FD              ; $C2EE: $85 $FD
           STA $FE              ; $C2F0: $85 $FE
           STA FACSSGN          ; $C2F2: $85 $66
           STY FACHO            ; $C2F4: $84 $62
L_038      LDA (FREKZP),y       ; $C2F6: $B1 $FB
           CMP #$30             ; $C2F8: $C9 $30
           BCC L_039            ; $C2FA: $90 $37
           CMP #$3A             ; $C2FC: $C9 $3A
           BCS L_039            ; $C2FE: $B0 $33
           INC FACSSGN          ; $C300: $E6 $66
           PHA                  ; $C302: $48
           TYA                  ; $C303: $98
           PHA                  ; $C304: $48
           ASL $FD              ; $C305: $06 $FD
           ROL $FE              ; $C307: $26 $FE
           LDX $FD              ; $C309: $A6 $FD
           LDY $FE              ; $C30B: $A4 $FE
           ASL $FD              ; $C30D: $06 $FD
           ROL $FE              ; $C30F: $26 $FE
           ASL $FD              ; $C311: $06 $FD
           ROL $FE              ; $C313: $26 $FE
           CLC                  ; $C315: $18
           TXA                  ; $C316: $8A
           ADC $FD              ; $C317: $65 $FD
           STA $FD              ; $C319: $85 $FD
           TYA                  ; $C31B: $98
           ADC $FE              ; $C31C: $65 $FE
           STA $FE              ; $C31E: $85 $FE
           PLA                  ; $C320: $68
           TAY                  ; $C321: $A8
           PLA                  ; $C322: $68
           AND #$CF             ; $C323: $29 $CF
           CLC                  ; $C325: $18
           ADC $FD              ; $C326: $65 $FD
           STA $FD              ; $C328: $85 $FD
           LDA $FE              ; $C32A: $A5 $FE
           ADC #$00             ; $C32C: $69 $00
           STA $FE              ; $C32E: $85 $FE
           INY                  ; $C330: $C8
           BNE L_038            ; $C331: $D0 $C3
L_039      RTS                  ; $C333: $60
L_040      LDA UNUSED2          ; $C334: $A5 $57
           STA INPPTR           ; $C336: $85 $43
           LDA UNUSED2 + 1      ; $C338: $A5 $58
           STA INPPTR + 1       ; $C33A: $85 $44
           LDA #$FF             ; $C33C: $A9 $FF
           STA $59              ; $C33E: $85 $59
           STA $5A              ; $C340: $85 $5A
           SEC                  ; $C342: $38
           ASL INPPTR           ; $C343: $06 $43
           ROL INPPTR + 1       ; $C345: $26 $44
           LDA #$00             ; $C347: $A9 $00
           STA VARNAM           ; $C349: $85 $45
           STA VARNAM + 1       ; $C34B: $85 $46
L_041      SEC                  ; $C34D: $38
           LDA INPPTR           ; $C34E: $A5 $43
           SBC VARNAM           ; $C350: $E5 $45
           STA INDEX            ; $C352: $85 $22
           LDA INPPTR + 1       ; $C354: $A5 $44
           SBC VARNAM + 1       ; $C356: $E5 $46
           STA INDEX + 1        ; $C358: $85 $23
           LSR INDEX + 1        ; $C35A: $46 $23
           ROR INDEX            ; $C35C: $66 $22
           CLC                  ; $C35E: $18
           LDA INDEX            ; $C35F: $A5 $22
           ADC VARNAM           ; $C361: $65 $45
           STA INDEX            ; $C363: $85 $22
           LDA INDEX + 1        ; $C365: $A5 $23
           ADC VARNAM + 1       ; $C367: $65 $46
           STA INDEX + 1        ; $C369: $85 $23
           LDA INDEX            ; $C36B: $A5 $22
           AND #$FE             ; $C36D: $29 $FE
           STA INDEX            ; $C36F: $85 $22
           CMP $59              ; $C371: $C5 $59
           BNE L_042            ; $C373: $D0 $07
           LDA INDEX + 1        ; $C375: $A5 $23
           CMP $5A              ; $C377: $C5 $5A
           BNE L_042            ; $C379: $D0 $01
           RTS                  ; $C37B: $60
L_042      LDA INDEX            ; $C37C: $A5 $22
           STA $59              ; $C37E: $85 $59
           LDA INDEX + 1        ; $C380: $A5 $23
           STA $5A              ; $C382: $85 $5A
           CLC                  ; $C384: $18
           LDA L_085            ; $C385: $AD $36 $C6
           ADC INDEX            ; $C388: $65 $22
           STA FORPNT           ; $C38A: $85 $49
           LDA L_085 + 1        ; $C38C: $AD $37 $C6
           ADC INDEX + 1        ; $C38F: $65 $23
           STA FORPNT + 1       ; $C391: $85 $4A
           LDY #$01             ; $C393: $A0 $01
           LDA (FORPNT),y       ; $C395: $B1 $49
           CMP $FE              ; $C397: $C5 $FE
           BNE L_043            ; $C399: $D0 $07
           DEY                  ; $C39B: $88
           LDA (FORPNT),y       ; $C39C: $B1 $49
           CMP $FD              ; $C39E: $C5 $FD
           BEQ L_045            ; $C3A0: $F0 $18
L_043      BCC L_044            ; $C3A2: $90 $0B
           LDA INDEX            ; $C3A4: $A5 $22
           STA INPPTR           ; $C3A6: $85 $43
           LDA INDEX + 1        ; $C3A8: $A5 $23
           STA INPPTR + 1       ; $C3AA: $85 $44
           JMP L_041            ; $C3AC: $4C $4D $C3
L_044      LDA INDEX            ; $C3AF: $A5 $22
           STA VARNAM           ; $C3B1: $85 $45
           LDA INDEX + 1        ; $C3B3: $A5 $23
           STA VARNAM + 1       ; $C3B5: $85 $46
           JMP L_041            ; $C3B7: $4C $4D $C3
L_045      RTS                  ; $C3BA: $60
L_046      PHA                  ; $C3BB: $48
           TYA                  ; $C3BC: $98
           PHA                  ; $C3BD: $48
           LSR INDEX + 1        ; $C3BE: $46 $23
           ROR INDEX            ; $C3C0: $66 $22
           LDA TMPDATA          ; $C3C2: $A5 $A3
           PHA                  ; $C3C4: $48
           LDA TMPDATA + 1      ; $C3C5: $A5 $A4
           PHA                  ; $C3C7: $48
           LDA #$00             ; $C3C8: $A9 $00
           STA ARGHO + 1        ; $C3CA: $85 $6B
           STA $6C              ; $C3CC: $85 $6C
           LDX #$10             ; $C3CE: $A2 $10
L_047      LSR TMPDATA + 1      ; $C3D0: $46 $A4
           ROR TMPDATA          ; $C3D2: $66 $A3
           BCC L_048            ; $C3D4: $90 $0B
           LDA ARGHO + 1        ; $C3D6: $A5 $6B
           CLC                  ; $C3D8: $18
           ADC INDEX            ; $C3D9: $65 $22
           STA ARGHO + 1        ; $C3DB: $85 $6B
           LDA $6C              ; $C3DD: $A5 $6C
           ADC INDEX + 1        ; $C3DF: $65 $23
L_048      ROR                  ; $C3E1: $6A
           STA $6C              ; $C3E2: $85 $6C
           ROR ARGHO + 1        ; $C3E4: $66 $6B
           ROR ARGHO            ; $C3E6: $66 $6A
           ROR FAC2             ; $C3E8: $66 $69
           DEX                  ; $C3EA: $CA
           BNE L_047            ; $C3EB: $D0 $E3
           PLA                  ; $C3ED: $68
           STA TMPDATA + 1      ; $C3EE: $85 $A4
           PLA                  ; $C3F0: $68
           STA TMPDATA          ; $C3F1: $85 $A3
           CLC                  ; $C3F3: $18
           LDA L_082            ; $C3F4: $AD $32 $C6
           ADC FAC2             ; $C3F7: $65 $69
           STA OPPTR            ; $C3F9: $85 $4B
           LDA L_082 + 1        ; $C3FB: $AD $33 $C6
           ADC ARGHO            ; $C3FE: $65 $6A
           STA OPPTR + 1        ; $C400: $85 $4C
           JSR L_075            ; $C402: $20 $BB $C5
           JSR L_077            ; $C405: $20 $11 $C6
           LDA FACSSGN          ; $C408: $A5 $66
           CMP FAC1             ; $C40A: $C5 $61
           BNE L_051            ; $C40C: $D0 $19
           LDY FACHO            ; $C40E: $A4 $62
L_049      SEC                  ; $C410: $38
           LDA #$05             ; $C411: $A9 $05
           SBC FAC1             ; $C413: $E5 $61
           TAX                  ; $C415: $AA
L_050      LDA OLDLIN,x         ; $C416: $B5 $3B
           STA (FREKZP),y       ; $C418: $91 $FB
           INY                  ; $C41A: $C8
           INX                  ; $C41B: $E8
           CPX #$05             ; $C41C: $E0 $05
           BNE L_050            ; $C41E: $D0 $F6
           TYA                  ; $C420: $98
           TAX                  ; $C421: $AA
           DEX                  ; $C422: $CA
           PLA                  ; $C423: $68
           TAY                  ; $C424: $A8
           PLA                  ; $C425: $68
           RTS                  ; $C426: $60
L_051      BCC L_053            ; $C427: $90 $07
           JSR L_054            ; $C429: $20 $36 $C4
L_052      LDY FACHO            ; $C42C: $A4 $62
           BNE L_049            ; $C42E: $D0 $E0
L_053      JSR L_059            ; $C430: $20 $DB $C4
           JMP L_052            ; $C433: $4C $2C $C4
L_054      LDY #$01             ; $C436: $A0 $01
L_055      LDA FREKZP,y         ; $C438: $B9 $FB $00
           STA L_058,y          ; $C43B: $99 $D9 $C4
           DEY                  ; $C43E: $88
           BPL L_055            ; $C43F: $10 $F7
           LDA FREKZP           ; $C441: $A5 $FB
           STA VARNAM           ; $C443: $85 $45
           LDA FREKZP + 1       ; $C445: $A5 $FC
           STA VARNAM + 1       ; $C447: $85 $46
           CLC                  ; $C449: $18
           LDA FACHO            ; $C44A: $A5 $62
           ADC VARNAM           ; $C44C: $65 $45
           STA VARNAM           ; $C44E: $85 $45
           LDA #$00             ; $C450: $A9 $00
           ADC VARNAM + 1       ; $C452: $65 $46
           STA VARNAM + 1       ; $C454: $85 $46
           SEC                  ; $C456: $38
           LDA FACSSGN          ; $C457: $A5 $66
           SBC FAC1             ; $C459: $E5 $61
           STA $59              ; $C45B: $85 $59
           SEC                  ; $C45D: $38
           LDA STREND           ; $C45E: $A5 $31
           SBC $59              ; $C460: $E5 $59
           STA STREND           ; $C462: $85 $31
           LDA STREND + 1       ; $C464: $A5 $32
           SBC #$00             ; $C466: $E9 $00
           STA STREND + 1       ; $C468: $85 $32
L_056      LDY #$00             ; $C46A: $A0 $00
           SEC                  ; $C46C: $38
           LDA (FREKZP),y       ; $C46D: $B1 $FB
           STA INPPTR           ; $C46F: $85 $43
           SBC $59              ; $C471: $E5 $59
           STA (FREKZP),y       ; $C473: $91 $FB
           INY                  ; $C475: $C8
           LDA (FREKZP),y       ; $C476: $B1 $FB
           STA INPPTR + 1       ; $C478: $85 $44
           SBC #$00             ; $C47A: $E9 $00
           STA (FREKZP),y       ; $C47C: $91 $FB
           LDA INPPTR           ; $C47E: $A5 $43
           STA FREKZP           ; $C480: $85 $FB
           LDA INPPTR + 1       ; $C482: $A5 $44
           STA FREKZP + 1       ; $C484: $85 $FC
           JSR L_073            ; $C486: $20 $B1 $C5
           BNE L_056            ; $C489: $D0 $DF
           SEC                  ; $C48B: $38
           LDA INPPTR           ; $C48C: $A5 $43
           SBC VARNAM           ; $C48E: $E5 $45
           STA INDEX            ; $C490: $85 $22
           LDA INPPTR + 1       ; $C492: $A5 $44
           SBC VARNAM + 1       ; $C494: $E5 $46
           STA INDEX + 1        ; $C496: $85 $23
           CLC                  ; $C498: $18
           LDA INDEX            ; $C499: $A5 $22
           ADC #$04             ; $C49B: $69 $04
           STA INDEX            ; $C49D: $85 $22
           LDA INDEX + 1        ; $C49F: $A5 $23
           ADC #$00             ; $C4A1: $69 $00
           STA INDEX + 1        ; $C4A3: $85 $23
           CLC                  ; $C4A5: $18
           LDA VARNAM           ; $C4A6: $A5 $45
           ADC $59              ; $C4A8: $65 $59
           STA INPPTR           ; $C4AA: $85 $43
           LDA VARNAM + 1       ; $C4AC: $A5 $46
           ADC #$00             ; $C4AE: $69 $00
           STA INPPTR + 1       ; $C4B0: $85 $44
           LDA VARNAM           ; $C4B2: $A5 $45
           STA FREKZP           ; $C4B4: $85 $FB
           LDA VARNAM + 1       ; $C4B6: $A5 $46
           STA FREKZP + 1       ; $C4B8: $85 $FC
           LDA INPPTR           ; $C4BA: $A5 $43
           STA VARNAM           ; $C4BC: $85 $45
           LDA INPPTR + 1       ; $C4BE: $A5 $44
           STA VARNAM + 1       ; $C4C0: $85 $46
           LDA FREKZP           ; $C4C2: $A5 $FB
           STA INPPTR           ; $C4C4: $85 $43
           LDA FREKZP + 1       ; $C4C6: $A5 $FC
           STA INPPTR + 1       ; $C4C8: $85 $44
           JSR L_068            ; $C4CA: $20 $90 $C5
           LDY #$01             ; $C4CD: $A0 $01
L_057      LDA L_058,y          ; $C4CF: $B9 $D9 $C4
           STA FREKZP,y         ; $C4D2: $99 $FB $00
           DEY                  ; $C4D5: $88
           BPL L_057            ; $C4D6: $10 $F7
           RTS                  ; $C4D8: $60
L_058      .WORD $0000          ; $C4D9: $00 $00
L_059      LDY #$01             ; $C4DB: $A0 $01
L_060      LDA FREKZP,y         ; $C4DD: $B9 $FB $00
           STA L_063,y          ; $C4E0: $99 $64 $C5
           DEY                  ; $C4E3: $88
           BPL L_060            ; $C4E4: $10 $F7
           LDA FREKZP           ; $C4E6: $A5 $FB
           STA VARNAM           ; $C4E8: $85 $45
           LDA FREKZP + 1       ; $C4EA: $A5 $FC
           STA VARNAM + 1       ; $C4EC: $85 $46
           CLC                  ; $C4EE: $18
           LDA FACHO            ; $C4EF: $A5 $62
           ADC VARNAM           ; $C4F1: $65 $45
           STA VARNAM           ; $C4F3: $85 $45
           LDA #$00             ; $C4F5: $A9 $00
           ADC VARNAM + 1       ; $C4F7: $65 $46
           STA VARNAM + 1       ; $C4F9: $85 $46
           SEC                  ; $C4FB: $38
           LDA FAC1             ; $C4FC: $A5 $61
           SBC FACSSGN          ; $C4FE: $E5 $66
           STA $59              ; $C500: $85 $59
           CLC                  ; $C502: $18
           ADC STREND           ; $C503: $65 $31
           STA STREND           ; $C505: $85 $31
           LDA #$00             ; $C507: $A9 $00
           ADC STREND + 1       ; $C509: $65 $32
           STA STREND + 1       ; $C50B: $85 $32
L_061      LDY #$00             ; $C50D: $A0 $00
           CLC                  ; $C50F: $18
           LDA (FREKZP),y       ; $C510: $B1 $FB
           STA INPPTR           ; $C512: $85 $43
           ADC $59              ; $C514: $65 $59
           STA (FREKZP),y       ; $C516: $91 $FB
           INY                  ; $C518: $C8
           LDA (FREKZP),y       ; $C519: $B1 $FB
           STA INPPTR + 1       ; $C51B: $85 $44
           ADC #$00             ; $C51D: $69 $00
           STA (FREKZP),y       ; $C51F: $91 $FB
           LDA INPPTR           ; $C521: $A5 $43
           STA FREKZP           ; $C523: $85 $FB
           LDA INPPTR + 1       ; $C525: $A5 $44
           STA FREKZP + 1       ; $C527: $85 $FC
           JSR L_073            ; $C529: $20 $B1 $C5
           BNE L_061            ; $C52C: $D0 $DF
           SEC                  ; $C52E: $38
           LDA INPPTR           ; $C52F: $A5 $43
           SBC VARNAM           ; $C531: $E5 $45
           STA INDEX            ; $C533: $85 $22
           LDA INPPTR + 1       ; $C535: $A5 $44
           SBC VARNAM + 1       ; $C537: $E5 $46
           STA INDEX + 1        ; $C539: $85 $23
           CLC                  ; $C53B: $18
           LDA INDEX            ; $C53C: $A5 $22
           ADC #$04             ; $C53E: $69 $04
           STA INDEX            ; $C540: $85 $22
           LDA INDEX + 1        ; $C542: $A5 $23
           ADC #$00             ; $C544: $69 $00
           STA INDEX + 1        ; $C546: $85 $23
           CLC                  ; $C548: $18
           LDA VARNAM           ; $C549: $A5 $45
           ADC $59              ; $C54B: $65 $59
           STA INPPTR           ; $C54D: $85 $43
           LDA VARNAM + 1       ; $C54F: $A5 $46
           ADC #$00             ; $C551: $69 $00
           STA INPPTR + 1       ; $C553: $85 $44
           JSR L_064            ; $C555: $20 $66 $C5
           LDY #$01             ; $C558: $A0 $01
L_062      LDA L_063,y          ; $C55A: $B9 $64 $C5
           STA FREKZP,y         ; $C55D: $99 $FB $00
           DEY                  ; $C560: $88
           BPL L_062            ; $C561: $10 $F7
           RTS                  ; $C563: $60
L_063      .WORD $0000          ; $C564: $00 $00
L_064      LDX INDEX + 1        ; $C566: $A6 $23
           CLC                  ; $C568: $18
           TXA                  ; $C569: $8A
           ADC VARNAM + 1       ; $C56A: $65 $46
           STA VARNAM + 1       ; $C56C: $85 $46
           CLC                  ; $C56E: $18
           TXA                  ; $C56F: $8A
           ADC INPPTR + 1       ; $C570: $65 $44
           STA INPPTR + 1       ; $C572: $85 $44
           INX                  ; $C574: $E8
           LDY INDEX            ; $C575: $A4 $22
           BEQ L_067            ; $C577: $F0 $0E
           DEY                  ; $C579: $88
           BEQ L_066            ; $C57A: $F0 $07
L_065      LDA (VARNAM),y       ; $C57C: $B1 $45
           STA (INPPTR),y       ; $C57E: $91 $43
           DEY                  ; $C580: $88
           BNE L_065            ; $C581: $D0 $F9
L_066      LDA (VARNAM),y       ; $C583: $B1 $45
           STA (INPPTR),y       ; $C585: $91 $43
L_067      DEY                  ; $C587: $88
           DEC VARNAM + 1       ; $C588: $C6 $46
           DEC INPPTR + 1       ; $C58A: $C6 $44
           DEX                  ; $C58C: $CA
           BNE L_065            ; $C58D: $D0 $ED
           RTS                  ; $C58F: $60
L_068      LDY #$00             ; $C590: $A0 $00
           LDX INDEX + 1        ; $C592: $A6 $23
           BEQ L_070            ; $C594: $F0 $0E
L_069      LDA (VARNAM),y       ; $C596: $B1 $45
           STA (INPPTR),y       ; $C598: $91 $43
           INY                  ; $C59A: $C8
           BNE L_069            ; $C59B: $D0 $F9
           INC VARNAM + 1       ; $C59D: $E6 $46
           INC INPPTR + 1       ; $C59F: $E6 $44
           DEX                  ; $C5A1: $CA
           BNE L_069            ; $C5A2: $D0 $F2
L_070      LDX INDEX            ; $C5A4: $A6 $22
           BEQ L_072            ; $C5A6: $F0 $08
L_071      LDA (VARNAM),y       ; $C5A8: $B1 $45
           STA (INPPTR),y       ; $C5AA: $91 $43
           INY                  ; $C5AC: $C8
           DEX                  ; $C5AD: $CA
           BNE L_071            ; $C5AE: $D0 $F8
L_072      RTS                  ; $C5B0: $60
L_073      LDY #$00             ; $C5B1: $A0 $00
           LDA (FREKZP),y       ; $C5B3: $B1 $FB
           BNE L_074            ; $C5B5: $D0 $03
           INY                  ; $C5B7: $C8
           LDA (FREKZP),y       ; $C5B8: $B1 $FB
L_074      RTS                  ; $C5BA: $60
L_075      SED                  ; $C5BB: $F8
           LDA #$00             ; $C5BC: $A9 $00
           STA OPMASK           ; $C5BE: $85 $4D
           STA DEFPNT           ; $C5C0: $85 $4E
           STA DEFPNT + 1       ; $C5C2: $85 $4F
           LDY #$10             ; $C5C4: $A0 $10
L_076      ASL OPPTR            ; $C5C6: $06 $4B
           ROL OPPTR + 1        ; $C5C8: $26 $4C
           LDA OPMASK           ; $C5CA: $A5 $4D
           ADC OPMASK           ; $C5CC: $65 $4D
           STA OPMASK           ; $C5CE: $85 $4D
           LDA DEFPNT           ; $C5D0: $A5 $4E
           ADC DEFPNT           ; $C5D2: $65 $4E
           STA DEFPNT           ; $C5D4: $85 $4E
           LDA DEFPNT + 1       ; $C5D6: $A5 $4F
           ADC DEFPNT + 1       ; $C5D8: $65 $4F
           STA DEFPNT + 1       ; $C5DA: $85 $4F
           DEY                  ; $C5DC: $88
           BNE L_076            ; $C5DD: $D0 $E7
           CLD                  ; $C5DF: $D8
           LDA OPMASK           ; $C5E0: $A5 $4D
           AND #$F0             ; $C5E2: $29 $F0
           LSR                  ; $C5E4: $4A
           LSR                  ; $C5E5: $4A
           LSR                  ; $C5E6: $4A
           LSR                  ; $C5E7: $4A
           ORA #$30             ; $C5E8: $09 $30
           STA OLDTXT + 1       ; $C5EA: $85 $3E
           LDA OPMASK           ; $C5EC: $A5 $4D
           AND #$0F             ; $C5EE: $29 $0F
           ORA #$30             ; $C5F0: $09 $30
           STA DATLIN           ; $C5F2: $85 $3F
           LDA DEFPNT           ; $C5F4: $A5 $4E
           AND #$F0             ; $C5F6: $29 $F0
           LSR                  ; $C5F8: $4A
           LSR                  ; $C5F9: $4A
           LSR                  ; $C5FA: $4A
           LSR                  ; $C5FB: $4A
           ORA #$30             ; $C5FC: $09 $30
           STA OLDLIN + 1       ; $C5FE: $85 $3C
           LDA DEFPNT           ; $C600: $A5 $4E
           AND #$0F             ; $C602: $29 $0F
           ORA #$30             ; $C604: $09 $30
           STA OLDTXT           ; $C606: $85 $3D
           LDA DEFPNT + 1       ; $C608: $A5 $4F
           AND #$0F             ; $C60A: $29 $0F
           ORA #$30             ; $C60C: $09 $30
           STA OLDLIN           ; $C60E: $85 $3B
           RTS                  ; $C610: $60
L_077      LDY #$00             ; $C611: $A0 $00
           STY FAC1             ; $C613: $84 $61
L_078      LDA OLDLIN,y         ; $C615: $B9 $3B $00
           CMP #$30             ; $C618: $C9 $30
           BNE L_079            ; $C61A: $D0 $08
           CPY #$04             ; $C61C: $C0 $04
           BEQ L_079            ; $C61E: $F0 $04
           LDX FAC1             ; $C620: $A6 $61
           BEQ L_080            ; $C622: $F0 $0A
L_079      STY FAC1             ; $C624: $84 $61
           LDA #$05             ; $C626: $A9 $05
           SEC                  ; $C628: $38
           SBC FAC1             ; $C629: $E5 $61
           STA FAC1             ; $C62B: $85 $61
           RTS                  ; $C62D: $60
L_080      INY                  ; $C62E: $C8
           BNE L_078            ; $C62F: $D0 $E4
L_081      .BYTE $00            ; $C631: $00
L_082      .WORD $0000          ; $C632: $00 $00
L_084      .WORD $0000          ; $C634: $00 $00
L_085      .WORD L_085          ; $C636: $36 $C6

