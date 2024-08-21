global _start
section .data
; How many data elements we have
count:
    dq 7
array:
    dq 5, 20, 33, 80, 52, 10, 1
find:
    dq 10

; Program to find number in an array
; returns 1 if number is found, 0 otherwise
section .text
_start:
    ;;; Initialize registers ;;;
    ; Put count into rcx
    mov rcx, [count]
    ; Use rdi as store for the final count caluclation
    mov rdi, [count]

    ;;; Check pre-conditions ;;;
    ; If no numbers, stop
    test rcx, rcx
    jz endloop

mainloop:
    ; Get the next value inddexed by rbx
    mov rax, [array + rcx * 8 - 8]
    ; check if number is found
    cmp rax, [find]
    jne loopcontrol

    lea rdi, [rcx - 1]
    jmp endloop

loopcontrol:
    ; decrement rcx and keep going until rcx is zero
    dec rcx
    jnz mainloop

endloop:
    ; we're done

    mov rax, 60
    syscall
