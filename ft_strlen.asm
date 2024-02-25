%include "compiler_macros.inc"
section .text

; Function declaration:
;   size_t strlen(const char* s);
; Input arguments:
;   rdi == const char* s)
; Return:
;   returns length of a string

global FT_STRLEN

FT_STRLEN:
    xor rax, rax    ; reset the register to 0
    cmp BYTE [rdi], 0 ; *str == '\0'
    je .end_strlen ; jump to end if *str is null terminator

    .loop:
        inc rax ; increase rax by 1
        cmp BYTE [rdi + rax], 0 ; *(str + rax) == '\0'
        jne .loop ; continue loop

    .end_strlen:
        ret ; returns the value in the rax register
