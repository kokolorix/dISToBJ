//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#include "ObjectRepository.h"

namespace srdev
{
	struct ObjectRepository::Impl
	{

	};

	ObjectRepository::ObjectRepository()
		: impl_(new Impl)
	{
		//ctor
	}

	srdev::ObjectRepositoryPtr ObjectRepository::make()
	{
		return make_shared<ObjectRepository>();
	}

	ObjectRepository::~ObjectRepository()
	{
		//dtor
	}

	ObjectRepository::ObjectRepository(const ObjectRepository& other)
		: impl_(new Impl(*other.impl_))
	{
		//copy ctor
	}

	ObjectRepository& ObjectRepository::operator=(const ObjectRepository& rhs)
	{
		if (this == &rhs)
			return *this; // handle self assignment
		//assignment operator
		return *this;
	}

	void ObjectRepository::ImplDeleter::operator()(Impl* impl)
	{
		delete impl;
	}

}