DATA SEGMENT
    MSG1 DB 0AH,0DH,"HELLO WORLD$"
    MSG2 DB 0AH,0DH,"HELLO WORLD AGAIN$"
DISP MACRO ARG
    MOV AH,09H
    LEA DX,ARG
    INT 21H
ENDM
DATA ENDS

CODE SEGMENT
    ASSUME CS: CODE, DS: DATA

START:
        MOV AX,DATA
        MOV DS,AX
        
        DISP MSG1
        DISP MSG2
        
MOV AH,4CH
INT 21H

CODE ENDS
END START
    
