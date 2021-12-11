DATAS SEGMENT
    ;此处输入数据段代码  
    string db 'There is a message', 0ah, 0dh, '$'
    inputting db 'How many seconds do you want to delay: $'
    n dw 10 
    count dw 1
    interval dw 36
DATAS ENDS

STACKS SEGMENT 
    ;此处输入堆栈段代码
    dw 100 dup(?)
STACKS ENDS 

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
start: 
main proc far

    mov ax, datas
    mov ds, ax

    lea dx, inputting
    mov ah, 09h
    int 21h


    mov al, 1ch
    mov ah, 35h
    int 21H

    push es
    push bx
    push ds

    mov dx, offset print
    mov ax, seg print
    mov ds, ax
    mov al, 1ch
    mov ah, 25h
    int 21H

    pop ds
    ; in al, 21h
    ; and al, 11111110b
    ; out 21h, al

    sti

    mov di, 20000
delay:
    mov si, 30000
delay1:
    dec si
    jnz delay1
    dec si
    jnz delay1
    dec di
    jnz delay

    pop dx
    pop ds
    mov al, 1ch
    mov ah, 25h
    int 21H

    mov ax, 4c00h
    int 21H

main endp

print proc near
    push ds
    push ax
    push cx
    push dx

    mov ax, datas
    mov ds, ax

    sti

    dec count
    jnz exit

    mov dx, offset string
    mov ah, 09h
    int 21H

    mov dx, 100
    in al, 61h
    and al, 0fch

sound:
    ; xor al, 02
    ; out 61h, al

    mov cx, 1400h

wait1:
    loop wait1
    dec dx
    jne sound
    mov count, 36

exit:
    cli
    pop dx
    pop cx
    pop ax
    pop ds
    iret

print endp

    end start