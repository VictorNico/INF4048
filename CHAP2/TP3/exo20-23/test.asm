extern printf,scanf 
section .data
; declaration des variables en memoire
a:  dd  0
b:  dd  0
c:  dd  0
d:  dd  0
fmt:db "%d", 10, 0 
fmtlec:db "%d",0
section .text
global _start

_start:

push 3
 ;affectation
pop eax
mov [a], eax

push 42
push 3
 ;recuperation en memoire
mov eax, [a] 
push eax
 ;multiplication
pop eax
pop ebx
mul ebx
push eax

  ; addition
pop eax
pop ebx
add eax,ebx
push eax

  ;affectation
pop eax
mov [b], eax

;affiher
mov eax, [a] 
push eax
push dword fmt
call printf

;affiher
mov eax, [b] 
push eax
push dword fmt
call printf

mov eax,1 ; sys_exit 
mov ebx,0; Exit with return code of 0 (no error)
int 80h