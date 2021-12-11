DATAS SEGMENT
    ;此处输入数据段代码  
    string db 'There is a message', 0ah, 0dh, '$'
    inputting db 'How many seconds do you want to delay: $'
    n dw 10 
    m db 18
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

    ;读入多位数
    mov bx, 0 ;存储到bx
L1:
	mov ah, 1
	int 21h	
	
	cmp al, 0dh 
	jz L2 	;输入结束

	sub al, 30h	
	mov ah, 0
	xchg bx, ax
	mul n
	add bx, ax;
	jmp L1
	
L2:
    mov al, bl
    mul m;        * 18
    mov interval, ax


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
    sti

    mov di, 20000
delay:
    mov si, 30000
delay1:
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
    mov cx, 1400h

wait1:
    loop wait1
    dec dx
    jne sound
    mov ax, interval
    mov count, ax

exit:
    cli
    pop dx
    pop cx
    pop ax
    pop ds
    iret

print endp
codes ends
    end start





















