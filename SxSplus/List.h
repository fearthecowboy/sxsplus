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

//#include <list>
#include "ptr.h"


#if FALSE
int NearestPowerOf2(int i){   
	int x = ((i - 1) & i);   
	return x ? NearestPowerOf2(x) : i << 1;
}

template< class T, class Ts>
class List : public Ptr<Ts>  {
public:
	List (unsigned int size) : Ptr<Ts>(new Ts) {
		if (_objectPointer) {
			_objectPointer->Size = 0;
			_objectPointer->Count = 0;
			_objectPointer->Items = NULL;
			
			// and resize it.
			Size = size;
		}
	};

	List (Ts *pointer, unsigned int size) : Ptr<T>(pointer) {
		if (_objectPointer) {
			_objectPointer->Size = size;
			_objectPointer->Count =size;
		}
	};

	List (List<T,Ts>* pointer) : Ptr<Ts>((Ts*)(void*)pointer){
	}

	List (List<T,Ts>& pointer) : Ptr<Ts>((Ts*)(void*)pointer) {
	};

	List () : Ptr<Ts>(new Ts)  {
		if (_objectPointer) {
			_objectPointer->Size = 0;
			_objectPointer->Count = 0;
			_objectPointer->Items = NULL;
			
			// and resize it.
			Size = 32;
		}
	};
	
	__declspec( property(get=get_Size ,  put=put_Size)  ) unsigned int Size;
	__declspec( property(get=get_Count ,  put=put_Count)  )  unsigned int Count;
	__declspec( property(get=get_Items ,  put=put_Items)  )  T** Items;

	unsigned int get_Count() {
		if (Items) {
			return _objectPointer->Count;	
		}
		return 0;
	}

	unsigned int get_Size() {
		if (Items) {
			return _objectPointer->Size;	
		}
		return 0;
	}

	T** get_Items() {
		if ( _objectPointer && _objectPointer->Items) {
			return _objectPointer->Items;	
		}
		return 0;
	}

	T** put_Items(T** newItems) {
		if ( _objectPointer ) {
			if( _objectPointer->Items ) {
				delete _objectPointer->Items;
			}
			_objectPointer->Items = newItems;
			return _objectPointer->Items;	
		}
		return 0;
	}

	unsigned int put_Count(unsigned int newCount) {
		if (Items) {
			if( _objectPointer->Count < newCount ) {
				EnterCriticalSection(&ThreadLock);
				if( Size < newCount ) {
					Size = newCount;
				}
				_objectPointer->Count = newCount;
				LeaveCriticalSection(&ThreadLock);
			}
			return _objectPointer->Count;
		}
		return 0;
	}

	unsigned int put_Size(unsigned int newSize) {
		if (_objectPointer) {
			if( _objectPointer->Size < newSize ) {
				EnterCriticalSection(&ThreadLock);
				newSize = NearestPowerOf2(newSize-1);

				auto oldList = _objectPointer->Items;
				_objectPointer->Items = new T*[newSize];
				memset( _objectPointer->Items, 0, sizeof(T*)*newSize);
				
				for(auto i=0;i<Size;i++) {
					_objectPointer->Items[i] = oldList[i];
				}
				delete oldList;
				_objectPointer->Size= newSize;	
				LeaveCriticalSection(&ThreadLock);
			}
			return _objectPointer->Size;			
		}
		return 0;
	}

	void Add(T* item) {
		if(Items) {
			Items[++Count] = item;
		}
	}

	T& operator[]( unsigned int index ) {
		if(Items) {
			if( index >= Count ) {
				return *NULL;
			}
			return _objectPointer->Items[index];
		}
	}
};

#endif