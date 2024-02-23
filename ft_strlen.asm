section .text

global FT_STRLEN

FT_STRLEN:
    xor rax, rax    ; reset the register to 0

    .LOOP:
        cmp BYTE [rdi + rax], 0 ; *(str + rax) == '\0'
        je  .END_STRLEN ; if equal, end of string found
        inc rax ; increase rax by 1
        jmp .LOOP ; continue loop

    .END_STRLEN:
        ret ; returns the rax register