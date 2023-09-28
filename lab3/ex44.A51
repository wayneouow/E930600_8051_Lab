ORG 0               ; start from 0000H
        MOV DPTR, #TABLE    ; DPTR point to TABLE
		MOV R5,#2
START:  MOV R0, #1          ; initialize typed signal
        MOV R1, #4          ; set 3 row
        MOV R2, #11110111B  ; set first row
SCAN:   MOV A, R2           ; move R2 to A
        MOV P2, A           ; input scanned signal
		JNB P2.7, GET     ; scan column 1
        INC R0              ; add #01 into R0
        JNB P2.6, GET     ; scan column 2
        INC R0              ; add #01 into R0
        JNB P2.5, GET     ; scan column 3
        INC R0              ; add #01 into R0
        JNB P2.4, CALCULATE     ; scan column 1
        RR A                ; next row
        MOV R2, A           ; move A to R2
        DJNZ R1, SCAN       ; scan 3 rows
        SJMP START          ; jump to scan keypad again
GET:	CALL DEBOUNCE		;call debounce
		MOV A,R0			; if A has defined , jumo to define B
		DJNZ R5, NUM_ONE			;move R0 to A
		MOV R7,A				;add #1 into A
		MOV R5, #2
		SJMP START
NUM_ONE:MOV R6, A			;move R0 to B
		SJMP START			; jump to scan keypad again
CALCULATE: CALL DEBOUNCE    ;call debounce function
		MOV A, R1			; move R0 to A
		DEC A				;sub #1 into A
		JZ	DIV1			;if A = 3,push A button, jump to add1 
		DEC A				;sub #1 into A
		JZ	MUL1			;if A = 7,push B button, jump to sub1
		DEC A				;sub #1 into A
		JZ	SUB1			;if A = 11,push C button, jump to mul1
		DEC A				;sub #1 into A
		JZ	ADD1			;if A = 15,push D button, jump to div1
		SJMP START			; jump to start
KEYIN:  MOVC A, @A+DPTR     ; according A, get signal from TABLE
        MOV P1, A           ; output displayed signal
        RET
KEYIN_B: MOV A, B 
		MOVC A, @A+DPTR     ; according A, get signal from TABLE
        MOV P1, A           ; output displayed signal
        RET
DEBOUNCE: MOV R4, #200       ; move 50 times into R4
DE_500_us: MOV R3, #250     ; move 250 times into R3
        DJNZ R3, $          ; jump to itself R3 times
        DJNZ R4, DE_500_us  ; delay 25ms
        RET                 ; return to main code
ADD1:	MOV A,R6
		MOV B,R7
		ADD A, B       		; A+B, then save into ACC
		MOV B, #10
		DIV AB
PRINT:	MOVC A, @A+DPTR     ; according A, get signal from TABLE
        MOV P1, A           ; output displayed signal
		MOV R4, #250  ; move 50 times into R4
DEL1_500_us: MOV R3, #250     ; move 250 times into R3
        DJNZ R3, $          ; jump to itself R3 times
        DJNZ R4, DEL1_500_us  ; delay 25ms
        CALL KEYIN_B		; jump to keyin B, output B
		SJMP START          ; jump to scan keypad again
SUB1:	MOV A,R6
		MOV B,R7
		SUBB A,B       	; A-B, then save into ACC
		CALL KEYIN			; jump to KEYIN
		LJMP START          ; jump to scan keypad again
MUL1:	MOV A,R6
		MOV B,R7
		MUL AB          	; multipulate A B
		MOV B,#10
		DIV AB
		CALL KEYIN			; jump to KEYIN
		MOV R4, #250  ; move 50 times into R4
DEL2_500_us: MOV R3, #250     ; move 250 times into R3
        DJNZ R3, $          ; jump to itself R3 times
        DJNZ R4, DEL2_500_us  ; delay 25ms
        CALL KEYIN_B		; jump to keyin B, output B
		LJMP START          ; jump to scan keypad again
DIV1:	MOV A,R6
		MOV B,R7
		DIV AB          	; multipulate A B 
		CALL KEYIN			; jump to KEYIN
		MOV R4, #250  ; move 50 times into R4
DEL_500_us: MOV R3, #250     ; move 250 times into R3
        DJNZ R3, $          ; jump to itself R3 times
        DJNZ R4, DEL_500_us  ; delay 25ms
        CALL KEYIN_B		; jump to keyin B, output B
		LJMP START          ; jump to scan keypad again
TABLE:  DB 00000011B        ; display 0”
		DB 10011111B        ; display 1“1”
        DB 00100101B        ; display 2“2”
        DB 00001101B        ; display 4“3”
        DB 10011001B        ; display 4“4”
        DB 01001001B        ; display 5“5”
        DB 01000001B        ; display 6 “6”
        DB 00011011B        ; display 7 “7”
        DB 00000001B        ; display 8
        DB 00001001B        ;display 9 
        END