//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#include "Object.h"
namespace srdev
{

	Object::Object()
	{
		//ctor
	}

	Object::~Object()
	{
		//dtor
	}

	Object::Object(const Object& other)
	{
		//copy ctor
	}

	Object& Object::operator=(const Object& rhs)
	{
		if (this == &rhs)
			return *this; // handle self assignment
		//assignment operator
		return *this;
	}


	Result ObjectPtr::operator[](const String& name)
	{
		return Result(name, *this, (*this)->findOrCreateValue(name));
	}

	srdev::ObjectPtr& ObjectPtr::operator+=(const PropertyPtr& p)
	{
		return *this;
	}

	Result Result::operator[](const String& name)
	{
		if(const auto p = dynamic_pointer_cast<const VoidValue>(_result))
		{
			ObjectPtr obj = Object::make();
			_result = _object->findOrCreateValue(_name, Value::make(obj));
			return obj[name];
		}

		if (const auto p = dynamic_pointer_cast<const ObjectValue>(_result))
		{
			ObjectPtr& obj = const_cast<ObjectPtr&>(p->getValue());
			if (!obj)
				obj = Object::make();
			return obj[name];
		}

		throw NotFoundException(__func__);
	}

	srdev::Result Result::operator[](const String::value_type* name)
	{
		return operator[](String(name)); 
	}

	srdev::Result Result::operator=(ValuePtr r)
	{
		_result = _object->findOrCreateValue(_name, r);
		return *this;
	}

}

using namespace srdev;

ValuePtr& Object::findOrCreateValue(const String &name, ValuePtr value /*= ValuePtr()*/)
{
	PropertyPtr p = findProperty(name);
	if (!p)
	{
		p = Property::make(name, value ? value : Value::make());
		_properties.push_back(p);
	}
	else
	{
		if (value)
			p->_value = value;
	}
	return p->_value;
}

ObjectPtr srdev::Object::make()
{
	auto obj = make_shared<Object>();
	return obj;
}

//srdev::ObjectPtr srdev::Object::make(std::initializer_list<std::pair<String, ValuePtr>> properties)
//{
//	ObjectPtr obj = make_shared<Object>();
//	for (auto p : properties)
//		obj[p.first] = p.second;
//	return obj;
//}
//
//ObjectPtr Object::make(std::initializer_list<PropertyPtr>properties)
//{
//    auto obj = Object::make();
//    obj->_properties.assign(properties);
//    return obj;
//}
//
PropertyPtr Object::findProperty(const String &name)
{
	auto it = std::find_if(_properties.begin(), _properties.end(), [name](PropertyPtr p) { return p->getName() == name; });
	if (it == _properties.end())
		return PropertyPtr();
	else
		return *it;
}
