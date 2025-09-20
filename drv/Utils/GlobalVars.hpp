#pragma once
#include "Windows.h"
#include <cstdint>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <fstream>


#ifndef GLOBALVARS_HPP
#define GLOBALVARS_HPP

namespace G
{
	using namespace std;

	constexpr DWORD var1026A = 2147483648;
	constexpr DWORD var1026B = 1073741824;
	constexpr DWORD var1026C = 3;
	constexpr DWORD var1026D = 16;

	extern const char* DriverName;
	extern const char* DriverPath;
	extern DWORD DeviceHandle;



}

#endif

