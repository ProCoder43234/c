DATA SEGMENT
     MSG DB 'HELLO WORLD !$'    
     MSG1 DB 0AH,0DH,'ANOTHER STRING !$' 
     A DB ?
     
     PRINT MACRO ARG
       MOV AH,09H
       LEA DX,ARG
       INT 21H
     PRINT ENDM     
                             
                             
DATA ENDS

CODE SEGMENT 
    ASSUME CS: CODE,DS:DATA
START:     

    MOV AX, DATA
    MOV DS,AX
    
    PRINT MSG
    PRINT MSG1
    
    CALL GET_NUM  
    MOV A,AL
    CALL GET_NUM     
    MOV AL,A  
    
    AND AL,0F0H
    MOV CL,4H
    ROR AL,CL
    ADD AL,30H
    CMP AL,39H
    JLE SKIP3
    ADD AL,7H 
    
SKIP3:MOV AH,02H 
    MOV DL,AL
    INT 21H
    
    MOV AL,A
    AND AL,0FH
    ADD AL,30H
    CMP AL,39H
    JLE SKIP4
    ADD AL,7H
    
SKIP4:MOV AH,02H 
    MOV DL,AL
    INT 21H  
    
    
    
    MOV AH,4CH
    INT 21H

GET_NUM PROC
    MOV AH,01H
    INT 21H
    SUB AL,30H
    CMP AL,09H
    JLE SKIP1
    SUB AL,07H
SKIP1:MOV CL,04H
    ROL AL,CL
    MOV BL,AL
     MOV AH,01H
    INT 21H
    SUB AL,30H
    CMP AL,09H
    JLE SKIP2
    SUB AL,07H
SKIP2: ADD AL,BL 
     
RET
GET_NUM ENDP

CODE ENDS
END START