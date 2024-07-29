%include "compiler_macros.inc"
%include "os_syscalls.inc"
section .text

; Function declaration:
;   ssize_t write(int fd, const void *buf, size_t nbyte);
; Input arguments:
;   rdi == int fd
;   rsi == const void *buf
;   rds == size_t nbyte
; Return:
;   on success returns number of bytes written
;   else -1 and sets errno to indicate the error

global FT_WRITE

FT_WRITE:
    xor rax, rax    ; reset the register to 0
    mov rax, SYS_WRITE ; load write function
    syscall ; make syscall

    test rax, rax
    js .handle_error    ; handle error if write returns -1
    ret ; return after successful writing

    .handle_error:
        neg rax
        mov rax, -1
        ret
