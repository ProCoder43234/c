data segment
    a db 0ffh
    b db 02h
    quo db ?
    rem db ?
data ends

code segment
assume cs:code,ds

start: mov ax,data
       mov ds,ax
             
       mov ah,00h      
       mov al,a
       div b
       mov quo,al
        
         
mov ah,4ch
int 21h
code ends
end start