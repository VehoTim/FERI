extern scanf                                    ; c funkcija scanf
extern printf                                   ; funkcija print

section .data
vpis db "%ld", 0                                ; spremenljivka za vpis
izpis db "%ld", 10, 0                           ; spremenljivka za izpis

section .bss                                    
i resq 1                                        ; i bo spremenljivka, ki jo bomo incrementirali
N resq 1                                        

section .text                                   
global main                         

main:                                           ; zacetek glavnega programa
push rbp

mov rdi, vpis                                   ; kazalec v vpis
mov rsi, N                                      ; naslov na N
mov rax, 0                                      ; beremo

call scanf                                      ; za branje uporabimo scanf

mov dword [i], 1                                ; i v dword nastavimo na 1

.loop:                                          ; zacnemo zanko
mov rax, [i]
cmp rax, [N]                                    ; ponavljamo dokler ne pridemo do N

je .exit

mov rdi, izpis                                  ; pripravimo kazalec na izpis
mov rsi, [i]                                    ; vrednost je trenuten i
mov rax, 0                                      
call printf                                     ; izpis

inc dword [i]                                   ; povecamo i v dword

jmp .loop                                       ; vrnemu se na zacetek zanke

.exit:                                          ; zapustimo zanko
pop rbp
mov rax, 0
ret                                             ; konec programa