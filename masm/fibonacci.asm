data segment
    arr db 10 dup(?)
    string1 db 0ah,'00','$'
    string2 db 0ah,'01','$'
    count db 0ah
data ends

code segment
assume cs:code,ds:data

start: mov ax,data
       mov ds,ax

       lea si,arr
       mov [si],00h
       inc si
       mov [si],01h
       inc si
                
       mov ch,count         
       mov cl,04h
       
       cmp count,00h
       jz end
       
       lea dx,string1
       mov ah,09h
       int 21h
       
       cmp count,01h
       jz end    
       
       mov dl,' '
       mov ah,02h  
       int 21h
       
       lea dx,string2
       mov ah,09h
       int 21h
       
       cmp count,02h
       jz end
       
       sub ch,2
       
       mov dl,' '
       mov ah,02h  
       int 21h        
       
back:  mov ah,[si-1]
       mov al,[si-2]
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
  
end:   mov ah,4ch
       int 21h 

code ends
end start