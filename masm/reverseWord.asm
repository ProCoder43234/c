data segment
    num dw 1253h
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax

       mov ax,num
       mov cl,04h
       rol ah,cl
       rol al,cl
       mov bh,al
       mov bl,ah
       mov num,bx
       
       mov dl,bh
       and dl,0f0h
       shr dl,cl
       add dl,30h
       cmp dl,3ah
       jc skip1
       add dl,07h
       
skip1: mov ah,02h
       int 21h
       
       mov dl,bh
       and dl,0fh 
       add dl,30h
       cmp dl,3ah
       jc skip2
       add dl,07h
       
skip2: mov ah,02h       
       int 21h     
            
       mov dl,bl
       and dl,0f0h
       shr dl,cl
       add dl,30h
       cmp dl,3ah
       jc skip3
       add dl,07h
       
skip3: mov ah,02h
       int 21h
       
       mov dl,bl
       and dl,0fh 
       add dl,30h
       cmp dl,3ah
       jc skip4
       add dl,07h
       
skip4: mov ah,02h       
       int 21h
  
mov ah,4ch
int 21h 

code ends
end start