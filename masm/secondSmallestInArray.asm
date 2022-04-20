data segment
    arr db 01h,07h,02h,09h,03h,06h
    sm db 0ffh
    sm2 db 0ffh
    len equ 04
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax 
       
       mov cl,len
       mov al,sm
       mov bl,sm2
       lea si,arr 
       
back:  cmp al,[si]
       jc skip
       mov bl,al
       mov al,[si]
       jmp skip1

skip:  cmp bl,[si]
       jc skip1
       mov bl,[si]

skip1: inc si
       loop back
      
       mov sm,al
       mov sm2,bl
    
         
mov ah,4ch
int 21h    
code ends
end start