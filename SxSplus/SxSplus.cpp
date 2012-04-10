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

#define SXSPLUS_PRIVATE
#include "stdafx.h"
#include "ptr.h"
#include "List.h"
#include "SxSplus.h"
#include "ModuleStack.h"
#include <Strsafe.h>
#include "SxSInternal.h"

// This is an example of an exported variable
// SXSPLUS_API int nSxSplus=0;

SXSPLUS_API void SxSDispose(void* objectToDispose) {
	Reference::DecrementReferenceCount(objectToDispose);
}

/// 
/// Replacement for the Kernel32 Function LoadLibraryW
///
SXSPLUS_API HMODULE SxSLoadLibraryW(LPCWSTR libraryName) {
	return NULL;
}

/// 
/// Replacement for the Kernel32 Function LoadLibraryA
///
SXSPLUS_API HMODULE SxSLoadLibraryA(LPSTR libraryName){
	return NULL;
}

/// 
/// Replacement for the Kernel32 Function LoadLibraryExW
///
SXSPLUS_API HMODULE SxSLoadLibraryExW(LPCWSTR libraryName,HANDLE reserved,DWORD dwFlags){
	return NULL;
}

/// 
/// Replacement for the Kernel32 Function LoadLibraryExA
///
SXSPLUS_API HMODULE SxSLoadLibraryExA(LPSTR libraryName,HANDLE reserved,DWORD dwFlags){
	return NULL;
}

SXSPLUS_API AssemblyReferences* SxSGetAssemblies(const wchar_t* context) {
	
	List<AssemblyReference, AssemblyReferences> result(3);
	
	result.Size =  5; 
	
	/*AssemblyReferenceCollection* result = (AssemblyReferenceCollection*)NULL;

	SafeString foo = NewSafeString();
	foo.Buffer;

	for( int i=0; i< result->Count; i++ ) {
		printf("%s", result->Items[i]->Name);
	}
	*/

	return result.AddRef();
}

SxSFile* AddItem(SxSFiles* f) {
	Ptr<SxSFile> result;

	// when returning a pointer to the client, use AddRef() to increase the ref count. 
	return result.AddRef();
}

SXSPLUS_API SxSFiles* SxSGetFiles(AssemblyReference* assemblyReference) {
	Ptr<SxSFiles> result;

	//SxSFileCollection* result = new SxSFileCollection();
	int i,j;

	for(i =0;i<10;i++ ) {
		/*
		auto x = AddItem(&result); 
		for( j=0;j < 100; j++ ) {
			auto q= [&](int n) { 
				auto a = n*2;
			};
			q(100);
		}
		// x->
		// result->Items[i]->FileName = L"foo.dll";
		// result->Items[i]->FullPath = L"c:\\output\\foo.dll";
		*/
	}


	/*
	for( int i=0; i< result->Count; i++ ){
		result->Items[i]->Key = NewSafeString(400); 
		sprintf( result->Items[i]->Key, "my name is :%s", foo);
	}
	*/


	// when returning a pointer to the client, use AddRef() to increase the ref count. 
	return result.AddRef();
}

AssemblyIdentity::AssemblyIdentity() {
	
}

AssemblyIdentity::~AssemblyIdentity() {

}

SXSPLUS_API void SxSGetAssembly(const wchar_t* assemblyStrongName, AssemblyIdentity* assembly) {
	assembly->Version.Value = 100;
	assembly->Architecture = x86;
	
	// AssemblyReference ref;
}

SXSPLUS_API const SafeString* SxSTest() {
	// auto filename = SafeString(1024);
	Ptr<SafeString> result = new SafeString(1024);
	Ptr<ModuleStack> stack = new ModuleStack(256);

	for(auto a=0;a < stack->Count; a++) {
		GetModuleFileNameW( stack->Modules[a], result->Buffer, result->Length);
		wprintf(L" MODULE: %s\r\n", result->Buffer);
	}

	return result.AddRef();
}

SXSPLUS_API AssemblyReferences* SxSTest2() {
	List<AssemblyReference, AssemblyReferences> result;
	auto obj = new AssemblyReference();
	obj->Location = L"Location";
	obj->Identity.Name = L"Name";
	obj->Identity.Version = 1;
	obj->Identity.Language=L"en";
	obj->Identity.Architecture = x86;

	result.Add(obj);

	return result.AddRef();
}
