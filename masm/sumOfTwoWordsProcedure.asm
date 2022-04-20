data segment
    a dw 0ffffh;
    b dw 025ffh;
    sum dw ?
    carry db 00h
data ends
    
code segment
assume cs:code, ds:data

start: mov ax,data
       mov ds,ax
       
       call addition

mov ah,4ch
int 21h
       
addition proc       
       mov ax,a
       add ax,b
       jnc skip
       inc carry

skip: mov sum,ax

ret
addition endp

code ends                                               
end start