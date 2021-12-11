DATAS SEGMENT
    ;此处输入数据段代码  
    string_1 db 'Please input a string: $'
    options db 10, 13, '1. head', 10, 13, '2. tail', 10, 13, '3. mid', 10, 13, '4. all', 10, 13, '0. exit', 10, 13, '$'
    string_3 db 'Input your option: $'
    string_2 db 'The result is $'
    crf db 13, 10, '$'
    buf db 200
        db ?
        db 200 dup(?)
    result db 200 dup(?)
    len dw ?
DATAS ENDS

STACKS SEGMENT 
    ;此处输入堆栈段代码
    dw 100 dup(?)
STACKS ENDS 

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
begin:	
	jmp main

main proc
    MOV AX,DATAS
    MOV DS,AX
    mov ax, stacks
    mov ss, ax
    ;此处输入代码段代码
    lea dx, string_1
    mov ah,09h
    int 21h
    
    ;输入字符串
    lea dx,buf; 输入字符串
    mov ah,0ah
    int 21h
    
    lea dx, options
    mov ah, 09h
    int 21h
    
    mov cl, buf+1; 记录字符串长度
    mov ch, 0
    mov len, cx

    mov cx, 0FFFFH

circle:
  
    lea si, buf+2
    lea di, result

       
    lea dx, string_3
    mov ah, 09h
    int 21h
    
    mov ah, 01h
    int 21h
    
    lea dx, crf
    mov ah, 09h
    int 21
    
    mov bl, al;  存放操作
    
    cmp bl, '1'
    jz drop_head
    cmp bl, '2'  
    jz drop_tail
    cmp bl, '3' 
    jz drop_mid
    cmp bl, '4'
    jz drop_all
    cmp bl, '0'
    jz exit

drop_head:
    call head
    jmp print

drop_tail:
	call tail
	jmp print

drop_mid:
    call mid
    jmp print
    
drop_all:
    call all
    jmp print

print:

	mov al, '$'; 标志新数组结尾
    mov [di], al
    
    lea dx, crf; 回车换行
    mov ah, 09h
    int 21h
    
    lea dx, string_2; 提示符
    mov ah, 09h
    int 21h
    
    lea dx, result; 打印结果
    mov ah, 09h
    int 21h

    lea dx, crf
    mov ah, 09h
    int 21h

    loop circle

exit:
    MOV AH,4CH
    INT 21H

main endp

head proc
    mov cx, len
	mov bx, 0

compare3:
	mov al, [si]
	cmp al, '*'
	jnz next1
	
	inc si
	inc bx
	loop compare3
	mov cx, len
	sub cx, bx


next1:
	lea si, buf+2; 重新将si指向开始位置
    add si, bx

copy1:
	mov al, [si]
	mov [di], al
	inc si
	inc di
	loop copy1

	ret
endp head

tail proc

	mov bx, 0
	mov dx, len
	dec dx
	add si, dx; 将si指向字符串末尾
compare2:
	mov al, [si]

	cmp al, '*'
	jnz next2
	
	dec si
	inc bx
	loop compare2

next2:
	mov cx, len
	sub cx, bx

	lea si, buf+2; 重新将si指向开始位置

copy2:
	mov al, [si]
	mov [di], al
	inc si
	inc di
	loop copy2

	ret
endp tail

mid proc 
    mov di, si
    mov bx, 0
	mov dx, len
	dec dx
	add di, dx; 将di指向字符串末尾

    mov bx, 0; 记录开头*数
    mov dx, 0; 记录结尾*数
    
    mov cx, len
num1:               ; 计算bx
    mov al, [si]
    cmp al, '*'
    jnz out1
    inc si
    inc bx
    loop num1

out1:
    mov cx, len
num2:               ; 计算cx
    mov al, [di]
    cmp al, '*'
    jnz out2
    dec di
    inc dx
    loop num2

out2:
    lea di, result

    mov cx, bx
    cmp cx, 0
    jz end1
    mov al, '*'
copyhead:           ; 复制头部*
    mov [di], al
    inc di
    loop copyhead

end1:
    mov cx, len
    sub cx, bx
    sub cx, dx
copymid:            ; 处理中间段
    mov al, [si]
    cmp al, '*'
    jz jump         ; 不复制*
    mov [di], al
    inc di
jump:
    inc si
    loop copymid

    mov cx, dx
    cmp cx, 0
    jz end2
    mov al, '*'
copytail:           ; 复制末尾段
    mov [di], al
    inc di
    loop copytail
end2:
    ret
endp mid

all proc  
    mov cx, len
compare4:
    mov al, [si]
    cmp al, '*'    ; 如果为*就跳过
    jz equal
    mov [di], al; 否则将字符放入新数组
    inc di
equal:
    inc si
    loop compare4

	ret
endp all
        




    