ORG 0 ; start from 0000H
MOV DPTR, #TABLE ; DPTR point to TABLE
MOV R5, #2 ;cnt

START: MOV R0, #1 ; initialize typed signal
MOV R1, #4 ; set 4 row
MOV R2, #11110111B ; set first row


SCAN: MOV A, R2 ; move R2 to A
MOV P2, A ; input scanned signal
JNB P2.7, NUMIN ; scan column 1
INC R0 ; add #01 into R0
JNB P2.6, NUMIN ; scan column 2
INC R0 ; add #01 into R0
JNB P2.5, NUMIN ; scan column 3
INC R0 ; add #01 into R0
JNB P2.4, KEYIN ; scan column 4

RR A ; next row
MOV R2, A ; move A to R2
DJNZ R1, SCAN ; scan 4 rows
SJMP START;

NUMIN: CALL DEBOUNCE ; call debounce function
MOV A,R0;
DJNZ R5, NUM_ONE;
MOV R6, A;
;MOV R5, #2;
SJMP START;

NUM_ONE: MOV R7,A;
SJMP START;

KEYIN: CALL DEBOUNCE ;call debounce function
		MOV A, R1			; move R0 to A
		DEC A				;sub #1 into A
		JZ	_DIV_			;if A = 3,push A button, jump to add1 
		DEC A				;sub #1 into A
		JZ	_MUL_			;if A = 7,push B button, jump to sub1
		DEC A				;sub #1 into A
		JZ	_SUB_			;if A = 11,push C button, jump to mul1
		DEC A				;sub #1 into A
		JZ	_ADD_		;if A = 15,push D button, jump to div1
		SJMP START;
		
CAL_DISP:
	MOV B, #10;
	DIV AB;
	
	MOVC A, @A+DPTR;
	MOV P1, A;
	
	CALL DELAY;	
	
	MOV A,B;
	MOVC A, @A+DPTR;
	MOV P1, A;
	
	RET;


DEBOUNCE: MOV R4, #100 ; move 50 times into R4
DE_500_us: MOV R3, #250 ; move 250 times into R3
DJNZ R3, $ ; jump to itself R3 times
DJNZ R4, DE_500_us ; delay 25ms
RET ; return to main code



	
_ADD_:

	MOV A, R6;
	MOV B, R7;
	ADD A,B;
	SJMP  CAL_DISP;
_SUB_:

	MOV A, R6;
	MOV B, R7;
	SUBB A,B;
	SJMP  CAL_DISP;

_MUL_:

	MOV A, R6;
	MOV B, R7;
	MUL AB;
	SJMP  CAL_DISP;
	
_DIV_:
	MOV A, R6;
	MOV B, R7;
	DIV AB;
	SJMP  CAL_DISP;
	
DELAY:
 MOV R3,#250  
D1:
 MOV R4,#250
D2:
 DJNZ R4,D2
 DJNZ R3,D1
 RET	;


TABLE: 	
		DB 00000011B
		DB 10011111B
        DB 00100101B
        DB 00001101B
        DB 10011001B
        DB 01001001B
        DB 01000001B
        DB 00011011B
        DB 00000001B
        DB 00001001B
		
		
		END