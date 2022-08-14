#pragma once

namespace opticus {

// Use them in your public API, which is intended to be used in the user's side.
// If you follow the folder convention, it should be all the functions being in the public/ directory.
#ifdef _WIN32
  #ifdef OPTICUS_BUILD_DLL
	  #define EXTENSION_API __declspec(dllexport)
  #else 
    #define EXTENSION_API __declspec(dllimport)
  #endif
#endif

}