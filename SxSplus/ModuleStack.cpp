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
#include "stdafx.h"
#include "ModuleStack.h"
#include "winnt.h"
#include <DbgHelp.h>

namespace SxSplus {

	#ifdef _M_IX86
	  // Disable global optimization and ignore /GS waning caused by inline assembly.
	  #pragma optimize( "g", off )
	  #pragma warning( push )
	  #pragma warning( disable : 4748 )
	#endif

	ModuleStack::ModuleStack()  {
		DWORD MachineType;
		CONTEXT Context;
		STACKFRAME64 StackFrame;

		// Use current context.
	#ifdef _M_IX86
		// GetThreadContext cannot be used on the current thread.
		// Capture own context - on i386, there is no API for that.
		ZeroMemory( &Context, sizeof( CONTEXT ) );

		Context.ContextFlags = CONTEXT_CONTROL;
    
		//
		// Those three registers are enough.
		//
		__asm {
		Label:
		  mov [Context.Ebp], ebp;
		  mov [Context.Esp], esp;
		  mov eax, [Label];
		  mov [Context.Eip], eax;
		}
	#else
		RtlCaptureContext( &Context );
	#endif  

	  //
	  // Set up stack frame.
	  //
	  ZeroMemory( &StackFrame, sizeof( STACKFRAME64 ) );
	#ifdef _M_IX86
	  MachineType                 = IMAGE_FILE_MACHINE_I386;
	  StackFrame.AddrPC.Offset    = Context.Eip;
	  StackFrame.AddrPC.Mode      = AddrModeFlat;
	  StackFrame.AddrFrame.Offset = Context.Ebp;
	  StackFrame.AddrFrame.Mode   = AddrModeFlat;
	  StackFrame.AddrStack.Offset = Context.Esp;
	  StackFrame.AddrStack.Mode   = AddrModeFlat;
	#elif _M_X64
	  MachineType                 = IMAGE_FILE_MACHINE_AMD64;
	  StackFrame.AddrPC.Offset    = Context.Rip;
	  StackFrame.AddrPC.Mode      = AddrModeFlat;
	  StackFrame.AddrFrame.Offset = Context.Rsp;
	  StackFrame.AddrFrame.Mode   = AddrModeFlat;
	  StackFrame.AddrStack.Offset = Context.Rsp;
	  StackFrame.AddrStack.Mode   = AddrModeFlat;
	#elif _M_IA64
	  MachineType                 = IMAGE_FILE_MACHINE_IA64;
	  StackFrame.AddrPC.Offset    = Context.StIIP;
	  StackFrame.AddrPC.Mode      = AddrModeFlat;
	  StackFrame.AddrFrame.Offset = Context.IntSp;
	  StackFrame.AddrFrame.Mode   = AddrModeFlat;
	  StackFrame.AddrBStore.Offset= Context.RsBSP;
	  StackFrame.AddrBStore.Mode  = AddrModeFlat;
	  StackFrame.AddrStack.Offset = Context.IntSp;
	  StackFrame.AddrStack.Mode   = AddrModeFlat;
	#else
	  #error "Unsupported platform"
	#endif

	  HMODULE lastModule= (HMODULE)-1;
	  HMODULE module = (HMODULE)-1;
	
		//
		// Dbghelp is is singlethreaded, so acquire a lock.
		//
		EnterCriticalSection( &ThreadLock );

		while ( StackWalk64(MachineType,GetCurrentProcess(),GetCurrentThread(),&StackFrame,MachineType == IMAGE_FILE_MACHINE_I386 ? NULL: &Context, NULL,SymFunctionTableAccess64, SymGetModuleBase64, NULL ) && StackFrame.AddrPC.Offset != 0 ) {
			GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,(LPCWSTR)(void*) StackFrame.AddrPC.Offset,  &module);
			
			// skip duplicate handles, so we're not seeing the same thing twice in a row.
			if( module != lastModule && module != Kernel32Module && module != NTDLLModule ) {
				Modules.push_back( module);
				lastModule = module;
			}
		}

		LeaveCriticalSection( &ThreadLock );
	}
	ModuleStack::~ModuleStack() {
	}


	#ifdef _M_IX86
	  #pragma warning( pop )
	  #pragma optimize( "g", on )
	#endif
};