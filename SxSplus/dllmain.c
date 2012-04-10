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

int initalized = 0;

// private data
CRITICAL_SECTION ThreadLock;
HMODULE Kernel32Module;
HMODULE NTDLLModule;

// init/teardown 
void Init() {
	InitializeCriticalSection(&ThreadLock);
	SymInitialize( GetCurrentProcess(), NULL, TRUE );
	Kernel32Module = LoadLibraryW(L"Kernel32");
	NTDLLModule = LoadLibraryW(L"NTDLL");
}

void Dispose() { 
	 DeleteCriticalSection(&ThreadLock);
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			if( !initalized ) {
				// call appropriate initializers 
				Init();
				
			}
			initalized = 1;
			break;

		case DLL_PROCESS_DETACH:
			if( initalized ) {
				// call appropriate disposers 
				Dispose();

			}
			initalized = 0;
			break;
	}
	return TRUE;
}