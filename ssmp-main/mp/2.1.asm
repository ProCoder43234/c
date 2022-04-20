code segment
    assume code:cs       
start:

    mov ax,0700h
    mov ds,ax   
    mov dl,00h
  
    mov bx,0128h
    mov ax,[bx]
    mov bx,012ah
    mov cx,[bx]
    add ax,cx
    jnc L1
    inc dl
    L1:
        mov bx,012ch
        mov [bx],ax
        mov bx,012eh
        mov [bx],dl
    hlt

code ends
end start
        
    