%ifndef __OS_SYSCALLS_INC__
%define __OS_SYSCALLS_INC__

; syscall macros for Linux
%ifdef __linux__
    %define SYS_READ    0
    %define SYS_WRITE   1

; syscall macros for macOS
%elif __APPLE__
    %define SYS_READ    0x2000003
    %define SYS_WRITE   0x2000004

%else
    %error "Unsupported operating system"

%endif

%endif ; __OS_SYSCALLS_INC__
