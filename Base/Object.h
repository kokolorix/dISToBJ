//---------------------------------------------------------------------------
#ifndef ObjectH
#define ObjectH
//---------------------------------------------------------------------------

#include "Base.h"
#include "Property.h"
#include <iterator>

namespace srdev
{
	using ::std::vector;
	//class Object;
	 struct Result;
	 //using ObjectPtr = shared_ptr<const Object>;
	 
	 struct ObjectPtr;
	 struct PropertyPtr;




	class Object : public Base
	{
	public:
		Object();
		virtual ~Object();
		Object(const Object& other);
		Object& operator=(const Object& other);

		static ObjectPtr make();
		template<typename T>
		static ObjectPtr make(std::initializer_list<T> properties);
		template<typename It>
		static ObjectPtr make(It first, It last);
	
		//static ObjectPtr make(std::initializer_list<std::pair<String, ValuePtr>> properties);

		PropertyPtr findProperty(const String &name);
	protected:

	private:
		PropertyPtrVector _properties;
		ValuePtr& findOrCreateValue(const String &name, ValuePtr value = ValuePtr());

		friend struct ObjectPtr;
		friend struct Result;
		REDIRECT_STL_CONTAINER(PropertyPtrVector, _properties)
	};

	struct ObjectPtr : public shared_ptr<Object>
	{
		using Base = shared_ptr<Object>;
		using Base::Base;
      ObjectPtr(const Base& ptr) : Base(ptr){}
		Result operator [] (const String& name);
		ObjectPtr& operator += (const PropertyPtr& p);
		REDIRECT_STL_CONTAINER(PropertyPtrVector, (*this)->_properties)
	};
	using ObjectValue = ValueImpl<ObjectPtr>;

	struct Result
	{
	public:
		Result(const String& n, ObjectPtr& o) :_name(n), _object(o) {}
		Result(const String& n, ObjectPtr& o, ValuePtr r) :_name(n), _object(o), _result(r) {}
		Result(const Result& r) = default;
		Result(Result&& r) = default;

	private:
		//IdType _id;
		String _name;
		ObjectPtr _object;
		ValuePtr _result;

	public:
		Result operator =(ValuePtr r);
		template<typename T>
		Result operator =(T r);
		Result operator [] (const String& name);
		Result operator [] (const String::value_type* name);
		const Value& operator * () const { return *_result; }
		ValuePtr operator -> () { return _result; }
		operator ValuePtr () const { return _result; }
		operator double() const { return _result; }
		template<typename T>
		bool operator == (T y) const;
	};

	template<typename It>
	inline ObjectPtr srdev::Object::make(It first, It last)
	{
		ObjectPtr obj ( new Object());
		std::transform(first, last, std::back_inserter(obj->_properties), [](auto& t)
		{
			return Property::make(t);
		});
		return obj;
	}

	template<typename T>
	inline ObjectPtr srdev::Object::make(std::initializer_list<T> p)
	{
		return Object::make(p.begin(), p.end());
	}
	//template<>
	//inline ObjectPtr srdev::Object::make(std::initializer_list<PropertyPtr> properties)
	//{
	//	ObjectPtr obj = make_shared<Object>();
	//	obj->_properties.assign(properties);
	//	return obj;
	//}

	template<typename T>
	Result srdev::Result::operator=(T r)
	{
		_result = _object->findOrCreateValue(_name, Value::make(r));
		return *this;
	}

	template<typename T>
	inline bool srdev::Result::operator==(T y) const
	{
		if (auto x = dynamic_pointer_cast<const ValueImpl<T>>(_result))
			return x->getValue() == y;
		return static_cast<T>(_result) == y;
	}
	template<>
	inline bool srdev::Result::operator==(const String::value_type* y) const
	{
		if (auto x = dynamic_pointer_cast<const ValueImpl<String>>(_result))
			return x->getValue() == y;
		return _result->toString() == y;
	}


}
#endif // OBJECT_H
