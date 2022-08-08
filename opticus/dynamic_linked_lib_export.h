#pragma once

#include <stdio.h>
#include <stdlib.h>

namespace opticus {

extern "C" __declspec(dllexport) void __cdecl myprint(const char* str);

}