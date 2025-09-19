#include "Misc.hpp"

bool M::CreateDriver(string var1, string var2)
{
	SC_HANDLE temp1, temp2;
	int temp4;
	Struct10318 temp3;

	int result = 1 | 2 | 4 | 8 | 16 | 32;
	temp1 = OpenSCManagerA(0, 0, result);
	if (!temp1) return false;

	result = 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256;
	temp2 = OpenServiceA(temp1, var1.c_str(), result);
	if (temp2 != 0)
	{
		if (ControlService(temp2, 4, (LPSERVICE_STATUS)&temp3) != 0)
		{ 
			if (temp3.Member1031F != 1)
			{
				if (ControlService(temp2, 1, (LPSERVICE_STATUS)&temp3) == 0)
				{
					CloseServiceHandle(temp2);
					CloseServiceHandle(temp1);
					return false;
				}
				for (int i = 0; i <= 10; ++i)
				{
					if (ControlService(temp2, 4, (LPSERVICE_STATUS)&temp3) == 0)
					{
						CloseServiceHandle(temp2);
						CloseServiceHandle(temp1);
						return true;
					}
					else
					{
						if (temp3.Member1031F == 1)
						{
							break;
						}
					}
					Sleep(4000);
				}
				if (temp3.Member1031F != 1)
				{
					CloseServiceHandle(temp2);
					CloseServiceHandle(temp1);
					return false;
				}
			}
		}
		CloseServiceHandle(temp2);
		CloseServiceHandle(temp1);
		return true;
	}
	result = 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256;
	temp2 = CreateServiceA(temp1, var1.c_str(), var1.c_str(), result, 1, 3, 1, var2.c_str(), 0, 0, 0, 0, 0);
	if (temp2 == 0)
	{
		CloseServiceHandle(temp1);
		return false;
	}
	CloseServiceHandle(temp2);
	CloseServiceHandle(temp1);
	return true;
}

bool M::InstallDriver(const std::wstring& driverName, const std::wstring& driverPath)
{
	wstring regBase = L"SYSTEM\\CurrentControlSet\\Services\\" + driverName;
	HKEY hKey = nullptr;
	if (driverName.empty() || driverPath.empty()) {
		return false;
	}

	if (RegCreateKeyExW(HKEY_LOCAL_MACHINE, regBase.c_str(), 0, nullptr, 0, KEY_WRITE, nullptr, &hKey, nullptr) != ERROR_SUCCESS)
		return false;

	DWORD temp1 = 1;
	DWORD temp2 = 3;
	bool success =
		RegSetValueExW(hKey, L"DisplayName", 0, REG_SZ,
			(const BYTE*)driverName.c_str(), (driverName.size() + 1) * sizeof(wchar_t)) == ERROR_SUCCESS &&
		RegSetValueExW(hKey, L"ErrorControl", 0, REG_DWORD,
			(const BYTE*)&temp1, sizeof(DWORD)) == ERROR_SUCCESS &&
		RegSetValueExW(hKey, L"ImagePath", 0, REG_SZ,
			(const BYTE*)(L"\\??\\" + driverPath).c_str(), (driverPath.size() + 4 + 1) * sizeof(wchar_t)) == ERROR_SUCCESS &&
		RegSetValueExW(hKey, L"Start", 0, REG_DWORD,
			(const BYTE*)&temp2, sizeof(DWORD)) == ERROR_SUCCESS &&
		RegSetValueExW(hKey, L"Type", 0, REG_DWORD,
			(const BYTE*)&temp1, sizeof(DWORD)) == ERROR_SUCCESS;

	RegCloseKey(hKey);
	return success;
}

bool M::RemoveDriver(const std::wstring& driverName) {
	std::wstring baseKey = L"SYSTEM\\CurrentControlSet\\Services\\" + driverName;

	auto deleteValue = [](const std::wstring& subKey, const std::wstring& valueName) -> bool {
		HKEY hKey;
		if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
			return false;

		LONG result = RegDeleteValueW(hKey, valueName.c_str());
		RegCloseKey(hKey);
		return result == ERROR_SUCCESS;
		};

	if (deleteValue(baseKey, L"DisplayName") &&
		deleteValue(baseKey, L"ErrorControl") &&
		deleteValue(baseKey, L"ImagePath") &&
		deleteValue(baseKey, L"Start") &&
		deleteValue(baseKey, L"Type")) {
		return true;
	}

	return false;
}
 
bool M::StartDriver(string var1, string var2)
{
	Struct10318 temp1;
	SC_HANDLE temp2, temp3, temp4;

}