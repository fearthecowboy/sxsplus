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

#define PTRCAST( basetype, obj ) Ptr<basetype>((basetype*)(void*)obj)

namespace SxSplus {
	class Reference {
		void* Pointer;
		int ReferenceCount;

	public: 
		static unsigned int GetReferenceCount(void* pointer);
		static unsigned int IncrementReferenceCount(void* pointer);
		static unsigned int DecrementReferenceCount(void* pointer);

	private:
		static unsigned int Size;
		static unsigned int Count;
		static Reference* References;

		static unsigned int GetReferenceIndex(void* pointer);
	};

	template < class t >
	class Ptr  {
	   public:
		Ptr (t *pointer) :_objectPointer( pointer ) {
			if ( _objectPointer ) {
				Reference::IncrementReferenceCount(_objectPointer);
			}
		};

		Ptr (Ptr<t>* pointer) :_objectPointer( (t*)(void*)pointer ) {
			if ( _objectPointer ) {
				Reference::IncrementReferenceCount(_objectPointer);
			}
		}

		Ptr (Ptr<t>& pointer) :_objectPointer( pointer._objectPointer ) {
			if ( _objectPointer ) {
				Reference::IncrementReferenceCount(_objectPointer);
			}
		};

		Ptr () :_objectPointer( 0 ) {
		};
   
		virtual ~Ptr () {
			if ( _objectPointer ) {
				Reference::DecrementReferenceCount(_objectPointer);
			}
		};

		virtual void operator = (Ptr<t>* pointer) {
			// remove the old pointer
			if ( _objectPointer ) {
				Reference::DecrementReferenceCount(_objectPointer);
			}

			// attach to the new one.
			_objectPointer = (t*)(void*)pointer;
			if ( _objectPointer ) {
				Reference::IncrementReferenceCount(_objectPointer);
			}
		};


		virtual void operator = (Ptr<t>& pointer) {
			// remove the old pointer
			if ( _objectPointer ) {
				Reference::DecrementReferenceCount(_objectPointer);
			}

			// attach to the new one.
			_objectPointer = pointer._objectPointer;
			if ( _objectPointer ) {
				Reference::IncrementReferenceCount(_objectPointer);
			}
		};
   
		virtual void operator = (t *pointer) {
			if ( _objectPointer ) {
				Reference::DecrementReferenceCount(_objectPointer);
			}

			// attach to the new one.
			_objectPointer = pointer;
			if ( _objectPointer ) {
				Reference::IncrementReferenceCount(_objectPointer);
			}
		};
   
		virtual operator t* () const {
			return _objectPointer;
		};
   
		virtual operator void* () const {
			return (void*) _objectPointer;
		};
   
		virtual bool operator ! () const {
			if ( _objectPointer ) {
				return false;
			}
			return true;
		};
   
		virtual bool operator == ( const t *pointer ) const {
			return ( _objectPointer == pointer );
		};
   
		virtual bool operator == ( const void *pointer ) const {
			return ( (void*)_objectPointer == pointer );
		};
   
		virtual bool operator == ( const Ptr<t>& pointer ) const {
			return ( _objectPointer == pointer._objectPointer );
		};

		virtual bool operator != ( const t *pointer ) const {
			return ( _objectPointer != pointer );
		};
   
		virtual bool operator != ( const void *pointer ) const {
			return ( (void*)_objectPointer != pointer );
		};
   
		virtual bool operator != ( const Ptr<t>& pointer ) const {
			return ( _objectPointer != pointer._objectPointer );
		};
   
		virtual t& operator * () const {
			return *_objectPointer;
		};
   
		virtual t* operator-> () const {
			// ENSURE( _objectPointer != NULL , "Object pointer is NULL" , NULL , (long)(void*)_objectPointer );
			return _objectPointer;
		};

		virtual t* AddRef() const {
			Reference::IncrementReferenceCount(_objectPointer);
			return _objectPointer;
		}

		virtual t* Release() const {
			if( Reference::DecrementReferenceCount(_objectPointer) ) {
				return _objectPointer;
			}
			return NULL;
		}

		void* operator new( size_t n ) {
			return new t;
		}
		protected:

		t* _objectPointer;
	};

};