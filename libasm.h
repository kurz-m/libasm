#ifndef __LIBASM_H__
#define __LIBASM_H__

#include <sys/types.h>

#ifdef __cplusplus

	extern "C" size_t ft_strlen(const char* str);
	extern "C" char* ft_strcpy(char* dest, const char* src);
	extern "C" int ft_strcmp(const char* s1, const char* s2);

#else

	size_t	ft_strlen(const char* str);
	char* ft_strcpy(char* dest, const char* src);
	int ft_strcmp(const char* s1, const char* s2);

#endif


#endif
