DATA SEGMENT
    ARR DB 0FFH,0FEH,03H,04H
    LARGE DB 00H
    LOW DB 0FFH
    LEN EQU 04
    LARGE2 DB 00H
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
      MOV AX,DATA
      MOV DS, AX

      LEA SI,ARR
      MOV CL,LEN
      MOV AL,LARGE

BACK: CMP AL,[SI]
      JNC SKIP
      MOV AL,[SI]
SKIP: INC SI
      LOOP BACK
      MOV LARGE, AL
      
      MOV CL,LEN
      MOV AL,LOW

BACK2: CMP [SI],AL
      JNC SKIP2
      MOV AL,[SI]
SKIP2: DEC SI
      LOOP BACK2
      MOV LOW, AL
      
      MOV CL,LEN
      MOV AL,LARGE2
      MOV AH,LARGE
      
BACK3: CMP AL,[SI]
      JNC SKIP3
      CMP [SI],AH
      JNC SKIP3
      MOV AL,[SI]
SKIP3:
      INC SI
      LOOP BACK3
      MOV LARGE2,AL
      
      
MOV AX,4CH
INT 21H

CODE ENDS
END START