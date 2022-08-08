#include <stdio.h>

#include "dynamic_linked_lib_export.h"

namespace opticus {

extern "C" __declspec(dllexport) void __cdecl myprint(const char* str) {
  printf("%s", str);
}

}