#ifndef BSE_PROTOCORE_H
#define BSE_PROTOCORE_H

// -------------------------------------------------------------------------------
//     The point of this "Proto" is to fix the multiple definition error that
// occurs through log.cpp file which includes Core.h while Core.h includes log.h
// -------------------------------------------------------------------------------

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
	#define BSE_ASSERT(x,...) {if(!(x)) BSE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }
	#define BSE_CORE_ASSERT(x,...) {if(!(x)) BSE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
	#define BSE_ASSERT(x,...)
	#define BSE_CORE_ASSERT(x,...)
#endif

// useful macros
#define BIT(x) (1 << x)

// FPS						ms between frames 
#define BSE_FPSNOLIMIT		0.0f
#define BSE_FPS120			0.0083f
#define BSE_FPS90			0.0111f
#define BSE_FPS60			0.0167f
#define BSE_FPS30			0.0333f
#define BSE_FPS15			0.0667f
#define BSE_FPS10			0.1f
#define BSE_FPS5			0.2f
#define BSE_FPS4			0.25f
#define BSE_FPS3			0.3333f
#define BSE_FPS2			0.5f
#define BSE_FPS1			1.0f

// defines before anything Vendor-ish is included
// #define GLM_FORCE_CTOR_INIT // to force GLM initialize vectors and matrices 

// basic includes
// #include <BSE/common.h>
#include <common.h>

#endif
