data segment
    arr1 db 01h,04h,0f1h,21h,08h
    arr2 db 11h,0a1h,01h,22h,07h
    size db 05h
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax

       lea si,arr1
       lea di,arr2
       
       mov ch,size
       mov cl,04h
       
back:  mov ah,[si]
       mov al,[di]
       add ah,al
       mov [si],ah
       
       mov dl,[si]
       and dl,0f0h
       shr dl,cl
       add dl,30h
       cmp dl,3ah
       jc skip1
       add dl,07h
       
skip1: mov ah,02h
       int 21h
       
       mov dl,[si]
       and dl,0fh 
       add dl,30h
       cmp dl,3ah
       jc skip2
       add dl,07h
       
skip2: mov ah,02h       
       int 21h
       
       mov dl,' '
       mov ah,02h
       int 21h   
        
       inc si
       inc di
       
       dec ch
       jnz back        
  
mov ah,4ch
int 21h 

code ends
end start