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
