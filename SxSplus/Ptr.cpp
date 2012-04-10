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
#include "ptr.h"
#include "stdio.h"

namespace SxSplus {
	unsigned int Reference::Size = 32;
	unsigned int Reference::Count = 0;
	Reference* Reference::References = new Reference[Reference::Size];

	unsigned int Reference::GetReferenceIndex(void* pointer) {
		unsigned int result =0xffffffff;
		unsigned int emptySpot =0xffffffff;

		EnterCriticalSection( &ThreadLock ); 
		__try {
			// look it up first.
			for( auto i=0;i< Size; i++ ) {
				if( pointer == References[i].Pointer ) {
					result = i;
					//printf("found object %x\r\n", pointer);
					__leave;
				}
				if( emptySpot = 0xffffffff && References[i].ReferenceCount == 0 ) {
					emptySpot = i;
				}
			}

			//printf("Adding object %x\r\n", pointer);

			// take the first empty spot if we found one.
			if( emptySpot != 0xffffffff) {
				References[emptySpot].Pointer = pointer;
				References[emptySpot].ReferenceCount = 0;
				result = emptySpot;
				__leave;
			}

			// not there? make sure we have room.
			if( Size == Count ) {
				auto newSize = Size*2;
				auto oldReferences = References;
				References = new Reference[newSize];
				for( auto i=0;i<Size; i++) {
					References[i]=oldReferences[i];
				}
				delete oldReferences;
				Size = newSize;
			}



			// we've got room. add this pointer to the list. 
			result = Count;
			References[result].Pointer = pointer;
			References[result].ReferenceCount = 0;
			Count++;
		}
		__finally {
			LeaveCriticalSection( &ThreadLock );
		}
	
		return result;
	}

	unsigned int Reference::GetReferenceCount(void* pointer){
		unsigned int result =0;
		if( pointer ) {
			EnterCriticalSection( &ThreadLock ); 
			result = References[GetReferenceIndex(pointer)].ReferenceCount;
			LeaveCriticalSection( &ThreadLock );
		}
		return result;
	}

	unsigned int Reference::IncrementReferenceCount(void* pointer) {
		unsigned int result =0;
		if( pointer ) {
			EnterCriticalSection( &ThreadLock ); 
			result = (References[GetReferenceIndex(pointer)].ReferenceCount++);
			LeaveCriticalSection( &ThreadLock );
		}
		return result;
	}
	unsigned int Reference::DecrementReferenceCount(void* pointer) {
		unsigned int result =0;
		if( pointer ) {
			EnterCriticalSection( &ThreadLock ); 
			auto index = GetReferenceIndex(pointer);
			if( References[index].ReferenceCount > 0 )  {
				result = --References[index].ReferenceCount;
				if( result == 0 ) {
					//("deleting object %x\r\n", pointer);
					delete References[index].Pointer;
					References[index].Pointer = NULL;
				}
			}
			LeaveCriticalSection( &ThreadLock );
		}
		return result;
	}

};