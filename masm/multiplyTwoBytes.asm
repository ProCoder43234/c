data segment
    a db 0d1h
    b db 02h
    product dw ?
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax
       
       mov al,a
       mul b
       mov product,ax

mov ah,4ch
int 21h
code ends   
end start