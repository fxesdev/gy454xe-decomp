TYPE(ML610CASESplus)

d_080DC			EQU 80DCH
d_080F4			EQU 80F4H
cursor_noflash	EQU 80DDH
setup_contrast	EQU 810EH
vars_start		EQU 8226H
magic_string	EQU 860EH
screen_buffer	EQU 87D0H
stack_start		EQU 8A18H

EXTRN TABLE	: _casio_logo	; 01F10
EXTRN CODE	: _buffer_clear	; 02D38
EXTRN CODE	: $$start_up
EXTRN CODE	: _render		; 0312C
EXTRN CODE	: _memcpy_nn		; 07EF6
EXTRN CODE	: _invalid_var	; 1B4EA

; 04588
_f_04588:
	MOV ER0, SP
	RT

; 0458C
_get_remaining_stack_space:
	MOV R2, #BYTE1 stack_start
	MOV R3, #BYTE2 stack_start
	MOV ER0, SP
	SUB R0, R2
	SUBC R1, R3
	RT

; 04598
_reset_magic_string:
	LEA magic_string
	MOV R0, #0FH
_$rms_loop:
	ST R0, [EA+]
	ADD R0, #-1
	BNE _$rms_loop
	RT

; 045A6
_need_reset:
	PUSH LR
	PUSH XR4
	LEA magic_string
	MOV R0, #0FH
_$nr_loop:
	L R1, [EA+]
	CMP R1, R0
	BNE _$nr_yes
	ADD R0, #-1
	BNE _$nr_loop
	L R0, setup_contrast
	CMP R0, #1DH
	BGTS _$nr_yes
	CMP R0, #4
	BLTS _$nr_yes
	MOV R6, #0AH
	MOV R4, #BYTE1 vars_start
	MOV R5, #BYTE2 vars_start
_$nr_loop2:
	MOV ER0, ER4
	BL _invalid_var
	BNE _$nr_yes
	ADD ER4, #0AH
	ADD R6, #-1
	BNE _$nr_loop2
	L R0, d_080DC
	AND R0, #11111000B
	BEQ _$nr_no
_$nr_yes:
	POP XR4
	MOV R0, #1
	POP PC
_$nr_no:
	POP XR4
	MOV R0, #0
	POP PC

_shutdown:
	L R0, cursor_noflash
	BNE _$stop_exit
	BL _buffer_clear
	MOV R0, #156
	MOV R1, #0
	PUSH ER0
	MOV R0, #BYTE1 screen_buffer
	MOV R0, #BYTE2 screen_buffer
	MOV R2, #10*12
	MOV R3, #0
	ADD ER0, ER2
	MOV R2, #BYTE1 _casio_logo
	MOV R3, #BYTE2 _casio_logo
	BL _memcpy_nn
	POP ER0
	BL _render
	MOV R0, #88H
	MOV R1, #13H
	BL delay
	MOV ER0, #3
	ST R0, 0F031H
	ST R1, 0F00AH
	LEA 0F010H
	MOV ER2, #0
	ST ER2, [EA+]
	BL f_047DA
	BL f_047EA
	BL _stop_enable
	B $$start_up

; 04640
_delay:
	MOV ER2, ER0
	LEA 0F024H
	MOV ER0, #1
	ST R0, [EA+]
	ST R1, [EA]
	LEA 0F022H
	MOV R0, #0
	ST R0, [EA+]
	ST R0, [EA]
	LEA 0F020H
	ST R2, [EA+]
	ST R3, [EA]
	LEA 0F025H
	MOV R0, #1
	ST R0, [EA]
	LEA 0F014H
	MOV R0, #0
	ST R0, [EA+]
	ST R0, [EA]
; 04670
_stop_enable:
	LEA 0F008H
	MOV R2, #50H
	MOV R3, #0A0H
	ST R2, [EA]
	ST R3, [EA+]
	MOV R0, #2
	ST R0, [EA]
	NOP
	NOP
_$stop_exit:
	RT
	
; 04686
_waitkey:
	LEA 0F014H
	L R0, [EA]
	AND R0, #11111101B
	ST R0, [EA]
	LEA 0F008H
	MOV R2, #50H
	MOV R3, #0A0H
	ST R2, [EA]
	ST R3, [EA+]
	MOV R0, #2
	ST R0, [EA]
	NOP
	NOP
	RT
	
; 046A6
_get_IE0:
	LEA 0F014H
	L R0, [EA]
	RT
	
; 046AE
_f_046AE:
	TB d_080F4.7
	BNE _$j_046bc
	MOV R0, #88H
; 046B6
_f_046B6:
	ST R0, d_080F4
	RT
_$j_046bc:
	MOV R0, #1
	RT
	
; 046C0
_f_046C0:
	MOV R0, #80H
	BAL _f_046B6
	
; 046C4
_f_046C4:
	MOV R0, #0
	ST R0, d_080F4
	RT

; 046CC	
_f_046CC:
	TB d_080F4.7
	BEQ _$j_046dc
	BAL _$j_046bc
	
; 046D4
_f_046D4:
	TB d_080F4.3
	BEQ _$j_046dc
	BAL _$j_046bc
_$j_046dc:
	MOV R0, #0
	RT
	
; UNFINISHED!!!
