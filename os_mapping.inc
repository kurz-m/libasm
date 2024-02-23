%ifndef __OS_MAPPING_INC__
%define __OS_MAPPING_INC__

%ifdef __linux__

%elifdef __APPLE__

%else
    ; something about not supported OS
%endif

%endif ; __OS_MAPPING_INC__