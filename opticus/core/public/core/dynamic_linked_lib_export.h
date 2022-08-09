#pragma once

#include "core/platform_detection.h"

namespace opticus {

#ifdef OPTICUS_PLATFORM_WINDOWS
  #ifdef OPTICUS_BUILD_DLL
	  #define OPTICUS_API __declspec(dllexport)
  #else 
    #define OPTICUS_API __declspec(dllimport)
  #endif
#endif

}