// SxSplusTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sxsplus.h"


int _tmain(int argc, wchar_t* argv[]) {
	/*
	auto string = SxSTest();
	
	wprintf(string->Buffer);
	SxSDispose((void*)string);

	auto ref = SxSTest2();
	for( auto i=0;i< ref->Count; i++ ) {
		wprintf(L"HEY : %s\r\n\r\n", ref->Items[i]->Location );
	}

	SxSDispose((void*)ref);
	*/
	SxSTest();
	auto ref = SxSTest2();

	return 0;
}

