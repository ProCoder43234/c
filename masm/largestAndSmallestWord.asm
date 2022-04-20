data segment
    arr dw 01h,07h,02h,09h,03h,06h
    lg dw 0000h
    sm dw 0ffffh
    len equ 06
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax 
       

       call largest
       call smallest   
         
mov ah,4ch
int 21h               

;to find largest element
largest proc
       mov cl,len
       mov ax,lg
       lea si,arr
       
back:  cmp ax,[si]
       jnc skip
       mov ax,[si]

skip:  add si,02h 
       loop back
      
       mov lg,ax

ret       
largest endp

;to find smallest element
smallest proc
       mov cl,len
       mov ax,sm
       lea si,arr
      
back2: cmp ax,[si]
       jc skip2
       mov ax,[si]

skip2: add si,02h
       loop back2
       
       mov sm,ax

ret
smallest endp


code ends
end start