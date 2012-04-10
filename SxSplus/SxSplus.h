#pragma once
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

#ifdef SXSPLUS_EXPORTS
#define SXSPLUS_API  __declspec(dllexport)
#else
#define SXSPLUS_API __declspec(dllimport)
#endif

enum Architecture {
	unknown		= 0,
	automatic	= 0,

	any			= 1,
	cpuany		= 1,
	msil		= 1,

    x86			= 2,     
	win32		= 2,

    x64			= 3,
	amd64		= 3,
}; 

typedef void* SXS_ASSEMBLYREFERENCE;		// a reference to a single installed assembly
typedef void* SXS_ASSEMBLYREFERENCES;		// a collection of references to installed assemblies 
typedef void* SXS_METADATA;					// a reference to the Metadata of an assembly
typedef void* SXS_METADATAPROPERTY;			// a reference to an individual property in the metadata of an assembly
typedef void* SXS_METADATAFILTER;			// a reference to a Metadata filter
typedef void* SXS_FILE;						// a reference to a file in an assembly
typedef void* SXS_FILES;					// a reference to a collection of files in an assembly
typedef void* SXS_CONTEXT;					// a reference to a context that filters the selection of SXS assemblies

#define WSTRINGPARAM( name ) const wchar_t* name, unsigned int name##Length
#define STRINGPARAM( name ) const char* name, unsigned int name##Length

// extern SXSPLUS_API int nSxSplus;
/*
/// A context string that directs the function to whatever can be guessed based on the 
/// execution stack, loaded modules and the exe.
///
const wchar_t* AUTO_CONTEXT = L"Name=<*>, Version=<*>";

/// a context string that indicates 
const wchar_t* NO_CONTEXT = L"NONE";

// how to specify a dll strong name
const wchar_t* a_file_strongname = L"foo.dll; Name=foo, Version=1.0.3300.0, Culture=neutral, PublicKeyToken=b77a5c561934e089";

// how to specify an assembly strong name
const wchar_t* an_assembly_strongname = L"foo, Version=1.0.3300.0, Culture=neutral, PublicKeyToken=b77a5c561934e089";
*/
// processorArchitecture=XXX
// architecture=XXX
// processor=XXX

// language=XXX
// lang=XXX
// culture=XXX

///=======================================================================
/// Enhanced LoadLibrary functions
///=======================================================================

