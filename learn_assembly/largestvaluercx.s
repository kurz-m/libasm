global _start
section .data
; How many data elements we have
count:
    dq 7

array:
    dq 5, 20, 33, 80, 52, 10, 1

; Program to find largest number in array
section .text
_start:
    ;;; Initialize registers ;;;
    ; Put count into rcx
    mov rcx, [count]
    ; Use rdi to hold current max
    mov rdi, 0

    ;;; Check pre-conditions ;;;
    ; If no numbers, stop
    test rcx, rcx
    jz endloop

mainloop:
    ; Get the next value inddexed by rbx
    mov rax, [array - 8  + rcx * 8]
    ; check if new max
    cmp rax, rdi
    jle loopcontrol

    ; Otherwise, new max element
    mov rdi, rax

loopcontrol:
    ; decrement rcx and keep going until rcx is zero
    dec rcx
    jnz mainloop

endloop:
    ; we're done
    mov rax, 60
    syscall
