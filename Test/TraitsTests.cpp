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
		static uint32_t getId() { return PropertyT::getId(); }
		static const String& getName() { static const String s = PropertyT::getName(); return s; }
		static ValuePtr getDefaultValue() { static ValuePtr p = PropertyT::getDefaultValue(); return p; }
		enum { Id = IdT };
		using Type = TypeT;

		static PropertyPtr make(ObjectPtr object)
		{
			PropertyPtr property = Property::make(getName(), getDefaultValue());
			object->addProperty(property, Id);
			return property;
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
		ObjectImpl<Traits>* operator -> () const 
		{
			ObjectImpl<Traits>* impl = static_cast<ObjectImpl<Traits>*>(object_.get());
			return impl; 
		}
	private:
		ObjectPtr object_;
	};

	template<class ObjectT, class BaseT, class PropertiesT>
	struct ObjectTraits
	{
		using BaseTraits = BaseT;
		using Properties = PropertiesT;

		static const String& getCategory() { static const String s = ObjectT::getCategory();  return s; }
		static const String& getName() { static const String s = ObjectT::getName(); return s; }
		static const UuId& getTypeId() { static const UuId  id = ObjectT::getTypeId(); return id; }


		template < size_t > struct SizeT { };

		template < typename TupleType >
		static void InitializeProperties(ObjectPtr object)
		{
			InitializeProperties<TupleType>(SizeT<std::tuple_size<TupleType>::value>(), object);
		}

		template < typename TupleType >
		static void InitializeProperties (SizeT<0>, ObjectPtr object) { }

		template < typename TupleType, size_t N >
		static void InitializeProperties(SizeT<N>, ObjectPtr object)
		{
			InitializeProperties<TupleType>(SizeT<N - 1>(), object);
			using Traits = typename  std::tuple_element<N - 1, TupleType>::type;
			Traits::make(object);
		}
		
		static Wrapper<ObjectTraits<ObjectT, BaseT, PropertiesT>> make(UuId objectId = generateNullId())
		{
			ObjectPtr object = Object::make(getTypeId(), objectId);

			InitializeProperties<PropertiesT::List>(object);


			return object;
		}

	};

	//template<typename ValueT>
	//struct ValueAccess
	//{
	//	ValueAccess() : property_(nullptr) {}
	//	ValueAccess& operator = (PropertyPtr property) { property_ = property.get(); return *this; }
	//	ValueAccess(PropertyPtr property) : property_(property.get()) {}
	//	operator const ValueT& () const { return  dynamic_pointer_cast<const ValueImpl<ValueT>>(property_->getValue())->getValue(); }
	//	operator const ValuePtr () const { return  property_->getValue(); }
	//	ValueAccess& operator = (ValuePtr value) { property_->setValue(value); return *this; }
	//private:
	//	Property* property_;
	//};
}

namespace test
{
	namespace System
	{
		namespace ObjectBaseT
		{
			struct ObjectT
			{
				static String getName() { return String(); }
				static UuId getId() { return generateNullId(); }
			};
			struct PropertiesT 
			{ 
				using List = std::tuple<>;
				enum { LastId = std::tuple_size<List>::value };
			};
		}
		using ObjectBase = ObjectTraits<ObjectBaseT::ObjectT, ObjectBaseT::ObjectT, ObjectBaseT::PropertiesT>;
	}
	template<>
	struct ObjectAccess<System::ObjectBase> : public Object {};

	namespace System
	{
		namespace ObjectTypeT
		{
			using BaseTraits  = System::ObjectBase;
			namespace SymbolName 
			{ 
				struct PropertyT 
				{ 
					static String getName() { return "SymbolName"; } 
					static ValuePtr getDefaultValue() { return StringValue::make(""); }
				};
				using Traits = PropertyTraits<PropertyT, String, BaseTraits::Properties::LastId + 1>; 
			}
			namespace DisplayName 
			{ 
				struct PropertyT 
				{ 
					static String getName() { return "DisplayName"; } 
					static ValuePtr getDefaultValue() { return StringValue::make(""); }
				};
				using Traits = PropertyTraits<PropertyT, String, BaseTraits::Properties::LastId + 2>; 
			}
			struct ObjectT
			{
				static String getCategory() { return "System"; }
				static String getName() { return "Type"; }
				static UuId getTypeId() { static const UuId id = generateIdFromString("{28BAB130-9B65-4C9D-92A2-A30AA581C4BA}"); return id; }
			};
			struct PropertiesT
			{
				using SymbolName = SymbolName::Traits;
				using DisplayName = DisplayName::Traits;
				using List = std::tuple<SymbolName,DisplayName>;
				enum { LastId = std::tuple_size<List>::value };
			};
			using Traits = ObjectTraits<ObjectT, BaseTraits, PropertiesT>;
		}
		using ObjectType = ObjectTypeT::Traits;
	}

	template<>
	struct ObjectAccess<System::ObjectType> : public ObjectImpl<System::ObjectType::BaseTraits>
	{
		String getSymbolName() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::ObjectType::Properties::SymbolName::Id)->getValue())->getValue(); }
		void setSymbolName(const String& name) { getProperty(System::ObjectType::Properties::SymbolName::Id)->setValue(StringValue::make(name)); }
		String getDisplayName() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::ObjectType::Properties::DisplayName::Id)->getValue())->getValue(); }
		void setDisplayName(const String& name) { getProperty(System::ObjectType::Properties::DisplayName::Id)->setValue(StringValue::make(name)); }
	};

	template<>
	struct ObjectImpl<System::ObjectType> : public ObjectAccess<System::ObjectType>
	{
		void doSomething() {}
	};
}
namespace
{
	void typeTest()
	{
		using namespace test;
		auto type = System::ObjectType::make();
		String name = type->getSymbolName();
		type->setSymbolName("nonsense");
		name = type->getSymbolName();
	}

}
