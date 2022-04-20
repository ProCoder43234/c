data segment
    arr db 01h,07h,02h,09h,03h,06h
    lg db 00h
    len equ 04
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax 
       
       mov cl,len
       mov lg,al
       lea si,arr 
       
back:  cmp al,[si]
       jnc skip
       mov al,[si]

skip: inc si
      loop back
      
      mov lg,al
         
mov ah,4ch
int 21h    
code ends
end start