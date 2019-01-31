//---------------------------------------------------------------------------
#ifndef ObjectH
#define ObjectH
//---------------------------------------------------------------------------

#include "Base.h"
#include "Property.h"
#include <iterator>
#include "Iterator.h"

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
		PropertyPtrVector properties_;
		ValuePtr& findOrCreateValue(const String &name, ValuePtr value = ValuePtr());

		friend struct ObjectPtr;
		friend struct Result;
		REDIRECT_STL_CONTAINER(PropertyPtrVector, properties_)
	};

	struct ObjectPtr : public shared_ptr<Object>
	{
		using Base = shared_ptr<Object>;
		using Base::Base;
		ObjectPtr() : Base(nullptr) {}
		ObjectPtr(Base ptr) : Base(ptr) {}
		Result operator [] (const String& name);
		ObjectPtr& operator += (const PropertyPtr& p);
		REDIRECT_STL_CONTAINER(PropertyPtrVector, (*this)->properties_)
	};
	using ObjectValue = ValueImpl<ObjectPtr>;

	struct Result
	{
	public:
		Result(const String& n, ObjectPtr& o) :_name(n), _object(o) {}
		Result(const String& n, ObjectPtr& o, ValuePtr r) :_name(n), _object(o), result_(r) {}
		Result(const Result& r) = default;
		Result(Result&& r) = default;

	private:
		//IdType _id;
		String _name;
		ObjectPtr _object;
		ValuePtr result_;

	public:
		Result operator =(ValuePtr r);
		template<typename T>
		Result operator =(T r);
		Result operator [] (const String& name);
		Result operator [] (const String::value_type* name);
		const Value& operator * () const { return *result_; }
		ValuePtr operator -> () { return result_; }
		operator ValuePtr () const { return result_; }
		operator double() const { return result_; }
		template<typename T>
		bool operator == (T y) const;
	};

	template<typename It>
	inline ObjectPtr srdev::Object::make(It first, It last)
	{
		ObjectPtr obj ( new Object());
		std::transform(first, last, std::back_inserter(obj->properties_), [](auto& t)
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
	//	obj->properties_.assign(properties);
	//	return obj;
	//}

	template<typename T>
	Result srdev::Result::operator=(T r)
	{
		result_ = _object->findOrCreateValue(_name, Value::make(r));
		return *this;
	}

	template<typename T>
	inline bool srdev::Result::operator==(T y) const
	{
		if (auto x = dynamic_pointer_cast<const ValueImpl<T>>(result_))
			return x->getValue() == y;
		return static_cast<T>(result_) == y;
	}
	template<>
	inline bool srdev::Result::operator==(const String::value_type* y) const
	{
		if (auto x = dynamic_pointer_cast<const ValueImpl<String>>(result_))
			return x->getValue() == y;
		return result_->toString() == y;
	}


}
#endif // OBJECT_H
