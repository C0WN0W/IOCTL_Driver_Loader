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
	SC_HANDLE temp2, temp3;

	if (var1.empty()) return false;
	if (!CreateDriver(var1, var2)) return false;

	temp2 = OpenSCManagerA(0, 0, 1 | 2 | 4 | 8 | 16 | 32);
	if (!temp2) return false;
	temp3 = OpenServiceA(temp2, var1.c_str(), 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256);
	if (!temp3)
	{
		CloseServiceHandle(temp2);
		return false;
	}
	if (ControlService(temp3, 4, (LPSERVICE_STATUS)&temp1))
	{
		if (temp1.Member1031F = 4)
		{
			CloseServiceHandle(temp3);
			CloseServiceHandle(temp2);
			return true;
		}
	}
	else if (!StartServiceA(temp3, 0, 0))
	{
		CloseServiceHandle(temp3);
		CloseServiceHandle(temp2);
		return false;
	}
	for (int i = 0; i <= 10; ++i)
	{
		if (ControlService(temp3, 4, (LPSERVICE_STATUS)&temp1) == 0)
		{
			CloseServiceHandle(temp3);
			CloseServiceHandle(temp2);
			return false;
		}
		else
		{
			if (temp1.Member1031F == 4)
			{
				break;
			}
		}
		Sleep(4000);
	}
	CloseServiceHandle(temp3);
	CloseServiceHandle(temp2);
	if (temp1.Member1031F == 4) 
		return true;
	else 
		return false;
}

bool M::StopDriver(string var1)
{
	Struct10318 temp1;
	SC_HANDLE temp2, temp3;

	temp2 = OpenSCManagerA(0, 0, 1 | 2 | 4 | 8 | 16 | 32);
	if (!temp2) return false;
	temp3 = OpenServiceA(temp2, var1.c_str(), 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256);
	if (!temp3)
	{
		CloseServiceHandle(temp2);
		return false;
	}
	if (ControlService(temp3, 4, (LPSERVICE_STATUS)&temp1) != 0)
	{
		if (temp1.Member1031F != 1)
		{
			if (ControlService(temp3, 1, (LPSERVICE_STATUS)&temp1) == 0)
			{
				CloseServiceHandle(temp3);
				CloseServiceHandle(temp2);
				return false;
			}
			for (int i = 0; i <= 10; ++i)
			{
				if (ControlService(temp3, 4, (LPSERVICE_STATUS)&temp1) == 0)
				{
					CloseServiceHandle(temp3);
					CloseServiceHandle(temp2);
					return true;
				}
				else
				{
					if (temp1.Member1031F == 1)
					{
						break;
					}
				}
				Sleep(4000);
			}
			if (temp1.Member1031F != 1)
			{
				CloseServiceHandle(temp3);
				CloseServiceHandle(temp2);
				return false;
			}
		}
	}
	CloseServiceHandle(temp3);
	CloseServiceHandle(temp2);
	return true;
}

int M::OpenDevice(string var1)
{
	string temp1 = "\\\\.\\" + var1;
	int temp2 = (int)CreateFileA(temp1.c_str(), (G::var1026A | G::var1026B), 0, 0, G::var1026C, 128, 0);
	return temp2;
}

int M::IOCTL_Code(int var1, int var2, int var3, int var4)
{
	int result = (var1 << 16) | (var4 << 14) | (var2 << 2) | (var3);
	return result;
}

int	M::IOCTL_IO(int var1)
{
	return M::IOCTL_Code(34, var1, 0, 0);
}

const char* M::RandomLetter(int var1)
{	
	string word;
	srand((unsigned)time(NULL) + var1);
	for (int i = 0; i < var1; i++)
	{
		int temp1 = rand() % 52;
		if (temp1 < 26)
			word = word + (char)(65 + temp1);
		else
			word = word + (char)(97 + (temp1 - 26));
	}
	return word.c_str();
}

const char* M::DynamicName()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 50);

	string result = RandomLetter(3) + to_string(dis(gen)) + RandomLetter(3) + ".sys";
	return result.c_str();
}