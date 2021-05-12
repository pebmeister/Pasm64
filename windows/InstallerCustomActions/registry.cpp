#include "pch.h"


using namespace std;

static DWORD MapRegistryError(DWORD error)
{

	return error;
}

// Internal function to split full Registry pathname (of a key or value) into a base pathname and the
// rightmost component of the path.  Given a path of the form "...\key\key\key\name" this splits it into
// "HKEY_...\key\key\key" and "name".  Note that "name" can be either a key or a value.
//
// basePath [out]: This is set to the base path without the trailing baseName.  If there are no path separators
//                 in fullPath, this is set to the empty string.
//
// baseName [out]: This is set to the last component of fullPath.  If there are no path separators in fullPath,
//                 this is set to fullPath.  If fullPath ends with a path separator, this is set to the empty
//                 string.
//
// fullPath [in]: The full path of a Registry key or value.
static void RegistrySplitPath(_In_ const wstring& fullPath, _Out_ wstring& basePath, _Out_ wstring& baseName)
{
	auto const nameIndex = fullPath.find_last_of(L'\\');

	// check that fullPath contains the '\'
	// if the '\' is not present basePath will be cleared and the baseName
	// will be a copy of fullPath
	if (nameIndex > fullPath.size())
	{
		basePath.clear();
		baseName = fullPath;
		return;
	}

	// extract the basePath and baseName
	basePath = fullPath.substr(0, nameIndex);

	if (fullPath.size() == nameIndex)
	{
		baseName.clear();
		return;
	}

	baseName = fullPath.substr(nameIndex + 1, fullPath.size() - nameIndex);
}

// This function reads an arbitrary value from the 64-bit Registry.
//
// Parameters:
//
// keyHandle [in]: The handle of a Registry key.  This can be one of the manifest constants
//                 HKEY_LOCAL_MACHINE, KEY_CURRENT_USER, etc. that identify the root of a Registry hive (see
//                 https://msdn.microsoft.com/en-us/library/ms724836.aspx).
//
// valuePath [in]: The pathname (relative to the key referenced by keyHandle) of the Registry value to read.
//
// pType [out, opt]: If not nullptr, points to a DWORD where the type of the data will be written.
//
// pData [in, opt]: If not nullptr, points to memory where the value's data will be written.  If pData is
//                  nullptr, and pByteCont is not nullptr, this succeeds and stores the size of the data (in
//                  bytes) in the memory pointed to by pByteCont.
//
// pByteCont [in, out, opt]: If not nullptr, points to the size of the buffer pointed to by pData.  After
//                           success, the size (in bytes) of the data is written to this memory.  After
//                           failure due to insufficient buffer size, the required size (in bytes) of the data
//                           is written to this memory.
//
// Returns true if successful, otherwise returns false and sets the last error value.
static bool GetRegistryValue(HKEY keyHandle, const wstring& valuePath, DWORD* pType, BYTE* pData, DWORD* pByteCount)
{
	// Validate the lpValueName
	if (valuePath.size() == 0 || keyHandle == nullptr)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return  false;
	}

	// Split valuePath into the subkey pathname from the value name.
	wstring subkeyPath, valueName;
	RegistrySplitPath(valuePath, subkeyPath, valueName);

	// Open the key in the 64-bit Registry..
	HKEY subkeyHandle = nullptr;

	Finally<> cleanup([&subkeyHandle]
		{
			// Do NOT close keyHandle here!  That handle is owned by the caller.
			if (subkeyHandle != nullptr)
				RegCloseKey(subkeyHandle);
		});

	auto regStatus = RegOpenKeyExW(keyHandle, subkeyPath.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &subkeyHandle);

	if (regStatus != ERROR_SUCCESS)
	{
		SetLastError(MapRegistryError(regStatus));
		return false;
	}

	// query the registry data
	// if the name is zero byte we really want the default value
	// that is achieved by passing nullptr as the name
	regStatus = RegQueryValueExW(subkeyHandle, valueName.size() > 0 ? valueName.c_str() : nullptr, nullptr, pType, pData, pByteCount);

	// check the error
	if (regStatus != ERROR_SUCCESS)
	{
		SetLastError(MapRegistryError(regStatus));
		return false;
	}

	return true;
}

