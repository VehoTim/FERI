extern scanf
extern printf

section .data
vpis db "%s", 0
izpis db "Obrnjeno: %s", 10, 0

section .bss
array1: resb 32                             ; array1 velikosti 32bajtov
array2: resb 32                              ; array velikosti 32bajtov

section .text
global main

main:
    push rbp

    mov rdi, vpis                           ; poziv za vnos polja znakov
    mov rsi, array1
    mov rax, 0
    call scanf

    mov esi, array1                         ; esi je source kopiranja
    mov edi, array2                          ; edi je destination kopiranja
    mov ecx, 32                             ; kopirali bomo 32-krat
    rep movsb                               ; po en bajt

    mov rdi, array2                          ; nad poljem 2
    call reverse                            ; izvedemo funkcijo reverse

    mov rdi, izpis                          ; izpisemo novo array
    mov rsi, array2
    mov rax, 0
    call printf

    pop rbp                 
    mov rax, 0
    ret                                     ; exit programa

reverse:                                    ; funkcija reverse
    mov rsi, rdi
    cld                                     ; izbrisemo zastavico (direction flag) - premikanje nazaj

    .lenArray:               
        lodsb                               ; preberemo naslednji znak
        cmp al, 0                           ; shranjujemo znake v al
        jnz .lenArray                       

        sub rsi, 2

    reversing:
        cmp rsi, rdi                        ; primerjamo ce smo na koncu
        jle .exit

        mov byte dl, [rdi]                  ; znak shranjujemo v dl
        std                                 ; nastavimo zastavico (direction flag) - premikanje naprej
        lodsb                               ; nalozimo naslednji znak
        mov byte [rsi + 1], dl              ; znak napisemo na konec novega arraya
        cld                                 ; ponovno izbrisemo zastavico
        stosb                               ; shranimo napredek

        jmp reversing                       ; ponovimo

    .exit:
        ret