#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "struct.hpp"

namespace M
{
	using namespace std;
	bool CreateDriver(string var1, string var2);
	bool InstallDriver(const std::wstring& driverName, const std::wstring& driverPath);
	int	 IOCTL_IO(int var1);
	bool StartDriver(string var1, string var2);
	bool StopDriver(string var1);
	bool RemoveDriver(const std::wstring& var1);
	int  OpenDevice(string var1);
	
	const char* DynamicName(string var1);

	int IOCTL_Code(int var1, int var2, int var3, int var4);

	DWORD64 GetStructPtr(Struct10317* var1);
	DWORD64 GetStringPtr(string* var1);
	DWORD64 GetBytePtr(vector<unsigned char> var1);
	
	const char* RandomLetter(int var1);

}