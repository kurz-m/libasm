%ifndef __COMPILER_MACROS_INC__
%define __COMPILER_MACROS_INC__

; macros for gcc compiler
%ifdef __GNUC__
    %define FT_STRLEN   ft_strlen
    %define MALLOC      malloc

; macros for clang compiler
%elif __clang__
    %define FT_STRLEN   _ft_strlen
    %define MALLOC      _malloc

; throw error
%else
    %error "Unsupported compiler"
%endif

%endif ; __COMPILER_MACROS_INC__
