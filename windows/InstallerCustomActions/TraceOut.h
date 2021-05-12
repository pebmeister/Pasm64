#pragma once

extern DWORD ChangeTab(int change);
extern void TraceOut(MSIHANDLE hModule, const WCHAR* sMsg, int nTab);
extern void TraceOut(MSIHANDLE hModule, std::wostringstream& ss, int i);
extern void DisplayError(MSIHANDLE hModule, NTSTATUS err, PWCHAR errorName);
extern void DisplayError(MSIHANDLE hModule, NTSTATUS err);
extern NTSTATUS ParseMultiString(PWCHAR sDest, DWORD nBufLen, PWCHAR sSource);
extern BOOL Installing(MSIHANDLE hModule, PWCHAR sComponent);
extern BOOL Deleting(MSIHANDLE hModule, PWCHAR sComponent);
extern NTSTATUS GetTokenAllocAndAssign(PWSTR* pcDest, PWSTR sSource, PWSTR sDelimiter);
extern NTSTATUS Prop(MSIHANDLE hModule, LPWSTR sName, LPWSTR* psValue, PDWORD pdwSize);
