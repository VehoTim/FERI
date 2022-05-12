; nasm -f elf64 RV07_min3.asm -o RV07_min3.o && gcc RV07_min3.o -lc -no-pie && ./a.out

; V zbirnem jeziku napišite funkcijo min3, ki prejme 3 cela števila in vrne najmanjše.
; V glavnem programu prikažite primer uporabe funkcije.

global main 

section .data
    poziv: db "Vpisi stevilo #%ld: ", 0              ; string za poziv stevila
    vpis: db "%ld", 0                                ; spremenljivka za vpis
    izpis: db "Najmanjse stevilo: %ld", 10, 0        ; spremenljivka za izpis

section .bss                                    
    n1 resq 1                                        ; n1 je stevilo 1
    n2 resq 1                                        ; n2 je stevilo 2
    n3 resq 1                                        ; n3 je stevilo 2

; -----------------------------------------------------------------------------------------------------

section .text 

    extern scanf                                    ; c funkcija scanf
    extern printf                                   ; funkcija print                 

main:                                               ; zacetek glavnega programa

; -----------------------------------------------------------------------------------------------------

    push rbp                                        ; nastavimo sklad

; -----------------------------------------------------------------------------------------------------

    mov rax, 0                                      ; poziv za vnos prvega stevila
    mov rdi, poziv
    mov rsi, 1
    call printf

	mov rax, 0                                      ; beremo
	mov rdi, vpis                                   ; kazalec v vpis
	mov rsi, n1                                     ; naslov na n1
	call scanf                                      ; za branje uporabimo scanf

    mov rax, 0                                      ; poziv za vnos drugega stevila
	mov rdi, poziv
	mov rsi, 2
	call printf

	mov rax, 0                                      ; beremo
	mov rdi, vpis                                   ; kazalec v vpis
	mov rsi, n2                                     ; naslov na n2
	call scanf                                      ; za branje uporabimo scanf

    mov rax, 0                                      ; poziv za vnos tretjega stevila
	mov rdi, poziv
	mov rsi, 3
	call printf

    mov rax, 0                                      ; beremo
	mov rdi, vpis                                   ; kazalec v vpis
	mov rsi, n3                                     ; naslov na n3
	call scanf                                      ; za branje uporabimo scanf

	; -----------------------------------------------------------------------------------------------------

	mov rdi, [n1]                                   ; z rdi se bomo sklicecvali na prvo stevilo
	mov rsi, [n2]                                   ; z rsi se bomo sklicecvali na drugo stevilo
	mov rdx, [n3]                                   ; z rdx se bomo sklicecvali na tretje stevilo

	call min3                                       ; poklicemo min3 funkcijo

	mov rdi, izpis
	mov rsi, rax
	mov rax, 0
	call printf                                     ; izpis najmanjsega stevila

	; -----------------------------------------------------------------------------------------------------

	pop rbp
	mov rax, 0
	ret                                             ; konec programa

	min3:
		; compare first and second number
		cmp rdi, rsi
		jle .prvi_tretji

		; compare second and first number
		cmp rsi, rdi
		jle .drugi_tretji
		jmp .tretja

		; compare first and third number
		.prvi_tretji:
			cmp rdi, rdx
			jle .prva
			jmp .tretja

		; compare second and third number
		.drugi_tretji:
			cmp rsi, rdx
			jle .druga
			jmp .tretja

		; return first number
		.prva:
			mov rax, rdi
			ret

		; return second number
		.druga:
			mov rax, rsi
			ret

		; return third number
		.tretja:
			mov rax, rdx
			ret