data segment
    msg1 db 0ah,0dh,'Enter the numbers: ','$' 
    newline db 0ah,0dh,' ','$'
    arr dw ?
    sum dw ?
    
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
       
       mov ch,02h
       mov cl,04h
       lea si,arr

read:  call scan
       mov bh,al
       shl bh,cl
       call scan
       add bh,al
       call scan
       mov bl,al
       shl bl,cl
       call scan
       add bl,al
       mov [si],bx
       add si,02h
       call scan
       dec ch
       jnz read                
       
next:  lea si,arr 

       mov ax,[si]
       mov bx,[si+2]
       add ax,bx
       mov sum,ax 
           
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