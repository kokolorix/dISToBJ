//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#include "Property.h"
namespace srdev
{
	Property::Property()
	{
		//ctor
	}

	Property::~Property()
	{
		//dtor
	}

	Property::Property(const Property& other)
	{
		//copy ctor
	}

//	PropertyPtr::PropertyPtr(pair<String, ValuePtr> p)
//		: Base(Property::make(p.first, p.second))
//	{
//
//	}

	PropertyPtr::operator ValuePtr() const
	{
		return (*this)->getValue();
	}

}
