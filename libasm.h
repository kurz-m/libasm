#ifndef __LIBASM_H__
#define __LIBASM_H__

#include <sys/types.h>

#ifdef __cplusplus

	extern "C" size_t ft_strlen(const char* str);
	extern "C" char* ft_strcpy(char* dest, const char* src);

#else

	size_t	ft_strlen(const char* str);
	char* ft_strcpy(char* dest, const char* src);

#endif


#endif