#ifdef __cplusplus
extern "C" {
#endif
/// 
/// Replacement for the Kernel32 Function LoadLibraryW
///
SXSPLUS_API HMODULE SxSLoadLibraryW(LPCWSTR libraryName);

/// 
/// Replacement for the Kernel32 Function LoadLibraryA
///
SXSPLUS_API HMODULE SxSLoadLibraryA(LPSTR libraryName);

/// 
/// Replacement for the Kernel32 Function LoadLibraryExW
///
SXSPLUS_API HMODULE SxSLoadLibraryExW(LPCWSTR libraryName,HANDLE reserved,DWORD dwFlags);

/// 
/// Replacement for the Kernel32 Function LoadLibraryExA
///
SXSPLUS_API HMODULE SxSLoadLibraryExA(LPSTR libraryName,HANDLE reserved,DWORD dwFlags);

///=======================================================================
/// Trivial Assembly Interactions
///=======================================================================

/// 
/// Gets a reference for the given side-by-side assembly (context not used)
///
SXSPLUS_API SXS_ASSEMBLYREFERENCE SxSGetAssembly(WSTRINGPARAM(assemblyStrongName));
SXSPLUS_API SXS_ASSEMBLYREFERENCE SxSGetAssemblyA(STRINGPARAM(assemblyStrongName));

///
/// Gets a list of assemblies 
///
SXSPLUS_API SXS_ASSEMBLYREFERENCES SxSGetAssemblies();

///
/// Finds assemblies that match the given criteria
///
SXSPLUS_API SXS_ASSEMBLYREFERENCES SxSFindAssemblies(SXS_METADATAFILTER filter);


///
/// Gets a list of files in an assembly
///
SXSPLUS_API SXS_FILES SxSGetFiles(SXS_ASSEMBLYREFERENCE assemblyReference);

/// 
/// Gets the folder for the given side-by-side assembly
///
SXSPLUS_API const wchar_t* SxSGetAssemblyFolder(WSTRINGPARAM(assemblyStrongName));
SXSPLUS_API const char* SxSGetAssemblyFolderA(STRINGPARAM(assemblyStrongName));

///
/// I think this implies a per-thread-activation-context stack.
///

/// 
/// Creates an SxSplus Activation context
///
SXSPLUS_API SXS_CONTEXT SxSCreateContext(SXS_METADATAFILTER filter);

///
/// Activates an SxSplus activation context 
///
SXSPLUS_API void SxSActivateContext(SXS_CONTEXT context);

///
/// Deactivates an SxSplus activation context
///
SXSPLUS_API void SxSDeactivateContext(SXS_CONTEXT context);

///=======================================================================
/// Additional Metadata 
///=======================================================================

/// 
/// Gets the per-assembly metadata for an assembly 
///
SXSPLUS_API SXS_METADATA SxSGetAssemblyMetadata(SXS_ASSEMBLYREFERENCE assemblyReference);

/// 
/// Clears the per-assembly metadata for an assembly 
///
SXSPLUS_API void SxSClearAssemblyMetadata(SXS_ASSEMBLYREFERENCE assemblyReference);

///
/// Adds per-assembly metadata to an installed assembly
///
SXSPLUS_API SXS_METADATAPROPERTY SxSAddAssemblyMetadataProperty(SXS_METADATA assembly, WSTRINGPARAM(propertyName));
SXSPLUS_API SXS_METADATAPROPERTY SxSAddAssemblyMetadataPropertyA(SXS_METADATA assembly, STRINGPARAM(propertyName));

///
/// Removes per-assembly metadata from an installed assembly
///
SXSPLUS_API void SxSRemoveAssemblyMetadata(SXS_METADATAPROPERTY);

///
/// Adds per-assembly metadata to an installed assembly
///
SXSPLUS_API void SxSAddAssemblyMetadataValue(SXS_METADATAPROPERTY, WSTRINGPARAM(value));
SXSPLUS_API void SxSAddAssemblyMetadataValueA(SXS_METADATAPROPERTY, STRINGPARAM(value));

///
/// Removes per-assembly metadata property value from an installed assembly
///
SXSPLUS_API void SxSRemoveAssemblyMetadataValue(SXS_METADATAPROPERTY, WSTRINGPARAM(value));
SXSPLUS_API void SxSRemoveAssemblyMetadataValueA(SXS_METADATAPROPERTY, STRINGPARAM(value));


///
/// Gets the metadata information for a given PE Module
/// 
SXSPLUS_API SXS_METADATAFILTER SxSGetModuleMetadataFilter(WSTRINGPARAM(moduleFullPath));
SXSPLUS_API SXS_METADATAFILTER SxSGetModuleMetadataFilterA(STRINGPARAM(moduleFullPath));

///
/// Gets the SxS Application name for the currently executing context
///
SXSPLUS_API SXS_METADATAFILTER SxSGetCurrentMetadataFilter();

///
/// Allows the user to create a filter for finding assemblies base on arbitrary metadata
///
SXSPLUS_API SXS_METADATAFILTER SxSCreateFilter();

///
/// Adds an 'include' to a filter
///
SXSPLUS_API void SxSAddInclude(SXS_METADATAFILTER metadataFilter, WSTRINGPARAM(includeFilter) );
SXSPLUS_API void SxSAddIncludeA(SXS_METADATAFILTER metadataFilter, STRINGPARAM(includeFilter) );

///
/// Adds an 'exclude' to a filter
///
SXSPLUS_API void SxSAddExclude(SXS_METADATAFILTER metadataFilter, WSTRINGPARAM(excludeFilter) );
SXSPLUS_API void SxSAddExcludeA(SXS_METADATAFILTER metadataFilter, STRINGPARAM(excludeFilter) );

///=======================================================================
/// Assembly Query/Enumerations
///=======================================================================

///
/// Gets the available assemblies for the currently executing context
/// 
// SXSPLUS_API void SxSGetAssemblies();



///
/// Get
///
SXSPLUS_API void SxS();

///
///
///
SXSPLUS_API void SxS();

///
///
///
SXSPLUS_API void SxSDispose(void* objectToDispose);

SXSPLUS_API void* SxSTest();
SXSPLUS_API void* SxSTest2();

#ifdef __cplusplus
}; /* closing brace for extern "C" */
#endif
