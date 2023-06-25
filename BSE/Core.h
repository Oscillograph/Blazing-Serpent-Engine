#ifndef BSE_CORE_H
#define BSE_CORE_H

#ifdef BSE_PLATFORM_WINDOWS
	#ifdef BSE_BUILD_DLL
		#define BSE_API __declspec(dllexport)
	#else
		#define BSE_API __declspec(dllimport)
	#endif
#else
	#error BSE currently only supports Windows.
#endif

// useful macros
#define BIT(x) (1 << x)

// basic includes
#include <stdio.h>

// basic functions
namespace BSE {
	BSE_API void print_hello(); 
}

#endif
