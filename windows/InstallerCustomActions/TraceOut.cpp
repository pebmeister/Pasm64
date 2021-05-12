// ReSharper disable CppClangTidyClangDiagnosticLanguageExtensionToken
// ReSharper disable CppParameterMayBeConst

#include "pch.h"

#pragma warning(suppress : 4996)

#define FAILURE_TEXT L" FAILURE: 0x" // NOLINT(cppcoreguidelines-macro-usage);

int NTabCount = 0;

DWORD ChangeTab(const int change)
{
    auto nTemp = NTabCount + change;
	if (nTemp < 0)
	{
		nTemp = 0;
	}
	return NTabCount = nTemp;
}

void TraceOut(MSIHANDLE hModule, const WCHAR* sMsg, int nTab)
{
	PWCHAR sTemp;

    if (nTab != 0)
	{
		ChangeTab(nTab);
	}
    auto scNumElements = wcslen(sMsg) + NTabCount + 1;
    auto scbTemp = scNumElements * sizeof(WCHAR);
	sTemp = static_cast<PWCHAR>(malloc(scbTemp));
	if (sTemp == nullptr)
		return;

	// zero out memory
	ZeroMemory(sTemp, scbTemp);

	__try
	{
		for (auto i = 0; i < NTabCount; i++)
		{
			wcscat_s(sTemp, scNumElements, L"\t");
		}

		// fix additional case so if hModule is NULL 
		// we still print the message
		wcscat_s(sTemp, scNumElements, sMsg);

		if (hModule == NULL)
		{
			wprintf(sTemp);
			wprintf(L"\n");
			__leave;
		}

        auto hRec = MsiCreateRecord(1);
		if (!hRec)
			__leave;

		__try
		{
            NTSTATUS nErr;
            nErr = MsiRecordSetStringW(hRec, 0, L"DbgOut: [1]");
			if (nErr != ERROR_SUCCESS)
				__leave;

			nErr = MsiRecordSetStringW(hRec, 1, sTemp);
			if (nErr != ERROR_SUCCESS)
				__leave;

			nErr = MsiProcessMessage(hModule, INSTALLMESSAGE_INFO, hRec);
			if (nErr != IDOK)
				__leave;
		}
		__finally
		{
			MsiCloseHandle(hRec);
		}
	}
	__finally
	{
		free(sTemp);
		if (nTab > 0)
		{
			ChangeTab(nTab);
		}
	}
	return;
}

void TraceOut(const MSIHANDLE hModule, std::wostringstream& ss, const int i)
{
    const auto messageBuffer = ss.str();
	TraceOut(hModule, messageBuffer.c_str(), i);
	ss.str(L"");
}

// ReSharper disable once CppParameterMayBeConst
void DisplayError(const MSIHANDLE hModule, const NTSTATUS err, const PWCHAR errorName)  // NOLINT(misc-misplaced-const)
{
	LPWSTR lpMessageBuffer = nullptr;
    // NTSTATUS nLocalErr = 0;

    const auto nBuffLen = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr,
        err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPWSTR>(&lpMessageBuffer),
        0,
        nullptr);

	// nLocalErr = GetLastError();
	const auto scbMsg = (
		wcslen(errorName)		// Length of Error Name padded
		+ wcslen(FAILURE_TEXT) // Length of the text that is inserted in every DisplayError string
		+ 8                     // Length of error number in hex, padded
		+ nBuffLen              // Length of the buffer populated by FormatMessage
		+ 1                     // NULL Terminator
		)
		* sizeof(WCHAR);

    const auto sMsg = static_cast<PWCHAR>(malloc(scbMsg));  // NOLINT(readability-qualified-auto)
	if (nBuffLen)
	{
		swprintf_s(sMsg, scbMsg, L"%s" FAILURE_TEXT L"%08x%s", errorName, err, lpMessageBuffer);
	}
	else
	{
		swprintf_s(sMsg, scbMsg, L"%s" FAILURE_TEXT L"%08x", errorName, err);
	}

	TraceOut(hModule, sMsg, 0);

	if (lpMessageBuffer)
	{
		LocalFree(lpMessageBuffer); // Free system buffer
	}

	SetLastError(err);
	return;
}

void DisplayError(const MSIHANDLE hModule, const NTSTATUS err)
{
	const auto msg =  L"";  // NOLINT(readability-qualified-auto, readability-qualified-auto)
    // ReSharper disable once CppCStyleCast
    DisplayError(hModule, err, (PTCHAR) msg);  // NOLINT(clang-diagnostic-old-style-cast, clang-diagnostic-cast-qual)
}

NTSTATUS ParseMultiString(PWCHAR sDest, const DWORD nBufLen, PWCHAR sSource)
{
	PWCHAR psSource, psDest;
    const auto nSourceLen = static_cast<DWORD>(wcslen(sSource));

    // ReSharper disable once CppLocalVariableMayBeConst
    auto psSourceEnd = sSource + nSourceLen;  // NOLINT(readability-qualified-auto)
    // ReSharper disable once CppLocalVariableMayBeConst
    auto psDestEnd = sDest + nBufLen;  // NOLINT(readability-qualified-auto)

	for (psDest = sDest, psSource = sSource;
		psDest < psDestEnd && psSource < psSourceEnd;
		psDest++, psSource++)
	{
		if (wcsncmp(psSource, L"[~]", 3) == 0)
		{
			*psDest = L'\0';
			psSource += 2;
		}
		else
		{
			*psDest = *psSource;
		}
	}

	*psDest++ = L'\0';
	*psDest = L'\0';

	return ERROR_SUCCESS;
}

