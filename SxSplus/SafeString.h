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

typedef struct SafeString {
	wchar_t*	Buffer;
	size_t		Length;
#ifndef SXSPLUS_PRIVATE
};
#else 
public:
	~SafeString();
	SafeString();
	SafeString(const wchar_t* string,unsigned int maxlength = 256);
	SafeString(unsigned int size);
	SafeString(SafeString& copy);
	bool IsNullOrEmpty() const;
	SafeString& SPrintF(unsigned int maxLength, const wchar_t* format, ...); 
	operator const wchar_t*() const;
	operator wchar_t*();

private: 
	void Resize(unsigned int maxlength);
	void Deallocate();
	void Empty();
	void Copy( const wchar_t* string,unsigned int maxlength );

} SafeString;

bool IsNullOrEmpty(const wchar_t* text);
#endif 