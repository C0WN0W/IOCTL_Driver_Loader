#pragma once
#include "Misc.hpp"

namespace Drv
{
	HANDLE DeviceHandle;
	std::string DriverName, DriverPath;

	void _Init();
	bool Install();
	bool Uninstall();
	bool ApplyMemory(int PID, int Length);
	bool ReleaseMemory(int PID, DWORD64 Address);

}


