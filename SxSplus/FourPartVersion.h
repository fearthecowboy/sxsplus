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

namespace SxSplus {
	union FourPartVersion {
		struct {
			unsigned __int16 Major;
			unsigned __int16 Minor;
			unsigned __int16 Revision;
			unsigned __int16 Build;
		} DUMMYSTRUCTNAME;
		unsigned __int64 Value;
		FourPartVersion();
		FourPartVersion(unsigned __int64 value);
		FourPartVersion static Parse(const wchar_t* versionString);
	};
};