ORG 0
MOV R0, #01H
MOV R1, #0FFH
SETB RS0 ; switch from RB0 to RB1
MOV R0, 00H
MOV A, 01H
MOV A, R0
MOV A, 08H
MOV A, @R0
CLR RS0 ; switch from RB1 to RB0
MOV A, R0
SJMP $
END
