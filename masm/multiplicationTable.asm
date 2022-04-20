data segment
    num db 04h
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax
                 
       mov ch,01h 
       mov cl,04h
       
back:  mov al,num
       
       mul ch
       mov bx,ax
 
       mov al,bh
       and al,0f0h
       shr al,cl
       add al,30h
       cmp al,39h
       jle skip1
       add al,07h
       
skip1: mov dl,al
       mov ah,02h
       int 21h
       
       mov al,bh
       and al,0fh
       add al,30h
       cmp al,39h
       jle skip2
       add al,07h

skip2: mov dl,al
       mov ah,02h      
       int 21h
       
       mov al,bl
       and al,0f0h
       mov cl,04h
       shr al,cl
       add al,30h
       cmp al,39h
       jle skip3
       add al,07h
       
skip3: mov dl,al
       mov ah,02h
       int 21h 
       
       mov al,bl
       and al,0fh
       add al,30h
       cmp al,39h
       jle skip4
       add al,07h
       
skip4: mov dl,al
       mov ah,02h
       int 21h
       
       mov dl,' '
       mov ah,02h
       int 21h  
            
       inc ch
       cmp ch,0bh
       jnz back
  
mov ah,4ch
int 21h 

code ends
end start