BOOL Installing(MSIHANDLE hModule, PWCHAR sComponent)
{
	INSTALLSTATE installState, installAction;

    TraceOut(hModule, L"In Installing", 1);
	TraceOut(hModule, sComponent, 0);

    const auto nErr = MsiGetComponentStateW(hModule, sComponent, &installState, &installAction);
	if (nErr != ERROR_SUCCESS)
	{
        // ReSharper disable once CppCStyleCast
        DisplayError(hModule, nErr, 
			(const PWCHAR)&L"Installing:GetComponentState ");  // NOLINT(clang-diagnostic-old-style-cast, clang-diagnostic-cast-qual)
		TraceOut(hModule, L"Installing() FAILED", -1);

		// Safest return value
		return FALSE;
	}

	if (installAction == INSTALLSTATE_LOCAL)
	{
		TraceOut(hModule, L"Installing", -1);
		return TRUE;
	}

	TraceOut(hModule, L"Not Installing", -1);
	return FALSE;
}

BOOL Deleting(MSIHANDLE hModule, PWCHAR sComponent)
{
	INSTALLSTATE installState, installAction;

    TraceOut(hModule, L"In Deleting", 1);
	TraceOut(hModule, sComponent, 0);

	const auto nErr = MsiGetComponentStateW(hModule, sComponent, &installState, &installAction);
	if (nErr != ERROR_SUCCESS)
	{
        // ReSharper disable once CppCStyleCast
        DisplayError(hModule, nErr, 
			(const PTCHAR) &L"Deleting:GetComponentState ");  // NOLINT(clang-diagnostic-old-style-cast, clang-diagnostic-cast-qual)
		TraceOut(hModule, L"Deleting() FAILED", -1);

		// Safest return value
		return FALSE;
	}

	if (installAction == INSTALLSTATE_ABSENT)
	{
		TraceOut(hModule, L"Deleting", -1);
		return TRUE;
	}

	if (
		installState == INSTALLSTATE_LOCAL
		&& installAction == INSTALLSTATE_LOCAL
		)
	{
		TraceOut(hModule, L"Reinstalling", -1);
		return TRUE;
	}

	TraceOut(hModule, L"Not Deleting", -1);
	return FALSE;
}

NTSTATUS GetTokenAllocAndAssign(PWSTR* pcDest, PWSTR sSource, PWSTR sDelimiter)
{
    *pcDest = nullptr;

    // ReSharper disable once CppLocalVariableMayBeConst
    auto pcCurTok = _wcstok(sSource, sDelimiter);  // NOLINT(readability-qualified-auto)
	if (pcCurTok == nullptr)
		return GetLastError();

	*pcDest = static_cast<PWCHAR>(malloc((wcslen(pcCurTok) + 1) * sizeof(WCHAR)));
	if (*pcDest == nullptr)
		return GetLastError();

	if (wcscmp(pcCurTok, L" ") == 0)
	{
		wcscpy(*pcDest, L"");
	}
	else
	{
		wcscpy(*pcDest, pcCurTok);
	}

	return ERROR_SUCCESS;
}

NTSTATUS ExecuteQuery(MSIHANDLE hModule,
	MSIHANDLE* phDb,
	PWCHAR sQuery,
	MSIHANDLE* phView
)
{
    TraceOut(hModule, L"In ExecuteQuery", 1);

	*phDb = MsiGetActiveDatabase(hModule);

	NTSTATUS nRes = MsiDatabaseOpenViewW(*phDb, sQuery, phView);
	if (nRes != ERROR_SUCCESS)
	{
		TraceOut(hModule, L"MsiDatabaseOpenView failed", 1);
		MsiCloseHandle(*phView);
		return nRes;
	}

	nRes = MsiViewExecute(*phView, NULL);
	if (nRes != ERROR_SUCCESS)
	{
		TraceOut(hModule, L"MsiViewExecute failed", -1);
		MsiCloseHandle(*phView);
		return nRes;
	}
	TraceOut(hModule, L"ExecuteQuery Success", -1);
	return ERROR_SUCCESS;
}

/// <summary>
/// Get an MSI Property
/// </summary>
/// <param name="hModule">Installer handle</param>
/// <param name="sName">Name of property</param>
/// <param name="psValue">pointer to string that receives malloc'ed value. Should br freed when done</param>
/// <param name="pdwSize">optional size of string</param>
/// <returns>0 == SUCCESS</returns>
NTSTATUS Prop(MSIHANDLE hModule, LPWSTR sName, LPWSTR* psValue, PDWORD pdwSize)
{
	NTSTATUS nRet;
	DWORD tmpSize = 0;
	LPWSTR sValue;

    
	if (pdwSize == nullptr)
		pdwSize = &tmpSize;

	tmpSize = *pdwSize;
	if (tmpSize == 0)
	{
        // ReSharper disable once CppCStyleCast
        nRet = MsiGetPropertyW(hModule, sName, (LPWSTR) L"", pdwSize);  // NOLINT(clang-diagnostic-old-style-cast, clang-diagnostic-cast-qual)

		if (nRet != ERROR_MORE_DATA)
		{
			DisplayError(hModule, nRet);
			return nRet;
		}
		++* pdwSize;
		sValue = static_cast<LPWSTR>(malloc(*pdwSize * sizeof(WCHAR)));
		if (sValue == nullptr)
		{
			nRet = GetLastError();
			DisplayError(hModule, nRet);
			return nRet;
		}
		ZeroMemory(sValue, *pdwSize * sizeof(WCHAR));
		*psValue = sValue;
	}
	sValue = *psValue;

	nRet = MsiGetPropertyW(hModule, sName, sValue, pdwSize);

	return nRet;
}
