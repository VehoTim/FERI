extern scanf                                    ; c funkcija scanf
extern printf                                   ; funkcija print

section .data
vpis db "%ld", 0                                ; spremenljivka za vpis
izpis db "%ld", 10, 0                           ; spremenljivka za izpis

section .bss                                    
i resq 1                                        ; i bo spremenljivka, ki jo bomo incrementirali
N resq 1                                        ; N je spremenljivka v katero bomo brali

section .text                                   
global main                         

main:                                           ; zacetek glavnega programa
push rbp

mov rdi, vpis                                   ; kazalec v vpis
mov rsi, N                                      ; naslov na N
mov rax, 0                                      ; beremo

call scanf                                      ; za branje uporabimo scanf

mov rsi, 2                                      ; za 2 bomo delili N
mov rax, [N]                                    ; nalozimo N
mov rdx, 0                                      
div rsi                                         ; opravimo deljenje nalozenega N z 2
mov [N], rax                                    ; shranimo nov N

mov dword [i], 1                                ; i nastavimo na 1

.loop:                                          ; zacnemo zanko
mov rax, [i]
cmp rax, [N]                                    ; ponavljamo dokler ne pridemo do N (ki smo ga delili z 2)

jg .exit                                        ; koncamo ce pridemo do N/2

mov rsi, 47                                     ; delili bomo z 47
mov rdx, 0                                      
div rsi                                         ; opravimo deljenje trenutnega i z 47
cmp rdx, 0                                      ; preverimo ostanek
jne .preskoci                                   ; ce ni deljivo preskocimo izpis

mov rdi, izpis
mov rsi, [i]
mov rax, 0
call printf

.preskoci:

inc dword [i]                                   ; povecamo i v dword

jmp .loop                                       ; vrnemu se na zacetek zanke

.exit:                                          ; zapustimo zanko
pop rbp
mov rax, 0
ret                                             ; konec programa