// This function write an arbitrary value from the 64-bit Registry.
//
// Parameters:
//
// subkey [in]:	   The subkey path of a registry key in HKEY_LOCAL_MACHINE.
//
bool DeleteRegistryKeyW(_In_ const std::wstring& subkey)
{
	// Validate the valuePath
	if (subkey.empty())
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return false;
	}

	// HKEY subkeyHandle = nullptr;
	wstring regPath;
	wstring regKeyName;

	auto regStatus = RegDeleteKeyW(HKEY_LOCAL_MACHINE, subkey.c_str());
	if (regStatus != ERROR_SUCCESS)
	{
		SetLastError(MapRegistryError(regStatus));
		return false;
	}

	return true;
}


// This function write an arbitrary value from the 64-bit Registry.
//
// Parameters:
//
// keyHandle [in]: The handle of a Registry key.  This can be one of the manifest constants
//                 HKEY_LOCAL_MACHINE, KEY_CURRENT_USER, etc. that identify the root of a Registry hive (see
//                 https://msdn.microsoft.com/en-us/library/ms724836.aspx).
//
// valuePath [in]: The pathname (relative to the key referenced by keyHandle) of the Registry value to read.
//
// dataType [in]: The type of the data to be written.
//
// pData [in]: Points to a buffer containing the data to be written.
//
// byteCount [in]: The size (in bytes) of the buffer pointed to by pData. if string include the space for null terminating bytes (Add 2 for unicode)
//
// Returns true if successful, otherwise returns false and sets the last error value.
static bool SetRegistryValue(HKEY keyHandle, const wstring& valuePath, DWORD dataType, const void* pData, DWORD byteCount)
{
	// Validate the valuePath
	if (keyHandle == nullptr || valuePath.size() == 0 || pData == nullptr || byteCount == 0)
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return false;
	}

	HKEY subkeyHandle = nullptr;
	wstring regPath;
	wstring regKeyName;

	// split the path into a registry Path and registry KeyName
	RegistrySplitPath(valuePath, regPath, regKeyName);

	// Create or open the registry key.
	Finally<> cleanup([&subkeyHandle]
		{
			// Do NOT close keyHandle here!  That handle is owned by the caller.
			if (subkeyHandle != nullptr)
				RegCloseKey(subkeyHandle);
		});

	auto regStatus = RegCreateKeyExW(keyHandle, regPath.c_str(), NULL, nullptr,
		REG_OPTION_NON_VOLATILE, KEY_WOW64_64KEY | KEY_ALL_ACCESS, nullptr, &subkeyHandle, nullptr);

	if (regStatus != ERROR_SUCCESS)
	{
		SetLastError(MapRegistryError(regStatus));
		return false;
	}

	// set the registry value
	regStatus = RegSetKeyValueW(subkeyHandle, nullptr, regKeyName.size() > 0 ? regKeyName.c_str() : nullptr, dataType, pData, byteCount);

	// check the error
	if (regStatus != ERROR_SUCCESS)
	{
		SetLastError(MapRegistryError(regStatus));
		return false;
	}

	return true;
}

// This function reads a REG_SZ value from the 64-bit registry.
//
// Parameters:
//
// valuePathName [in, opt]: The pathname (relative to the key references by parameter keyHandle) of the value
//                          to read.  If the type of the value is not REG_SZ, this returns false, and sets the
//                          last error to ERROR_INVALID_PARAMETER.
//
// valueName [out]: The data read from the Registry value.
//
// keyHandle [in]: The handle of a Registry key under which parameter valuePathName is located.
//
// Returns true if successful, otherwise returns false and sets the last error value.
bool GetRegistrySzValue(_In_ const wstring& valuePathName, _Out_ wstring& data, _In_ HKEY keyHandle)
{
	DWORD keyType = 0;
	DWORD cbBytes = 0;

	auto status = GetRegistryValue(keyHandle, valuePathName, &keyType, nullptr, &cbBytes);

	if (status)
	{
		if (keyType != REG_SZ)
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return false;
		}

		unique_ptr<wchar_t[]> dataBuffer;

		// This will handle the case if cbBytes is not a multiple of sizeof(wchar_t)
		const auto bufferSize = cbBytes / sizeof(wchar_t);

		try
		{
			dataBuffer = make_unique<wchar_t[]>(bufferSize);
		}
		catch (bad_alloc)  // NOLINT(misc-throw-by-value-catch-by-reference)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			return false;
		}

		status = GetRegistryValue(keyHandle, valuePathName, &keyType, LPBYTE(dataBuffer.get()), &cbBytes);

		if (status)
		{
			data = dataBuffer.get();
		}
	}

	return status;
}

