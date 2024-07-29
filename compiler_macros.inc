%ifndef __COMPILER_MACROS_INC__
%define __COMPILER_MACROS_INC__

; macros for gcc compiler
%ifdef __GNUC__
    %define FT_STRLEN   ft_strlen
    %define FT_STRCPY   ft_strcpy
    %define FT_STRCMP   ft_strcmp
    %define FT_WRITE    ft_write
    %define MALLOC      malloc

%else
    %error "Unsupported compiler"
%endif

%endif ; __COMPILER_MACROS_INC__
