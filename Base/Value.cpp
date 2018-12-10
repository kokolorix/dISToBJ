//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "Value.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;

Value::Value()
{
	//ctor
}

Value::~Value()
{
	//dtor
}

Value::Value(const Value& other)
{
	//copy ctor
}

srdev::ValuePtr Value::parse(const String& s)
{
	return StringValue::make(s);
}

ValuePtr Value::make()
{
	return VoidValue::make();
}

srdev::ValuePtr Value::make(std::initializer_list<ValuePtr> v)
{
	return ValueImpl<ValuePtrVector>::make(v);
}

Value& Value::operator=(const Value& rhs)
{
	if (this == &rhs)
		return *this; // handle self assignment
	//assignment operator
	return *this;
}

ValuePtr::operator int32_t() const
{
	if (auto p = dynamic_pointer_cast<const ValueImpl<int32_t>>(*this))
		return p->getValue();
	else if (auto p = dynamic_pointer_cast<const ValueImpl<double>>(*this))
		return cast<int32_t>(p->getValue());
	else if (auto p = dynamic_pointer_cast<const ValueImpl<uint32_t>>(*this))
		return cast<int32_t>(p->getValue());
	else if (auto p = dynamic_pointer_cast<const ValueImpl<String>>(*this))
		return cast<int32_t>(p->getValue());
	else
		throw ImpossibleCastException(__func__);
}

ValuePtr::operator uint32_t() const
{
	if (auto p = dynamic_pointer_cast<const ValueImpl<uint32_t>>(*this))
		return p->getValue();
	else if (auto p = dynamic_pointer_cast<const ValueImpl<double>>(*this))
		return cast<uint32_t>(p->getValue());
	else if (auto p = dynamic_pointer_cast<const ValueImpl<int32_t>>(*this))
		return cast<uint32_t>(p->getValue());
	else if (auto p = dynamic_pointer_cast<const ValueImpl<String>>(*this))
		return cast<uint32_t>(p->getValue());
	else
		throw ImpossibleCastException(__func__);
}

ValuePtr::operator double() const
{
	if (auto p = dynamic_pointer_cast<const ValueImpl<double>>(*this))
		return p->getValue();
	else if (auto p = dynamic_pointer_cast<const ValueImpl<int32_t>>(*this))
		return cast<double>(p->getValue());
	else if (auto p = dynamic_pointer_cast<const ValueImpl<String>>(*this))
		return cast<double>(p->getValue());
	else
		throw ImpossibleCastException(__func__);
}

//
ValuePtr::operator String() const
{
	return (*this) ? (*this)->toString() : String();
}

//ValuePtr::operator UuId() const
//{
//	throw ImpossibleCastException(__func__);
//}