// SetRegistrySzValue is used to set and create registry string value
//
// If the lpValueName registry value does not exist, the functionreturn false
// GetLastError returns RT_ERROR_REGISTRY_MISSING and the value returned through the lpcbData parameter is undefined.
//
// on failure call should call GetLastError
// GetRegistryValue will read the 64 bit registry from HKEY_LOCAL_MACHINE
//
// lpValueName[in]
// The name of the registry value.
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[in]
// string registry value.
bool SetRegistrySzValue(_In_ const wstring& lpValueName, _In_ const wstring& value, _In_ HKEY keyHandle)
{
    // ReSharper disable once CppFunctionalStyleCast
    return SetRegistryValue(keyHandle, lpValueName, REG_SZ, value.c_str(), DWORD((value.size() * 2) + sizeof(wchar_t)));  // NOLINT(bugprone-misplaced-widening-cast)
}

// GetRegistryExpandSzValue will read the 64 bit registry from HKEY_LOCAL_MACHINE and retrieve a wstring with expanded environment variables
//
// lpValueName[in, optional]
// The full path and name of the registry value
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[out]
// A variable that receives the value of the registry key.
//
// If the data type is not REG_EXPAND_SZ the function will return false and SetLastError to ERROR_INVALID_PARAMETER
//
bool GetRegistryExpandSzValue(_In_ const wstring& lpValueName, _Out_ wstring& value, _In_ HKEY keyHandle)
{
	value.clear();
	DWORD keyType;
	DWORD cbBytes = 0;
	auto status = GetRegistryValue(keyHandle, lpValueName, &keyType, nullptr, &cbBytes);
	if (status)
	{
		if (keyType != REG_EXPAND_SZ)
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return false;
		}
		unique_ptr<WCHAR[]> data;
		try
		{
			data = make_unique<WCHAR[]>(cbBytes / 2);
		}
		catch (bad_alloc)  // NOLINT(misc-throw-by-value-catch-by-reference)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			return false;
		}
		status = GetRegistryValue(keyHandle, lpValueName, &keyType, LPBYTE(data.get()), &cbBytes);
		if (status)
		{
			value = data.get();
		}
	}
	return status;
}

// function to set and create registry string value
//
// If the lpValueName registry value does not exist, the function return false
// GetLastError returns RT_ERROR_REGISTRY_MISSING and the value returned through the lpcbData parameter is undefined.
//
// on failure call should call GetLastError
// GetRegistryValue will read the 64 bit registry from keyHandle
//
// lpValueName[in]
// The name of the registry value.
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[in] string registry value.
bool SetRegistryExpandSzValue(_In_ const wstring& lpValueName, _In_ const wstring& value, _In_ HKEY keyHandle)
{
	return SetRegistryValue(keyHandle, lpValueName, REG_EXPAND_SZ, value.c_str(), DWORD((value.size() * 2) + sizeof(wchar_t)));  // NOLINT(bugprone-misplaced-widening-cast)
}

