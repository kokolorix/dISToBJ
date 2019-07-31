//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "TraitsTests.h"
#include "Object.h"
//#include "BaseTraits.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;

namespace
{
	bool test = Test::addTestCase(make_shared<Test::TraitsTests>(), "TraitsTests");
}

namespace
{
	void typeTest();
}

srdev::TestResult srdev::Test::TraitsTests::runTest()
{
	typeTest();

	return TestResult::Successful;
}

namespace test
{
	template<class PropertyT, typename TypeT, size_t IdT>
	struct PropertyTraits
	{
		static String getName() { return PropertyT::name(); }
		static uint32_t getId() { return PropertyT::id(); }
		enum { Id = IdT };
		typedef TypeT Type;

		static PropertyPtr create(const String& name, size_t id, Type value)
		{
			PropertyPtr p = Property::make(name, value);
			return p;
		}
	};

	template<class Traits>
	struct ObjectAccess { /*static_assert(false, "Only specializations are usefully");*/ };

	template<class Traits>
	struct ObjectImpl : public ObjectAccess<typename Traits> { 	};

	template<class Traits>
	struct Wrapper
	{
		Wrapper(ObjectPtr object) : object_(object) {}
		ObjectImpl<Traits>* operator -> () const { return (ObjectImpl<Traits>*)object_.get(); }
	private:
		ObjectPtr object_;
	};

	template<class ObjectT, class BaseT, class PropertiesT>
	struct ObjectTraits
	{
		typedef BaseT BaseTraits;
		typedef PropertiesT Properties;

		static String getCategory() { return ObjectT::category(); }
		static String getName() { return ObjectT::name(); }
		static UuId getId() { return ObjectT::id(); }
		static Wrapper<ObjectTraits<ObjectT, BaseT, PropertiesT>> make(UuId objectId = generateNullId())
		{
			ObjectPtr obj = Object::make(getId(), objectId);
			return obj;
		}

	};

	template<typename ValueT>
	struct ValueAccess
	{
		ValueAccess(PropertyPtr property) :property_(property) {}
		operator const ValueT& () const { return  dynamic_pointer_cast<const ValueImpl<ValueT>>(property_->getValue())->getValue(); }
		//ValueAccess& operator = (const ValueT& value) { property_->setValue(ValueImpl<ValueT>::make(value)); return *this; }
		operator const ValuePtr () const { return  property_->getValue(); }
		ValueAccess& operator = (ValuePtr value) { property_->setValue(value); return *this; }
	private:
		PropertyPtr property_;
	};
}

namespace test
{
	namespace Null
	{
		struct Properties { enum { LastId = 0 }; };
		struct Object
		{
			static String name() { return ""; }
			static UuId id() { return generateNullId(); }
		};
		using Traits = ObjectTraits<Object, Object, Properties>;


	}
	template<>
	struct ObjectAccess<Null::Traits> : public Object
	{
	};

	namespace System
	{
		namespace Type_Impl
		{
			using BaseTraits = Null::Traits;
			namespace Name { struct Property { static String name() { return "Name"; } }; using Traits = PropertyTraits<Property, String, BaseTraits::Properties::LastId + 1>; }
			struct ObjectT
			{
				static String category() { return "System"; }
				static String name() { return "Type"; }
				static UuId id() { static const UuId id = generateIdFromString("{28BAB130-9B65-4C9D-92A2-A30AA581C4BA}"); return id; }
			};
			struct PropertiesT
			{
				using Name = Name::Traits;
				enum { LastId = Name::Id };
			};
		}
		using Type = ObjectTraits<Type_Impl::ObjectT, Type_Impl::BaseTraits, Type_Impl::PropertiesT>;
	}
	template<>
	struct ObjectAccess<System::Type> : public ObjectImpl<System::Type::BaseTraits>
	{
		ValueAccess<String> Name =  ValueAccess<String>(getProperty(System::Type::Properties::Name::Id));
	};

	template<>
	struct ObjectImpl<System::Type> : public ObjectAccess<System::Type>
	{
		void doSomething() {}
	};
}
namespace
{
	void typeTest()
	{
		using namespace test;
		auto type = System::Type::make();
		String name = type->Name;
		type->Name = "Holdrio";
	}

}
