.model small
.stack 100h

.data
	number db "00000$"
.code

main proc
	MOV AX, @DATA
	MOV DS, AX
	push bp
	mov bp,sp
	SUB SP, 2
	SUB SP, 2
	SUB SP, 2
L7: ;
	PUSH CX
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	POP AX
	POP AX
	POP CX
	MOV [BP], CX
	MOV BP, AX
L6: ;
	PUSH CX
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	POP AX
	POP AX
	POP CX
	MOV [BP], CX
	MOV BP, AX
L5: ;
	PUSH CX
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	POP AX
	POP AX
	POP CX
	MOV [BP], CX
	MOV BP, AX
L4: ;
L8: ;
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	MOV AX, [BP]
	CALL print_output
	CALL new_line
	POP BP
L9: ;
L3: ;
L10: ;
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	MOV AX, [BP]
	CALL print_output
	CALL new_line
	POP BP
L12: ;
	JMP L2
L11: :
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	MOV AX, [BP]
	CALL print_output
	CALL new_line
	POP BP
L13: ;
L2: ;
L14: ;
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	MOV AX, [BP]
	CALL print_output
	CALL new_line
	POP BP
L16: ;
	JMP L1
L15: :
L17: ;
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	MOV AX, [BP]
	CALL print_output
	CALL new_line
	POP BP
L19: ;
	JMP L1
L18: :
L20: ;
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	MOV AX, [BP]
	CALL print_output
	CALL new_line
	POP BP
L22: ;
	JMP L1
L21: :
	PUSH CX
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	POP AX
	POP AX
	POP CX
	MOV [BP], CX
	MOV BP, AX
L24: ;
	PUSH BP
	MOV BX, 0
	ADD BP, BX
	MOV AX, [BP]
	CALL print_output
	CALL new_line
	POP BP
L23: ;
L1: ;
	MOV DX,CX
	JMP main_exit
L0: ;
main_exit:

	MOV AX, 4CH
	INT 21H
	ADD SP, 0
	POP BP
main endp

new_line proc
push ax
push dx
mov ah,2
mov dl,0Dh
int 21h
mov ah,2
mov dl,0Ah
int 21h
pop dx
pop ax
ret
new_line endp

print_output proc  ;print what is in ax
push ax
push bx
push cx
push dx
push si
lea si,number
mov bx,10
add si,4
cmp ax,0
jnge negate
print:
xor dx,dx
div bx
mov [si],dl
add [si],'0'
dec si
cmp ax,0
jne print
inc si
lea dx,si
mov ah,9
int 21h
pop si
pop dx
pop cx
pop bx
pop ax
ret
negate:
push ax
mov ah,2
mov dl,'-'
int 21h
pop ax
neg ax
jmp print
print_output endp

end main

