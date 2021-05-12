;********************************************
;*											*
;*	INITPROG								*
;*											*
;*	init the program						*
;*											*
;*	set nxtlen to start of basic program	*
;*	set start line number					*
;*	set line increment						*
;*	set tblptr and tbltmp to tbl			*
;*											*
;*	destroys a								*
;*											*
;********************************************
INITPROG
				lda INCR
				bne ++
				lda INCR + 1
				bne ++
+			
				ldx #ILLEGALQUANITY
				jmp ERROR
+
				lda #127
				sta CIAICR
				sta CI2ICR

				;
				;	set	NXTLN
				;
				lda TXTTAB				;	load start of basic
				sta NXTLN				;	into next line
				lda TXTTAB + 1
				sta NXTLN + 1

				lda LSTART
				sta	LNUM
				lda LSTART + 1
				sta LNUM + 1

				;
				;	set table size to 0
				;
				lda #0
				sta TBLSZ
				sta TBLSZ + 1

				;
				;	determine	memory	map
				;
				lda R6510
				sta R6510SV

				;
				;	check if basic is mapped in
				;
				and #%00000001
				beq +

				;
				;	we will switch basic out and use
				;	$A000	- $BFFF for our table
				;
				lda #<TBLLOC			;	Set Table location
				sta TBL
				lda #>TBLLOC
				sta TBL + 1

				;
				;	map out basic
				;
				lda R6510
				; and #~%00000001
				and #%11111110
				sta R6510
+
				lda TBL					;	Copy Table location to Table Pointer
				sta TBLPTR				;	and Table temp pointer
				sta TBLTMP
				lda TBL + 1
				sta TBLPTR + 1
				sta TBLTMP + 1
				rts

;********************************************
;*											*
;*	RESTORE									*
;*											*
;*	restore original memory state			*
;*											*
;********************************************
RESTORE
				lda R6510SV
				sta R6510
				lda #129
				sta CIAICR
				sta CI2ICR

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

				rts
                
