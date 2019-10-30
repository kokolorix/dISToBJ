//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "Value.h"
#include <Compare.h>
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
	using ChT = String::value_type;

	if (iequal(s, "true"))
		return BooleanValue::make(true);
	else if (iequal(s, "false"))
		return BooleanValue::make(false);
	else if(isDecNumber(s))
	{
		ChT* ch;
		long long i = std::strtoll(s.c_str(), &ch, 10);
		auto l = std::distance<const ChT*>(s.c_str(), ch);
		if (l == static_cast<signed>(s.length()))
		{
			l = is_one_of(*s.c_str(), '-', '+') ? l - 1 : l;
			//if( l <= 10)
			{
				if (*s.c_str() == '-')
				{
					if (i < std::numeric_limits<int32_t>::min())
						return Int64Value::make(i);
					else
						return Int32Value::make(static_cast<int32_t>(i));
				}
				else
				{
					if (i > std::numeric_limits<int64_t>::max())
						return UInt64Value::make(i);
					else if (i > std::numeric_limits<int32_t>::max())
						return Int64Value::make(i);
					else
						return Int32Value::make(static_cast<int32_t>(i));
				}
			}
		}
	}
	else if (isHexNumber(s))
	{
		ChT* ch;
		unsigned long long i = std::strtoull(s.c_str(), &ch, 16);
		auto l = std::distance<const ChT*>(s.c_str(), ch);
		if (l == static_cast<signed>(s.length()))
		{
			if (i > std::numeric_limits<uint32_t>::max())
				return UInt64Value::make(i);
			else
				return UInt32Value::make(static_cast<uint32_t>(i));
		}
	}
	else if (isFloatingPointNumber(s))
	{
		ChT* ch;
		double d =std::strtod(s.c_str(), &ch);
		auto l = std::distance<const ChT*>(s.c_str(), ch);
		if (l == static_cast<signed>(s.length()))
			return DoubleValue::make(d);
	}

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
