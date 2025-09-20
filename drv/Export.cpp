#include "Export.hpp"
#include "DRV.c"

HANDLE Drv::DeviceHandle = nullptr;
std::string Drv::DriverName, Drv::DriverPath = "";

void Drv::_Init()
{
	srand(static_cast<unsigned>(time(nullptr)));
}

bool Drv::Install()
{
	const char* temp1 = "Drv64";
	DriverName = "WinDrv64.sys";
	DriverPath = "C:\\WinDrv64.sys";

	DeviceHandle = M::OpenDevice(temp1);
	if (DeviceHandle != INVALID_HANDLE_VALUE && DeviceHandle != NULL)
		return true;
	else
		DeleteFileA(DriverPath.c_str());
	std::ofstream outFile(DriverPath, std::ios::binary);
	if (!outFile)
		return false;
	outFile.write(reinterpret_cast<const char*>(EAC_Drv), sizeof(EAC_Drv));
	outFile.close();
	return true;
}

bool Drv::Uninstall()
{
	CloseHandle(Drv::DeviceHandle);
	M::StopDriver(DriverName);
	M::RemoveDriver(std::wstring(DriverPath.begin(), DriverPath.end()));
	DeleteFileA(DriverPath.c_str());
}