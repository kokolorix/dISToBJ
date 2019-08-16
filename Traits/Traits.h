//---------------------------------------------------------------------------
#ifndef TraitsH
#define TraitsH
//---------------------------------------------------------------------------

namespace srdev
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
		static void InitializeProperties(SizeT<0>, ObjectPtr object) { }

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
}

#endif
