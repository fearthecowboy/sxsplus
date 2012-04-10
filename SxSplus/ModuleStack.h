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

#include "ptr.h"
#include <list>

namespace SxSplus {
	class ModuleStack {
		public:
			std::list<HMODULE> Modules;				
	
			ModuleStack();
			~ModuleStack();
	};
};