// GetRegistryRegMultiSzValue will read the 64 bit registry from keyHandle and retrieve a wstring vector
//
// lpValueName[in, optional]
// The full path and name of the registry value
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[out]
// A variable that receives the value of the registry key.
//
// If the data type is not REG_MULTI_SZ the function will return false and SetLastError to ERROR_INVALID_PARAMETER
//
bool GetRegistryMultiSzValue(_In_ const wstring& lpValueName, _Out_ vector<wstring>& value, _In_ HKEY keyHandle)
{
	value.clear();
	DWORD keyType;
	DWORD cbBytes = 0;
	auto status = GetRegistryValue(keyHandle, lpValueName, &keyType, nullptr, &cbBytes);
	if (status)
	{
		if (keyType != REG_MULTI_SZ)
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return false;
		}
		unique_ptr<WCHAR[]> data;
		try
		{
			data = make_unique<WCHAR[]>(cbBytes / 2);
		}
		catch (bad_alloc)  // NOLINT(misc-throw-by-value-catch-by-reference)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			return false;
		}

		status = GetRegistryValue(keyHandle, lpValueName, &keyType, LPBYTE(data.get()), &cbBytes);
		if (status)
		{
			value.clear();
			auto index = 0;

			while (data.get()[index])
			{
				wstring string;
				string.clear();
				do
				{
					if (data.get()[index])
					{
						string.append(1, data.get()[index]);
					}
					index++;
				} while (data.get()[index]);
				value.push_back(string);
				index++;
			}
		}
	}
	return status;
}

// function to set and create registry multi string values
//
// If the lpValueName registry value does not exist, the functionreturn false
// GetLastError returns RT_ERROR_REGISTRY_MISSING and the value returned through the lpcbData parameter is undefined.
//
// on failure caller should call GetLastError
// GetRegistryValue will read the 64 bit registry from keyHandle
//
// lpValueName[in]
// The name of the registry value.
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// wstrings[in] vector of string registry values.
//
bool SetRegistryMultiSzValue(_In_ const wstring& lpValueName, _In_ vector<wstring>& wstrings, _In_ HKEY keyHandle)
{
	wstring regvalue;
	DWORD size = 0;
	for (auto str : wstrings)
	{
		regvalue.append(str.c_str());
		size += (DWORD)str.size();
		if (str.length() == 0 || str[str.length() - 1] != L'\0')
		{
			regvalue.append(1, L'\0');
			size += 1;
		}
	}
	regvalue.append(1, L'\0');
	size += 1;

	size *= 2; // wide string!
	return SetRegistryValue(keyHandle, lpValueName, REG_MULTI_SZ, regvalue.c_str(), size);
}

// GetRegistryDWordValue will read the 64 bit registry from keyHandle and retrieve a DWORD value
//
// lpValueName[in, optional]
// The full path and name of the registry value
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[out]
// A variable that receives the value of the registry key.
//
// If the data type is not REG_DWORD the function will return false and SetLastError to ERROR_INVALID_PARAMETER
//
bool GetRegistryDWordValue(_In_ const wstring& lpValueName, _Out_ uint32_t& value, _In_ HKEY keyHandle)
{
	value = 0;
	DWORD keyType;
	DWORD cbBytes = 0;
	auto status = GetRegistryValue(keyHandle, lpValueName, &keyType, nullptr, &cbBytes);
	if (status)
	{
		if (keyType != REG_DWORD)
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return false;
		}
		status = GetRegistryValue(keyHandle, lpValueName, &keyType, LPBYTE(&value), &cbBytes);
	}
	return status;
}

// function to set and create registry DWORD value
//
// If the lpValueName registry value does not exist, the functionreturn false
// GetLastError returns RT_ERROR_REGISTRY_MISSING and the value returned through the lpcbData parameter is undefined.
//
// on failure caller should call GetLastError
// GetRegistryValue will read the 64 bit registry from keyHandle
//
// lpValueName[in]
// The name of the registry value.
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[in] DWORD registry value.
bool SetRegistryDWordValue(_In_ const wstring& lpValueName, _In_ const uint32_t value, _In_ HKEY keyHandle)
{
	return SetRegistryValue(keyHandle, lpValueName, REG_DWORD, &value, DWORD(sizeof(DWORD)));
}

