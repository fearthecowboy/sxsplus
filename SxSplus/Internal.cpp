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

#define _SCL_INSECURE_DEPRECATE



#include <list>

#include "stdafx.h"


SXSPLUS_API void* SxSTest2() {
		
	
		std::list<wchar_t*> results;

		results.push_front( L"Hello World" );

		wprintf(L"%s", results.front() );
		return NULL;
	}