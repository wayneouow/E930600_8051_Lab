ORG 0000h
JMP LOOP ;jump into loop
ORG 0030h
LOOP: MOV SP, #32h ;SP = #32H
MOV A, #11111100B ;A = #0xfe
MOV P2, A ;P2 = A
SETB P1.0 ;set p1.0 to high
MOV R0, #8D ;set the execution times of marquee
JMP P1.3, MARQUEE ;jump into marquee when p1.0 is low
JMP LOOP ;infinite loop

MARQUEE: PUSH 00h ;push the value of R0 into stack
MOV R0, #250D ;set the execution times of DELAY1
CALL DELAY1 ;call DELAY1
POP 00h ;pop out the value of R0 which is pushed in line11
RL A ;left rotate
MOV P2, A ;set the value of A into P2
DJNZ R0, MARQUEE ;loop back until MARQUEE execute 8 times
JMP LOOP ;end of MARQUEE, back to LOOP

DELAY1: PUSH 00h ;push the remain times of DELAY1 into stack
MOV R0, #250D ;set the execution times of DELAY2
CALL DELAY2 ;call DELAY2
POP 00h ;pop the remain times of DELAY1 back to R0
DJNZ R0, DELAY1 ;loop until R0 is 0
RET ;return to MARQUEE
DELAY2: DJNZ R0, DELAY2 ;loop until R0 is 0
RET ;return to DELAY1
END

