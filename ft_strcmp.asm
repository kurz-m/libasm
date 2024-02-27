%include "compiler_macros.inc"

; Function declaration:
;   int strcmp(const char* s1, const char* s2);
; Input arguments:
;   rdi == const char* s1
;   rsi == const char* s2
; Return
;   returns an integer < 0, == 0, > 0
;   if s1 < s2, s1 == s2, or s1 > s2

section .text

global FT_STRCMP

FT_STRCMP:
    xor r8, r8
    
    .loop:
        movzx al, BYTE [rdi + r8]
        movzx dl, BYTE [rsi + r8]
        cmp al, dl
        jne .end_strcmp
        test al, al
        jz .end_strcmp
        inc r8
        je .loop
    
    .end_strcmp:
        sub rax, rdx
        ret
