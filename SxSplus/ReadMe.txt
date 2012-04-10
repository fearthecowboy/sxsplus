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

==============================================================================
SxSplus Overview
==============================================================================

SxSplus is adding an additional dimension to Windows Side-by-side technology
to enable developers greater flexibility in creating and consuming libraries
that are stored in SxS.

Enhancements
============

	Enhanced LoadLibrary functions
		New enhanced versions of LoadLibrary/LoadLibraryEx are provided that
		can located assemblies given an assembly strong name, as well as 
		automatically identify and activate the most appropriate context 
		for loading assemblies.
		
	Trivial Assembly Interactions
		Additional Functions for providing trivial access to information about
		an assembly.
		
	Additional Metadata 
		Applications, modules, and assemblies in SxSplus can provide 
		additional metadata information that provides greater support for 
		querying the intended use of a given assembly.

	Assembly Query/Enumerations
		Functions to locate assemblies given the strong name without requiring
		the developer to directly use activation contexts, or even under be 
		aware that they are there.

	

