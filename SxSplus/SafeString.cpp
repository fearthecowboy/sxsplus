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
#include "SafeString.h"
#include <Strsafe.h>
#include "ptr.h"

namespace SxSplus {
	SafeString::~SafeString() {
		Deallocate();
	}

	SafeString::SafeString():Buffer(NULL), Length(0) {
	}

	SafeString::SafeString(const char* string, unsigned int maxlength, UINT codepage )   {
		this->SafeString::SafeString(); // call initializing constructor
		Copy(string, maxlength,codepage);
	}

	SafeString::SafeString(const wchar_t* string, unsigned int maxlength )   {
		this->SafeString::SafeString(); // call initializing constructor
		Copy(string, maxlength);
	}

	SafeString::SafeString(SafeString& copy) {
		this->SafeString::SafeString(); // call initializing constructor
		Copy(copy.Buffer, copy.Length);
	}

	SafeString::SafeString(unsigned int size) {
		this->SafeString::SafeString(); // call initializing constructor
		Resize(size);
	}

	bool SafeString::IsNullOrEmpty() const {
		return (Buffer == NULL || *Buffer == 0);
	}

	SafeString::operator const wchar_t*() const {
		return Buffer;
	}

	SafeString::operator wchar_t*() {
		return Buffer;
	}

	const char* SafeString::ToAnsi( UINT codepage) const {
		size_t sz;
		if( SUCCEEDED(StringCchLengthW(Buffer, Length, &sz))) {
			sz++; // add one for the null
			auto sizeRequired = WideCharToMultiByte( codepage, 0, Buffer, sz, NULL, 0,  NULL, NULL);
			auto result = new char[sizeRequired];
			memset( result, 0 , sizeRequired);
			if( SUCCEEDED( WideCharToMultiByte( codepage, 0, Buffer, sz, result, sizeRequired,  NULL, NULL))) {
				Reference::IncrementReferenceCount(result);
				return result;
			}
			// failed, delete the result
			delete result;
		}
		return NULL;
	}

	SafeString& SafeString::SPrintF(unsigned int maxLength, const wchar_t* format, ...) {
		if( SxSplus::IsNullOrEmpty(format) ) {
			Empty();
		}

		Resize(maxLength);

		va_list args;
		va_start(args, format);
	
		if(!SUCCEEDED(StringCbVPrintf(Buffer,maxLength,format, args) ) ) {
			Empty();
		}
		va_end(args);
		return *this;
	}

	void SafeString::Resize(unsigned int maxlength) {
		if( Length >= maxlength ) {
			Empty();
			return;
		}
		Deallocate();
		Buffer = new wchar_t[maxlength];
		Length = maxlength;
		Empty();
	}

	void SafeString::Empty() {
		memset( Buffer, 0, Length );
	}

	void SafeString::Deallocate() {
		auto buffer = Buffer;
		if( buffer ) {
			// change the fields first
			Buffer = NULL;
			Length =0;

			// and delete the buffer
			delete buffer;
		}
	}

	void SafeString::Copy( const wchar_t* string,unsigned int maxlength) {
		if( string != NULL ) {
			size_t sz;
			if( SUCCEEDED(StringCchLengthW(string, maxlength, &sz))) {
				sz++; // add one for the null
				Resize(sz);
				if( SUCCEEDED( StringCchCopyW( Buffer, sz, string))) {
					return;
				}
			}
		}
		Deallocate();
	}

	void SafeString::Copy( const char* string,unsigned int maxlength,UINT codepage) {
		if( string != NULL ) {
			// check the length of the incoming string first.
			size_t sz;
			if( SUCCEEDED(StringCchLengthA(string, maxlength, &sz))) {
				sz++; // add one for the null
				Resize(sz);
				if( SUCCEEDED( MultiByteToWideChar(codepage, 0, string, sz, Buffer, sz))) {
					return;
				}
			}
		}
		Deallocate();
	}

	bool IsNullOrEmpty(const wchar_t* text) {
		return !( text && *text );
	}
};