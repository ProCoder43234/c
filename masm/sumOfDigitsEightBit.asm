data segment
    num db 0A8h
    sum db ?
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax
       
       mov cl,04h
       mov ah,num
       and ah,0f0h
       shr ah,cl
       
       mov al,num
       and al,0fh
       
       add ah,al
       mov sum,ah
       
       mov dl,sum
       and dl,0f0h
       shr dl,cl
       add dl,30h
       cmp dl,3ah
       jc skip1
       add dl,07h
       
skip1: mov ah,02h
       int 21h
       
       mov dl,sum
       and dl,0fh 
       add dl,30h
       cmp dl,3ah
       jc skip2
       add dl,07h
       
skip2: mov ah,02h       
       int 21h      
  
mov ah,4ch
int 21h 

code ends
end start