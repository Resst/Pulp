#pragma once

#ifdef PLP_PLATFORM_WINDOWS
	#ifdef PLP_BUILD_DLL
		#define PULP_API __declspec(dllexport)
	#else
		#define PULP_API __declspec(dllimport)
	#endif // PLP_BUILD_DLL
#else
	#error Only windows supported!
#endif // PLP_PLATFORM_WINDOWS

#ifdef PLP_ENABLE_ASSERTS
	#define PLP_ASSERT(x, ...) {if(!(x)){HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}}
	#define PLP_CORE_ASSERT(x, ...) {if(!(x)){HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__);__debugbreak();}}
#else
	#define PLP_ASSERT(x, ...)
	#define PLP_CORE_ASSERT(x, ...)
#endif