DATAS SEGMENT
    ;�˴��������ݶδ���  
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
    ;�˴������ջ�δ���
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
    ;�˴��������δ���
    lea dx, string_1
    mov ah,09h
    int 21h
    
    ;�����ַ���
    lea dx,buf; �����ַ���
    mov ah,0ah
    int 21h
    
    lea dx, options
    mov ah, 09h
    int 21h
    
    mov cl, buf+1; ��¼�ַ�������
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
    
    mov bl, al;  ��Ų���
    
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

	mov al, '$'; ��־�������β
    mov [di], al
    
    lea dx, crf; �س�����
    mov ah, 09h
    int 21h
    
    lea dx, string_2; ��ʾ��
    mov ah, 09h
    int 21h
    
    lea dx, result; ��ӡ���
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
	lea si, buf+2; ���½�siָ��ʼλ��
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
	add si, dx; ��siָ���ַ���ĩβ
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

	lea si, buf+2; ���½�siָ��ʼλ��

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
	add di, dx; ��diָ���ַ���ĩβ

    mov bx, 0; ��¼��ͷ*��
    mov dx, 0; ��¼��β*��
    
    mov cx, len
num1:               ; ����bx
    mov al, [si]
    cmp al, '*'
    jnz out1
    inc si
    inc bx
    loop num1

out1:
    mov cx, len
num2:               ; ����cx
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
copyhead:           ; ����ͷ��*
    mov [di], al
    inc di
    loop copyhead

end1:
    mov cx, len
    sub cx, bx
    sub cx, dx
copymid:            ; �����м��
    mov al, [si]
    cmp al, '*'
    jz jump         ; ������*
    mov [di], al
    inc di
jump:
    inc si
    loop copymid

    mov cx, dx
    cmp cx, 0
    jz end2
    mov al, '*'
copytail:           ; ����ĩβ��
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
    cmp al, '*'    ; ���Ϊ*������
    jz equal
    mov [di], al; �����ַ�����������
    inc di
equal:
    inc si
    loop compare4

	ret
endp all
        




    