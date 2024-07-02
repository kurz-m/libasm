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
    xor rcx, rcx ; size_t i = 0

    .loop:
        movzx rax, BYTE [rdi + rcx] ; char c1 = *(s1 + i) + zero-extension
        movzx rdx, BYTE [rsi + rcx] ; char c2 = *(s2 + i) + zero-extension
        cmp al, dl ; compare chars for early return
        jne .end_strcmp ; jump to end if c1 != c2
        test al, al ; check for null-termination
        jz .end_strcmp ; jump to end if c1 == '\0'
        inc rcx ; increase counter -> ++i
        je .loop ; jump back to loop

    .end_strcmp:
        sub rax, rdx ; subtract c2 value from c1 value
        ret ; return the calculated value
