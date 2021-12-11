DATAS SEGMENT
    ;此处输入数据段代码  
    string_1 db 'Please input a string: $', 10, 13, '$'
    string_2 db 'The result is $'
	string_3 db 'UpperChar times: $'
	string_4 db 'LowerChar times: $'
	string_5 db 'Number times: $'
	string_6 db 'Other times: $'
    crlf db 13, 10, '$'

    buf db 100
    	db ?
    	db 100 dup(?)

    num_cnt db '0'
	lowch_cnt db '0'
	upch_cnt db '0'
	other_cnt db '0'

    arr_count db 100 dup(?)
	times_count db 100 dup(1)
	count dw 0
    
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
    dw 100 dup(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码
    mov ax, stacks
    mov ss, ax
    
    lea dx, string_1
    mov ah, 09H
    int 21h
    
    lea dx, buf
    mov ah, 0ah
    int 21h
	
	; 读入字符串
    mov bl,buf+1  ;buf1+1是输入的字符串长度
    mov bh, 0
    mov buf[bx+2], '$'
    
    ; 开始处理
    mov cx, bx
    lea si, buf+2
    lea di, arr_count

compare:
	mov al, [si]
	cmp al, 'a'
	jnl Upper
	cmp al, 'A'
	jnl Lower
	cmp al, '0'
	jnl num
	
next:
	; 判断是否已经存在并计数
	mov dx, count
	mov di, 0
check:
	cmp dx, 0
	jz save
	cmp al, arr_count[di]
	jnz noteq
	
	mov ah, times_count[di]
	add ah, 1
	mov times_count[di], ah
	
	jmp exist
noteq:
	
	dec dx
	add di, 1
	jmp check

save:	
	mov di, count
	mov arr_count[di], al
	mov bx, count
	inc bx
	mov count, bx
exist:	
	inc si
	loop compare  


    ; sort
	mov   cx, count
    dec   cx 
loop1:        
	mov  di, cx
	mov  bx, 0
Loop2:      
	mov  al, times_count[bx]
    cmp  al, times_count[bx+1]
    jge    continue
    xchg al, times_count[bx+1]
    mov  times_count[bx], al

    mov al, arr_count[bx]
	xchg al, arr_count[bx+1]
	mov arr_count[bx], al
Continue:    
	add   bx, 1 
    loop  loop2
    mov  cx, di
    loop  loop1
	
	
	; staicsti print
	lea dx, string_3
	mov ah, 09h
	int 21h
	mov dl, upch_cnt
	mov ah, 02h
	int 21
	
	lea dx, string_4
	mov ah, 09h
	int 21h
	mov dl, lowch_cnt
	mov ah, 02h
	int 21h
	
	lea dx, string_5
	mov ah, 09h
	int 21h
	mov dl, num_cnt
	mov ah, 02h
	int 21h
	
	lea dx, string_6
	mov ah, 09h
	int 21h
	mov dl, other_cnt
	mov ah, 02h
	int 21h
	
	
	
	
    lea dx, crlf
    mov ah, 09h
    int 21h

	; charprint
	mov cx, count
	mov di, 0
print:
	mov dl, arr_count[di]
	mov ah, 02h
	int 21h
	
	mov dl, times_count[di]
	add dl, '0'
	mov ah, 02h
	int 21h
	
    lea dx, crlf
    mov ah, 09h
    int 21h
	
	inc di
	loop print
	
	
	
    
    MOV AH,4CH
    INT 21H

Upper:
	cmp al, 'z'
	jg other
	add upch_cnt, 1
	jmp next  
Lower:
	cmp al, 'Z'
	jg other
	add lowch_cnt, 1
	jmp next
num:
	cmp al, '9'
	jg other
	add num_cnt, 1
	jmp next
other:
	add other_cnt, 1
	jmp next

CODES ENDS
    END START