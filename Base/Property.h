//---------------------------------------------------------------------------
#ifndef PropertyH
#define PropertyH
//---------------------------------------------------------------------------

#include "Base.h"
#include "Value.h"

namespace srdev
{
	class Property;
	//using PropertyPtr = shared_ptr<const Property>;
	using std::vector;
	using std::pair;

	struct PropertyPtr : public shared_ptr<Property>
	{
		using Base = shared_ptr<Property>;
		using Base::Base;
		PropertyPtr(Base ptr) : Base(ptr) {}
		PropertyPtr() : Base() {}
//		PropertyPtr(pair<String, ValuePtr> p);
		operator ValuePtr () const;
	};
	using PropertyPtrVector = vector<PropertyPtr>;

	class Property : public Base
	{
	public:
		Property();
		virtual ~Property();
		Property(const Property& other);
		Property(const String& name, ValuePtr value) : _name(name), _value(value) {}

		static PropertyPtr make(PropertyPtr p) { return p; }
		template<class T>
		static PropertyPtr make(const String& name, T value);
		template<class T>
		static PropertyPtr make(std::pair<const String, T> p);
		template<class T>
		static PropertyPtr make(std::pair<const String::value_type*, T> p);

		String getName() const { return _name; }
		ValuePtr getValue() const { return _value; }

	protected:

	private:
		String _name;
		ValuePtr _value;

		friend class Object;
	};

	template<class T>
	inline PropertyPtr srdev::Property::make(const String& name, T value)
	{
		return make_shared<Property>(name, Value::make(value));
	}
	template<>
	inline PropertyPtr srdev::Property::make(const String& name, ValuePtr value)
	{
		return make_shared<Property>(name, value);
	}
	template<class T>
	inline PropertyPtr Property::make(std::pair<const String, T> p)
	{
		return make_shared<Property>(p.first, Value::make(p.second));
	}
	template<class T>
	inline PropertyPtr Property::make(std::pair<const String::value_type*, T> p)
	{
		return make_shared<Property>(p.first, Value::make(p.second));
	}
	template<>
	inline PropertyPtr Property::make(std::pair<const String, const String::value_type*> p)
	{
		return Property::make(p);
	}

}
#endif // PROPERTY_H