// GetRegistryQWordValue will read the 64 bit registry from keyHandle and retrieve a uint64_t value
//
// lpValueName[in, optional]
// The full path and name of the registry value
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[out]
// A variable that receives the value of the registry key.
//
// If the data type is not REG_QWORD the function will return false and SetLastError to ERROR_INVALID_PARAMETER
//
bool GetRegistryQWordValue(_In_ const wstring& lpValueName, _Out_ uint64_t& value, _In_ HKEY keyHandle)
{
	value = 0;
	DWORD keyType;
	DWORD cbBytes = 0;
	auto status = GetRegistryValue(keyHandle, lpValueName, &keyType, nullptr, &cbBytes);
	if (status)
	{
		if (keyType != REG_QWORD)
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return false;
		}
		status = GetRegistryValue(keyHandle, lpValueName, &keyType, LPBYTE(&value), &cbBytes);
	}
	return status;
}

// function to set and create registry QWORD value
//
// If the lpValueName registry value does not exist, the function return false
// GetLastError returns RT_ERROR_REGISTRY_MISSING and the value returned through the lpcbData parameter is undefined.
//
// on failure caller should call GetLastError
// GetRegistryValue will read the 64 bit registry from keyHandle
//
// lpValueName[in]
// The name of the registry value.
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[in] QWORD registry value.
bool SetRegistryQWordValue(_In_ const  wstring& lpValueName, _In_ const uint64_t value, _In_ HKEY keyHandle)
{
	return SetRegistryValue(keyHandle, lpValueName, REG_QWORD, &value, DWORD(sizeof(uint64_t)));
}

// GetRegistryBinaryValue will read the 64 bit registry from keyHandle and retrieve a BYTE vector value
//
// lpValueName[in, optional]
// The full path and name of the registry value
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[out]
// A variable that receives the value of the registry key.
//
// If the data type is not REG_BINARY the function will return false and SetLastError to ERROR_INVALID_PARAMETER
//
bool GetRegistryBinaryValue(_In_ const  wstring& lpValueName, _Out_ vector<BYTE>& value, _In_ HKEY keyHandle)
{
	value.clear();
	DWORD keyType;
	DWORD cbBytes = 0;
	auto status = GetRegistryValue(keyHandle, lpValueName, &keyType, nullptr, &cbBytes);
	if (status)
	{
		if (keyType != REG_BINARY)
		{
			SetLastError(ERROR_INVALID_PARAMETER);
			return false;
		}
		unique_ptr<BYTE[]> data;
		try
		{
			data = make_unique<BYTE[]>(cbBytes);
		}
		catch (bad_alloc)  // NOLINT(misc-throw-by-value-catch-by-reference)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			return false;
		}

		status = GetRegistryValue(keyHandle, lpValueName, &keyType, LPBYTE(data.get()), &cbBytes);
		if (status)
		{
			vector<BYTE> bytes(data.get(), data.get() + cbBytes);
			value = bytes;
		}
	}
	return status;
}

// function to set and create registry Binary value
//
// If the lpValueName registry value does not exist, the functionreturn false
// GetLastError returns RT_ERROR_REGISTRY_MISSING and the value returned through the lpcbData parameter is undefined.
//
// on failure caller should call GetLastError
//
// lpValueName[in]
// The name of the registry value.
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[in] regbinary registry value.
//
bool SetRegistryBinaryValue(_In_ const  wstring& lpValueName, _In_ vector<BYTE>& value, _In_ HKEY keyHandle)
{
	return SetRegistryValue(keyHandle, lpValueName, REG_BINARY, value.data(), DWORD(value.size()));
}

