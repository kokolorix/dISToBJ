//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#include "ObjectPersistence.h"

namespace srdev
{
	struct ObjectPersistence::Impl
	{
		Impl(const String& connectionString):connectionString_(connectionString){}
		String connectionString_;
	};

	ObjectPersistence::ObjectPersistence(const String& connectionString)
		: impl_(new Impl(connectionString))
	{
		//ctor
	}

	srdev::ObjectPersistencePtr ObjectPersistence::make(const String& connectionString)
	{
		return make_shared<ObjectPersistence>(connectionString);
	}

	srdev::ObjectPtr ObjectPersistence::readObject(ConditionPtr condition)
	{
		return ObjectPtr();
	}

	srdev::ObjectPtrVector ObjectPersistence::readObjects(ConditionPtr condition)
	{
		return ObjectPtrVector();
	}

	ObjectPersistence::~ObjectPersistence()
	{
		//dtor
	}

	ObjectPersistence::ObjectPersistence(const ObjectPersistence& other)
		: impl_(new Impl(*other.impl_))
	{
		//copy ctor
	}

	ObjectPersistence& ObjectPersistence::operator=(const ObjectPersistence& rhs)
	{
		if (this == &rhs)
			return *this; // handle self assignment
		//assignment operator
		return *this;
	}

	void ObjectPersistence::ImplDeleter::operator()(Impl* impl)
	{
		delete impl;
	}

}