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
#include "ptr.h"

namespace SxSplus {
	class SxSAssembly {
	
	public: 
		Ptr<SafeString> Name;
		FourPartVersion Version;
		enum Architecture Architecture;
		Ptr<SafeString> Language;
		Ptr<SafeString> PublicKeyToken;

		SafeString Location;

	public:
		~SxSAssembly();
		SxSAssembly();
		static Ptr<SxSAssembly> SxSGetAssemblyByStrongName(Ptr<SafeString> canonicalStrongName);
	};
};

