data segment
    msg1 db 0ah,0dh,'Enter the numbers: ','$'
    msg2 db 0ah,0dh,'Array after sorting: ','$'
    newline db 0ah,0dh,' ','$'
    len db ?
    arr db ?

    print macro arg
        mov ah,09h
        lea dx,arg
        int 21h
    print endm
data ends

code segment
assume cs:code,ds:data

start:  mov ax,data
        mov ds,ax
        
        print msg1
        
        mov cl,04h
        mov ch,00h
        lea si,arr
        
read:   call scan
        cmp al,0dh
        jz next
        mov bh,al
        shl bh,cl
        call scan
        add bh,al
        call scan
        mov [si],bh
        inc si
        inc ch
        jmp read
        
next:   mov len,ch

back2:  lea si,arr

        mov cl,ch
        dec cl
        jz skip
        
back:   mov ah,[si]
        mov al,[si+1]
        cmp al,ah
        jnc go
        mov [si],al
        mov [si+1],ah

go:     inc si
        dec cl
        jnz back
        
        dec ch
        jnz back2                 
        
skip:   print newline
        print msg2
        
        lea si,arr
        mov cl,04h
        mov ch,len
        
end:    mov dl,[si]
        and dl,0f0h
        shr dl,cl
        add dl,30h
        cmp dl,39h
        jle skip1
        add dl,07h
        
skip1:  mov ah,02h
        int 21h
        
        mov dl,[si]
        and dl,0fh
        add dl,30h
        cmp dl,39h
        jle skip2
        add dl,07h

skip2:  mov ah,02h
        int 21h
        
        mov dl,' '
        mov ah,02h
        int 21h
        
        inc si
        dec ch
        jnz end                     
        
    
mov ah,4ch
int 21h

scan proc
    mov ah,01h
    int 21h
    cmp al,0dh
    jz rn
    sub al,30h
    cmp al,09h
    jle rn
    sub al,07h
    
rn: ret
scan endp 
code ends
end start
   