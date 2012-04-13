//-----------------------------------------------------------------------
// <copyright company="CoApp Project">
//     Copyright (c) 2010-2012 Garrett Serack and CoApp Contributors. 
//     Contributors can be discovered using the 'git log' command.
//     All rights reserved.
// </copyright>
// <license>
//     The software is licensed under the Apache 2.0 License (the "License")
//     You may not use the software except in compliance with the License. 
// </license>
//-----------------------------------------------------------------------

#include "stdafx.h"
#include "ptr.h"

using namespace SxSplus;

/// 
/// Replacement for the Kernel32 Function LoadLibraryW
///
SXSPLUS_API HMODULE SxSLoadLibraryW(LPCWSTR libraryName) {
	return NULL;
}

/// 
/// Replacement for the Kernel32 Function LoadLibraryA
///
SXSPLUS_API HMODULE SxSLoadLibraryA(LPSTR libraryName) {
	return NULL;
}

/// 
/// Replacement for the Kernel32 Function LoadLibraryExW
///
SXSPLUS_API HMODULE SxSLoadLibraryExW(LPCWSTR libraryName,HANDLE reserved,DWORD dwFlags) {
	return NULL;
}

/// 
/// Replacement for the Kernel32 Function LoadLibraryExA
///
SXSPLUS_API HMODULE SxSLoadLibraryExA(LPSTR libraryName,HANDLE reserved,DWORD dwFlags) {
	return NULL;
}
