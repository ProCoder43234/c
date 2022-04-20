data segment
    a db 0ffh;
    b db 0ffh;
    sum db ?
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
       mov al,a
       add al,b
       jnc skip
       inc carry

skip: mov sum,al

ret
addition endp

code ends                                               
end start