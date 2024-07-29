%ifndef __OS_SYSCALLS_INC__
%define __OS_SYSCALLS_INC__

; syscall macros for Linux
%ifdef __linux__
    %define SYS_READ    0
    %define SYS_WRITE   1

%else
    %error "Unsupported operating system"

%endif

%endif ; __OS_SYSCALLS_INC__
