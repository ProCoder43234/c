DATA SEGMENT
    ARR DW 0FFFFH,0FEEEH,3333H,4444H
    LARGE DW 0000H
    LEN EQU 04
    LARGE2 DW 0000H
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
      MOV AX,DATA
      MOV DS, AX

      LEA SI,ARR
      MOV CL,LEN
      MOV AX,LARGE

BACK: CMP AX,[SI]
      JNC SKIP
      MOV AX,[SI]
SKIP: INC SI
      LOOP BACK
      MOV LARGE, AX
      
      MOV CL,LEN
      MOV BX,LARGE2
      MOV AX,LARGE
      
BACK3: CMP BX,[SI]
      JNC SKIP3
      CMP [SI],AX
      JNC SKIP3
      MOV BX,[SI]
SKIP3:
      INC SI
      LOOP BACK3
      MOV LARGE2,BX
      
      
MOV AX,4CH
INT 21H

CODE ENDS
END START