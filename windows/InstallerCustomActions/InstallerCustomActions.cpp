// InstallerCustomActions.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "InstallerCustomActions.h"


bool Split(const std::wstring& str, WCHAR delimiter, std::vector<std::wstring>& splitStrings);
bool Join(const std::vector<std::wstring>& splitString,  WCHAR delimiter, std::wstring& str);

INSTALLERCUSTOMACTIONS_API UINT __stdcall SetPathEnvironmentVariable(const MSIHANDLE hModule)
{
    TraceOut(hModule, _T("Enter SetPathEnvironmentVariable"), 0);

    LPTSTR targetDir = nullptr;
    DWORD sz = 0;

    // ReSharper disable once CppCStyleCast
    Prop(hModule, (LPTSTR)_T("CustomActionData"), &targetDir, &sz);  // NOLINT(clang-diagnostic-old-style-cast)

    TraceOut(hModule, targetDir, 1);
    const std::wstring valuePathName = L"System\\CurrentControlSet\\Control\\Session Manager\\Environment\\Path";
    std::wstring value;

    if (GetRegistryExpandSzValue(valuePathName, value) == false)
    {
        DisplayError(hModule, GetLastError());
        TraceOut(hModule, _T("Exit SetPathEnvironmentVariable"), 0);
        return -1;
    }

    std::vector<std::wstring> paths;
    Split(value, L';', paths);

    for (auto &path : paths)
    {
        if (_tcsicmp(path.c_str(), targetDir) == 0)
        {
            TraceOut(hModule, _T("Path already exists"), 0);
            TraceOut(hModule, _T("Exit SetPathEnvironmentVariable"), 0);
            return 0;
        }
    }
    paths.push_back(std::wstring(L";") + targetDir);
    Join(paths, L';', value);

    TraceOut(hModule, value.c_str(), 0);

    if (SetRegistryExpandSzValue(valuePathName, value) == false)
    {
        DisplayError(hModule, GetLastError());
        TraceOut(hModule, _T("Exit SetPathEnvironmentVariable"), 0);
        return -1;
    }

    DWORD dwReturnValue = 0;
    SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, 0, reinterpret_cast<LPARAM>(L"Environment"), SMTO_ABORTIFHUNG,
                        5000, &dwReturnValue);

    TraceOut(hModule, _T("Exit SetPathEnvironmentVariable"), 0);
    return 0;
}

INSTALLERCUSTOMACTIONS_API UINT __stdcall RemovePathEnvironmentVariable(const MSIHANDLE hModule)
{
    TraceOut(hModule, _T("Enter RemovePathEnvironmentVariable"), 0);

    LPTSTR targetDir = nullptr;
    DWORD sz = 0;

    // ReSharper disable once CppCStyleCast
    Prop(hModule, (LPTSTR)_T("CustomActionData"), &targetDir, &sz);  // NOLINT(clang-diagnostic-old-style-cast)

    TraceOut(hModule, targetDir, 1);
    const std::wstring valuePathName = L"System\\CurrentControlSet\\Control\\Session Manager\\Environment\\Path";
    std::wstring value;

    if (GetRegistryExpandSzValue(valuePathName, value) == false)
    {
        DisplayError(hModule, GetLastError());
        TraceOut(hModule, _T("Exit RemovePathEnvironmentVariable"), 0);
        return -1;
    }

    std::vector<std::wstring> paths;
    std::vector<std::wstring> updatedPaths;
    auto found = false;
    Split(value, L';', paths);

    for (auto& path : paths)
    {
        if (_tcsicmp(path.c_str(), targetDir) != 0)
        {
            if (!path.empty())
            {
                TraceOut(hModule, _T("Adding to path"), 0);
                TraceOut(hModule, path.c_str(), 0);
                updatedPaths.push_back(path);
            }
        }
        else
            found = true;
    }

    if (!found)
    {
        TraceOut(hModule, _T("Path not found"), 0);
        TraceOut(hModule, _T("Exit RemovePathEnvironmentVariable"), 0);
        return 0;
    }

    TraceOut(hModule, _T("Path found!"), 0);
    Join(updatedPaths, L';', value);

    TraceOut(hModule, value.c_str(), 0);

    if (SetRegistryExpandSzValue(valuePathName, value) == false)
    {
        // DisplayError(hModule, GetLastError());
        TraceOut(hModule, _T("Exit RemovePathEnvironmentVariable  with error"), 0);
        return 0;
    }

    DWORD dwReturnValue = 0;
    SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, 0, reinterpret_cast<LPARAM>(L"Environment"), SMTO_ABORTIFHUNG,
        5000, &dwReturnValue);

    TraceOut(hModule, _T("Exit RemovePathEnvironmentVariable"), 0);
    return 0;
}

// Splits a string into a std::vector of strings at an arbitrary delimiter character.
bool Split(const std::wstring& str, const WCHAR delimiter, std::vector<std::wstring>& splitStrings)
{
    std::wstring temp;
    std::wstringstream wss(str);
    while (getline(wss, temp, delimiter))
    {
        splitStrings.push_back(temp);
    }

    return true;
}

bool Join(const std::vector<std::wstring>& splitString, const WCHAR delimiter, std::wstring& str)
{
    str = L"";
    for (auto &strs : splitString)
    {
        str += strs + delimiter;
    }
    str.erase(str.end() - 1, str.end());
    return true;
}
