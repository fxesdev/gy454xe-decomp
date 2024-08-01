TYPE(ML610CASESplus)

d_080DC			EQU 80DCH
setup_contrast	EQU 810EH
vars_start		EQU 8226H
magic_string	EQU 860EH
stack_start		EQU 8A18H

EXTRN CODE : _invalid_var_1B4EA

_f_04588:
	MOV ER0, SP
	RT
	
_f_0458C:
	MOV R2, #BYTE1 stack_start
	MOV R3, #BYTE2 stack_start
	MOV ER0, SP
	SUB R0, R2
	SUBC R1, R3
	RT
	
_reset_magic_string_04598:
	LEA magic_string
	MOV R0, #0FH
_$rms_loop:
	ST R0, [EA+]
	ADD R0, #-1
	BNE _$rms_loop
	RT

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
	BL _invalid_var_1B4EA
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

; UNFINISHED
