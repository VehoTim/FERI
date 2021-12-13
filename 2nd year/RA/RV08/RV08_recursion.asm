extern printf

section .data
odziv db "f(%ld) = %ld", 10, 0

section .bss
i: resq 1
N: resq 1

section .text
global main

main:
push rbp

mov dword [i], 3
mov dword [N], 10

.loop:                                          ; zacnemo zanko
mov rdi, [i]
cmp rdi, [N]

jg .exit

call recursion

mov rdi, odziv
mov rsi, [i]
mov rdx, rax
mov rax, 0 
call printf

inc dword [i]

jmp .loop

.exit:
pop rbp
mov rax, 0
ret

; f(n) = 1 + f(n-3) + f(n-2), n > 2, f(0) = 12, f(1)=22, f(2) = 45
recursion:

; n=0 vrnemo 12, n=1 vrnemo 22, n=2 vrnemo 45
cmp rdi, 0
je .fJe12
cmp rdi, 1
je .fJe22
cmp rdi, 2
je .fJe45

push rdi
sub rdi, 3
call recursion
pop rdi

push rax

push rdi
sub rdi, 2
call recursion
pop rdi

pop rsi
add rax, rsi
add rax, 1
ret

.fJe12:
mov rax, 12
ret

.fJe22:
mov rax, 22
ret

.fJe45:
mov rax, 45
ret