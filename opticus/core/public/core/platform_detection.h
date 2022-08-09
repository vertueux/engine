#pragma once

namespace opticus {

#ifdef _WIN32
	// Windows x64/x86 
	#ifdef _WIN64
		// Windows x64  
		#define OPTICUS_PLATFORM_WINDOWS
	#else
		// Windows x86 
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define OPTICUS_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define OPTICUS_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
// Check __ANDROID__ before __linux__
// since android is based on the linux kernel
// it has __linux__ defined 
#elif defined(__ANDROID__)
	#define OPTICUS_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define OPTICUS_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif // _WIN32

}