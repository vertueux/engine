#include <stdio.h>

#include "dynamic_linked_lib_export.h"

extern "C" __declspec(dllexport) void __cdecl myprint(const char* str) {
  printf("%s", str);
}