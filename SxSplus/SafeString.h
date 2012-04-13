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
	class SafeString {
	public:
		wchar_t*	Buffer;
		size_t		Length;

	public:
		~SafeString();
		SafeString();
		SafeString(const char* string, unsigned int maxlength=256, unsigned int codepage=0);
		SafeString(const wchar_t* string,unsigned int maxlength=256);
		SafeString(unsigned int size);
		SafeString(SafeString& copy);
		bool IsNullOrEmpty() const;
		SafeString& SPrintF(unsigned int maxLength, const wchar_t* format, ...); 
		operator const wchar_t*() const;
		operator wchar_t*();
		const char* ToAnsi( unsigned int codepage = 0) const;
	private: 
		void Resize(unsigned int maxlength);
		void Deallocate();
		void Empty();
		void Copy( const wchar_t* string,unsigned int maxlength );
		void Copy( const char* string,unsigned int maxlength, unsigned int codepage);

	};

	bool IsNullOrEmpty(const wchar_t* text);
};