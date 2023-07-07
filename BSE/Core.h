#ifndef BSE_CORE_H
#define BSE_CORE_H

#ifdef BSE_PLATFORM_WINDOWS
	#ifdef BSE_DLL
		#ifdef BSE_BUILD_DLL
			#define BSE_API __declspec(dllexport)
		#else
			#define BSE_API __declspec(dllimport)
		#endif
	#else
		#define BSE_API
	#endif
#else
	#error BSE currently only supports Windows.
#endif

// Assertions for debugging
#ifdef BSE_ENABLE_ASSERTS
	#define BSE_ASSERT(x,...) {if(!(x)) BSE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BSE_CORE_ASSERT(x,...) {if(!(x)) BSE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BSE_ASSERT(x,...)
	#define BSE_CORE_ASSERT(x,...)
#endif

// useful macros
#define BIT(x) (1 << x)

// basic includes
#include "./common.h"
#include "./log.h"

// basic functions
namespace BSE {
	BSE_API void print_hello(); 
	
	//BSE_API void Callback_dummy(Event& event);
}

#endif
