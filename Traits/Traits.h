//---------------------------------------------------------------------------
#ifndef TraitsH
#define TraitsH
//---------------------------------------------------------------------------

namespace srdev
{
	template<class PropertyT, typename TypeT, size_t IdT>
	struct PropertyTraits
	{
		static string getName() { return PropertyT::name(); }
		static uint32_t getId() { return PropertyT::id(); }
		enum { Id = IdT };
		typedef TypeT Type;

		static PropertyPtr create(const String& name, size_t id, Type value)
		{
			PropertyPtr p = Property::make(name, value);
			return p;
		}
	};

	template<class ObjectT, class BaseT, class PropertiesT>
	struct ObjectTraits
	{
		typedef BaseT BaseTraits;
		typedef PropertiesT Properties;

		static string getName() { return ObjectT::name(); }
		static UuId getId() { return ObjectT::id(); }
		static ObjectPtr create(const string& name)
		{
			ObjectPtr object = Object::make();
			object["Name"] = name;
			return object;
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
}

#endif
