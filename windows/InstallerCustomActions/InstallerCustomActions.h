#pragma once

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the INSTALLERCUSTOMACTIONS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// INSTALLERCUSTOMACTIONS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
// ReSharper disable IdentifierTypo
#ifdef INSTALLERCUSTOMACTIONS_EXPORTS
#define INSTALLERCUSTOMACTIONS_API __declspec(dllexport)
#else
#define INSTALLERCUSTOMACTIONS_API __declspec(dllimport)
#endif

INSTALLERCUSTOMACTIONS_API UINT __stdcall SetPathEnvironmentVariable(MSIHANDLE hModule);
INSTALLERCUSTOMACTIONS_API UINT __stdcall RemovePathEnvironmentVariable(const MSIHANDLE hModule);