// function to enumerate registry keys
//
//
// on failure caller should call GetLastError
//
// path[in]
// The name of the registry value.
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[out] vector of registry keys.
//
bool RegistryEnumKeys(_In_ const  wstring& path, _Out_ vector<wstring>& value, _In_ HKEY keyHandle)
{
	value.clear();
	HKEY key = nullptr;

	// open the registry keyPath
	auto regStatus = RegOpenKeyExW(keyHandle, path.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &key);
	if (regStatus != ERROR_SUCCESS)
	{
		SetLastError(MapRegistryError(regStatus));
		return false;
	}

	wstring className;
	DWORD classNameSize = 0;
	DWORD subKeys = 0;
	DWORD maxSubKeyLen = 0;
	DWORD maxClassLen = 0;
	DWORD values = 0;
	DWORD maxValueNameLen = 0;
	DWORD maxValueLen = 0;
	DWORD securityDescriptorLen = 0;
	FILETIME lastWriteTime = { 0 };  // NOLINT(clang-diagnostic-missing-field-initializers)

	className.reserve(classNameSize);

	auto status = RegQueryInfoKeyW(
		key,
		LPWSTR(className.c_str()),
		&classNameSize,
		nullptr,
		&subKeys,
		&maxSubKeyLen,
		&maxClassLen,
		&values,
		&maxValueNameLen,
		&maxValueLen,
		&securityDescriptorLen,
		&lastWriteTime
	);

	if (status)
	{
		RegCloseKey(key);
		SetLastError(MapRegistryError(status));
		return false;
	}

	value.clear();

	for (DWORD index = 0; index < subKeys; index++)
	{
		auto cbName = maxSubKeyLen + 1;
		unique_ptr<WCHAR[]> name;
		try
		{
			name = make_unique<WCHAR[]>(cbName);
		}
		catch (bad_alloc)  // NOLINT(misc-throw-by-value-catch-by-reference)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			return false;
		}
		status = RegEnumKeyW(
			key,
			index,
			name.get(),
			cbName
		);

		wstring val = name.get();

		if (status)
		{
			RegCloseKey(key);
			SetLastError(MapRegistryError(status));
			return false;
		}
		value.push_back(val);
	}

	RegCloseKey(key);

	sort(value.begin(), value.end());
	return true;
}

// function to enumerate registry values
//
// on failure caller should call GetLastError
//
// path[in]
// The name of the registry value.
//
// If lpValueName specifies a value that is not in the registry, the function returns false
// GetLastError will return RT_ERROR_REGISTRY_MISSING.
//
// value[out] vector of registry values.
//
bool RegistryEnumValues(_In_ const  wstring& path, _Out_ vector<wstring>& value, _In_ HKEY keyHandle)
{
	value.clear();
	HKEY key = nullptr;

	// open the registry keyPath
    const auto regStatus = RegOpenKeyExW(keyHandle, path.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &key);
	if (regStatus != ERROR_SUCCESS)
	{
		SetLastError(MapRegistryError(regStatus));
		return false;
	}

	wstring className;
	DWORD classNameSize = 0;
	DWORD subKeys = 0;
	DWORD maxSubKeyLen = 0;
	DWORD maxClassLen = 0;
	DWORD values = 0;
	DWORD maxValueNameLen = 0;
	DWORD maxValueLen = 0;
	DWORD securityDescriptorLen = 0;
	FILETIME lastWriteTime = { 0 };  // NOLINT(clang-diagnostic-missing-field-initializers)

	className.reserve(classNameSize);

	auto status = RegQueryInfoKeyW(
		key,
		LPWSTR(className.c_str()),
		&classNameSize,
		nullptr,
		&subKeys,
		&maxSubKeyLen,
		&maxClassLen,
		&values,
		&maxValueNameLen,
		&maxValueLen,
		&securityDescriptorLen,
		&lastWriteTime
	);

	if (status)
	{
		RegCloseKey(key);
		SetLastError(MapRegistryError(status));
		return false;
	}

	value.clear();

	for (DWORD index = 0; index < values; index++)
	{
		auto cbName = maxValueLen + 1;
		unique_ptr<WCHAR[]> name;
		try
		{
			name = make_unique<WCHAR[]>(cbName);
		}
		catch (bad_alloc)  // NOLINT(misc-throw-by-value-catch-by-reference)
		{
			SetLastError(ERROR_NOT_ENOUGH_MEMORY);
			return false;
		}
		status = RegEnumValueW(key,
			index,
			name.get(),
			&cbName,
			nullptr,
			nullptr,
			nullptr,
			nullptr);

		wstring val = name.get();

		if (status)
		{
			RegCloseKey(key);
			SetLastError(MapRegistryError(status));
			return false;
		}
		value.push_back(val);
	}

	RegCloseKey(key);

	sort(value.begin(), value.end());

	return true;
}
