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
#include "Assembly.h"



namespace SxSplus {

	Ptr<SxSAssembly> SxSAssembly::SxSGetAssemblyByStrongName(Ptr<SafeString> canonicalStrongName){
		return Ptr<SxSAssembly>();
	}

};

using namespace SxSplus;

// C API Exports:


SXSPLUS_API SXS_ASSEMBLY SxSGetAssemblyByStrongName(WSTRINGPARAM(canonicalStrongName)) {
	return SxSAssembly::SxSGetAssemblyByStrongName(new SafeString(canonicalStrongName,canonicalStrongNameLength)).AddRef();
}

SXSPLUS_API SXS_ASSEMBLY SxSGetAssemblyByStrongNameA(STRINGPARAM(canonicalStrongName)) {
	return SxSAssembly::SxSGetAssemblyByStrongName(new SafeString(canonicalStrongName,canonicalStrongNameLength)).AddRef();
}
