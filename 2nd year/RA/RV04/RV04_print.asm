global _start

section .text
_start
mov rax, 1
mov rdi, 1
mov rsi, izpis
mov rdx, 17
syscall
mov rax, 60
xor rdi, rdi
syscall

section .data
izpis: db "Tim Vehovar", 10, "2021", 10