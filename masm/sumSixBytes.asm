data segment
    msg1 db 0ah,0dh,'Enter the numbers: ','$' 
    msg2 db 0ah,0dh,'Sum = $'
    newline db 0ah,0dh,' ','$'
    sum db ?
    
    print macro arg
        lea dx,arg
        mov ah,09
        int 21h
    print endm 
data ends

code segment
assume cs:code,ds:data    

start: mov ax,data
       mov ds,ax
       
       print msg1
       
       mov ch,06h
       mov cl,04h 
       mov bl,00h

read:  call scan
       mov bh,al
       shl bh,cl
       call scan
       add bh,al
       add bl,bh
    
       call scan
       dec ch
       jnz read                
       
next:  mov sum,bl
       print newline
       print msg2

       mov dl,sum
       and dl,0f0h
       shr dl,cl
       add dl,30h
       cmp dl,39h
       jle skip1
       add dl,07h
       
skip1: mov ah,02h
       int 21h
       
       mov dl,sum
       and dl,0fh
       add dl,30h
       cmp dl,39h
       jle skip2
       add dl,07h

skip2: mov ah,02h      
       int 21h 
mov ah,4ch
int 21h 

scan proc
    mov ah,01
    int 21h 
    sub al,30h
    cmp al,09h
    jc rn
    jz rn
    sub al,07h
rn: ret
    scan endp
code ends
end start