//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#include "Condition.h"
namespace srdev
{
	Condition::Condition()
	{
		//ctor
	}

	Condition::Condition(const String& expression)
		: expression_(expression)
	{

	}

	bool Condition::checkCondition(ObjectPtr object)
	{
		throw std::logic_error("The method or operation is not implemented.");

	}

	void Condition::parseExpression()
	{
		throw std::logic_error("The method or operation is not implemented.");

	}

	srdev::String Condition::getSqlWhereStatement()
	{
		throw std::logic_error("The method or operation is not implemented.");

	}

	srdev::String Condition::getXPathStatement()
	{
		throw std::logic_error("The method or operation is not implemented.");

	}

	srdev::String Condition::toString() const
	{
			throw std::logic_error("The method or operation is not implemented.");
}

	Condition::~Condition()
	{
		//dtor
	}

	Condition::Condition(const Condition& other)
		:expression_(other.expression_)
	{
		//copy ctor
	}
}
