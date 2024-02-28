%include "compiler_macros.inc"

; Function declaration:
;   char* strcpy(char* dest, const char* src);
; Input arguments:
;   rdi == char* dest
;   rsi == const char* src
; Return:
;   returns pointer to dest

section .text

global FT_STRCPY

FT_STRCPY:
    xor rdx, rdx ; size_t i = 0
    mov rax, rdi ; copy pointer for later return
    test sil, sil ; *(s) == '\0'
    jz .end_strcpy ; if '\0', jump to return statement
    mov cl, BYTE [rsi + rdx] ; copy *(src + rdx) to lower byte of rcx

.loop:
    mov BYTE [rdi + rdx], cl ; copy char to *(dest + rdx)
    inc rdx ; increase rdx by 1 (++rdx)
    mov cl, BYTE [rsi + rdx] ; copy *(src + rdx) to lower byte of rcx
    test cl, cl ; check of null-termination: char & char
    jne .loop ; jump to loop if char is not equal '\0'

.end_strcpy:
    ret ; return the pointer to dest
