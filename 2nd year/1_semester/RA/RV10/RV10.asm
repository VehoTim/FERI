section .data
poziv db "Vnesite besedilo: ", 0
odziv db "Z majhnimi crkami: ", 0

section .bss
besedilo: resb 1024

section .text
global main

main:
    push rbp
    mov rax, 1
    mov rdi, 1
    mov rsi, poziv
    mov rdx, 18
    syscall

    mov rsi, besedilo
    mov rdi, 0
    mov rdx, 1024
    mov rax, 0
    syscall
    mov r15, rax

    mov rsi, besedilo
    mov rdi, rax
    call toLowerUnderscore

    mov rax, 1
    mov rdi, 1
    mov rsi, odziv
    mov rdx, 19
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, besedilo
    mov rdx, r15
    syscall

    pop rbp
    mov rax, 0
    ret

toLowerUnderscore:
    lodsb
    cmp al, 0
    je .konec
    cmp al, 'A'
    jge .testirajz
    cmp al, ' '
    je .underscore
    jmp toLowerUnderscore

    .testirajz:
        cmp al, 'Z'
        jge toLowerUnderscore
        xor al, 0x20

        mov byte[rsi-1], al
        jmp toLowerUnderscore

    .underscore:
        cmp al, '_'
        jge toLowerUnderscore
        xor al, 0x7f

        mov byte[rsi-1], al
        jmp toLowerUnderscore

    .konec:
        ret