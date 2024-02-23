%ifndef __OS_SYSCALLS_INC__
%define __OS_SYSCALLS_INC__

; syscall macros for Linux
%ifdef __linux__
    %define SYS_EXIT    1
    %define SYS_WRITE   4
    %define SYS_READ    0

; syscall macros for macOS
%elif __APPLE__
    %define SYS_EXIT    0x2000001
    %define SYS_WRITE   0x2000004
    %define SYS_READ    0x2000003

%else
    %error "Unsupported operating system"

%endif

%endif ; __OS_SYSCALLS_INC__
