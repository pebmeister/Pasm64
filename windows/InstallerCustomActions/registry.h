#pragma once

#include <functional>


template <bool preserveLastError = true>
class Finally final
{
private:
    // Holds the Callable to execute on destruction.
    std::function<void(void)> const action;

public:
    // Constructor.  Pass this constructor a lambda to be called at the end of the current scope.
    Finally(std::function<void(void)> _action)
        : action(_action)
    {
    }

    // Non-virtual destructor (because this class is non-inheritable).
    ~Finally()
    {
        DWORD error = 0;
        if (preserveLastError)
            error = GetLastError();
        action();
        if (preserveLastError)
            SetLastError(error);
    }

    // Disallow copy ctor, move ctor, assignment, and move assignment.
    Finally(const Finally&) = delete;
    Finally(const Finally&&) = delete;
    Finally& operator=(const Finally&) = delete;
    Finally& operator=(const Finally&&) = delete;
};

bool DeleteRegistryKeyW(_In_ const std::wstring& subkey);
bool SetRegistrySzValue(_In_ const std::wstring& lpValueName, _In_ const std::wstring& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool SetRegistryExpandSzValue(_In_ const std::wstring& lpValueName, _In_ const std::wstring& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool SetRegistryMultiSzValue(_In_ const std::wstring& lpValueName, _In_ std::vector<std::wstring>& wstrings, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool SetRegistryDWordValue(_In_ const std::wstring& lpValueName, _In_ const uint32_t value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool SetRegistryQWordValue(_In_ const std::wstring& lpValueName, _In_ const uint64_t value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool SetRegistryBinaryValue(_In_ const std::wstring& lpValueName, _In_ std::vector<BYTE>& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool GetRegistrySzValue(_In_ const std::wstring& lpValueName, _Out_ std::wstring& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool GetRegistryExpandSzValue(_In_ const std::wstring& lpValueName, _Out_ std::wstring& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool GetRegistryMultiSzValue(_In_ const std::wstring& lpValueName, _Out_ std::vector<std::wstring>& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool GetRegistryDWordValue(_In_ const std::wstring& lpValueName, _Out_ uint32_t& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool GetRegistryQWordValue(_In_ const std::wstring& lpValueName, _Out_ uint64_t& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool GetRegistryBinaryValue(_In_ const std::wstring& lpValueName, _Out_ std::vector<BYTE>& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool RegistryEnumValues(_In_ const std::wstring& path, _Out_ std::vector<std::wstring>& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
bool RegistryEnumKeys(_In_ const std::wstring& path, _Out_ std::vector<std::wstring>& value, _In_ HKEY keyHandle = HKEY_LOCAL_MACHINE);
