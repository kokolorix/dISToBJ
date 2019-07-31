#pragma once

#include "Object.h"
#include "Traits.h"
namespace srdev
{
	namespace Base
	{
		namespace Type
		{
			using BaseTraits = Null::Traits;
			namespace Name { struct Property { static String name() { return "Name"; } }; typedef PropertyTraits<Property, String, BaseTraits::Properties::LastId + 1> Traits; }
			namespace Status { struct Property { static String name() { return "Status"; } }; typedef PropertyTraits<Property, int32_t, BaseTraits::Properties::LastId + 2> Traits; }
			struct Properties
			{
				using Name = Name::Traits;
				using Status = Status::Traits;
				enum { LastId = Status::Id };
			};
			struct Object
			{
				static String name() { return "Root"; }
				static UuId id() {	 // {28BAB130-9B65-4C9D-92A2-A30AA581C4BA}
					static const UuId id = generateIdFromString("{28BAB130-9B65-4C9D-92A2-A30AA581C4BA}"); return id;
				}
			};
			using Traits = ObjectTraits<Object, BaseTraits, Properties>;
		}
		template<>
		struct ObjectAccess<Type::Traits> : public ObjectImpl<Type::BaseTraits>
		{
			String getName() { return dynamic_pointer_cast<StringValue>(getProperty(Type::Properties::Name::Id)->getValue())->getValue(); }
			int32_t getStatus() { return dynamic_pointer_cast<Int32Value>(getProperty(Type::Properties::Status::Id)->getValue())->getValue(); }
		};

		template<>
		struct ObjectImpl<Type::Traits> : public ObjectAccess<Type::Traits>
		{
			void doSomething() {}
		};

	}
	namespace Data
	{
		using BaseTraits = Type::Traits;
		namespace Unit { struct Property { static String name() { return "Unit"; } }; typedef PropertyTraits<Property, String, BaseTraits::Properties::LastId + 1> Traits; }
		namespace Size { struct Property { static String name() { return "Size"; } }; typedef PropertyTraits<Property, int32_t, BaseTraits::Properties::LastId + 2> Traits; }
		struct Properties
		{
			typedef Unit::Traits Unit;
			typedef Size::Traits Size;
			enum { LastId = Size::Id };
		};
		struct Object
		{
			static String name() { return "Data"; }
			static UuId id() {	 // {28BAB130-9B65-4C9D-92A2-A30AA581C4BA}
				static const UuId id = generateIdFromString("{28BAB130-9B65-4C9D-92A2-A30AA581C4BA}"); return id;
			}
		};
		using Traits = ObjectTraits<Object, BaseTraits, Properties>;
	}
	template<>
	struct ObjectAccess<Data::Traits> : public ObjectImpl<Data::BaseTraits>
	{
		String getUnit() { return dynamic_pointer_cast<StringValue>(getProperty(Data::Properties::Unit::Id)->getValue())->getValue(); }
		int32_t getSize() { return dynamic_pointer_cast<Int32Value>(getProperty(Data::Properties::Size::Id)->getValue())->getValue(); }
	};
}