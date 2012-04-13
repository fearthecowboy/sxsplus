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
#include "SafeString.h"
#include "ModuleStack.h"
#include <Strsafe.h>

using namespace SxSplus;


// This is an example of an exported variable
// SXSPLUS_API int nSxSplus=0;

SXSPLUS_API void SxSDispose(void* objectToDispose) {
	Reference::DecrementReferenceCount(objectToDispose);
}

SXSPLUS_API void* SxSTest() {
		
	// auto filename = SafeString(1024);
	Ptr<SafeString> result = new SafeString(1024);
	Ptr<ModuleStack> stack = new ModuleStack();

	for(auto it=stack->Modules.begin();it !=  stack->Modules.end() ; ++it) {
		GetModuleFileNameW( *it, result->Buffer, result->Length);
		wprintf(L" MODULE=>: %s\r\n", result->Buffer);
	}
	

	SafeString ansi = "Garrett Serack\r\n";
	SafeString wide = L"GARRETT SERACK\r\n";

	wprintf( ansi);
	wprintf( wide);

	auto ansichar = wide.ToAnsi();
	printf(ansichar);

	SxSDispose((void*)ansichar);

	return NULL;
}

