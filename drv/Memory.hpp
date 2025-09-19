#pragma once
#include <cstdlib>
#include <ctime>
#include "Misc.hpp"

namespace D
{
	void _Init();
	bool InstallDrv();
	bool UninstallDrv();
	bool ApplyMemory(int PID, int Length);
	bool ReleaseMemory(int PID, DWORD64 Address);

}


