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
#include "SxSplus.h"


FourPartVersion::FourPartVersion() {
	Value = 0;
}
FourPartVersion::FourPartVersion(unsigned __int64 value) {
	Value = value;
}

FourPartVersion FourPartVersion::Parse(const wchar_t* versionString) {
	return FourPartVersion(0);
}
