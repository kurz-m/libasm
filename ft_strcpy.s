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
    xor rcx, rcx ; size_t i = 0
    mov rax, rdi ; copy pointer for later return
    test sil, sil ; *(s) == '\0'
    jz .end_strcpy ; if '\0', jump to return statement
    mov dl, BYTE [rsi + rcx] ; copy *(src + rcx) to lower byte of rcx

.loop:
    mov BYTE [rdi + rcx], dl ; copy char to *(dest + rcx)
    inc rcx ; increase rcx by 1 (++rcx)
    mov dl, BYTE [rsi + rcx] ; copy *(src + rcx) to lower byte of rcx
    test dl, dl ; check of null-termination: char & char
    jne .loop ; jump to loop if char is not equal '\0'

.end_strcpy:
    ret ; return the pointer to dest
