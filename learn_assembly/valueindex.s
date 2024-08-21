
global _start
section .data

count:
    dq 10
array:
    dq 2, 4, 1, 24, 4234, 23, 12, 45, 21, 200
find:
    dq 200


; Program to find the value forward iterating
section .text
_start:
    ; initialize registers ;
    mov r8, [count]
    ; zero out counter register ;
    xor rcx, rcx

    ; check pre-conditions ;
    test r8, r8
    jz endloop

mainloop:
    ; get the value from the array ;
    mov rax, [array + rcx * 8]
    ; check if number is found ;
    cmp rax, [find]
    jne loopcontrol

    mov rdi, rcx
    jmp endloop

loopcontrol:
    inc rcx
    cmp rcx, r8
    jle mainloop

endloop:
    ; we are done ;
    mov rax, 60
    syscall
