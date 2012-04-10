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

#include "SafeString.h"
#include "FourPartVersion.h"
#include "PublicKeyToken.h"

namespace SxSplus {
	class AssemblyIdentity {
		SafeString Name;
		FourPartVersion Version;
		enum Architecture Architecture;
		SafeString Language;
		PublicKeyToken token;

	public:
		AssemblyIdentity();
		~AssemblyIdentity();
	};
};